# Archery Game in Raspi 3B+
## Inspired by
![bowman2Screenshot](./img/bowman2.jfif)  
This game is archery game based on flash.
  
# Running Equipment

- **Raspberry pi 3B+**  
- &nbsp;&nbsp;&nbsp;&nbsp;with **SSD1306**  
- &nbsp;&nbsp;&nbsp;&nbsp;**3 pullup Button**

# How to compile
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
