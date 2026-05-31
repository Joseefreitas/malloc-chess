CC = gcc

# Fontes e objetos
SRCS = pif_game.c $(wildcard functions/*.c)
OBJS = $(SRCS:.c=.o)

#  Raylib
RAYLIB_DIR = ./raylib/raylib/src
RAYLIB_LIB = $(RAYLIB_DIR)/libraylib.a
RAYLIB_MAKE = $(MAKE) -C $(RAYLIB_DIR) PLATFORM=PLATFORM_DESKTOP CC=$(CC) AR=ar RANLIB=ranlib

# Flags
CFLAGS = -I./functions -I$(RAYLIB_DIR) -Wall -O2
LDFLAGS = -L$(RAYLIB_DIR)
LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = pif_game

.PHONY: all clean run rebuild raylib raylib-clean

all: $(TARGET)

$(TARGET): $(OBJS) $(RAYLIB_LIB)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(RAYLIB_LIB):
	$(RAYLIB_MAKE)

raylib: $(RAYLIB_LIB)

raylib-clean:
	$(MAKE) -C $(RAYLIB_DIR) clean

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

rebuild: clean all

clean:
	rm -f $(OBJS) $(TARGET)
	$(MAKE) -C $(RAYLIB_DIR) clean
