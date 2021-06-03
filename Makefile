CC = gcc
TARGET = arrow_game

$(TARGET) : arrow.o bow.o character.o display.o game.o util.o
	$(CC) -c -o $(TARGET) arrow.o bow.o character.o display.o game.o util.o

arrow.o : arrow.c util.o
	$(CC) -c -o arrow.o arrow.c

bow.o : bow.c util.o
	$(CC) -c -o bow.o bow.c

character.o : character.c
	$(CC) -c -o character.o character.c

display.o : display.c util.o
	$(CC) -c -o display.o display.c

game.o : game.c
	$(CC) -c -o game.o game.c

util.o : util.c
	$(CC) -c -o util.o util.c

