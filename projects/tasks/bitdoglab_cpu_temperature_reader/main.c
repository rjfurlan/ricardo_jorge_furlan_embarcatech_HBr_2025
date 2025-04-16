#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "libs/ads.h"
#include "libs/display.h"
#include "libs/i2c.h"



int main()
{
    stdio_init_all();
    printf("BitDogLab - CPU Temperature\n");
   
    // Init OLED-Display
    i2c_bitdoglab_init();
    display_init();

    // Init Temperature AD
    ads_init(true, false);

    display_fill(false, false);
    display_msg( false, 3, 1, "BITDOGLAB");
    display_msg( false, 0, 3, "CPU TEMPERATURE");
    display_update();
    sleep_ms(5000);

    uint32_t count = 0;
    while (true) {
        char * working;
        char value[    17] = {0};
        char value_ad [17] = {0};

        switch(count & 0x03){
            case 0: working = "|";  break;
            case 1: working = "/";  break;
            case 2: working = "-";  break;
            case 3: working = "\\"; break;
        }

        // read Joystick-AD
        uint16_t ad_temp = ads_get(AD_TEMP);
        int32_t  temp_dec_celsius = conv_ad_to_deci_celsius(ad_temp);

        // show Data
        sprintf(value,    "%02d", temp_dec_celsius);
        int len = strlen(value);
        value[len] = value[len-1];
        value[len-1] = '.';

        sprintf(value_ad, "AD: 0x%03X", ad_temp);

        display_fill(false, false);
        display_msg( false, 0, 0, "CPU TEMPERATURE");
        display_msg( false, 7-len, 3, value);
        display_msg( false, 9, 3, "Celsius");
        display_msg( false, 7, 5, value_ad);
        display_msg( false, 0, 7, working);
        display_update();
        printf("%4d %s: temperature = %s Celsius (ad=%04x)\n", count, working, value, ad_temp);
        sleep_ms(250);
        count++;
    }
}