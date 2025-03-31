#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "lwip/tcp.h"

#include "Config.h"
#include "libs/WebUtils.h"
#include "HtmlDefaultPages.h"
#include "HtmlPage01.h"
#include "Msgs.h"
#include "Ui.h"
#include "WebServer.h"

static char web_server_buffer[WEBSERVER_BUFFER_SIZE];


// Tipo de página que a requisição espera que o servidor retorne
typedef enum{
    NO_RETURN,      // Algum erro interno, não vai retornar nenhuma página
    ERROR_PAGE,     // Retorna a página de erro 404
    FAVICON,        // Icone da página
    FULL_PAGE,      // Retorna a página principal completa
    UPDATE_DATA     // Retorna o JSON de atualização da página principal
} RETURN_PAGE;


// Função de callback para processar requisições HTTP
static uint32_t web_server_http_callback_n = 0;
static err_t http_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
    char buffer[16];
    web_server_http_callback_n++;

    if(WEBSERVER_REPORT) printf("WebServer - callback - requisição %d, Address tpcb=0x%08x, requisitada por: %s:%d\n", 
        web_server_http_callback_n,
        tpcb,
        ip_string(buffer, 16, (uint32_t)(tpcb->remote_ip.addr)),
        tpcb->remote_port
    );

    if (p == NULL) {   // Cliente fechou a conexão
        if(WEBSERVER_REPORT) printf("WebServer - callback - Conexão  0x%08x FECHADA\n", tpcb);
        tcp_close(tpcb);
        return ERR_OK;
    }

    // Processa a requisição HTTP
    char method[8] = {0};   // Inicializado com zeros
    char url[128]  = {0};   // Inicializado com zeros // A mensagem enviada pode ter até 48 caracteres
    int nr = sscanf((char *)p->payload, "%7s %127s", method, url);

    // Libera espaço na janela TCP
    tcp_recved(tpcb, p->len);
    
    // Libera o buffer recebido
    pbuf_free(p);

    // ---------- Trata requisição ----------
    RETURN_PAGE return_page = ERROR_PAGE;
    if(nr != 2){
        return_page = ERROR_PAGE;
        if(WEBSERVER_REPORT) printf("WebServer - callback - ERROR, não consegui ler 2 parâmetros, leu %d\n", nr);
    }else if(strcasecmp(method, "GET") != 0){   // Metodo não é GET
        return_page = ERROR_PAGE;
        if(WEBSERVER_REPORT) printf("WebServer - callback - ERROR, method != GET, => %s\n", method);
    }else{
        if(WEBSERVER_REPORT) printf("WebServer - callback - method=%s, URL=%s\n", method, url);
        if(strncasecmp(url, "/Update", 7) == 0){
            return_page = UPDATE_DATA;
            if(WEBSERVER_REPORT_FULL) printf("WebServer - callback - GET /Update\n");
        } else  if(strcasecmp(url, "/favicon.ico") == 0){
            return_page = FAVICON;
            if(WEBSERVER_REPORT_FULL) printf("WebServer - callback - GET /favicon.ico\n");
        } else if(strncasecmp(url, "/CB_R", 5) == 0){
            return_page            = FULL_PAGE;
            msg_page_received.read = true;
            ui_msg_read();      // faz ir para a tela da mensagem enviada, onde estará marcada lida    
            if(WEBSERVER_REPORT_FULL) printf("WebServer - callback - GET /CB_R\n");      // Leu a mensagem recebida
        } else if(strncasecmp(url, "/MsgLow", 7) == 0){
            return_page        = FULL_PAGE;
            msg_page_send.high = false;
            msg_page_send.read = false;
            msg_page_send.t_us = time_us_64();
            strncpy(msg_page_send.msg, url_decode(&url[12]), 48);
            ui_msg_received();
            if(WEBSERVER_REPORT_FULL) printf("WebServer - callback - GET /MsgLow, url:%s\n", url);
        } else if(strncasecmp(url, "/MsgHigh", 8) == 0){
            return_page        = FULL_PAGE;
            msg_page_send.high = true;
            msg_page_send.read = false;
            msg_page_send.t_us = time_us_64();
            strncpy(msg_page_send.msg, url_decode(&url[13]), 48);
            ui_msg_received();
            if(WEBSERVER_REPORT_FULL) printf("WebServer - callback - GET /MsgHigh, url:%s\n", url);
        } else if((strncasecmp(url, "/", 1) == 0)&&(strlen(url)==1)){
            return_page = FULL_PAGE;
            if(WEBSERVER_REPORT_FULL) printf("WebServer - callback - GET ? |%s|\n", url);
        } else {
            if(WEBSERVER_REPORT) printf("WebServer - callback - GET, ERRO Chamada GET não tratada, URL=|%s|\n", url);
        }
    }

    switch(return_page){
        case NO_RETURN:
        case ERROR_PAGE:
            if(WEBSERVER_REPORT_FULL) printf("WebServer - callback - Consider Tcp IP NO Received\n");
            break;
        default:
            ui_valid_tcp_received();        // Informa ao UI que foi recebida uma requisição válida do navegador (ele está conectado) 
            if(WEBSERVER_REPORT_FULL) printf("WebServer - callback - Consider Tcp IP Received\n");
    }

    // Gera e envia a mensagem solicitada
    switch(return_page){
        case NO_RETURN:
            if(WEBSERVER_REPORT_FULL) printf("WebServer - callback - PAGE: NO_RETURN\n");         
            break;
        case ERROR_PAGE:
            if(WEBSERVER_REPORT_FULL) printf("WebServer - callback - PAGE: ERROR_PAGE\n");         
            char * aux = htlm_error_page();
            tcp_write(tpcb, aux, strlen(aux), TCP_WRITE_FLAG_COPY);
            tcp_output(tpcb);
            break;
        case FAVICON:
            if(WEBSERVER_REPORT_FULL) printf("WebServer - callback - PAGE: FAVICON\n");         
//          uint32_t tm1_size = htlm_favicon_null(web_server_buffer, WEBSERVER_BUFFER_SIZE);
            uint32_t tm1_size = htlm_favicon_page(web_server_buffer, WEBSERVER_BUFFER_SIZE);
            tcp_write(tpcb, web_server_buffer, tm1_size, TCP_WRITE_FLAG_COPY);
            tcp_output(tpcb);
            break;
        case FULL_PAGE:
            if(WEBSERVER_REPORT_FULL) printf("WebServer - callback - PAGE: FULL_PAGE\n");         
            htlm_page01_full(tpcb, web_server_buffer, WEBSERVER_BUFFER_SIZE);
            break;
        case UPDATE_DATA:
            if(WEBSERVER_REPORT_FULL) printf("WebServer - callback - PAGE: UPDATE_DATA\n");         
            htlm_page01_update(tpcb, web_server_buffer, WEBSERVER_BUFFER_SIZE);
            break;
    }
    return ERR_OK;
}

