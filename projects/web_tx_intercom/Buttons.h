#ifndef BUTTONS_DEF
#define BUTTONS_DEF

typedef enum {
    BUTTON_A,
    BUTTON_B,
    BUTTON_C        // Joystick
} BUTTON;

typedef enum {
    NO_CLEAR,           // Não muda o número de clicks
    CLEAR_ONLY_ONE,     // caso haja clicks, desconta apenas um
    CLEAR_ALL           // caso haja clicks, desconta todos
} BUTTON_CLEAR_MODE;

// Inicializa os botões, configurando as GPIOs e definindo as interrupções para tratamento dos clicks
void    buttons_init();

// Retorna o número de clicks no botão e remove os clicks conforme o BUTTON_CLEAR_MODE
int32_t button_n_clicks(          BUTTON button,BUTTON_CLEAR_MODE clear_mode);

// Retorna o estado do botão baseado apenas no estado atual da GPIO correspondente
bool    button_pressed(           BUTTON button);

// Retorna se o botão foi previamente clicado ou se continua pressionado
bool    button_clicked_or_pressed(BUTTON button);

// Faz uma sequencia de testes com cada um dos botões
void    buttons_test();

#endif