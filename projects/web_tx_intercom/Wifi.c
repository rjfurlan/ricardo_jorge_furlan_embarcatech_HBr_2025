#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"    // necessita lwipopts.h
#include "libs/WebUtils.h"
#include "Config.h"
#include "Led.h"
#include "Wifi.h"

// Faz um print report da conexão
static void wifi_connection_info(uint8_t net_number){
    uint8_t *ip_addr = (uint8_t*)&(cyw43_state.netif[net_number].ip_addr.addr);
    uint8_t *netmask = (uint8_t*)&(cyw43_state.netif[net_number].netmask.addr);
    uint8_t *gw      = (uint8_t*)&(cyw43_state.netif[net_number].gw.addr);
    printf("WiFi - netif[%d]:\n",net_number);
    printf("        - Endereço IP Address: %3d.%3d.%3d.%3d\n", ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
    printf("        - Endereço Net Mask  : %3d.%3d.%3d.%3d\n", netmask[0], netmask[1], netmask[2], netmask[3]);
    printf("        - Endereço Gateway   : %3d.%3d.%3d.%3d\n",      gw[0],      gw[1],      gw[2],      gw[3]);
}

// Inicializa o Radio WiFI para Station mode
void wifi_init(){
    if(WIFI_REPORT) printf("WiFi - Iniciando Radio CYW43\n");
    if (cyw43_arch_init()) {
        printf("WiFi - Erro na inicialização do CYW43n");
        return;
    }
    sleep_ms(10);
    if(WIFI_REPORT) printf("WiFi - Habilitando radio para STA (Station) mode\n");
    cyw43_arch_enable_sta_mode();           // com esse não roda na RAW
    sleep_ms(10);
}


// Tenta fazer uma conexão com o roteador, o parâmetro attempts só tem efeito para debug
// retorno o IP se conectou ou 0 se não conectou
uint32_t wifi_connect(uint16_t attempts){
    if(WIFI_REPORT) printf("WiFi - Tentando conectar em: %s, pela %d vez(es)\n", WIFI_SSID, attempts);

    /* Connect to the WiFI network - loop until connected
       Tipos de autenticação possíveis:
            CYW43_AUTH_OPEN (0)                                    ///< No authorisation required (open)
            CYW43_AUTH_WPA_TKIP_PSK      (0x00200002)              ///< WPA authorisation
            CYW43_AUTH_WPA2_AES_PSK      (0x00400004)              ///< WPA2 authorisation (preferred)
            CYW43_AUTH_WPA2_MIXED_PSK    (0x00400006)              ///< WPA2/WPA mixed authorisation
            CYW43_AUTH_WPA3_SAE_AES_PSK  (0x01000004)              ///< WPA3 AES authorisation
            CYW43_AUTH_WPA3_WPA2_AES_PSK (0x01400004)fsdata_file   ///< WPA2/WPA3 authorisation   
    */
    int ret = cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS, CYW43_AUTH_WPA2_AES_PSK, WIFI_TIMEOUT_CONECTION_MS);
    if(ret==0){
        uint32_t ip = (uint32_t)(cyw43_state.netif[0].ip_addr.addr);
        if(WIFI_REPORT){
            char buffer[16];
            printf("WiFi - %s - Conectado com %d tentativas com IP: %s\n", WIFI_SSID, attempts, ip_string(buffer, 16, ip));
            wifi_connection_info(0);
            wifi_connection_info(1);
        }
        return ip;
    }
    return 0;       // IP = 0 ==> Não conectado
}    

// Informa se a conexão está ativa
bool wifi_connected(){
    return (cyw43_tcpip_link_status(&cyw43_state, CYW43_ITF_STA) == CYW43_LINK_UP);
}    