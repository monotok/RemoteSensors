//
// Created by hammer on 25/05/2020.
//

#include "BtnController.hpp"
#include "Arduino.h"

using namespace std;

BtnController::BtnController()
{
    this->lastButtonState = LOW;
    this->lastDebounceTime = 0;
    this->interruptTime = 0;
}

bool BtnController::debounceBtn()
{
    return this->currentButtonState == HIGH && this->lastButtonState == LOW &&
           this->interruptTime - this->lastDebounceTime > this->debounceDelay;
}

void BtnController::initBtnState(int inputPinNo)
{
    this->setCurrentBtnState(digitalRead(inputPinNo));
    this->setBtnInterruptTime();
}

void BtnController::reInitBtnState()
{
    this->updateLastBtnState();
}

void BtnController::setCurrentBtnState(int btnState)
{
    this->currentButtonState = btnState;
}

void BtnController::setBtnInterruptTime()
{
    this->interruptTime = millis();
}

void BtnController::updateLastBtnState()
{
    this->lastButtonState = this->currentButtonState;
}

void BtnController::updateLastDebounceTime()
{
    this->lastDebounceTime = this->interruptTime;
}