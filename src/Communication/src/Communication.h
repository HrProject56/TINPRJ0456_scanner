//
// Created by rwfli on 08/11/2022.
//

#ifndef COLORSENSOR_COMMUNICATION_H
#define COLORSENSOR_COMMUNICATION_H

class Communication {
    public:
        void setBT();
        void writeBT(std::initializer_list<unsigned short> color);
};


#endif //COLORSENSOR_COMMUNICATION_H
