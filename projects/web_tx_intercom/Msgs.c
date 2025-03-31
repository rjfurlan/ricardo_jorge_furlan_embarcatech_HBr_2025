#include "pico/stdlib.h"
#include "Msgs.h"

// Mensagem que o Navegador (page) enviou para o dispositivo IoT
MSG_TYPE msg_page_send     = {true, false, 0, ""};

// Mensagem que o Navegador (page) recebeu do dispositivo IoT
MSG_TYPE msg_page_received = {true, false, 0, "Nenhum mensagem ainda recebida"};
