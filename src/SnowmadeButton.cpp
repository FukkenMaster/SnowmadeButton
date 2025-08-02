#include "ButtonHandler.h"
#include <Arduino.h>

// Constructor #1
ButtonHandler::ButtonHandler(int inputPin, bool reverseLogic, int holdThreshold, int tickInterval, int debounceThreshold) : _inputPin(inputPin),
                                                                                                                             _reverseLogic(reverseLogic),
                                                                                                                             _holdThreshold(holdThreshold),
                                                                                                                             _tickInterval(tickInterval),
                                                                                                                             _debounceThreshold(debounceThreshold)
{
}

void ButtonHandler::setNextButtonState(ButtonState nextButtonState)
{
    // placehold function
    _previousButtonState = _currentButtonState;
    _currentButtonState = nextButtonState;
}

void ButtonHandler::setLongPressTimeout()
{
    // sets the timeout, if button being released before the timeout it registers as click, otherwise it is being processed as long press
    _holdTimeout = millis() + _holdThreshold;
}

void ButtonHandler::setTickTimeout()
{
    // sets the tick timeout to ensure time intervals between ticks
    _tickTimeout = millis() + _tickInterval;
}

bool ButtonHandler::isLongPress()
{
    // if user interaction with the button was longer than HOLD_THRESHOLD return true
    return millis() >= _holdTimeout;
}

bool ButtonHandler::isTickIntervalElapsed()
{
    // check if enough time interval between ticks is elapsed - return true or false accordingly
    return millis() >= _tickTimeout;
}

bool ButtonHandler::isClickPossible()
{
    // placeholder function
    return true;
}

bool ButtonHandler::isTickPossible()
{
    // check if enough time interval between ticks is elapsed - return true or false acordingly
    if (isTickIntervalElapsed())
    {
        // set timeout for the next tick
        setTickTimeout();
        return true;
    }
    else
        return false;
}

bool ButtonHandler::reversibleDigitalRead(int inputPin, bool reverseLogic)
{
    bool inputValue = digitalRead(inputPin);>
    return reverseLogic ? !inputValue : inputValue;
}

ButtonHandler::Event ButtonHandler::pollButton()
{
    switch (_currentButtonState)
    {
    case IDLE:
        // if button becomes engaged, otherwise do nothing
        if (reversibleDigitalRead(_inputPin, _reverseLogic))
        {
            setNextButtonState(ENGAGED);
            // start timer to distinguish between click and long press
            setLongPressTimeout();
            // Serial.println("ENGAGED"); //debug
        }
        // Serial.println("IDLE");
        break;
    case ENGAGED:
        // if button being released from the ENGAGED state
        // normal logic - buttonHeld==High==True==1 || buttonReleased==Low==False==0
        // reversed logic - buttonHeld==Low==False==0  ||  buttonReleased==High==True==1
        if (reversibleDigitalRead(_inputPin, _reverseLogic) == _reverseLogic)
        {
            // Serial.println("RELEASED");
            // user interaction with the button was short - reset to IDLE and return a click event if possible
            if (isClickPossible())
            {
                setNextButtonState(IDLE);
                return CLICK;
            }
            break;
        }
        // if button being held for a long duration - dispatch a tick and swith state to HOLDING, otherwise do nothing
        if (isLongPress())
        {
            // Serial.println("NOW HOLDING"); //debug
            setNextButtonState(HOLDING);
            return TICK;
        }
        break;
    case HOLDING:
        // if button being released from the HOLDING state
        if (reversibleDigitalRead(_inputPin, _reverseLogic) == _reverseLogic)
        {
            // Serial.println("RELEASED"); //debug
            // user interaction with the button was long - do nothing and reset to IDLE
            setNextButtonState(IDLE);
            break;
        }
        // attempt to perform a tick
        if (isTickPossible())
        {
            // Serial.println("TICK");  //debug
            return TICK;
        }
        break;
    default:
        break;
    }
    return NO_INPUT;
}
