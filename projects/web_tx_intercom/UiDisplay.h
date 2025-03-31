#ifndef UI_DISPLAY_DEF
#define UI_DISPLAY_DEF


typedef enum{
    CMD_RECEIVED_DATA,
    CMD_SEND_DATA,
    CMD_SEND_NEW_DATA,
    CMD_WIFI_CONNECTIN,
    CMD_WIFI_CONNECTED,
    CMD_VERSION,
} UI_DISPLAY_SHOW_CMD;


// Inicializa o estado da Interface do usuário UI do display
void ui_display_init();

// Atualiza o display, a próxima tela ativa é informada pela tela atualmente ativa ao ser atualizada
void ui_display_update();

// Solicita que determinada tela seja mostrada
// O parâmetro data depende da tela sendo validos apenas para:
//   - CMD_WIFI_CONNECTIN ==> *data contem o número de tentativas
//   - CMD_WIFI_CONNECTED ==> *data contem o IP da conexão
void ui_display_cmd_show(UI_DISPLAY_SHOW_CMD show, void * data);

#endif