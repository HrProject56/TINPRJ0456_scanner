//
// Created by rwfli on 08/11/2022.
//

#ifndef COLORSENSOR_COMMUNICATION_H
#define COLORSENSOR_COMMUNICATION_H


class Communication {
private:
    TwoWire *_wire;

public:
    void commInit();
    void commWrite(unsigned short &list);
    unsigned short &commRead();
};


#endif //COLORSENSOR_COMMUNICATION_H