<!-- Header Image -->
<p align="center">
  <img src="./images/header.png" alt="Snowmade Banner" width="100%" />
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
```arduino
import { ProjectModule } from 'yourproject';

const pm = new ProjectModule();

pm.doSomethingCool('parameter');
