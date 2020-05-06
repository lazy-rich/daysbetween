CC =		cc
CFLAGS =	-Wall -Wextra
PROG =		daysbetween
LIBS =		-lm

OBJS = main.o

all: ${PROG}

${PROG}: ${OBJS}
	${CC} ${CFLAGS} -o ${PROG} ${OBJS} ${LIBS}

clean:
	rm -f ${PROG} ${OBJS}

install: ${PROG}
	install -m 0700 ${PROG} ~/bin
