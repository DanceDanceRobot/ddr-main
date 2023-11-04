#pragma once
#include <string>
#include "udp_tx.hpp"
#include "connection_data.hpp"

class StdAlnUdpTx : public UdpTx
{
public:
  void init();
  bool get_wifi_flg();
  void write(const ConnectionData& data);

private:
  static constexpr char * ssid = "Controller_2";
  static constexpr char * password = "toyota471";
  static constexpr int kRemotePort = 9000; // 送信先
  static constexpr char *kRemoteIpadr = "192.168.4.2"; // 送信先
  static constexpr int kLocalPort = 5000; // 自身
  bool WiFi_flg_;
};