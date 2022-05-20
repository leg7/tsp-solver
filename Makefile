# Makefile du voyageur de commerce

include config.mk

SRC = import.cpp export.cpp data.cpp heuristics.cpp
OBJ = ${SRC:.cpp=.o}

all: tsp-solver

# Test

T = ${SRC} tests.cpp
TO = ${OBJ} tests.o

${TO}: ${T:.cpp=.h}

tests: ${TO}
	${CC} -o $@ ${TO} ${LDFLAGS}
	./tests

# Main program

M = ${SRC} tsp-solver.cpp
MO = ${OBJ} tsp-solver.o

${MO}: ${SRC:.cpp=.h}

tsp-solver: tests ${MO}
	${CC} -o $@ ${MO} ${LDFLAGS}

clean:
	rm -f tsp-solver tests ${MO} ${TO} *.out
