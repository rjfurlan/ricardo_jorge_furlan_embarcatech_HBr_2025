#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "libs/WebUtils.h"
#include "Ads.h"
#include "Buttons.h"
#include "Config.h"
#include "Display.h"
#include "UiDisplay.h"
#include "Msgs.h"

// Indica qual tela deve ser mostrada
typedef enum{
    RECEIVED_DATA,
    SEND_DATA,
    SEND_NEW_DATA,
    WIFI,
    VERSION,
    INVALID
} UI_DISPLAY_SHOW;

// retorna a próxima tela que deve ser mostrada a partir da fornecida
static UI_DISPLAY_SHOW ui_display_next_show(UI_DISPLAY_SHOW show){
    switch(show){
        case RECEIVED_DATA: return SEND_DATA;
        case SEND_DATA:     return SEND_NEW_DATA;
        case SEND_NEW_DATA: return WIFI;
        case WIFI:          return VERSION;
        case VERSION:       return RECEIVED_DATA;
        default:            return RECEIVED_DATA;
    }
}

static volatile bool     ui_display_wifi_connected;
static volatile uint32_t ui_display_wifi_attempts;
static volatile uint32_t ui_display_wifi_ip;
static volatile uint32_t ui_display_cycles;

static volatile UI_DISPLAY_SHOW ui_display_show;
static volatile UI_DISPLAY_SHOW ui_display_show_next;
static volatile UI_DISPLAY_SHOW ui_display_show_cmd;

static volatile uint64_t ui_display_timeout_us;

static char ui_display_buffer[17];


// Gera no display a tela de msg recebida
static UI_DISPLAY_SHOW show_received_data(bool init){
    if(init){   // inicialização da tela
        ui_display_timeout_us = time_us_64() + UI_DISPLAY_TIMEOUT_US;
        ui_display_cycles = 0;
    }

    if((ui_display_cycles==0)||(ui_display_cycles==5)){
        display_fill(false, false);
        if(msg_page_send.t_us==0){
            // Ainda não há nenhuma mensagem recebida
            display_msg(false, 2, 0, "MSG RECEBIDA");
            display_msg(false, 0, 4, "NENHUMA MENSAGEM");
            display_msg(true,  4, 6, "RECEBIDA");
        }else{
            // Gera a tela da mensagem recebida
            snprintf(ui_display_buffer, 19, "%d s", (uint32_t)((time_us_64() - msg_page_send.t_us) / 1000000));
            display_msg(false, 0, 0, msg_page_send.high?"MSG RECEBIDA - H":"MSG RECEBIDA - L");
            display_msg(false, 0, 2, msg_page_send.msg);
            display_msg(false, 0, 7, ui_display_buffer);
            if(msg_page_send.read) display_msg(false, 12, 7, "LIDA");
            if((ui_display_cycles==5)&&(!msg_page_send.read)){  // Caso a mensagem ainda não foi lida a tela pisca
                display_invert(false);
            }                    
            display_update();
        }
    }

    ui_display_cycles++;
    if(ui_display_cycles >= 10) ui_display_cycles = 0;

    // Caso o Joystick seja pressionado:
    //   - se a mensagem ainda não foi lida, torna ela LIDA
    //   - senão vai para a próxima tela
    if(button_n_clicks(BUTTON_C, CLEAR_ALL)){
        if(!msg_page_send.read) {
            msg_page_send.read = true;
            return RECEIVED_DATA;
        }else{
            return ui_display_next_show(RECEIVED_DATA);
        }
    }     
    return INVALID;
}

