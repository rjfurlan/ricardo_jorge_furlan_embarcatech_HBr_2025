#ifndef UI_LED_BUZZER_DEF
#define UI_LED_BUZZER_DEF

#include "UiConnectionType.h"

typedef enum {
    MSG_READ,       // Mensagem lida
    MSG_LOW,        // Mensagem não lida tipo Low  (buzzer Off)
    MSG_HIGH,       // Mensagem não lida tipo High (buzzer ON)
} UI_LED_BUZZER_MSG_ST;


// Inicializa o gerenciado dos LEDs RGB e do Buzzer A
void ui_led_buzzer_init();

// Atualiza o estado da conexão, e o estado da última mensagem recebida
// para configurar os LEDs e Buzzer de acordo
void ui_led_buzzer_refresh(UI_CONNECTION_STATE com_st, UI_LED_BUZZER_MSG_ST msg_st);

#endif