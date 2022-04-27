# Makefile du voyageur de commerce

include config.mk

SRC = import.cpp tempmain.cpp
OBJ = ${SRC:.cpp=.o}

all: voyage

${OBJ}: import.h config.mk

voyage: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f voyage ${OBJ}
