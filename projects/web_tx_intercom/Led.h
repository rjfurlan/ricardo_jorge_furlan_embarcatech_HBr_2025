#ifndef LED_DEF
#define LED_DEF


// Inicializa as GPIOs e os PWM para que os LEDs RGB possa ser utilizado nível de brilho nos LEDs
// Obs.: Caso seja utilizado o Buzzer B deve ser informada a função buzzer_set_led, para esta controlar o nível do LED G
//       Caso o Buzzer B não seja utilizado este parâmetro deve ser NULL
void led_init(void (*buzzer_set_led)(uint8_t));

// Define o nível para cada LED, 0 ==> apagado, 255 ==> 100% aceso
void led_set(uint8_t r, uint8_t g, uint8_t b);

// Executa testes nos LEDs
void led_text(void (*buzzer_set_led)(uint8_t));

#endif