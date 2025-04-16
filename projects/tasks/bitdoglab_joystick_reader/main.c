#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "libs/ads.h"
#include "libs/display.h"
#include "libs/i2c.h"
#include "libs/bitdoglab_defs.h"


int main()
{
    stdio_init_all();
    printf("BitDogLab - Joystick Reader\n");

    // Init OLED-Display
    i2c_bitdoglab_init();
    display_init();

    // Init Joystick-AD
    ads_init(false, false);

    display_fill(false, false);
    display_msg( false, 3, 1, "BITDOGLAB");
    display_msg( false, 0, 3, "JOYSTICK READER");
    display_update();
    sleep_ms(5000);

    uint32_t count = 0;
    while (true) {
        char * working;
        char value[    17] = {0};
        char value_hex[17] = {0};

        switch(count & 0x03){
            case 0: working = "|";  break;
            case 1: working = "/";  break;
            case 2: working = "-";  break;
            case 3: working = "\\"; break;
        }

        // read Joystick-AD
        uint16_t x = ads_get(AD_JOYSTICK_X);
        uint16_t y = ads_get(AD_JOYSTICK_Y);

        // show Data
        sprintf(value,     "%4d |  %4d",      x, y);
        sprintf(value_hex, "0x%03X | 0x%03X", x, y);
        display_fill(false, false);
        display_msg( false, 1, 0, "JOYSTICK VALUE");
        display_msg( false, 5, 2,"X |    Y");
        display_msg( false, 2, 4, value);
        display_msg( false, 1, 6, value_hex);
        display_msg( false, 0, 7, working);
        display_update();
        printf("%4d %s: X=0x%04x(%4d), Y=0x%04x(%4d)\n", count, working, x, x, y, y);
        sleep_ms(250);
        count++;
    }
}
