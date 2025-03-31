#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"

#include "hardware/irq.h"
#include "hardware/pwm.h"
#include "libs/WebUtils.h"
#include "Config.h"
#include "Msgs.h"
#include "Ui.h"
#include "UiConnection.h"
#include "UiDisplay.h"
#include "UiLedBuzzer.h"

// TimeTick que atualiza a interface do usuário
void irq_pwm_timetick_wrap() {
    pwm_clear_irq(UI_PWM_TIME_TICK_SLICE); //  limpa o Irq senão no return desta rotina nova interrupção será gerada.

    UI_CONNECTION_STATE con_st = ui_connection_get();
    ui_led_buzzer_refresh(con_st, msg_page_send.read? MSG_READ: ( msg_page_send.high?MSG_HIGH:MSG_LOW));
    ui_display_update();

    // if(UI_REPORT) printf("UI: TimeTick\n");
} 


// Inicializa a interface com o usuário, configurando:
//   o PWM que gera o TimeTick
//   definindo a interrupção que vai tratar o TimeTick
//   e inicializa os submodulos da UI: UiConnectio, UiDisplay e UiLedBuzzer
void ui_init(){
    ui_connection_init();
    ui_display_init();
    ui_led_buzzer_init();

    pwm_set_clkdiv_int_frac(  UI_PWM_TIME_TICK_SLICE, UI_PWM_TIME_TICK_DIVISOR, 0);
    pwm_set_wrap(             UI_PWM_TIME_TICK_SLICE, UI_PWM_TIME_TICK_WRAP);
    pwm_clear_irq(            UI_PWM_TIME_TICK_SLICE);
    pwm_set_irq_enabled(      UI_PWM_TIME_TICK_SLICE, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, irq_pwm_timetick_wrap);
    irq_clear(                PWM_IRQ_WRAP);
    irq_set_enabled(          PWM_IRQ_WRAP, true);
    pwm_set_enabled(          UI_PWM_TIME_TICK_SLICE, true);

    if(UI_REPORT) printf("UI: ui_inits\n");
}


// Quem chama está função, informa a UI que foi recebida uma solicitação valida do navegador (ele está conectado)
void ui_valid_tcp_received(){
    ui_connection_update(UPDATED);
    if(UI_REPORT) printf("UI: ui_valid_tcp_received\n");
}

// Quem chama está função, informa a UI que foi estabelecida uma conexão com o roteador WiFi com o ip como parâmetro
void ui_wifi_connected(uint32_t ip){
    ui_connection_update(CONNECTED);
    ui_display_cmd_show(CMD_WIFI_CONNECTED, &ip);
    if(UI_REPORT){
        char buffer[16];
        printf("UI: ui_wifi_connected, IP= %s\n", ip_string(buffer, 16, ip));
    }
}

// Quem chama está função, informa a UI que está tentando obter uma conexão com o roteador WiFi e está é a tenttiva attempts
void ui_wifi_connecting(uint32_t attempts){
    ui_connection_update(NO_CONNECTION);
    ui_display_cmd_show(CMD_WIFI_CONNECTIN, &attempts);
    if(UI_REPORT) printf("UI: ui_wifi_connecting, tentativa = %dus\n", attempts);
}

// Quem chama está função, informa ao UI que a ultima mensagem enviada foi lida no navegador
void ui_msg_read(){
    ui_valid_tcp_received();
    ui_display_cmd_show(CMD_SEND_DATA, NULL);
    if(UI_REPORT) printf("UI: ui_msg_read\n");
}

// Quem chama está função, informa ao UI que o dispositivo IoT acabou de receber uma mensagem
void ui_msg_received(){
    ui_valid_tcp_received();
    ui_display_cmd_show(CMD_RECEIVED_DATA, NULL);
    if(UI_REPORT) printf("UI: ui_msg_received\n");
}

// Quem chama está função, informa ao UI que foi enviada uma pelo dispositivo IoT, direta pelos botões
void ui_view_send_data(){
    ui_display_cmd_show(CMD_SEND_DATA, NULL);
    if(UI_REPORT) printf("UI: ui_view_send_data\n");
}