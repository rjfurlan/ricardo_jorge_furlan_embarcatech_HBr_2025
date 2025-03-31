//#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "lwip/tcp.h"

#include "WebUtils.h"

// converte um ip4 em um string, buffer_size >= 16
char * ip_string(char *buffer, uint16_t buffer_size, uint32_t ip4){     // buffer_size >= 16
    uint8_t *ip = (uint8_t*)&ip4;
    snprintf(buffer, buffer_size, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

    return buffer;
}

// Envia um dado Web com o tipo/tamanho chunck
void send_chunck(struct tcp_pcb *tpcb, char *buffer){
  char tmp[20];

  uint16_t buffer_length = strlen(buffer);
  sprintf(tmp, "%x\r\n", buffer_length);

  tcp_write( tpcb, tmp, strlen(tmp), TCP_WRITE_FLAG_COPY);
  tcp_write( tpcb, buffer, buffer_length, TCP_WRITE_FLAG_COPY);
  tcp_write( tpcb, "\r\n", 2, TCP_WRITE_FLAG_COPY);
  tcp_output(tpcb);
}

// Secodifica um string recebido do navegador para um string normal
char * url_decode(char *str) {
    char *src = str;
    char *dst = str;
    
    while (*src) {
        if (*src == '%') {      // converter os próximos 2 caracteres hexadecimais
            int c;
            sscanf(src + 1, "%2x", &c);  // Converte os dois caracteres hexadecimais
            *dst = (char)c;              // Armazena o caractere decodificado
            src += 3;                    // Avança 3 posições (passa o '%', e os dois caracteres hexadecimais)
        } else {
            *dst = *src;  // Se não for '%', copia o caractere diretamente
            src++;
        }
        dst++;    // Avança o destino
    }
    *dst = '\0';  // Finaliza a string
    return str;
}