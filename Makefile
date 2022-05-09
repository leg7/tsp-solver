# Makefile du voyageur de commerce

include config.mk

SRC = matrix.cpp import.cpp calcul-tour.cpp tour.cpp voyage.cpp
OBJ = ${SRC:.cpp=.o}

all: voyage

${OBJ}: matrix.h import.h calcul-tour.h tour.h config.mk

voyage: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f voyage ${OBJ} *.out
