# ロボット制御クラス  

## ROBO class  

メカナムの計算したりするクラス

コード中の *#debug* ってところ確認して直して

### サンプルコード
動くかは知りません

```c
//インスタンス生成
//モタドラ、モータの初期化をするぞい
ROBO robo();

//角度を取得
__angle__ = robo.get_angle();

void loop() {

    //通信の処理
    TSUUSHINN_NO_SHORI();

    //コマンドに応じた関数を呼び出す
    switch(__command__) {
        case __up__:
            robo.go_up();
            break;

        case __down__:
            robo.go_down();
            break;

        case __turn_right__:
            robo.turn_right();
            break;

        case __turn_left__:
            robo.turn_left();
            break;
        
        default:
            robo.stop();
            break;
        
    }

    // 更新
    robo.execute();
}
```
