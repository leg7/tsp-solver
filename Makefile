# Makefile du voyageur de commerce

include config.mk

SRC = matrix.cpp import.cpp tour.cpp calcul-tour.cpp voyage.cpp
OBJ = ${SRC:.cpp=.o}

all: voyage

${OBJ}: matrix.h import.h tour.h calcul-tour.h config.mk

voyage: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f voyage ${OBJ} *.out
