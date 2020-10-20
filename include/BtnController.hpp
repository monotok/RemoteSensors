//
// Created by hammer on 25/05/2020.
//

#ifndef REMOTESENSORS_BTNCONTROLLER_HPP
#define REMOTESENSORS_BTNCONTROLLER_HPP


class BtnController
{
public:
    BtnController();
    bool debounceBtn();
    void initBtnState(int inputPinNo);
    void reInitBtnState();
    void updateLastDebounceTime();


private:
    int currentButtonState;    // the current reading from the input pin
    int lastButtonState;       // the previous reading from the input pin
    unsigned long lastDebounceTime; // the last time the output pin was toggled
    const int debounceDelay = 200;        // the debounce time; increase if the output flickers
    unsigned long interruptTime;    // a timer to calc time between button presses

    void setCurrentBtnState(int btnState);
    void setBtnInterruptTime();
    void updateLastBtnState();
};


#endif //REMOTESENSORS_BTNCONTROLLER_HPP
