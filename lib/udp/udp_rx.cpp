#include "udp_rx.hpp"

void UdpRx::init(void){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
    MDNS.begin("UDP_Client00");
    udp.begin(Org_Port);
}

void UdpRx::update(void){
    uint8_t read_data;
    if (udp.parsePacket() > 0){
        udp.read(&read_data,sizeof(&read_data));
        udp.flush();
        updated_ = true;
        data_.deserialize(read_data);
    }
}

bool UdpRx::is_updated(void){
    return updated_;
}

ConnectionData UdpRx::read(void){
    updated_ = false;
    return data_;
}

