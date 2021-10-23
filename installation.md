# Setting up development environment

This section will explain how to setup an Arduino development enviroment in Visual Studio Code. This section will also explain how to setup this enviroment for develoment on the Balboa balancing robot. 

## Linux (Ubuntu)
1. Install VSCode
2. Install Arduino vscode extension
3. Install Arduino IDE 
4. In VSCode settings, set the arduino path:
```json 
    "arduino.path": "/home/user/Downloads/arduino-1.8.16"
```
5. Install the `Balboa32U4` library (Installing arduino libraries in vscode with CTRL+SHIFT+P followed by this command ">Arduino: Library manager)
6. Install the 'LSM6' library
7. Install the 'LIS3MDL' library
8. Type in the command ">Arduino: Change board type". Select Arduino Leonardo.

## Mac
1. Install VSCode
2. Install Arduino vscode extension
3. Install Arduino IDE
4. In VSCode settings, set the arduino path:
```json 
    "arduino.path": "/Application"
```
5. Install the `Balboa32U4` library (Installing arduino libraries in vscode with CMD+SHIFT+P followed by this command ">Arduino: Library manager)
6. Install the 'LSM6' library
7. Install the 'LIS3MDL' library
8. Type in the command ">Arduino: Change board type". Select Arduino Leonardo.