CC = gcc
CFLAGS = -Wall -lSDL2 -lSDL2_image
SRC = src/main.c src/game.c src/maze.c src/pacman.c src/ghost.c src/graphics.c
OBJ = $(SRC:.c=.o)
OUT = pacman

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUT) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OUT)
