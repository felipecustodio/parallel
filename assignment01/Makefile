# compiler
CC = gcc

# output
BINARY = ./students
BINARY_SEQ = ./students_seq
BINARY_PAR = ./students_par
IN = input.in

# sources
SRC_PAR = ./studentspar.c
SRC_SEQ = ./studentsseq.c

# includes
INCLUDES = .

# compiler flags
FLAGS = -g -std=c99 -lm -Wall -pedantic -fopenmp -ffast-math

# in case ANSI C is necessary
# FLAGS = -g -std=c89 -lm -Wall -pedantic -fopenmp -ffast-math

all: compile run

compile:
	$(CC) -o $(BINARY_SEQ) -I $(INCLUDES) $(SRC_SEQ) $(FLAGS)
	$(CC) -o $(BINARY_PAR) -I $(INCLUDES) $(SRC_PAR) $(FLAGS)
	$(CC) -o $(BINARY) -I $(INCLUDES) $(SRC_PAR) $(FLAGS)

run:
	$(BINARY_PAR) < $(IN) > program_output_par.out
	$(BINARY_SEQ) < $(IN) > program_output_seq.out

debug:
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes $(BINARY)

clean:
	rm *.o
