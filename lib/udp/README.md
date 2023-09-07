## UdpTxクラス  

UDP通信の送信を行うためのクラス  

### サンプルコード

```c
//インスタンス生成
UdpTx udp_tx();

//Udp初期設定　wifiに繋げる
//setup関数内におくといいと思われ
udp_tx.init();

//送信
//ConnectionData classに送信データを書き込んで
//write関数で送信
ConnectionData data();
data.reset();
data.up();
udp_tx.write(data);
```

## UdpRxクラス  

UDP通信の受信を行うためのクラス 

```c
//インスタンス生成
UdpRx udp_rx();

//Udp初期設定　wifiに繋げる
//setup関数内におくといいと思われ
udp_rx.init();

//受信
//update関数を送信と同じ周期で呼び出す
//timer割り込みなどを使うべきかも
udp_rx.update();

ConnectionData data();
//データが更新されているか確認
//戻り値がtrueだったら更新されている
if(udp_rx.is_updated()){
    data = udp_rx.read();
    // 受信した後の処理
};

```

## ConnectionDataクラス

送受信するデータを管理するクラス

```c
//インスタンス生成
ConnectionData data();

// データの初期化(すべて0)
data.reset();
// upのフラグを上げる
data.up();

data.r_turn();

//ConnectionDataクラスをuint8_tに変換する。
uint8_t write_data;
data.serialize(write_data);

// uint8_tをConnectionDataクラスに変換する。
uint8_t read_data;
data.deserialize(read_data);
```