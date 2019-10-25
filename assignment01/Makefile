# compiler
CC = gcc

# output
BINARY = ./students
IN = input.in

# sources
SRC = ./studentspar.c

# includes
INCLUDES = .

# compiler flags
# FLAGS = -g -std=c99 -lm -Wall -pedantic -fopenmp
FLAGS = -g -lm

# in case ANSI C is necessary
# FLAGS = -g -std=c89 -lm -Wall -pedantic -fopenmp

all: compile run

compile:
	$(CC) -o $(BINARY) -I $(INCLUDES) $(SRC) $(FLAGS)

run:
	$(BINARY) < $(IN)

debug:
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes $(BINARY)

clean:
	rm *.o
