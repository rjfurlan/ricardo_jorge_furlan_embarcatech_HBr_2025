#ifndef UI_DEF
#define UI_DEF

// Inicializa a interface com o usuário, configurando:
//   o PWM que gera o TimeTick
//   definindo a interrupção que vai tratar o TimeTick
//   e inicializa os submodulos da UI: UiConnectio, UiDisplay e UiLedBuzzer
void ui_init();

// Quem chama está função, informa ao UI que a ultima mensagem enviada foi lida no navegador
void ui_msg_read();

// Quem chama está função, informa ao UI que o dispositivo IoT acabou de receber uma mensagem
void ui_msg_received();

// Que chama está função, informa a UI que foi recebida uma solicitação valida do navegador (ele está conectado)
void ui_valid_tcp_received();

// Que chama está função, informa a UI que foi estabelecida uma conexão com o roteador WiFi com o ip como parâmetro
void ui_wifi_connected( uint32_t ip);

// Quem chama está função, informa a UI que está tentando obter uma conexão com o roteador WiFi e está é a tenttiva attempts
void ui_wifi_connecting(uint32_t attempts);

// Quem chama está função, informa ao UI que foi enviada uma pelo dispositivo IoT, direta pelos botões
void ui_view_send_data();

#endif