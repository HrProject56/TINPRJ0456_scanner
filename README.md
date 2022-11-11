## Project56 - Color Change Analysis with  Colorimetric Sensors

This file has the following content:
- `1`: File Structure
- `2`: Requirements 
- `3`: Installation
- `4`: Installation Notes
- `5`: How to update
- `6`: Code Credits

### 1) File structure
- Colorsensor/ `Main folder`
    - include/ `This directory is intended for project header files.`
      - README.md
    - lib/ `This directory is intended for project specific (private) libraries.`
      - ColorSensor/ `All libraries needed for the color sensor`
        - Adafruit_TCS34725/ 
        - Adafruit_BusIO/ 
      - Bluetooth/ `All libraries needed for the bluetooth connection`
        - BluetoothSerial/
      - README.md
    - src/ `This directory is intended for our classes`
      - ColorSensor/
      - Communication/
      - main.cpp
    - README.md `This file`

If you need to update one of the libraries refer to `3`.

### 2) Requirements
- [Github Student Developer Pack](https://education.github.com/pack)
- [CLion from Jetbrains through Github Student pack](https://www.jetbrains.com/clion/download)
- [PlatformIO](https://docs.platformio.org/en/latest/integration/ide/clion.html#installation)
- Android phone with version 9 or above

### 3) Installation
- Setup your Github Student account
- Create a jetbrains account and link it to your Github account
- Install CLion
- Install PlatformIO (Check `2` and `4` for more info)
- Clone repo with the following command in a directory of your choice:

```
git clone https://github.com/HrProject56/TINPRJ0456_scanner.git Colorsensor
```

- Open the cloned repo with CLion
- Check if PlatformIO is installed
- If PlatformIO is succesfully go to `Tools > PlatformIO` and click on `Re-Init`
- If you don't get an error then all dependencies should now be installed, if it so happens that an error shows up you will need to fix this first. One of the things you could try is checking if CMake is setup correctly. You can check this by going to `File > Settings > Build, Execution, Deployment > CMake`. The arguments should be filled in like this:
```
Enable Profile: checked
Name: firebeetle32
Build type: firebeetle32
Toolchain: MinGW
Generator: Use default (Ninja)
CMake options: empty
Build directory: empty
Build options: empty
Environment: empty
```
- Try `Re-Init` again until all issues are solved - if you are not sure if it's going to upload try to use PlatformIO's upload function. That should give a more detailed error on how and why it fails.

### 4) Installation Notes
- PlatformIO IDE should work automatically in CLion, if it doesn't please follow the instructions [here](https://docs.platformio.org/en/latest/core/installation/methods/installer-script.html#local-download-macos-linux-windows) as this is verified to work.
- If you chose to install the PlatformIO Core (CLI) with the options above, add the route to your installation folder to your environment PATH 

### 5) How to update
If you would need to update libraries for some reason follow the steps below:

- Make sure the code isn't giving ANY `#include` errors (warnings are fine)
- Go to the library you wish to replace as seen in the 'File structure' 
- Check the 'library.properties' file inside the library. In that file should be the URL from the library and/or the 'name' and 'author' from the library. 
- Copy and paste the URL (or if that isn't there, the 'name' + 'author') in your preferred search engine (i.e Google, or DuckDuckGo).
- If you found the repo clone it OR download the latest release in a local folder OUTSIDE of the project (releases are recomended as they tend to be more stable)
- Before moving your new, now local, library version in the project move the 'old' version out of the project and check where the `#include` errors are showing up
- Now move the new library version into the `lib/` folder (see `1`) and change the `#include` paths where the errors started occuring, to the new library.
- If the code still not works it can be that some naming conventions have changed between versions. This can only be resolved by reading the new documentation. 

### 6) Code Credits: 
- Code first made by: Ruben Flinterman (1037046)
