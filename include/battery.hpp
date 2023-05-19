#pragma once


#include <Arduino.h>


#ifndef __COLORSENSOR__BATTERY__H__
#define __COLORSENSOR__BATTERY__H__


Class Battery
{
    private:
        double _voltage;
        double _current;
        bool _voltageLow;

    public:
        Battery();
        void readVoltage();
        void readCurrent();
        void createWarning();

        void setVoltage(double voltage);
        void setCurrent(double current);
        void setVoltageLow(bool low);
        double getVoltage();
        double getCurrent();
        bool getVoltageLow();
};

#endif