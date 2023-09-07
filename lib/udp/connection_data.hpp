#pragma once 

class ConnectionData{
public:
    typedef struct data{
        bool up;
        bool down;
        bool left;
        bool right;
        bool l_turn;
        bool r_turn;
    } Data;
    Data data;
    ConnectionData(void){}

    void reset(){
        data = {0,0,0,0,0,0};
    }

    void up(){
        data.up = 1;
    }

    void down(){
        data.down = 1;
    }

    void left(){
        data.left = 1;
    }

    void right(){
        data.right = 1;
    }

    void l_turn(){
        data.l_turn = 1;
    }

    void r_turn(){
        data.r_turn = 1;    
    }

    uint8_t serialize() const {
        uint8_t ret = ( static_cast<uint8_t>(data.up     << 0) + 
                        static_cast<uint8_t>(data.down   << 1 ) + 
                        static_cast<uint8_t>(data.left   << 2 ) + 
                        static_cast<uint8_t>(data.right  << 3 ) + 
                        static_cast<uint8_t>(data.l_turn << 4 ) + 
                        static_cast<uint8_t>(data.r_turn << 5 ));
        return ret;
    }
    void deserialize(const uint8_t serial){
        data.up     = (serial & 0b00000001) != 0;
        data.down   = (serial & 0b00000010) != 0;
        data.left   = (serial & 0b00000100) != 0;
        data.right  = (serial & 0b00001000) != 0;
        data.l_turn = (serial & 0b00010000) != 0;
        data.r_turn = (serial & 0b00100000) != 0;
    }
};
