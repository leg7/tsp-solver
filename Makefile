# Makefile du voyageur de commerce

include config.mk

SRC = matrix.cpp import.cpp calcul-itineraire.cpp itineraire.cpp voyage.cpp
OBJ = ${SRC:.cpp=.o}

all: voyage

${OBJ}: matrix.h import.h calcul-itineraire.h itineraire.h config.mk

voyage: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f voyage ${OBJ} *.out
