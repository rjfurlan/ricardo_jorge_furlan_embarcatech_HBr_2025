#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "libs/BitDogLab_Defs.h"
#include "Buzzers.h"


#define PWM_CLK_DIV 125     // gera frequência de contagem de 1MHz
#define BUZZER_DELAY_MS 500

/*
Divisor de frequência 1MHZ

Nota  Freq(Hz)  Divisor  Div-1  Level
 do    261,63    3822     3821   1911
 do#   277,18    3608     3607   1804
 re    293,66    3405     3404   1703
 re#   311,13    3214     3213   1607
 mi    329,63    3034     3033   1517
 fa    349,23    2863     2862   1432
 fa#   369,99    2703     2702   1352
 sol   392,00    2551     2550   1276
 sol#  415,30    2408     2407   1204
 la    440,00    2273     2272   1137
 la#   466,16    2145     2144   1073
 si    493,88    2025     2024   1013
 do    523,25    1911     1910    956
*/


// WARNIGNG: Led G e Buzzer B compartilham o mesmo PWM slice na BitDogLab

static uint slice_num_a;
static uint slice_num_b;
static uint channel_a;
static uint channel_b;

static uint16_t wrapper_b;
static int16_t  level_led = -1;

static bool buzzer_b_disabled;

// Inicializa os Buzzers inclusive configurando os PWMs
// pode ser não utilizado o Buzzer B para evitar conflitos com o LED G
void buzzers_init(bool disable_buzzer_b){
    buzzer_b_disabled = disable_buzzer_b;
    slice_num_a = pwm_gpio_to_slice_num(BITDOGLAB_GPIO_BUZZER_A);
    channel_a   = pwm_gpio_to_channel(  BITDOGLAB_GPIO_BUZZER_A);
    pwm_set_clkdiv_int_frac(slice_num_a, PWM_CLK_DIV, 0);
    gpio_set_function(BITDOGLAB_GPIO_BUZZER_A, GPIO_FUNC_PWM);
    
    if(!buzzer_b_disabled){
        slice_num_b = pwm_gpio_to_slice_num(BITDOGLAB_GPIO_BUZZER_B);
        channel_b   = pwm_gpio_to_channel(  BITDOGLAB_GPIO_BUZZER_B);
        pwm_set_clkdiv_int_frac(slice_num_b, PWM_CLK_DIV, 0);
        gpio_set_function(BITDOGLAB_GPIO_BUZZER_B, GPIO_FUNC_PWM);
    }
    
    buzzer_set(BUZZER_A, OFF);
    buzzer_set(BUZZER_B, OFF);

    pwm_set_enabled(slice_num_a, true);
    if(!buzzer_b_disabled) pwm_set_enabled(slice_num_b, true);
}

static void buzzer_update_led(){
    // Utiliza o WRAP do Buzzer B para definir o LEVEL do LED
    pwm_set_chan_level(slice_num_b, channel_b==0?1:0, ((uint32_t)(wrapper_b + 1) * level_led) / 255);
}

// Ativa um buzzer com uma BUZZER_NOTE
void buzzer_set(BUZZER buzzer, BUZZER_NOTE note){
    if((buzzer == BUZZER_B)&&(buzzer_b_disabled)) return;
    uint16_t wrapper;
    uint16_t level;
    switch(note){
        case OFF: wrapper = 2272; level =    0; break; 
        case DO:  wrapper = 3821; level = 1911; break; 
        case RE:  wrapper = 3404; level = 1703; break; 
        case MI:  wrapper = 3033; level = 1517; break; 
        case FA:  wrapper = 2862; level = 1432; break; 
        case SOL: wrapper = 2550; level = 1276; break; 
        case LA : wrapper = 2272; level = 1137; break; 
        case SI:  wrapper = 2024; level = 1013; break; 
    }

    if (buzzer == BUZZER_A){
        pwm_set_wrap(      slice_num_a, wrapper);
        pwm_set_chan_level(slice_num_a, channel_a, level);
    }else{
        pwm_set_wrap(      slice_num_b, wrapper);
        pwm_set_chan_level(slice_num_b, channel_b, level);
        wrapper_b = wrapper;
        if(level_led >= 0) buzzer_update_led();
    }
}

// Ativa um buzzer com uma frequência específica, 0 ==> desligado
void buzzer_set_freq(BUZZER buzzer, uint16_t freq){
    if((buzzer == BUZZER_B)&&(buzzer_b_disabled)) return;

    if(freq == 0){
        if (buzzer == BUZZER_A){
            pwm_set_chan_level(slice_num_a, channel_a, 0);
        }else{
            pwm_set_chan_level(slice_num_b, channel_b, 0);
        }
        return;
    }

    // fosck = 1MHz 
    // Wrap  =      1  ==> count = 2       ==> fmax = 500kHz
    // Wrap  = 0xFFFF  ==> count = 0x10000 ==> fmax = 15,3Hz

    if(freq <    20) freq =    20;
    if(freq > 20000) freq = 20000;
    uint16_t count = (1000000 / freq);

    if (buzzer == BUZZER_A){
        pwm_set_wrap(      slice_num_a, count-1);
        pwm_set_chan_level(slice_num_a, channel_a, count >> 1);
    }else{
        pwm_set_wrap(      slice_num_b, count-1);
        pwm_set_chan_level(slice_num_b, channel_b, count >> 1);
        wrapper_b = count-1;
        if(level_led >= 0) buzzer_update_led();
    }
}

// Caso se utiliza o LED G e o Buzzer B, 
// essa função faz com que o nível do LED seja controlada pelo módulo do buzzer
// Evitando conflitos
void buzzer_set_led(uint8_t led_level){
    level_led = led_level;
    buzzer_update_led();
}

 // Toca uma escala musical
void buzzer_scale(BUZZER buzzer, uint32_t delay_ms){
    if((buzzer == BUZZER_B)&&(buzzer_b_disabled)) return;
    printf("Do\n");
    buzzer_set(buzzer, DO );
    sleep_ms(delay_ms);
    printf("Re\n");
    buzzer_set(buzzer, RE );
    sleep_ms(delay_ms);
    printf("Mi\n");
    buzzer_set(buzzer, MI );
    sleep_ms(delay_ms);
    printf("FA\n");
    buzzer_set(buzzer, FA );
    sleep_ms(delay_ms);
    printf("Sol\n");
    buzzer_set(buzzer, SOL);
    sleep_ms(delay_ms);
    printf("La\n");
    buzzer_set(buzzer, LA );
    sleep_ms(delay_ms);
    printf("Si\n");
    buzzer_set(buzzer, SI );
    sleep_ms(delay_ms);
    printf("OFF\n");
    buzzer_set(buzzer, OFF);
    sleep_ms(delay_ms);
}

// Rotina para testar os Buzzzers
void buzzers_test(){
    buzzers_init(false);
    buzzer_set(BUZZER_A, OFF);
    buzzer_set(BUZZER_B, OFF);
    printf("Inicio do teste dos buzzers, ambos estão desligado\n");

    printf("Teste do buzzer A, tocando escala de DO a SI\n");
    buzzer_scale(BUZZER_A, BUZZER_DELAY_MS);

    printf("Teste do buzzer B, tocando escala de DO a SI\n");
    buzzer_scale(BUZZER_B, BUZZER_DELAY_MS);

    printf("Concluído teste dos buzzers, ambos estão desligado\n");
}   
