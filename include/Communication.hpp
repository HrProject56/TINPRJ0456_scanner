//
// Created by rwfli on 08/11/2022.
//

#ifndef COLORSENSOR_COMMUNICATION_H
#define COLORSENSOR_COMMUNICATION_H


#include <Wire.h>


class Communication 
{
    private:
        TwoWire *_wire;

    public:
        void commInit();
        void commWrite(uint16_t &list);
        uint16_t &commRead();

        TwoWire *getI2CWire();
};


#endif //COLORSENSOR_COMMUNICATION_Hl