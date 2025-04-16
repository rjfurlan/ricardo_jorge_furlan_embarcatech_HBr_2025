#ifndef ADS_DEF
#define ADS_DEF

typedef enum {
    AD_JOYSTICK_X,
    AD_JOYSTICK_Y,
    AD_VSYS_1_3,
    AD_TEMP
} AdChannel;

void     ads_init(bool enable_temp_sensor, bool enable_read_VSYS);  // Inicializa o módulo ADC do Raspberry Pi Pico e
                                                                    // habilita a lentura do sensor de temperatura interno e o VSYS
uint16_t ads_get(AdChannel);                                        // Configura a canal do AD e só retorna após a leitura
void     ads_test();                                                // Simples teste que mostra em looping a leitura dos diversos canais do AD
int32_t  conv_ad_to_deci_celsius(uint16_t ad_value);                // Converte o valor AD em temperatura, em Celsius
int32_t  ads_get_temp_deci_celsius();                               // Retorna a temperatura, em Celsius, do sensor interno a RP2040

#endif