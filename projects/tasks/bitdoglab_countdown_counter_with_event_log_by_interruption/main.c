#include <stdio.h>
#include "pico/stdlib.h"
#include "libs/display.h"
#include "libs/i2c.h"
#include "libs/bitdoglab_defs.h"

volatile bool start    = false;
volatile int  b_clicks = 0;

void irq_button_a_b(uint gpio, uint32_t event_mask){
    if(gpio == BITDOGLAB_GPIO_BUTTON_A){
        start = true;
    } else if(gpio == BITDOGLAB_GPIO_BUTTON_B){
        b_clicks++;
    }    
}    

int main()
{
    stdio_init_all();
    sleep_ms(1000);
    printf("BitDogLab - CountDown Counter With Event Log By Interruption\n");

    // Init OLED-Display
    i2c_bitdoglab_init();
    display_init();

    // configure the buttons to generate interrupts
    gpio_init(   BITDOGLAB_GPIO_BUTTON_A);
    gpio_init(   BITDOGLAB_GPIO_BUTTON_B);
    gpio_pull_up(BITDOGLAB_GPIO_BUTTON_A);
    gpio_pull_up(BITDOGLAB_GPIO_BUTTON_B);
    gpio_set_irq_callback(irq_button_a_b);
    gpio_set_irq_enabled(BITDOGLAB_GPIO_BUTTON_A, GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(BITDOGLAB_GPIO_BUTTON_B, GPIO_IRQ_EDGE_FALL, true);

    display_fill(false, false);
    display_msg( false, 3, 0, "BITDOGLAB");
    display_msg( false, 3, 2, "COUNTDOWN");
    display_msg( false, 2, 3, "COUNTER WITH");
    display_msg( false, 2, 4, "EVENT LOG BY");
    display_msg( false, 2, 5, "INTERRUPTION");
    display_update();
    sleep_ms(5000);

    irq_set_enabled(IO_IRQ_BANK0, true);

    while (true) {
        if(start){
            int time_count = 9;
        
            int last_b_clicks = 0;
            b_clicks = 0;

            bool update = true;
            uint64_t t0 = time_us_64() + 1000000;
            while (time_count > 0){
                if(last_b_clicks != b_clicks){
                    last_b_clicks = b_clicks;
                    update = true;
                }
                if(time_us_64() >= t0){
                    time_count--;
                    update = true;
                    t0 += 1000000;
                }

                if(update){
                    char msg_time[8]     = {0};
                    char msg_b_clicks[8] = {0};

                    update = false;

                    sprintf(msg_time,     "%d", time_count);
                    sprintf(msg_b_clicks, "%d", b_clicks);

                    display_fill(false, false);
                    display_msg( false,  0, 0, "COUNTDOWN: ");
                    display_msg( false, 11, 0, msg_time);
                    display_msg( false,  0, 6, "BUTTON B");
                    display_msg( false,  3, 7, "CLICKS:");
                    display_msg( false, 11, 7, msg_b_clicks);
                                            
                    display_update();

                    printf("Countdown = %d, Button B Clicks = %d\n", time_count, b_clicks);
                }
            }
            start = false;
        }
        sleep_ms(1);
    }
}

