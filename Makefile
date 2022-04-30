# Makefile du voyageur de commerce

include config.mk

SRC = import.cpp tempmain.cpp calcul-itineraire.cpp
OBJ = ${SRC:.cpp=.o}

all: voyage

${OBJ}: import.h calcul-itineraire.h config.mk

voyage: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f voyage ${OBJ} *.out
