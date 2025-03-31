#ifndef MSGS_DEF
#define MSGS_DEF

typedef struct{
    bool     read;
    bool     high;
    uint64_t t_us;      // momento em que a mensagem foi recebida ou enviada
    char     msg[48+1];
} MSG_TYPE;

// Mensagem que o Navegador (page) enviou para o dispositivo IoT
extern MSG_TYPE msg_page_send;

// Mensagem que o Navegador (page) recebeu do dispositivo IoT
extern MSG_TYPE msg_page_received;


#endif