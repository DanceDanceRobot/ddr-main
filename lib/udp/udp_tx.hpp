#pragma once 

#include "WiFi.h"
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include "connection_data.hpp"

class UdpTx{
private: 
    static constexpr char * ssid = "Tiger-s.b";
    static constexpr char * password = "516a6a9041c41";
    static constexpr int Remote_Port = 9000;        // Destination port
    static constexpr int Org_Port = 9000;           // Source port
protected:
    WiFiUDP udp;
public:
    UdpTx(void){}
    virtual void init(void);
    virtual void write(const ConnectionData&);
};