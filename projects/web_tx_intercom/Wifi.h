#ifndef WIFI_DEF
#define WIFI_DEF

// Inicializa o Radio WiFI para Station mode
void     wifi_init();

// Tenta fazer uma conexão com o roteador, o parâmetro attempts só tem efeito para debug
// retorno o IP se conectou ou 0 se não conectou
uint32_t wifi_connect(uint16_t attempts);

// Informa se a conexão está ativa
bool     wifi_connected();

#endif