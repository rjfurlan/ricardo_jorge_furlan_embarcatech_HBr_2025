#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#include "libs/BitDogLab_Defs.h"
#include "Ads.h"

 // Inicializa o módulo ADC do Raspberry Pi Pico e habilita o sensor de temperatura interno
void     ads_init(){
    adc_init();                                 // Inicializa o módulo ADC do Raspberry Pi Pico
    adc_set_temp_sensor_enabled(true);          // Habilita o sensor de temperatura interno
    //gpio_pull_up(25);                         // para poder funcionar AD_VSYS_1_3
}

// Configura a canal do AD e só retorna após a leitura
uint16_t ads_get(AD ad){
    // Select INPUT
    switch (ad) {
        case AD_JOYSTICK_X: adc_select_input(BITDOGLAB_AD_JOYSTICK_X); break;
        case AD_JOYSTICK_Y: adc_select_input(BITDOGLAB_AD_JOYSTICK_Y); break;
        case AD_TEMP:       adc_select_input(BITDOGLAB_AD_TEMP);       break;
        case AD_VSYS_1_3:   adc_select_input(BITDOGLAB_AD_VSYS_1_3);   break;
    }
    sleep_us(2);
    return adc_read();
}

static int32_t conv_ad_to_deci_celsius(uint16_t ad){
    const float A = -3.3 / (1u << 12) / 0.001721;
    const float B = 27.0 + (0.706 / 0.001721);
    return (ad * A + B) * 10.0;
}
// Retorna a temperatura do sensor interno a RP2040
int32_t  ads_get_temp_deci_celsius(){
    return conv_ad_to_deci_celsius(ads_get(AD_TEMP));
}

// Simples teste que mostra em looping a leitura dos diversos canais do AD
void     ads_test(){
    printf("Iniciando testes dos Ads\n"); 
    ads_init();

    int32_t count = 0;
    while(1){
        uint16_t ad_temp     = ads_get(AD_TEMP);
        uint16_t ad_vsys_1_3 = ads_get(AD_VSYS_1_3);
        printf("%4d: x=%4d  y=%4d  tmp=%5.1f Celsius (%4d)  VSys=%4.2f Volts (%4d)\n", 
                ++count,
                ads_get(AD_JOYSTICK_X),
                ads_get(AD_JOYSTICK_Y),
                ads_get_temp_deci_celsius(ad_temp) * 0.1,
                ad_temp,
                3.3 / 4096 * ad_vsys_1_3 * 3.0,
                ad_vsys_1_3);
    }
}