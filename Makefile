CC = gcc
CFLAGS = -I./functions -I./raylib/raylib/src
LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

pif_game: pif_game.c functions/utilis.c functions/math_game.c functions/tabuleiro.c functions/constants.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDLIBS)

clean:
	rm -f pif_game