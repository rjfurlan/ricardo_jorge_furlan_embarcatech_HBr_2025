#ifndef HTML_PAGE01_DEF
#define HTML_PAGE01_DEF


// Coloca no buffer um Html toda a página HTML
// Retorna o número de bytes que foram colocados no buffer
uint32_t htlm_page01_full(  struct tcp_pcb *tpcb, char *buffer, uint32_t buffer_size);

// Coloca no buffer um Html com o JSON de update da página
// Retorna o número de bytes que foram colocados no buffer
uint32_t htlm_page01_update(struct tcp_pcb *tpcb, char *buffer, uint32_t buffer_size);

# endif