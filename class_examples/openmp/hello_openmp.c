// compile: gcc hello_openmp.c -o hello_openmp -lm -fopenmp
//
// run: hello_openmp
//
// source code from: https://people.sc.fsu.edu/~jburkardt/c_src/openmp/openmp.html
//

# include <stdlib.h>
# include <stdio.h>
# include <omp.h>

int main ( int argc, char *argv[] );

/******************************************************************************/

int main ( int argc, char *argv[] )

/******************************************************************************/
/*
  This code was adapted from:
  
  Purpose:

    HELLO has each thread print out its ID.

  Discussion:

    HELLO is a "Hello, World" program for OpenMP.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    23 June 2010

  Author (original code):

    John Burkardt
*/
{
  double wtime;
  int max_threads, thread_num, num_procs, num_threads, in_parallel;

  num_procs = omp_get_num_procs();
  max_threads = omp_get_max_threads();
  num_threads = omp_get_num_threads();
  
  printf ( "\n" );
  printf ( "HELLO_OPENMP\n" );
  printf ( "  C/OpenMP version\n" );

  printf ( "\n" );
  printf ( "  Number of processors available = %d\n", num_procs);
  printf ( "  Number of threads = %d and Max Number of threads = %d\n", num_threads, max_threads);

  wtime = omp_get_wtime ( );

  in_parallel = omp_in_parallel();

  printf ( "\n" );
  printf ( "  OUTSIDE the parallel region. in_parallel = %d\n", in_parallel );
  printf ( "\n" );

  thread_num = omp_get_thread_num ( );
  printf ( "  HELLO from main thread %d\n", thread_num ) ;

 
  printf ( "\n" );
  printf ( "  Going INSIDE the parallel region:\n" );
  printf ( "\n" );
/*
  INSIDE THE PARALLEL REGION, have each thread say hello.
*/
# pragma omp parallel private ( thread_num )   num_threads(8) 
  {
    thread_num = omp_get_thread_num();
    in_parallel = omp_in_parallel();
    max_threads = omp_get_max_threads ( );
    num_threads = omp_get_num_threads( );
    
    printf ("  Hello from thread %d, num_threads = %d, max_threads = %d and in_parallel = %d\n", thread_num, num_threads, max_threads, in_parallel);

  }
/*
  Finish up by measuring the elapsed time.
*/
  thread_num = omp_get_thread_num ( );
  num_threads = omp_get_num_threads( );
  in_parallel = omp_in_parallel( );
  wtime = omp_get_wtime ( ) - wtime;

  printf ( "\n" );
  printf ( "  Back OUTSIDE the parallel region, thread_num = %d, num_threads = %d and in_parallel = %d\n", thread_num, num_threads, in_parallel);
/*
  Terminate.
*/
  printf ( "\n" );
  printf ( "HELLO_OPENMP\n" );
  printf ( "  Elapsed wall clock time = %f\n", wtime );

  return 0;
}
