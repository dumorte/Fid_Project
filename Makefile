CC=gcc

CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -g -Wall -Wextra -Werror -std=c99
#O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

SRC= haar_feature.c integral_image.c pixel_operations.c display.c 
OBJ= ${SRC:.c=.o}
BIN= display

all: ${BIN}

${BIN}: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f ${BIN}
