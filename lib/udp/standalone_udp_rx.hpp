#pragma once
#include <string>
#include "udp_rx.hpp"
#include "connection_data.hpp"

class StdAlnUdpRx : public UdpRx
{
public:
  void init(void);
  // void update();
 
private:
  static constexpr char* ssid = "Controller_1";
  static constexpr char* password = "toyota471";
  static constexpr int klocalPort = 9000;
  const IPAddress ip{192,168,4,1};
  const IPAddress gateway{192,168,4,1};
  const IPAddress subnet{255,255,255,0};
};