// Gera no display a tela de msg já enviada
//   - Após timeout retorna para a tela de mensagem recebida
//   - caso o joystick seja pressionado vai para a próxima tela
static UI_DISPLAY_SHOW show_send_data(bool init){
    if(init){
        ui_display_timeout_us = time_us_64() + UI_DISPLAY_TIMEOUT_US;
        ui_display_cycles = 0;
    }else{
        if(time_us_64() > ui_display_timeout_us) return RECEIVED_DATA;
    }

    if((ui_display_cycles==0)||(ui_display_cycles==5)){
        display_fill(false, false);
        if(msg_page_received.t_us==0){
            // Ainda não há nenhuma mensagem enviada
            display_msg(false, 2, 0, "MSG ENVIADA");
            display_msg(false, 0, 4, "NENHUMA MENSAGEM");
            display_msg(true,  4, 6, "ENVIADA");
        }else{
            // Gera a tela da mensagem enviada
            snprintf(ui_display_buffer, 19, "%d s", (uint32_t)((time_us_64() - msg_page_received.t_us) / 1000000));
            display_msg(false, 0, 0, msg_page_received.high?"MSG ENVIADA - HI":"MSG ENVIADA - LO");
            display_msg(false, 0, 2, msg_page_received.msg);
            display_msg(false, 0, 7, ui_display_buffer);
            if(msg_page_received.read) display_msg(false, 12, 7, "LIDA");
            if((ui_display_cycles==5)&&(!msg_page_received.read)){ // Caso a mensagem ainda não foi lida a tela pisca
                display_invert(false);
            }                    
            display_update();
        }
    }

    ui_display_cycles++;
    if(ui_display_cycles >= 10) ui_display_cycles = 0;

    // Caso o Joystick seja pressionado vai para a próxima tela
    if(button_n_clicks(BUTTON_C, CLEAR_ALL)){
        return ui_display_next_show(SEND_DATA);
    }     
    return INVALID;
}


static int8_t new_msg_px;
static int8_t new_msg_py;
static char   new_msg_msg[49];
static char   new_msg_msg_trim[49];
static int8_t new_msg_p_msg;
static int8_t new_msg_dx;
static int8_t new_msg_dy;
static char * new_msg_keyboard = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 .,:/-+_!?#*";
                                         //123456789012345678901234567890123456789012345678

static void new_msg_clear_msg(){
    for(int i=0;i<48;i++) new_msg_msg[i] = ' ';
    new_msg_msg[48] = 0;
    new_msg_p_msg   = 0;
}

static void new_msg_trim_msg(){
    new_msg_msg[48]==0;
    strcpy(new_msg_msg_trim, new_msg_msg);
    int i = 47;
    while(i>=0){
        if(new_msg_msg_trim[i] == ' '){
            new_msg_msg_trim[i] = 0;
            i--;
        }else{
            i=-1;
        }
    }
}

