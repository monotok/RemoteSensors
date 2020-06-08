//
// Created by hammer on 07/06/2020.
//

#include <stdlib.h>
#include <string.h>
#include "DisplayController.hpp"

DisplayController::DisplayController() : fbd(8,4,3) { }

void DisplayController::initialiseDisplay()
{
    fbd.printToDisplay("////",4,"r");
}

void DisplayController::printFloat(float val)
{
    dtostrf(val, 4, 2, buf);
    fbd.printToDisplay(buf, strlen(buf), "r");
}


