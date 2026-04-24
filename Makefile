# Compiler and flags
CC = gcc
CFLAGS = -I include/raylib/src
LDLFILES = -L.
LDLIBS = -L. -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

#project name
PROJ_NAME = pif-game
