# ⚠ Disclaimer
# THE SOFTWARE IS PROVIDED "AS IS", USE AT YOUR OWN RISK
# O SOFTWARE É FORNECIDO "COMO ESTÁ", USE POR SUA CONTA E RISCO
 
### This code was developed for educational purposes as a task for phase 2, residency, of the EmbarcaTech professional training program, with the aim of demonstrating some points learned during the residency.


## The objective of this exercise is to remodel a simple example program into a proposed modular architecture.  


## code provided:

    #include "pico/stdlib.h"
    #include "pico/cyw43_arch.h"

    int main() {
        stdio_init_all();
        if (cyw43_arch_init()) {
            return -1;
        }

        while (true) {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            sleep_ms(500);
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
            sleep_ms(500);
        }
    }


## Proposed modular architecture
	projeto/
	├── app/
	│   └── main.c
	├── drivers/
	│   └── led_embutido.c
	├── hal/
	│   └── hal_led.c
	├── include/
	│   ├── led_embutido.h
	│   └── hal_led.h
	└── CMakeLists.txt
