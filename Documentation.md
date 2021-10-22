# Installation 

## Linux
1. Install VSCode
2. Install Arduino vscode extension
3. Install Arduino IDE with this command: 
```bash
    sudo snap install arduino
```
4. In VSCode settings, set the arduino path:
```json 
    "arduino.path": "/snap/arduino/current"
```
5. Install the `Balboa32U4` library
6. Type in the command ">Arduino: Change board type". Select Arduino Leonardo.

## Mac
1. Install VSCode
2. Install Arduino vscode extension
3. Install Arduino IDE
4. In VSCode settings, set the arduino path:
```json 
    "arduino.path": "/Application"
```
5. Install the `Balboa32U4` library
6. Type in the command ">Arduino: Change board type". Select Arduino Leonardo.

# References
- [https://pololu.github.io/balboa-32u4-arduino-library/](https://pololu.github.io/balboa-32u4-arduino-library/)
- [https://github.com/pololu/pololu-rpi-slave-arduino-library/tree/balboa](https://github.com/pololu/pololu-rpi-slave-arduino-library/tree/balboa)
- [https://www.pololu.com/docs/0J70/3.3](https://www.pololu.com/docs/0J70/3.3)
