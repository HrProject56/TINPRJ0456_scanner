//
// Created by rwfli on 08/11/2022.
//

#ifndef COLORSENSOR_COMMUNICATION_H
#define COLORSENSOR_COMMUNICATION_H


class Communication {
public:
    static void setBT();
    static void writeBT(unsigned short *list);
};


#endif //COLORSENSOR_COMMUNICATION_H