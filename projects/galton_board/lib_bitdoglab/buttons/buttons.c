#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

#include "buttons.h"

#define BUTTON_DEBOUNCE_TIME_US          50000  // 50 ms

// ---------- Captura Clicks no botão com debounce ----------
static volatile int button_a_n_clicks = 0;
static volatile int button_b_n_clicks = 0;
static volatile int button_c_j_clicks = 0;

// tratamento do debounce, se o botão está pressionado após o período de debounce ele é considerado  que foi pressionado
int64_t debounce_alarm_button_a(alarm_id_t id, void *user_data){
    if(!gpio_get(GPIO_BUTTON_A)) button_a_n_clicks++;
    gpio_set_irq_enabled(GPIO_BUTTON_A, GPIO_IRQ_EDGE_FALL, true);
    return 0;
}
// tratamento do debounce, se o botão está pressionado após o período de debounce ele é considerado  que foi pressionado
int64_t debounce_alarm_button_b(alarm_id_t id, void *user_data){
    if(!gpio_get(GPIO_BUTTON_B)) button_b_n_clicks++;
    gpio_set_irq_enabled(GPIO_BUTTON_B, GPIO_IRQ_EDGE_FALL, true);
    return 0;
}
// tratamento do debounce, se o botão está pressionado após o período de debounce ele é considerado  que foi pressionado
int64_t debounce_alarm_button_j(alarm_id_t id, void *user_data){
    if(!gpio_get(GPIO_JOYSTICK_BUTTON)) button_c_j_clicks++;
    gpio_set_irq_enabled(GPIO_JOYSTICK_BUTTON, GPIO_IRQ_EDGE_FALL, true);
    return 0;
}
void irq_button_a_b_j(uint gpio, uint32_t event_mask){
    // Ao detectar o Edge Fall do botão, que pode ser que o botão foi pressionado ou um bounce, 
    // ativa um timer para analisar o estado do botão após o período de Debounce para considerar se ele foi realmente pressionado ou não
    // Obs.: Durante o período de debounde novas interrupções do botão são bloqueadas, isso se o alarme de debounce conseguiu ser ativado
    if(gpio == GPIO_BUTTON_A){
        alarm_id_t id = add_alarm_in_us(BUTTON_DEBOUNCE_TIME_US, debounce_alarm_button_a, NULL, false);
        if(id > 0){
            gpio_set_irq_enabled(GPIO_BUTTON_A, GPIO_IRQ_EDGE_FALL, false);
        }
    }else if(gpio == GPIO_BUTTON_B){
        alarm_id_t id = add_alarm_in_us(BUTTON_DEBOUNCE_TIME_US, debounce_alarm_button_b, NULL, false);
        if(id > 0){
            gpio_set_irq_enabled(GPIO_BUTTON_B, GPIO_IRQ_EDGE_FALL, false);
        }
    }else if(gpio == GPIO_JOYSTICK_BUTTON){
        alarm_id_t id = add_alarm_in_us(BUTTON_DEBOUNCE_TIME_US, debounce_alarm_button_j, NULL, false);
        if(id > 0){
            gpio_set_irq_enabled(GPIO_JOYSTICK_BUTTON, GPIO_IRQ_EDGE_FALL, false);
        }
    }
}

