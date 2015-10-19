CC=gcc

CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -g -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

SRC= pixel_operations.c display.c
OBJ= ${SRC:.c=.o}

all: display

display: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f display
