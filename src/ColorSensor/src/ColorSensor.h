//
// Created by rwfli on 08/11/2022.
//

#ifndef COLORSENSOR_COLORSENSOR_H
#define COLORSENSOR_COLORSENSOR_H

#include "initializer_list"
using std::initializer_list;

class ColorSensor {
    public:
        void setColorSensor();
        initializer_list<unsigned short> getColor();
};


#endif //COLORSENSOR_COLORSENSOR_H
