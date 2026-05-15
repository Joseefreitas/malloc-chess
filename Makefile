# Compiler and flags
CC = gcc
CFLAGS = -I include/raylib/src
LDLFILES = -L.
LDLIBS = -L. -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

#project name
PROJ_NAME = pif-game

gcc pif_game.c functions/utilis.c functions/math_game.c -o pif_game -I ./functions -I./raylib/raylib/src -L. -lraylib -lGL -lm -lpthread -ldl -lrt -lX11  && ./pif_game
