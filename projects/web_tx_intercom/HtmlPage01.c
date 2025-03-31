#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "lwip/tcp.h"
#include "Config.h"
#include "libs/WebUtils.h"
#include "HtmlPage01.h"
#include "Msgs.h"


const char * HEADER_CHUNKED = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html; charset=UTF-8\r\n"
    "Transfer-Encoding: chunked\r\n"
    "Connection: close\r\n"
    "\r\n";

const char * HEADER_JSON = 
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: application/json\r\n"
    "Transfer-Encoding: chunked\r\n"
    "\r\n";    

const char * PAGE01_BODY_START =
    "<!DOCTYPE html>"
    "<html>"
      "<head>"
        "<title>" PROG_TITLE "</title>"
        "<style>"
          "body{background-color: rgb(100, 150, 200);}"
          "#msgR {"
            "width: 300px;"
            "height: 100px;"
            "font-size: 2.0em;"
          "}"
          "#msgS {"
            "width: 300px;"
            "height: 100px;"
            "font-size: 2.0em;"
          "}"
        "</style>"
      "</head>"
      "<body>";

const char * PAGE01_TILE =  
        "<h1 style=\"text-align: center;\">" PROG_NAME "</h1>";

const char * PAGE01_MSG_RECEIVED =  
        "<br>"
        "<br>"
        "<div style=\"display: flex; flex-direction: column; align-items: center; text-decoration: none; color: black;\">"
          "<h2 style=\"text-align: center;\">Mensagem Recebida</h2>"
          "<textarea id=\"msgR\" rows=\"2\" cols=\"16\" readonly %s>%s</textarea>"
          "<div>"
            "<input type=\"checkbox\" id=\"cb_msgR_read\" onclick=\"window.location.href='/CB_R'\" %s>"
            "<span>Mensagem lida</span>"
          "</div>"
        "</div>";

const char * PAGE01_MSG_SEND =
        "<br>"
        "<br>"
        "<form id=\"textForm\" method=\"GET\">"
          "<div style=\"display: flex; flex-direction: column; align-items: center;\">"
            "<h2 style=\"text-align: center;\">Mensagem enviada/enviar</h2>"
            "<textarea id=\"msgS\" name=\"msgS\" rows=\"2\" cols=\"16\" %s %s>%s</textarea>"
            "<div style=\"display: flex; gap: 10px;\">"
              "<button type=\"button\" onclick=\"submitForm('MsgLow')\">Enviar Low</button>"
              "<button type=\"button\" onclick=\"submitForm('MsgHigh')\">Enviar High</button>"
            "</div>"
            "<div>"
              "<input type=\"checkbox\" id=\"cb_msg_S_read\" onclick=\"return false;\" %s>"
              "<span>Mensagem lida</span>"
            "</div>"
          "</div>"
        "</form>";

const char * PAGE01_FOOTER =
        "<div style=\"position: fixed; bottom: 0; left: 0; width: 100%%; background-color: lightgray; text-align: center; padding: 10px; display: flex; justify-content: space-between; box-sizing: border-box;\">"
          "<b>Versão: " PROG_VERSION " Build: " PROG_BUILD " Data: " PROG_DATE "</b>"
          "<span>Requisições: %d</span>"
          "<span id=\"foot_partial\">(Atualizações: %d)</span>"
        "</div>";        

const char * PAGE01_SCRIPT =
        "<script>"
          "let lastUpdateTime = Date.now();" // Guarda o tempo da última atualização
          "let enableTimeOut = true;"        // Habilita timeout na requisição da página

          "function atualizarElementos() {"
            "fetch('/Update')"
              ".then(response => response.json())" // Converte para JSON
              ".then(data => {"
                "lastUpdateTime = Date.now();" // Atualiza o tempo da última resposta bem-sucedida
                "enableTimeOut = true;"        // Habilita timeout na atualização da página

                // Atualiza MSG recebida
                "document.getElementById(\"msgR\").innerText = data.msgR.msg;"
                "document.getElementById(\"cb_msgR_read\").checked = data.msgR.read;"
                "msgRbgCor =\"\";"
                "if(data.msgR.bcCor === 1) msgRbgCor =\"yellow\";"
                "if(data.msgR.bcCor === 2) msgRbgCor =\"red\";"
                "document.getElementById(\"msgR\").style.backgroundColor = msgRbgCor;"
                // Atualiza MSG enviada
                "document.getElementById(\"msgS\").innerText = data.msgS.msg;"
                "document.getElementById(\"cb_msg_S_read\").checked = data.msgS.read;"
                "msgSbgCor =\"\";"
                "if(data.msgS.bcCor === 1) msgSbgCor =\"yellow\";"
                "if(data.msgS.bcCor === 2) msgSbgCor =\"red\";"
                "document.getElementById(\"msgS\").style.backgroundColor = msgSbgCor;"
                // Atualiza rodapé
                "document.getElementById(\"foot_partial\").innerText = data.foot.partial;"
              "})"
              ".catch(error => console.error('Erro:', error));"

              "if (((Date.now() - lastUpdateTime) > %d) && enableTimeOut) {"
                "enableTimeOut = false;"  // Só gera alarme de timeout uma vez
                "alert(\"" UI_CONNECTION_TIMEOUT_WEB_MSG "\");"
              "}"
            "}"
          "function submitForm(actionValue) {"
            "let msgValue = encodeURIComponent(document.getElementById(\"msgS\").value);"
            "let url = `/${actionValue}?msg=${msgValue}`;"
            "window.location.href = url;"            // Redireciona para a URL formatada corretamente
          "}"
          "setInterval(atualizarElementos, 1000);"   // Atualiza a cada 1 segundo
        "</script>";

