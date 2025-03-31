#include "pico/stdlib.h"

#include "Config.h"
#include "Buzzers.h"
#include "Led.h"
#include "UiLedBuzzer.h"

static uint8_t ui_led_buzzer_cycle;     // Variável utilizada para definir os momentos dos LEDs piscarem e o Buzzer tocar

// Inicializa o gerenciado dos LEDs RGB e do Buzzer A
void ui_led_buzzer_init(){
    ui_led_buzzer_cycle = 0;
    led_set(0, 0, 0);
    buzzer_set_freq(BUZZER_A, 0);
}


// Atualiza o estado da conexão, e o estado da última mensagem recebida
// para configurar os LEDs e Buzzer de acordo
void ui_led_buzzer_refresh(UI_CONNECTION_STATE com_st, UI_LED_BUZZER_MSG_ST msg_st){
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    if(com_st == UPDATED){
        g = UI_LED_BUZZER_LED_GG_LEVEL;
    }else{
        if(ui_led_buzzer_cycle < UI_LED_BUZZER_DUTYCYCLE){
            if(com_st == NO_CONNECTION){
                r = UI_LED_BUZZER_LED_RR_LEVEL;
            }else{
                r = UI_LED_BUZZER_LED_YR_LEVEL;
                g = UI_LED_BUZZER_LED_YG_LEVEL;
            }
        }
    }
    bool buzzer_on = false;
    if(msg_st != MSG_READ){
       if((UI_LED_BUZZER_CYCLE - ui_led_buzzer_cycle) <= UI_LED_BUZZER_DUTYCYCLE){
            b = UI_LED_BUZZER_LED_BB_LEVEL;
            if(msg_st == MSG_HIGH){
                buzzer_on = true;
            }
       }
    }
    led_set(r, g, b);
    buzzer_set_freq(BUZZER_A, buzzer_on?UI_LED_BUZZER_BUZZER_FREQ:0);

    ui_led_buzzer_cycle++;
    if(ui_led_buzzer_cycle >= UI_LED_BUZZER_CYCLE) ui_led_buzzer_cycle = 0;
}
