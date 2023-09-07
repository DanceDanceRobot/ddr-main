# モータ制御クラス  

## DRIVER class  

モタドラICを制御するだけのクラス  

### サンプルコード

```c
//インスタンス生成
//driver_pin_t 型で使うピンをぶち込もう
//使うピンはboard_pins.hpp内に定義済み
DRIVER md1(DRIVER1_pin);

//ドライバ初期設定
//setup関数内におくといいと思われ
md1.init();

//過電流保護などのエラーが出たとき  
if(md1.is_error()){
    md1.reset();
}
```

## MOTOR class  

### サンプルコード
```c
//インスタンス生成
//motor_pin_t 型で使うピンをぶち込もう
//使うピンはboard_pins.hpp内に定義済み
//二つ目の引数ははPWM出力時に掛けられる係数的なやつ
//デフォルトで逆転させたければ-1.0f等をぶち込もう
MOTOR motor1(MOTOR1_pin,1.0f);

//ドライバ初期設定
//setup関数内におくといいと思われ
motor1.init();

//一秒正転
//出力は-1.0~1.0で指定
motor1.out(1.0f);
delay(1000);

//一秒停止（ブレーキ状態）
motor1.out(0);
delay(1000);

//一秒逆転
motor1.out(-0.5f); 
delay(1000);

//一秒空転
motor1.free();
delay(1000);
```