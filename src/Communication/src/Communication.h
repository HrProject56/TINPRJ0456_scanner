//
// Created by rwfli on 08/11/2022.
//

#ifndef COLORSENSOR_COMMUNICATION_H
#define COLORSENSOR_COMMUNICATION_H

#include "initializer_list"
using std::initializer_list;

class Communication {
    public:
        void setBT();
        void writeBT(initializer_list<unsigned short> list);
};


#endif //COLORSENSOR_COMMUNICATION_H
