# Archery Game in Raspi 3B+
## Inspired by
![bowman2Screenshot](./img/bowman2.jfif)  
This game is archery game based on flash.
  
# Running Equipment

- **Raspberry pi 3B+**  
- &nbsp;&nbsp;&nbsp;&nbsp;with **SSD1306**  
- &nbsp;&nbsp;&nbsp;&nbsp;**3 pullup Button**

# How to compile
--***Warning***--  
Actually, You can compile and run this only with * **proper** * configuration, which is very hard to fit,  
and I've would like to procrastinate to describe.  
Because it is combination of cross-compile to ARM, communication with i2c, gpio devices.  
  
But, At least you can try XD.
## Hardware Setting

TODO
## Driver Compilation & Usage

```
cd driver
make
```
And this will make gpio driver file <i>gpio-driver.ko</i>.  
Transfer this module file to raspberry pi, then in Raspberry pi
```
insmod gpio-driver.ko
```
This will install gpio driver.
## Main Game Compilation

Simply, in code root folder,
```
make
```
And this will output <i>arrow_game</i> which is game bin file.
# Demo
TODO
