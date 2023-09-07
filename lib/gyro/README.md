# ジャイロセンサ制御クラス  

基本的には秋月のサンプルコードを書き換えただけなので  

## xyz_t  

xyzデータをまとめて扱いたいので定義しておいた  

```c
struct xyz_t{
    float x;
    float y;
    float z;
};
```

## サンプルコード

```c
//I2Cを使うので
#include <Wire.h>

//インスタンス生成
//arduinoのI2Cインスタンスをぶち込もう
BMX055 gyro_sens(Wire);

//初期化
//必ずWire.begin()を実行してから
Wire.begin();
gyro_sens.init();


//加速度センサ値取得
xyz_t data = gyro_sens.read_acc();
Serial.printf("%f,%f,%f,",data.x,data.y,data.z);

//ジャイロセンサ値取得
data = gyro_sens.read_gyro();
Serial.printf("%f,%f,%f,",data.x,data.y,data.z);

//磁気センサ値取得  
data = gyro_sens.read_mag();
Serial.printf("%f,%f,%f\r\n",data.x,data.y,data.z);
```