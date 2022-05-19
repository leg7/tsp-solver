# Makefile du voyageur de commerce

include config.mk

SRC = import.cpp export.cpp data.cpp heuristics.cpp tsp-solver.cpp tests.cpp
OBJ = ${SRC:.cpp=.o}

all: tsp-solver

${OBJ}: import.h export.h data.h heuristics.h tests.h config.mk

tsp-solver: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f tsp-solver ${OBJ} *.out
