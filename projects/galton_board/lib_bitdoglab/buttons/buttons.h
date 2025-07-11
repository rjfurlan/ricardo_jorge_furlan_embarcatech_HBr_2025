#ifndef BUTTONS_H
#define BUTTONS_H

#include "../board_config.h"

typedef enum {
    NO_CLEAR,           // Não muda o número de clicks
    CLEAR_ONLY_ONE,     // caso haja clicks, desconta apenas um
    CLEAR_ALL           // caso haja clicks, desconta todos
} BUTTON_CLEAR_MODE;

// Inicializa os botões, configurando as GPIOs e definindo as interrupções para tratamento dos clicks
void    buttons_init();

// Retorna o número de clicks no botão e remove os clicks conforme o BUTTON_CLEAR_MODE
int32_t button_n_clicks(          Button button, BUTTON_CLEAR_MODE clear_mode);

// Retorna o estado do botão baseado apenas no estado atual da GPIO correspondente
bool    button_pressed(           Button button);

// Retorna se o botão foi previamente clicado ou se continua pressionado
bool    button_clicked_or_pressed(Button button);

// Faz uma sequencia de testes com cada um dos botões
void    buttons_test();

#endif // BUTTONS_H