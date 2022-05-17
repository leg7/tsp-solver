# Makefile du voyageur de commerce

include config.mk

SRC = import.cpp export.cpp data.cpp calcul-tour.cpp voyage.cpp
OBJ = ${SRC:.cpp=.o}

all: voyage

${OBJ}: import.h export.h data.h calcul-tour.h config.mk

voyage: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f voyage ${OBJ} *.out
