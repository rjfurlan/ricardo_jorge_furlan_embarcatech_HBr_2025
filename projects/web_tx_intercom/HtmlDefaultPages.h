#ifndef HTML_DEFAULT_PAGES_DEF
#define HTML_DEFAULT_PAGES_DEF

// Retorna um string com um HTML de uma página de erro, 404
char *   htlm_error_page();

// Coloca no buffer um Html com um icone vazio, tamanho zero
// Retorna o número de bytes que foram colocados no buffer
uint32_t htlm_favicon_null(char *buffer, uint32_t buffer_size);

// Coloca no buffer um Html com um icone utilizado neste sistema
// Retorna o número de bytes que foram colocados no buffer
uint32_t htlm_favicon_page(char *buffer, uint32_t buffer_size);


#endif