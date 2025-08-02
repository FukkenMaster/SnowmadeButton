#include <Arduino.h>
#include <SnowmadeButton.h>

#define BUTTON_PIN 3

// Create SnowmadeButton object
SnowmadeButton button(BUTTON_PIN);
// Mandatory parameter is BUTTON_PIN
// Optional parameters are:
//                          _reverseLogic(reverseLogic)                 reverse the logic of the button.   normal logic - buttonHeld==High==True==1 || buttonReleased==Low==False==0
//                                                                      reversed logic - buttonHeld==Low==False==0  ||  buttonReleased==High==True==1
//                          _holdThreshold(holdThreshold)               if button being held for 800ms+ intentional hold should be confirmed ; default is 800
//                          _tickInterval(tickInterval)                 ms interval between ticks while button being held down ; default is 333
//                          _debounceThreshold(debounceThreshold)       Software debounce is not implemented!
// Alternative button initialization examples:
// SnowmadeButton button (3, 0, 800, 333, 100);
// SnowmadeButton button (3, 1); // PIN 3 reversed logic

void setup()
{
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT); // set Arduino pin mode
}

void loop()
{
    switch (button.pollButton())
    {
    case CLICK:
        /* execute this code on CLICK (short press) event */
        break;
    case TICK:
        /* execute this code on TICK (long press) event */
        break;
    case NO_INPUT:
        /* execute default behavior */
        animation.drawFrame();
        break;
    default:
        Serial.println("Error: pollButton() returned an invalid value");
        break;
    }
}