// Gera no display a tela de msg a ser enviada que está sendo enviada
//   - Após timeout retorna para a tela de mensagem recebida, o movimento do Joystick reseta o timeout
//   - O Joystick faz mover o cursor na tela
//   - Caso o joystick seja pressionado:
//      - se o cursor estivar na área de keyboard, o caractere selecionado será adicionado a mensagem
//      - caso o cursor estivar na área da mensagem o cursor da mensagem é atualizado
//      - caso o cursor estivar na área de comandos o comando será realizado:
//         - LO    => Envia a mensagem corrento como Low
//         - HIGH  => Envia a mensagem corrento como High
//         - CLEAR => Limpa a mensagem corrente
//         - NEXT  => Vai para a próxima tela
static UI_DISPLAY_SHOW show_send_new_data(bool init){
    static int8_t px;
    static int8_t py;

    if(init){
        ui_display_timeout_us = time_us_64() + UI_DISPLAY_TIMEOUT_US;
        ui_display_cycles = 0;
        px         = 13;
        py         =  4;
        new_msg_dx =  0;
        new_msg_dy =  0;
    }else{
        if(time_us_64() > ui_display_timeout_us) return RECEIVED_DATA;
    }

    // Gera a tela
    display_fill(false, false);
    display_msg( false, 2, 0, "MSG A ENVIAR");
    display_msg( false, 0, 1,  new_msg_msg);
    display_msg( false, 0, 4, "LO HI CLEAR NEXT");
                            // 0123456789012345
    display_msg( false, 0, 5, new_msg_keyboard);
    if(ui_display_cycles & 0x01){        // Pisca o cursor da mensagem
        display_invert_char(false, new_msg_p_msg & 0x0F, 1 + (new_msg_p_msg>>4));
    }

    if(py==4){
        // Para os comandos, caso o cursor em cima de algum todo o texto do comando é invertido
        if((px>=0)&&(px<=1)){
            display_invert_char(false,  0, 4);
            display_invert_char(false,  1, 4);
            if(ui_display_cycles &0x01) display_invert_char(false, px, 4);
        }else if((px>=3)&&(px<=4)){
            display_invert_char(false,  3, 4);
            display_invert_char(false,  4, 4);
            if(ui_display_cycles &0x01) display_invert_char(false, px, 4);
        }else if((px>=6)&&(px<=10)){
            display_invert_char(false,  6, 4);
            display_invert_char(false,  7, 4);
            display_invert_char(false,  8, 4);
            display_invert_char(false,  9, 4);
            display_invert_char(false, 10, 4);
            if(ui_display_cycles &0x01) display_invert_char(false, px, 4);
        }else if((px>=12)&&(px<=15)){
            display_invert_char(false, 12, 4);
            display_invert_char(false, 13, 4);
            display_invert_char(false, 14, 4);
            display_invert_char(false, 15, 4);
            if(ui_display_cycles &0x01) display_invert_char(false, px, 4);
        }else{
            display_invert_char(false, px, py);
        }
    }else{
        display_invert_char(false, px, py);     // Inverte o cursor nas demais posições
    }
    display_update();
    
    if(button_n_clicks(BUTTON_C, CLEAR_ALL)){   
        // Trata se o Joystick foi pressionado
        new_msg_dx = 0;
        new_msg_dy = 0;
        ui_display_timeout_us = time_us_64() + UI_DISPLAY_TIMEOUT_US;
        if(py==4){
            // Trata comandos
            if((px>=0)&&(px<=1)){
                // Envia Mensagem como Low
                new_msg_trim_msg();
                msg_page_received.high = false;
                msg_page_received.read = false;
                msg_page_received.t_us = time_us_64();
                strcpy(msg_page_received.msg, new_msg_msg_trim);
                return SEND_DATA;
            }else if((px>=3)&&(px<=4)){
                // Envia Mensagem como High
                new_msg_trim_msg();
                msg_page_received.high = true;
                msg_page_received.read = false;
                msg_page_received.t_us = time_us_64();
                strcpy(msg_page_received.msg, new_msg_msg_trim);
                return SEND_DATA;
            }else if((px>=6)&&(px<=10)){
                // Limpa a mensagem
                new_msg_clear_msg();
                printf("Limpa a mensagem\n");
            }else if((px>=12)&&(px<=15)){
                // vai para a próxima tela
                return ui_display_next_show(SEND_NEW_DATA);
            }    
        }else if(py<=3){
            // Atualizar cursor da mensagem
            new_msg_p_msg = px + 16 * (py-1);
        }else if(py>=5){
            // Adiciona o caractere selecionado a mensagem
            int16_t p = px + 16 * (py-5);
            new_msg_msg[new_msg_p_msg] = new_msg_keyboard[p];
            new_msg_p_msg++;
            if(new_msg_p_msg >= 48) new_msg_p_msg = 0;
        }
    }else{
        // trata os movimentos do Joystick atualizando o cursor da tela
        uint16_t x = ads_get(AD_JOYSTICK_X);
        uint16_t y = ads_get(AD_JOYSTICK_Y);
        if(UI_DISPLAY_REPORT) printf("Ui Display - AD, x=%4d, y=%4d\n", x, y);

        int8_t dx_last = new_msg_dx;
        int8_t dy_last = new_msg_dy;
        if(     x < (2048-512)) new_msg_dx--;
        else if(x > (2048+512)) new_msg_dx++;
                           else new_msg_dx=0;
    
        if(     y < (2048-512)) new_msg_dy++;
        else if(y > (2048+512)) new_msg_dy--;
                           else new_msg_dy=0;
        if((new_msg_dx != dx_last)||(new_msg_dy != dy_last)){
            ui_display_timeout_us = time_us_64() + UI_DISPLAY_TIMEOUT_US;
        }
                      
        if(new_msg_dx<-3){
            new_msg_dx=0;
            px--;
            if(px<0) px = 15;
        }else if(new_msg_dx>3){
            new_msg_dx=0;
            px++;
            if(px>15) px = 0;
        }
        if(new_msg_dy<-3){
            new_msg_dy=0;
            py--;
            if(py<1) py = 7;
        }else if(new_msg_dy>3){
            new_msg_dy=0;
            py++;
            if(py>7) py = 1;
        }
    }

    ui_display_cycles++;
    return INVALID;
}

