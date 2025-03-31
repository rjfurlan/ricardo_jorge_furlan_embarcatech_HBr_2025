#include "pico/stdlib.h"
#include "Config.h"
#include "UiConnection.h"


static UI_CONNECTION_STATE ui_connection_state;
static uint64_t            ui_connection_last_refresh_us;

// Inicializa o gerenciado de estado da conexão
void ui_connection_init(){
    ui_connection_state           = NO_CONNECTION;
    ui_connection_last_refresh_us = 0;
}


// Executa o refresh do estado da comunicação, baseado no estado atual e Timeout
// retorna o estado atualizado
UI_CONNECTION_STATE ui_connection_get(){    
    if(ui_connection_state == UPDATED){
        if(time_us_64() > (ui_connection_last_refresh_us + UI_CONNECTION_MAX_DELAY_US))
            ui_connection_state = CONNECTED;
    }
    return ui_connection_state;
}


// Esta função ao ser chamada informa que houve alteração do estado da conexão ou um update da mesma
// retorna o estado atualizado
UI_CONNECTION_STATE ui_connection_update(UI_CONNECTION_STATE state){
    if(state == UPDATED){
        if(ui_connection_state != NO_CONNECTION){
            ui_connection_state = UPDATED;
            ui_connection_last_refresh_us = time_us_64();
        }
    } else ui_connection_state = state;
    return ui_connection_state;
}

