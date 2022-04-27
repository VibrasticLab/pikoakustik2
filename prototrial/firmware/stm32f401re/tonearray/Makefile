OUT = tone
SRC = $(OUT).c
CC = gcc
LIB = -lm
DEF = -DWEIRD_SINE=0

all: $(SRC)
	$(CC) -o $(OUT)_bin $(DEF) $(LIB) $(SRC)

clean:
	rm -f $(OUT)_bin
