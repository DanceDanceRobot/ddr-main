#pragma once 
#pragma once 

#include "WiFi.h"
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include "connection_data.hpp"

class UdpRx{
private: 
    static constexpr char * ssid = "Tiger-s.b";
    static constexpr char * password = "516a6a9041c41";
    static constexpr int Remote_Port = 9000;        // Destination port
    static constexpr int Org_Port = 9000;           // Source port
    WiFiUDP udp;
    bool updated_;
    ConnectionData data_;
public:
    UdpRx(void){}

    void init(void);
    void update(void);
    bool is_updated(void);
    ConnectionData read(void);
};