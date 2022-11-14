//
// Created by rwfli on 08/11/2022.
//

#ifndef COLORSENSOR_COLORSENSOR_H
#define COLORSENSOR_COLORSENSOR_H

#include "initializer_list"
using std::initializer_list;

class ColorSensor {
public:
    static void setColorSensor();
    uint16_t * getColor();
    void printColor(int r, int g, int b, int c, int temp, int lux, int a_size);
};


#endif //COLORSENSOR_COLORSENSOR_H