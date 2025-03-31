#ifndef UI_CONNECTION_DEF
#define UI_CONNECTION_DEF

#include "UiConnectionType.h"


// Inicializa o gerenciado de estado da conexão
void                ui_connection_init();

// Executa o refresh do estado da comunicação, baseado no estado atual e Timeout
// retorna o estado atualizado
UI_CONNECTION_STATE ui_connection_get();

// Esta função ao ser chamada informa que houve alteração do estado da conexão ou um update da mesma
// retorna o estado atualizado
UI_CONNECTION_STATE ui_connection_update(UI_CONNECTION_STATE state);

#endif