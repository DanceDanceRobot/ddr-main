#include <string.h>
#include "udp_tx.hpp"

void UdpTx::init(void){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
    MDNS.begin("UDP_Client01");
    udp.begin(Org_Port);
}

void UdpTx::write(const ConnectionData& data){
    uint8_t send_data = data.serialize();
    //udp.beginPacket(MDNS.queryHost("UDP_Client00"), Remote_Port);
    udp.beginPacket(MDNS.queryHost("UDP_Client00"), Remote_Port);
    udp.write(send_data);
    udp.endPacket();
    Serial.print("send : ");
    Serial.print(send_data);
    Serial.println();
}