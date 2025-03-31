#ifndef ADS_DEF
#define ADS_DEF

typedef enum {
    AD_JOYSTICK_X,
    AD_JOYSTICK_Y,
    AD_VSYS_1_3,
    AD_TEMP
} AD;

void     ads_init();                    // Inicializa o módulo ADC do Raspberry Pi Pico e habilita o sensor de temperatura interno
uint16_t ads_get(AD);                   // Configura a canal do AD e só retorna após a leitura
void     ads_test();                    // Simples teste que mostra em looping a leitura dos diversos canais do AD
int32_t  ads_get_temp_deci_celsius();   // Retorna a temperatura do sensor interno a RP2040

#endif