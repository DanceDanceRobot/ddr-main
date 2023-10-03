#include "standalone_udp_rx.hpp"

void StdAlnUdpRx::init(){
  WiFi.softAP(ssid,password);
  delay(100);
  WiFi.softAPConfig(ip,gateway,subnet);

  udp.begin(klocalPort);
}

// void StdAlnUdpRx::update(){
//   if(udp.parsePacket() > 0){ // 受信してない時、packetsize=0(らしい)
//     packet_buffer = 0;
//     udp.read(packet_buffer,sizeof(ConnectionData::Data));
//     Serial.println(packet_buffer);
//     data_ = ConnectionData::deserialize(packet_buffer);
//     updated_ = true;
//   }
// }