#ifndef BUZZER_DEF
#define BUZZER_DEF

typedef enum {
    BUZZER_A,
    BUZZER_B
} BUZZER;

typedef enum {
    OFF,    // silencia o Buzzer
    DO,
    RE,
    MI,
    FA,
    SOL,
    LA,
    SI
} BUZZER_NOTE;

void buzzers_init(bool disable_buzzer_b);               // Inicializa os Buzzers inclusive configurando os PWMs
                                                        // pode ser não utilizado o Buzzer B para evitar conflitos com o LED G
void buzzer_scale(   BUZZER buzzer, uint32_t delay_ms); // Toca uma escala musical
void buzzer_set(     BUZZER buzzer, BUZZER_NOTE note);  // Ativa um buzzer com uma BUZZER_NOTE
void buzzer_set_freq(BUZZER buzzer, uint16_t freq);     // Ativa um buzzer com uma frequência específica, 0 ==> desligado
void buzzer_set_led(uint8_t led_level);                 // Caso se utiliza o LED G e o Buzzer B, 
                                                        // essa função faz com que o nível do LED seja controlada pelo módulo do buzzer
                                                        // Evitando conflitos
void buzzers_test();                                    // Rotina para testar os Buzzzers

#endif