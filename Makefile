BUILDROOT_OUTPUT=$(HOME)/buildroot/output
CROSS_COMPILE=$(BUILDROOT_OUTPUT)/host/bin/arm-linux-

CC = $(CROSS_COMPILE)gcc
TARGET = arrow_game
OBJECTS = game_main.o gpio.o display.o game.o arrow.o bow.o character.o draw.o util.o
CFLAGS = -Wall

all: $(TARGET)
	rm *.o

$(TARGET): $(OBJECTS)
	$(CC) -g -o $(TARGET) $(OBJECTS) -lm

%.o: %.c
	$(CC) -c $< $(CFLAGS)

game_main.o : game_main.c game.o
	$(CC) -c game_main.c $(CFLAGS)

draw.o: draw.c graphic.o
	$(CC) -c draw.c $(CFLAGS)

game.o: game.c arrow.o bow.o character.o draw.o
	$(CC) -c game.c $(CFLAGS)

display.o: display.c display.h 
	$(CC) -c display.c $(CFLAGS)

util.o: util.c util.h
	$(CC) -c util.c $(CFLAGS)

clean:
	rm *.o $(TARGET)