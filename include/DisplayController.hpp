//
// Created by hammer on 07/06/2020.
//

#ifndef REMOTESENSORS_DISPLAYCONTROLLER_HPP
#define REMOTESENSORS_DISPLAYCONTROLLER_HPP
#define byte unsigned char

#include "FourBitDisplay.h"

class DisplayController
{
public:
    DisplayController();
    void initialiseDisplay();
    void printFloat(float val);

private:
    FourBitDisplay fbd;
    char buf[4] = {0};

};


#endif //REMOTESENSORS_DISPLAYCONTROLLER_HPP
