#include <stdio.h>
#include <omp.h>

#define NT1 2
#define NT2 4


int main(void)
{
    omp_set_nested(1);

    #pragma omp parallel num_threads(NT1)    
    {
        int id_thread_01, em_paralelo_01, numero_threads_01;
		id_thread_01 = omp_get_thread_num();
		numero_threads_01 = omp_get_num_threads();
		em_paralelo_01 = omp_in_parallel();
		printf("Thread do primeiro nível (id_thread_01: %d | em_paralelo_01: %d | numero_threads_01: %d)\n", id_thread_01, em_paralelo_01, numero_threads_01);
		fflush(0);
		#pragma omp parallel num_threads(NT2) firstprivate(id_thread_01)
		{
			int id_thread_02, em_paralelo_02, numero_threads_02;
			id_thread_02 = omp_get_thread_num();
			numero_threads_02 = omp_get_num_threads();
			em_paralelo_02 = omp_in_parallel();
			printf("\tThread do segundo nível (id_thread_01: %d, id_thread_02: %d, em_paralelo_02: %d, numero_threads_02: %d)\n", id_thread_01, id_thread_02, em_paralelo_02, numero_threads_02);
			fflush(0);
		}
    }

    return 0;
}