// Callback de conexão: associa o http_callback à conexão
static uint32_t web_server_con_listen_n = 0;
static err_t listen_connection_request(void *arg, struct tcp_pcb *newpcb, err_t err) {
    char buffer[16];
    if(WEBSERVER_REPORT) printf("WebServer - Connection Listen %d requisitada por: %s:%d\n",
            ++web_server_con_listen_n,
            ip_string(buffer, 16, (uint32_t)(newpcb->remote_ip.addr)),
            newpcb->remote_port );
    tcp_recv(newpcb, http_callback);  // Associa o callback HTTP
    return ERR_OK;
}

// Inicializa o servidor Web
int16_t web_server_init(){
    if(WEBSERVER_REPORT) printf("WebServer - Criando Web Server Http baseado em TCP IP\n");

    struct tcp_pcb *pcb = tcp_new();
    if (!pcb) {
        printf("WebServer - Erro ao criar PCB\n");
        return -1;
    }

    // Liga o servidor na porta SERVER_PORT
    if (tcp_bind(pcb, IP_ADDR_ANY, WEBSERVER_PORT) != ERR_OK) {
        printf("WebServer - Erro ao ligar o servidor na porta %d\n", WEBSERVER_PORT);
        return -2;
    }
    if(WEBSERVER_REPORT) printf("WebServer - Ligado a porta %d\n", WEBSERVER_PORT);

    sleep_ms(100);                                 // colocado por precaução
    //pcb = tcp_listen(pcb);                       // Coloca o PCB em modo de escuta
    pcb = tcp_listen_with_backlog(pcb, 5);         // Coloca o PCB em modo de escuta
    sleep_ms(100);                                 // colocado por precaução
    tcp_accept(pcb, listen_connection_request);    // Associa o callback de conexão

    if(WEBSERVER_REPORT) printf("WebServer - Ouvindo a porta %d\n", WEBSERVER_PORT);
    return 0;
}
