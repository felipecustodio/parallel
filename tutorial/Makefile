EXECS=mpi_hello_world
MPICC?=mpicc

all: ${EXECS}

mpi_hello_world: hello.c
		${MPICC} -o hello hello.c

clean:
		rm ${EXECS}
