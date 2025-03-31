#ifndef WEB_UTILS_DEF
#define WEB_UTILS_DEF

#include "lwip/tcp.h"

// converte um ip4 em um string, buffer_size >= 16
char * ip_string(char *buffer, uint16_t buffer_size, uint32_t ip4);

// Envia um dado Web com o tipo/tamanho chunck
void   send_chunck(struct tcp_pcb *tpcb, char *buffer);

// Secodifica um string recebido do navegador para um string normal
char * url_decode(char *str);

#endif