const char * PAGE01_BODY_END =
      "</body>"
    "</html>\r\n\r\n";

const char * UPDATE_JSON =
    "{"
      "\"msgR\":{\"msg\" : \"%s\", \"read\" : %s, \"bcCor\" : %d},"
      "\"msgS\":{\"msg\" : \"%s\", \"read\" : %s, \"bcCor\" : %d},"
      "\"foot\":{\"partial\":\"(Atualizações: %d)\"}"
    "}";





static int32_t html_pag1_n_full    = 0;
static int32_t html_pag1_n_updates = 0;

// Coloca no buffer um Html toda a página HTML
// Retorna o número de bytes que foram colocados no buffer
uint32_t htlm_page01_full(  struct tcp_pcb *tpcb, char *buffer, uint32_t buffer_size){
    uint16_t buffer_length;
    html_pag1_n_full++;
    html_pag1_n_updates = 0;
    if(HTML_REPORT) printf("htlm_page01_full: NFull=%d, NPartial=%d\n", html_pag1_n_full, html_pag1_n_updates);

    // Cabeçalho inicial
    tcp_write( tpcb, HEADER_CHUNKED, strlen(HEADER_CHUNKED), TCP_WRITE_FLAG_COPY);
    tcp_output(tpcb);

    // Cabeçalho início do Doc, Head e inicio do body
    buffer_length = 0;
    snprintf(&buffer[buffer_length], buffer_size-buffer_length, PAGE01_BODY_START);

    // Título da página
    buffer_length = strlen(buffer);
    snprintf(&buffer[buffer_length], buffer_size-buffer_length, PAGE01_TILE);

    // Campo das mensagem recebida
    int8_t cor_r = 0;
    if(!msg_page_received.read){
      if(msg_page_received.high){
        if(html_pag1_n_updates & 0x01) cor_r = 2;
      }else{
        cor_r = 1;
      }
    }
    buffer_length = strlen(buffer);
    snprintf(&buffer[buffer_length], buffer_size-buffer_length, PAGE01_MSG_RECEIVED,
        cor_r==0?"":(cor_r==1?"style=\"background-color: yellow;\"":"style=\"background-color: red;\""),
        msg_page_received.msg,
        msg_page_received.read?"checked":""
    );

    // Campo das mensagem enviada
    int8_t cor_s = 0;
    if(!msg_page_send.read){
      if(msg_page_send.high){
        cor_s = 2;
      }else{
        cor_s = 1;
      }
    }
    buffer_length = strlen(buffer);
    snprintf(&buffer[buffer_length], buffer_size-buffer_length, PAGE01_MSG_SEND,
        msg_page_send.t_us == 0? "placeholder=\"Nenhuma Msg enviada\r\nDigite algo...\"":"",
        cor_s==0?"":(cor_s==1?"style=\"background-color: yellow;\"":"style=\"background-color: red;\""),
        msg_page_send.msg, 
        msg_page_send.read?"checked":""
      );

    // rodapé da página
    buffer_length = strlen(buffer);
    snprintf(&buffer[buffer_length], buffer_size-buffer_length, PAGE01_FOOTER, html_pag1_n_full, html_pag1_n_updates);

    // scripts da página
    buffer_length = strlen(buffer);
    snprintf(&buffer[buffer_length], buffer_size-buffer_length, PAGE01_SCRIPT, UI_CONNECTION_MAX_DELAY_US / 1000);

    // finalização do documento
    buffer_length = strlen(buffer);
    snprintf(&buffer[buffer_length], buffer_size-buffer_length, PAGE01_BODY_END);

    if(HTML_REPORT) {
        printf("Page Html:\n");
        printf(buffer);
    }    

    send_chunck(tpcb, buffer);
    send_chunck(tpcb, "");
}

// Coloca no buffer um Html com o JSON de update da página
// Retorna o número de bytes que foram colocados no buffer
uint32_t htlm_page01_update(struct tcp_pcb *tpcb, char *buffer, uint32_t buffer_size){
    uint16_t buffer_length;

    html_pag1_n_updates++;
    if(HTML_REPORT) printf("htlm_page01_update: NFull=%d, NPartial=%d\n", html_pag1_n_full, html_pag1_n_updates);

    // Cabeçalho inicial
    tcp_write( tpcb, HEADER_JSON, strlen(HEADER_JSON), TCP_WRITE_FLAG_COPY);
    tcp_output(tpcb);

    // Calculo das cores das áreas de texto
    int8_t cor_r = 0;
    int8_t cor_s = 0;
    if(!msg_page_received.read){
      if(msg_page_received.high){
        if(html_pag1_n_updates & 0x01) cor_r = 2;
      }else{
        cor_r = 1;
      }
    }
    if(!msg_page_send.read){
      if(msg_page_send.high){
        cor_s = 2;
      }else{
        cor_s = 1;
      }
    }

    // Criar JSON
    buffer_length = 0;
    snprintf(&buffer[buffer_length], buffer_size-buffer_length, UPDATE_JSON,
        msg_page_received.msg, msg_page_received.read?"true": "false", cor_r,
        msg_page_send.msg,     msg_page_send.read?    "true": "false", cor_s,
        html_pag1_n_updates);

    send_chunck(tpcb, buffer);
    if(HTML_REPORT) {
        printf("Page update Html:\n");
        printf(buffer);
    }   

    send_chunck(tpcb, "");
}
