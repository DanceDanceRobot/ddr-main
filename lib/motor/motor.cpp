#include "motor.hpp"

/////////////////////////////////////////////////
//driver class///////////////////////////////////
/////////////////////////////////////////////////  
void DRIVER::init(void){
    pinMode((int)pin.MODE, OUTPUT);
    pinMode((int)pin.STBY, OUTPUT);
    pinMode((int)pin.ERR, INPUT);

    //start phase mode
    digitalWrite((int)pin.MODE,HIGH);
    digitalWrite((int)pin.STBY,LOW);
    delay(10);

    digitalWrite((int)pin.STBY,HIGH);
    delay(10);
    digitalWrite((int)pin.MODE,HIGH);
    delay(10);
}

void DRIVER::reset(void){
    digitalWrite((int)pin.STBY,LOW);
    delay(100);

    init();
}

/////////////////////////////////////////////////
//motor class////////////////////////////////////
/////////////////////////////////////////////////
void MOTOR::init(void){
    ledcSetup(pin.pwm.ch,PWM_FRQ,PWM_WIDTH); 
    ledcAttachPin((int)pin.pwm.pin, pin.pwm.ch);

    pinMode((int)pin.en,OUTPUT);
    digitalWrite((int)pin.en,HIGH);
}

void MOTOR::out(float duty){
    assert(duty<1.0f || duty>-1.0f);

    digitalWrite((int)pin.en,HIGH);
    ledcWrite(pin.pwm.ch,(duty+1)*PWM_RESOL*motor_k);
}

void MOTOR::free(void){
    digitalWrite((int)pin.en,LOW);
    ledcWrite(pin.pwm.ch,0);
}