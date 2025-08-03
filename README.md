<!-- Header Image -->
<p align="center">
  <img src="./images/header.png" alt="Snowmade Banner" width="100%" />
  <img src="https://upload.wikimedia.org/wikipedia/commons/5/5b/Arduino_Logo_Registered.svg" alt="Arduino Logo" width="25%" />
</p>

<h1 align="center">SnowmadeButton</h1>

<p align="center">
 Little Arduino based service that can poll buttons are register shor and long presses in a non blocking way.
</p>

---

## 🚀 About

CLICK (for short press) and TICK (for long press) events in a non-blocking way. 
Buttons should use hardware debounce, software substitude is not included and not recomended. 


## Examples
```cpp
#include <Arduino.h>
#include <SnowmadeButton.h>

#define BUTTON_PIN 3

SnowmadeButton button(BUTTON_PIN);

void setup()
{
    pinMode(BUTTON_PIN, INPUT);
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
    default:
        break;
    }
}