// Gera no display a tela com o estado da conexão WiFI
//   - Após timeout retorna para a tela de mensagem recebida
//   - caso o joystick seja pressionado vai para a próxima tela
static UI_DISPLAY_SHOW show_wifi(bool init){
    display_fill(false, false);
    display_msg( false, 2, 0, "WiFi - SSID");
    display_msg( false, 0, 2, WIFI_SSID); 
    if(ui_display_wifi_connected){
        display_msg(false, 0, 5, "Conectado-IP:");
        display_msg(true,  0, 7, ip_string(ui_display_buffer, 16, ui_display_wifi_ip));
    }else{
        snprintf(ui_display_buffer, 16, "Tentativa %d",  ui_display_wifi_attempts);
        display_msg(false, 0, 5, "Conectando...");
        display_msg(true,  0, 7, ui_display_buffer);
    }
    if(init){
        ui_display_timeout_us = time_us_64() + UI_DISPLAY_TIMEOUT_US;
    }else{
        if(time_us_64() > ui_display_timeout_us){
            return RECEIVED_DATA;
        }
    }
    // Caso o Joystick seja pressionado vai para a próxima tela
    if(button_n_clicks(BUTTON_C, CLEAR_ALL)){
        return ui_display_next_show(WIFI);
    } 
    return INVALID;
}

// Gera no display a tela da versão do software
//   - Após timeout retorna para a tela de mensagem recebida
//   - caso o joystick seja pressionado vai para a próxima tela
static UI_DISPLAY_SHOW show_version(bool init){
    if(init){
        ui_display_timeout_us = time_us_64() + UI_DISPLAY_TIMEOUT_US;
        display_show_prog_version();
    }else{
        if(time_us_64() > ui_display_timeout_us) {
            return RECEIVED_DATA;
        }    
    }

    // Caso o Joystick seja pressionado vai para a próxima tela
    if(button_n_clicks(BUTTON_C, CLEAR_ALL)){
        return ui_display_next_show(VERSION);
    }
    return INVALID;
}

// Inicializa o estado da Interface do usuário UI do display
void ui_display_init(){
    ui_display_show      = VERSION;
    ui_display_show_next = INVALID;
    ui_display_show_cmd  = INVALID;

    ui_display_wifi_connected = false;
    ui_display_wifi_attempts  = 0;
    ui_display_wifi_ip        = 0;
    new_msg_clear_msg();
}

// Atualiza o display, a próxima tela ativa é informada pela tela atualmente ativa ao ser atualizada
void ui_display_update(){
    bool init = false;                                           

    // ui_display_show_next != INVALID ==> update, init=true

    if(ui_display_show_cmd != INVALID){
        ui_display_show     = ui_display_show_cmd;
        ui_display_show_cmd = INVALID;
        init = true;
    } else{
        if(ui_display_show_next != INVALID){
            ui_display_show = ui_display_show_next;
            init = true;
        }
    }

    switch(ui_display_show){
        case RECEIVED_DATA: ui_display_show_next = show_received_data(init); break;
        case SEND_DATA:     ui_display_show_next = show_send_data(init);     break;
        case SEND_NEW_DATA: ui_display_show_next = show_send_new_data(init); break;
        case WIFI:          ui_display_show_next = show_wifi(init);          break;
        case VERSION:       ui_display_show_next = show_version(init);       break;
    }
}

// Solicita que determinada tela seja mostrada
// O parâmetro data depende da tela sendo validos apenas para:
//   - CMD_WIFI_CONNECTIN ==> *data contem o número de tentativas
//   - CMD_WIFI_CONNECTED ==> *data contem o IP da conexão
void ui_display_cmd_show(UI_DISPLAY_SHOW_CMD show, void * arg){
    switch(show){
        case CMD_RECEIVED_DATA:
            ui_display_show_cmd = RECEIVED_DATA;
            break;
        case CMD_SEND_DATA:
            ui_display_show_cmd = SEND_DATA;
            break;
        case SEND_NEW_DATA:
            ui_display_show_cmd = SEND_NEW_DATA;
            break;
        case CMD_WIFI_CONNECTIN:
            ui_display_wifi_connected = false;
            ui_display_wifi_attempts  = *((uint32_t *)arg);
            ui_display_wifi_ip        = 0;
            ui_display_show_cmd       = WIFI;
            break;
        case CMD_WIFI_CONNECTED:
            ui_display_wifi_connected = true;
            ui_display_wifi_attempts  = 0;
            ui_display_wifi_ip        = *((uint32_t *)arg);
            ui_display_show_cmd       = WIFI;
            break;
        case CMD_VERSION:      
            ui_display_show_cmd = VERSION;
            break;
    }    
}
