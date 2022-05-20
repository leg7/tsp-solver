VERSION = 1

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# flags
CPPFLAGS = -O3 -Wall -Wpedantic -Wextra -march=native -fdiagnostics-color=always
LDFLAGS = -Wl,-O1 -Wl,--as-needed

# compiler
CC = g++
