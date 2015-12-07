CC=gcc

CPPFLAGS= `pkg-config --cflags gtk+-3.0`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-3.0`
 
SRC= showUI.c callback.c
OBJ= ${SRC:.c=.o}
BIN= UI

all: ${BIN}

${BIN}: ${OBJ}
	${CC} -o ${BIN} ${OBJ} ${CFLAGS} ${LDLIBS}

clean:
	rm -f *~ *.o
	rm -f ${BIN}
