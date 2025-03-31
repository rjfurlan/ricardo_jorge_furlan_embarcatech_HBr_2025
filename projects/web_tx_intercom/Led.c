#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "libs/BitDogLab_Defs.h"
#include "Led.h"


/*
checar o div 256
checar o wrap 255
*/

#define LED_TESTE_TIME_MS 1000

void (*led_buzzer_set_led)(uint8_t);

// Inicializa as GPIOs e os PWM para que os LEDs RGB possa ser utilizado nível de brilho nos LEDs
// Obs.: Caso seja utilizado o Buzzer B deve ser informada a função buzzer_set_led, para esta controlar o nível do LED G
//       Caso o Buzzer B não seja utilizado este parâmetro deve ser NULL
void led_init(void (*buzzer_set_led)(uint8_t)){
    led_buzzer_set_led = buzzer_set_led;

    uint slice_rb = pwm_gpio_to_slice_num(BITDOGLAB_GPIO_LED_R);
    // pwm_set_clkdiv_int_frac4(slice_rb, 0, 0);  // div = 0 > div = 256
    // backwards compatibility
    pwm_set_clkdiv_int_frac(slice_rb, 0, 0);      // div = 0 > div = 256
    pwm_set_wrap(slice_rb, 254);

    uint slice_g;
    if(led_buzzer_set_led == NULL){
        slice_g  = pwm_gpio_to_slice_num(BITDOGLAB_GPIO_LED_G);
        // pwm_set_clkdiv_int_frac4(slice_g,  0, 0);  // div = 0 > div = 256
        // backwards compatibility
        pwm_set_clkdiv_int_frac(slice_g,  0, 0);      // div = 0 > div = 256
        pwm_set_wrap(slice_g,  254);
    }
    
    led_set(0, 0, 0);
    gpio_set_function(BITDOGLAB_GPIO_LED_R, GPIO_FUNC_PWM);
    gpio_set_function(BITDOGLAB_GPIO_LED_G, GPIO_FUNC_PWM);
    gpio_set_function(BITDOGLAB_GPIO_LED_B, GPIO_FUNC_PWM);
    pwm_set_enabled(slice_rb, true);

    if(led_buzzer_set_led == NULL){
        pwm_set_enabled(slice_g,  true);
    }
}

// Define o nível para cada LED, 0 ==> apagado, 255 ==> 100% aces
void led_set(uint8_t r, uint8_t g, uint8_t b){
    pwm_set_gpio_level(BITDOGLAB_GPIO_LED_R, r);
    pwm_set_gpio_level(BITDOGLAB_GPIO_LED_B, b);
    if(led_buzzer_set_led == NULL) pwm_set_gpio_level(BITDOGLAB_GPIO_LED_G, g);
                              else led_buzzer_set_led(g);
}

// Executa testes nos LEDs
void led_text(void (*buzzer_set_led)(uint8_t)){
    led_init(buzzer_set_led);
    printf("LEDs apagados\n");
    led_set(0x00, 0x00, 0x00);
    sleep_ms(LED_TESTE_TIME_MS);

    printf("LED Vermelho  25%\n");
    led_set(0x40, 0x00, 0x00);
    sleep_ms(LED_TESTE_TIME_MS);
    printf("LED Vermelho  50%\n");
    led_set(0x80, 0x00, 0x00);
    sleep_ms(LED_TESTE_TIME_MS);
    printf("LED Vermelho 100%\n");
    led_set(0xFF, 0x00, 0x00);
    sleep_ms(LED_TESTE_TIME_MS);
    
    printf("LED Verde  25%\n");
    led_set(0x00, 0x40, 0x00);
    sleep_ms(LED_TESTE_TIME_MS);
    printf("LED Verde  50%\n");
    led_set(0x00, 0x80, 0x00);
    sleep_ms(LED_TESTE_TIME_MS);
    printf("LED Verde 100%\n");
    led_set(0x00, 0xFF, 0x00);
    sleep_ms(LED_TESTE_TIME_MS);

    printf("LED Azul  25%\n");
    led_set(0x00, 0x00, 0x40);
    sleep_ms(LED_TESTE_TIME_MS);
    printf("LED Azul  50%\n");
    led_set(0x00, 0x00, 0x80);
    sleep_ms(LED_TESTE_TIME_MS);
    printf("LED Azul 100%\n");
    led_set(0x00, 0x00, 0xFF);
    sleep_ms(LED_TESTE_TIME_MS);

    printf("LED Branco  25%\n");
    led_set(0x40, 0x40, 0x40);
    sleep_ms(LED_TESTE_TIME_MS);
    printf("LED Branco  50%\n");
    led_set(0x80, 0x80, 0x80);
    sleep_ms(LED_TESTE_TIME_MS);
    printf("LED Branco 100%\n");
    led_set(0xFF, 0xFF, 0xFF);
    sleep_ms(LED_TESTE_TIME_MS);

    printf("LEDs apagados\n");
    led_set(0x00, 0x00, 0x00);
}
