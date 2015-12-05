CC=gcc

CPPFLAGS= `pkg-config --cflags sdl`
CFLAGS= -g -Wall -Wextra -Werror -pedantic -std=c99 #-O3
LDFLAGS=
LDLIBS= `pkg-config --libs sdl` -lSDL_image

SRC= feature_scaling.c integral_image.c pixel_operations.c main.c haar_feature.c classifier.c adaboost.c detection.c eigenface.c
OBJ= ${SRC:.c=.o}
BIN= main 

all: ${BIN}

${BIN}: ${OBJ}

clean:
	rm -f *~ *.o
	rm -f ${BIN}
