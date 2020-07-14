
// Button.h

#ifndef _BUTTON_h
#define _BUTTON_h

class Button
{
private:
    int _pin;

    enum States
    {
        Idle,                     //waiting for a button press
        FirstPress,               //a press was detected
        DebouncingFirst,          //is waiting the time defined to debounce the 1st press
        DebouncingSecond,         //is waiting the time defined to debounce the 2nd press
        WaitingFirstPressRelease, //
        WaitingSecondPress,       //the time window for a second press, started when the first press is released
        WaitingLongPressRelease,
        WaitingSecondPressRelease,
    };
    States state;

    unsigned long startDebouncingMillis;
    unsigned long startSecondPressWaitingMillis;

public:
    enum class PressTypes
    {
        None,
        SingleClick,
        DoubleClick,
        LongClick
    };

private:
    PressTypes PressType;

public:
    Button(int pin);
    unsigned int debounceTimeMs;     //time to debounce
    unsigned int longPressTimeMs;    //minimum time to consider a press as long touch
    unsigned int doublePressDelayMs; //maximum time between two presses to be considered a double press
    PressTypes GetPressType();
    void Refresh();
};

#endif
