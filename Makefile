CC=gcc
MPICC?=mpicc
FLAGS=-Wall

# filenames
EXEC = run
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
 
# main target
$(EXEC): $(OBJECTS)
	$(MPICC) $(OBJECTS) -o $(EXEC)
 
# obtain object files
%.o: %.c
	$(MPICC) -c $(FLAGS) $< -o $@

# remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
