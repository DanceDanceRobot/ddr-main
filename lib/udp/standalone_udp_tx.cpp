#include "standalone_udp_tx.hpp"

void StdAlnUdpTx::init(){
  WiFi.begin(ssid,password);
  WiFi_flg_ = true;
  while (WiFi.status() != WL_CONNECTED){
    static int i = 0;
    i++;
    if(i>100){
      WiFi_flg_ = false;
      break;
    }
    delay(100);  
  }
  if(WiFi_flg_ == true){
    udp.begin(kLocalPort);
  }
}

bool StdAlnUdpTx::get_wifi_flg(){
  return WiFi_flg_;
}

void StdAlnUdpTx::write(const ConnectionData& data){
  if(WiFi_flg_ == true){
    uint8_t send_data = data.serialize();
    udp.beginPacket(kRemoteIpadr, kRemotePort);
    udp.write(send_data);
    udp.endPacket();
  }
}