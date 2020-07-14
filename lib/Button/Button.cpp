#include "Button.h"
#include "Arduino.h"

Button::Button(int pin)
{
    Serial.println("constructor");
    _pin = pin;
    pinMode(_pin, INPUT);
    //default values, can be customized, they are public
    debounceTimeMs = 20;
    longPressTimeMs = 1000;
    doublePressDelayMs = 300;
    //initial state of the state machine
    state = Idle;
}

void Button::Refresh()
{
    switch (state)
    {
    case Idle:
        PressType = PressTypes::None;
        if (digitalRead(_pin))
        {
            state = DebouncingFirst;
            startDebouncingMillis = millis();
        }
        break;
    case DebouncingFirst:
        if (millis() - startDebouncingMillis >= debounceTimeMs)
        {
            state = digitalRead(_pin) ? WaitingFirstPressRelease : WaitingSecondPress;
        }
        break;
    case WaitingFirstPressRelease:
        if (!digitalRead(_pin))
        {
            if (millis() - startDebouncingMillis >= longPressTimeMs)
            {
                PressType = PressTypes::LongClick;
                state = Idle;
            }
            else
            {
                startSecondPressWaitingMillis = millis();
                state = WaitingSecondPress;
            }
        }
        break;
    case WaitingSecondPress:
        if (millis() - startSecondPressWaitingMillis >= doublePressDelayMs)
        {
            PressType = PressTypes::SingleClick;
            state = Idle;
            break;
        }
        if (digitalRead(_pin))
        {
            state = DebouncingSecond;
            startDebouncingMillis = millis();
        }
        break;
    case DebouncingSecond:
        if (millis() - startDebouncingMillis >= debounceTimeMs)
        {
            if (digitalRead(_pin))
            {
                state = WaitingSecondPressRelease;
            }
            else
            {
                PressType = PressTypes::SingleClick;
                state = Idle;
            }
        }
        break;
    case WaitingSecondPressRelease:
        if (!digitalRead(_pin))
        {
            PressType = PressTypes::DoubleClick;
            state = Idle;
            break;
        }
        break;

    default:
        break;
    }
}

Button::PressTypes Button::GetPressType()
{
    return PressType;
};
