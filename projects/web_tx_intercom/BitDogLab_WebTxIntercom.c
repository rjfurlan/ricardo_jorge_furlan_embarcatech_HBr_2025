#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "libs/WebUtils.h"
#include "Config.h"
#include "Ads.h"
#include "Buttons.h"
#include "Buzzers.h"
#include "Display.h"
#include "I2C.h"
#include "Led.h"
#include "Msgs.h"
#include "Ui.h"
#include "WebServer.h"
#include "Wifi.h"


int main()
{
    stdio_init_all();
    sleep_ms(PROG_INITIAL_DELAY_1_MS);
    
    // Inicializa os principais módulos
    i2c_bitdoglab_init();
    ads_init();
    buttons_init();
    buzzers_init(true);
    display_init();
    led_init(NULL);
    display_show_prog_version();
    sleep_ms(PROG_INITIAL_DELAY_2_MS);

    printf("START: %s - %s - Version:%s - Build:%s - Data:%s\n\n", PROG_NAME, PROG_TITLE, PROG_VERSION, PROG_BUILD, PROG_DATE);

    wifi_init();        // Inicializa o radio WiFi, mas não faz a conexão, a conexão é feita no main loop
    web_server_init();  // Habilita o servidor, ativando a escuta               
    ui_init();          // Inicializa a UI interface do usuário: LEDs, Display, Buzzer

    uint32_t main_loop_cycle = 0;      // Conta o número de vezes que rodou o main loop
    uint16_t attempts        = 0;      // Conta o número de tentativas de conexão com o roteador WiFi

    // Main Loop:
    //  - Verifica se há botões (A ou B) que foram clicados para enviar mensagens
    //  - Verifica o estado da conexão WiFi, tentando reconectar caso esteja desconectada
    while (true) {
        main_loop_cycle++;
        // Botão A envia mensagem Normal (LOW)
        if(button_n_clicks(BUTTON_A, CLEAR_ALL)){
            strcpy(msg_page_received.msg, BUTTON_A_MSG);
            msg_page_received.high = BUTTON_A_MSG_HIGH;
            msg_page_received.read = false;
            msg_page_received.t_us = time_us_64();
            ui_view_send_data();
        }
        // Botão B envia mensagem Urgente (HIGH)
        if(button_n_clicks(BUTTON_B, CLEAR_ALL)){
            strcpy(msg_page_received.msg, BUTTON_B_MSG);
            msg_page_received.high = BUTTON_B_MSG_HIGH;
            msg_page_received.read = false;
            msg_page_received.t_us = time_us_64();
            ui_view_send_data();
        }

        // Monitora o estado da conexão com o roteador WiFi
        if(wifi_connected()){
            // Roteador conectado => Não faz nada
            printf("%4d:Main loop - %s\n", main_loop_cycle, PROG_NAME);
            attempts = 0;
            sleep_ms(1000);
        }else{
            // Roteador desconectado => tenta conectar
            attempts++;
            ui_wifi_connecting(attempts);       // informa a UI que esta desconectado
            printf("%4d:Main loop - %s: Tentativa %d de conectar com o roteador\n", main_loop_cycle, PROG_NAME, attempts);
            uint32_t ip = wifi_connect(attempts);
            if(ip){
                char buffer[16];
                printf("%4d:Main loop - %s: Conectado na tentativa %d, com IP: %s\n", main_loop_cycle, PROG_NAME, attempts, ip_string(buffer, 16, ip));
                ui_wifi_connected(ip);       // informa a UI que esta conectado e qual IP
            }
        }
    }
}
