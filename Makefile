# Makefile du voyageur de commerce

include config.mk

SRC = import.cpp export.cpp data.cpp calcul-tour.cpp tsp-solver.cpp
OBJ = ${SRC:.cpp=.o}

all: tsp-solver

${OBJ}: import.h export.h data.h calcul-tour.h config.mk

tsp-solver: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f tsp-solver ${OBJ} *.out
