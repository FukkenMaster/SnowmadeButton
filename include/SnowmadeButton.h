#pragma once

class ButtonHandler
{

public:
    enum Event
    {
        NO_INPUT,
        CLICK,
        TICK
    };
    
    // Constructor #1 with normal button logic - buttonHeld==High==True==1 || buttonReleased==Low==False==0
    // and options to reverse the logic
    // and customize timings
    ButtonHandler(int inputPin, bool reverseLogic = false, int holdThreshold = 800, int tickInterval = 333, int debounceThreshold = 100);
    Event pollButton();

private:
    enum ButtonState
    {
        IDLE,
        ENGAGED,
        HOLDING
    };

    int _inputPin;
    int _holdThreshold = 800;                // if button being held for 800ms+ intentional hold should be confirmed ; default is 800
    int _tickInterval = 333;                 // ms interval between ticks while button being held down ; default is 333
    int _debounceThreshold = 100;            // button presses for under 100ms should be filtered out as unintentional ; default is 100
    bool _reverseLogic = false;              // reversed logic - buttonHeld==Low==False==0  ||  buttonReleased==High==True==1 ; defalult is false
    unsigned long _holdTimeout = 0;          // default is 0
    unsigned long _tickTimeout = 0;          // default is 0
    ButtonState _currentButtonState = IDLE;  // defaul is IDLE
    ButtonState _previousButtonState = IDLE; // defaul is IDLE

    void setNextButtonState(ButtonState nextButtonState);
    void setLongPressTimeout();
    void setTickTimeout();
    bool isLongPress();
    bool isTickIntervalElapsed();
    bool isClickPossible();
    bool isTickPossible();
    bool reversibleDigitalRead(int inputPin, bool reverseLogic);
};
