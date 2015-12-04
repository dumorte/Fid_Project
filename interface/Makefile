CC=gcc

CPPFLAGS= `pkg-config --cflags gtk+-2.0`
CFLAGS= -Wall -Wextra -Werror -std=c99 -O3
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-2.0` `pkg-config --libs gtkimageview`
 
SRC= graphint.c callback.c
OBJ= ${SRC:.c=.o}
BIN= interface

all: ${BIN}

${BIN}: ${OBJ}
	${CC} -o ${BIN} ${OBJ} ${CFLAGS} ${LDLIBS}

clean:
	rm -f *~ *.o
	rm -f ${BIN}