// Inicializa os botões, configurando as GPIOs e definindo as interrupções para tratamento dos clicks
void    buttons_init(){
        // ---------- Configuração dos botões A, B e C (Joystick) ----------
    gpio_pull_up(     GPIO_BUTTON_A);
    gpio_set_dir(     GPIO_BUTTON_A,        GPIO_IN);
    gpio_set_function(GPIO_BUTTON_A,        GPIO_FUNC_SIO);
    gpio_pull_up(     GPIO_BUTTON_B);
    gpio_set_dir(     GPIO_BUTTON_B,        GPIO_IN);
    gpio_set_function(GPIO_BUTTON_B,        GPIO_FUNC_SIO);
    gpio_pull_up(     GPIO_JOYSTICK_BUTTON);
    gpio_set_dir(     GPIO_JOYSTICK_BUTTON, GPIO_IN);
    gpio_set_function(GPIO_JOYSTICK_BUTTON, GPIO_FUNC_SIO);

    gpio_set_irq_callback(irq_button_a_b_j);
    gpio_set_irq_enabled(GPIO_BUTTON_A,        GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(GPIO_BUTTON_B,        GPIO_IRQ_EDGE_FALL, true);
    gpio_set_irq_enabled(GPIO_JOYSTICK_BUTTON, GPIO_IRQ_EDGE_FALL, true);

    sleep_us(BUTTON_DEBOUNCE_TIME_US);   // Para garantir que os Pull UP já estão efetivos
    irq_set_enabled(IO_IRQ_BANK0, true);
}

// Retorna o número de clicks no botão e remove os clicks conforme o BUTTON_CLEAR_MODE
int32_t button_n_clicks(Button button,BUTTON_CLEAR_MODE clear_mode){
    int32_t ret;
    if(button == BUTTON_A){
        ret = button_a_n_clicks;
        switch(clear_mode){
            case NO_CLEAR: break;
            case CLEAR_ONLY_ONE:
                if(button_a_n_clicks > 0) button_a_n_clicks--;
                break;
            case CLEAR_ALL:
                button_a_n_clicks = 0;
                break;
        }
    }else if(button == BUTTON_B){
        ret = button_b_n_clicks;
        switch(clear_mode){
            case NO_CLEAR: break;
            case CLEAR_ONLY_ONE:
                if(button_b_n_clicks > 0) button_b_n_clicks--;
                break;
            case CLEAR_ALL:
                button_b_n_clicks = 0;
                break;
        }
    }else if(button == BUTTON_JOYSTICK){
        ret = button_c_j_clicks;
        switch(clear_mode){
            case NO_CLEAR: break;
            case CLEAR_ONLY_ONE:
                if(button_c_j_clicks > 0) button_c_j_clicks--;
                break;
            case CLEAR_ALL:
                button_c_j_clicks = 0;
                break;
        }
    } else{
        ret = -1;
    }
    return ret;
}

// Retorna o estado do botão baseado apenas no estado atual da GPIO correspondente
bool button_pressed(Button button){
    return !gpio_get(button);
}

// Retorna se o botão foi previamente clicado ou se continua pressionado
bool button_clicked_or_pressed(Button button){
    return (button_n_clicks(button, CLEAR_ALL) > 0) || button_pressed(button);
}

static uint32_t last_n_clicks_a;
static uint32_t last_n_clicks_b;
static uint32_t last_n_clicks_j;
static void buttons_test_changed(){
    last_n_clicks_a = button_a_n_clicks;
    last_n_clicks_b = button_b_n_clicks;
    last_n_clicks_j = button_c_j_clicks;

    while((last_n_clicks_a == button_a_n_clicks)&&(last_n_clicks_b == button_b_n_clicks)&&(last_n_clicks_j == button_c_j_clicks)){
        sleep_us(1000);
    }
}

static void  button_test_button(char button_c, Button button){
    printf("Testes dos botão %c\n", button_c);
    printf("número de clicks atuais: %d\n\n", button_n_clicks(button, NO_CLEAR));
    printf("Click no botão %c\n", button_c);
    buttons_test_changed();
    printf("número de clicks atuais: %d (esperado 1)\n\n", button_n_clicks(button, NO_CLEAR));
    printf("Click no botão %c\n", button_c);
    buttons_test_changed();
    printf("número de clicks atuais: %d (esperado 2)\n\n", button_n_clicks(button, NO_CLEAR));
    printf("Click no botão %c\n", button_c);
    buttons_test_changed();
    printf("número de clicks atuais: %d (esperado 3)\n\n", button_n_clicks(button, NO_CLEAR));
    printf("Click no botão %c\n", button_c);
    buttons_test_changed();
    printf("número de clicks atuais: %d (esperado 4)\n\n", button_n_clicks(button, NO_CLEAR));
    printf("número de clicks atuais: %d (esperado 4), leitura com remoção de 1\n", button_n_clicks(button, CLEAR_ONLY_ONE));
    printf("número de clicks atuais: %d (esperado 3)\n\n", button_n_clicks(button, NO_CLEAR));
    printf("número de clicks atuais: %d (esperado 3), leitura com remoção de ALL\n", button_n_clicks(button, CLEAR_ALL));
    printf("número de clicks atuais: %d (esperado 0)\n\n", button_n_clicks(button, NO_CLEAR));
    printf("número de clicks atuais: %d (esperado 0), leitura com remoção de 1\n", button_n_clicks(button, CLEAR_ONLY_ONE));
    printf("número de clicks atuais: %d (esperado 0)\n\n", button_n_clicks(button, NO_CLEAR));
}

// Faz uma sequencia de testes com cada um dos botões
void    buttons_test(){
    printf("Iniciando Testes dos botões\n\n");
    buttons_init();
    button_test_button('A', BUTTON_A);
    button_test_button('B', BUTTON_B);
    button_test_button('J', BUTTON_JOYSTICK);
    printf("Fim de teste dos botões\n\n");
}