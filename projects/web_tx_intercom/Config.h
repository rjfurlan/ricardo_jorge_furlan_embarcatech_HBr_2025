#ifndef CONFIG_DEF
#define CONFIG_DEF

 
#define PROG_NAME           "WEB TX INTERCOM"
#define PROG_TITLE                   "TX COM"
#define PROG_VERSION                "0.00.20"
#define PROG_BUILD                     "0001"
#define PROG_DATE                "22/02/2025"

#define WIFI_SSID  "MinhaRedeWiFi"  // Insira o nome  da sua rede Wi-Fi
#define WIFI_PASS  "MinhaSenha123"  // Insira a senha da sua rede Wi-Fi

#define PROG_INITIAL_DELAY_1_MS                  0        // Tempo de espera, logo após stdio_init_all, para conectar terminal de monitoração
#define PROG_INITIAL_DELAY_2_MS              10000        // Tempo de espera, após inicialização básica, antes de ativar servições da rede

#define BUTTON_A_MSG        "Tudo tranquilo por aqui."    // Mensagem que será automaticamente enviada ao clicar no botão A
#define BUTTON_A_MSG_HIGH                       false     // tipo da mensagem: false => Low, true => High

#define BUTTON_B_MSG  "Venha Logo preciso de sua ajuda!"  // Mensagem que será automaticamente enviada ao clicar no botão A
#define BUTTON_B_MSG_HIGH                     true        // tipo da mensagem: false => Low, true => High



#define HTML_REPORT                          false


#define UI_PWM_TIME_TICK_SLICE                   0        // Slice=6B, slice 6, channel B
#define UI_PWM_TIME_TICK_BASE_FREQUENCY  125000000        // 125MHz, Frequência de entrada no PWM pré divisor
#define UI_PWM_TIME_TICK_DIVISOR               250        // => 500kMHz, Divisor, o valor deve estar entre: 0 e 255
#define UI_PWM_TIME_TICK_COUNT               50000        // freq = 500kHz com count = 50000 ==> wrap a cada 10 Hz 500k / 50000
#define UI_PWM_TIME_TICK_WRAP                49999        // WRAP = COUNT - 1


#define UI_CONNECTION_MAX_DELAY_US         5000000        // Tempo sem receber requisições TCP IP para classificar como desconectado do Browser
#define UI_CONNECTION_TIMEOUT_WEB_MSG "A conexão com a BitDogLab parece ter sido perdida!"
      
#define UI_DISPLAY_TIMEOUT_US             10000000        // Tempo para o display retornar para a tela de Mensagens recebidas
#define UI_DISPLAY_REPORT                    false        // habilita prints para facilitar debug
      
#define UI_LED_BUZZER_BUZZER_FREQ             1000        // 1kHz
#define UI_LED_BUZZER_CYCLE                      5        // frequência base de atualização é 10Hz, com cycle =5 => liiscar e beep em 2Hz
#define UI_LED_BUZZER_DUTYCYCLE                  2        // duração das pisca das dos LED e Buzzer 2 => 40%
#define UI_LED_BUZZER_LED_RR_LEVEL              30
#define UI_LED_BUZZER_LED_YR_LEVEL              20
#define UI_LED_BUZZER_LED_YG_LEVEL              15
#define UI_LED_BUZZER_LED_GG_LEVEL              20
#define UI_LED_BUZZER_LED_BB_LEVEL              30
#define UI_LED_BUZZER_REPORT                 false        // habilita prints para facilitar debug
      
#define UI_REPORT                             true        // habilita prints para facilitar debug

#define WEBSERVER_BUFFER_SIZE             (8*1024)
#define WEBSERVER_PORT                          80
#define WEBSERVER_REPORT                      true        // habilita prints para facilitar debug
#define WEBSERVER_REPORT_FULL                false        // habilita prints detalhados para facilitar debug


#define WIFI_TIMEOUT_CONECTION_MS             3000        // tempo para tentar se conectar ao roteador
#define WIFI_REPORT                           true        // habilita prints para facilitar debug


#endif
