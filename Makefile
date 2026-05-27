CC = gcc

# Fontes e objetos
SRCS = pif_game.c $(wildcard functions/*.c)
OBJS = $(SRCS:.c=.o)

# Flags
CFLAGS = -I./functions -I./raylib/raylib/src -Wall -O2
LDFLAGS = -L.
LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = pif_game

.PHONY: all clean run rebuild

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

rebuild: clean all

clean:
	rm -f $(OBJS) $(TARGET)
