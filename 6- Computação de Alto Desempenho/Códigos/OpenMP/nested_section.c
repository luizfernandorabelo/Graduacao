#include <stdio.h>
#include <omp.h>

#define NT1 4
#define NT2 2


void fazerTarefa(int numero_tarefa, int id_thread_externa) 
{
    int id_thread_interna, total_threads;

    printf("\tfazer_tarefa: %d, id_thread_externa: %d \n", numero_tarefa, id_thread_externa);
    fflush(0);
    
    #pragma omp parallel num_threads(NT2) private(id_thread_interna, total_threads)
    {
		id_thread_interna = omp_get_thread_num();
		total_threads = omp_get_num_threads();
		#pragma omp for 
        for(int i = 0; i < NT2; i++) 
		{
			printf("\t\t- tarefa %d, id_thread_externa: %d, id_thread_interna: %d, total_threads: %d\n", numero_tarefa, id_thread_externa, id_thread_interna, total_threads);
			fflush(0);
		}
    }
}


int main()
{
    int id_thread_externa, total_threads;
    
    omp_set_nested(1);

    #pragma omp parallel num_threads(NT1) private(id_thread_externa, total_threads)
    {
		id_thread_externa = omp_get_thread_num();
		total_threads = omp_get_num_threads( );

		printf("Primeiro nível (main) id_thread_externa: %d, num_threads01:%d\n", id_thread_externa, total_threads);
        fflush(0);

		#pragma omp sections 
		{
			#pragma omp section
			{
				printf("Main section 1 omp_get_thread_num(): %d \n", omp_get_thread_num());
				fflush(0);
				fazerTarefa(1, id_thread_externa);
			}
			#pragma omp section
			{
				printf("Main section 2 omp_get_thread_num():%d \n", omp_get_thread_num());
				fflush(0);
				fazerTarefa(2, id_thread_externa);
			}
			#pragma omp section
			{
				printf("Main section 3 omp_get_thread_num():%d \n", omp_get_thread_num());
				fflush(0);
				fazerTarefa(3, id_thread_externa);
			}
			#pragma omp section
			{
				printf("Main section 4 omp_get_thread_num():%d \n", omp_get_thread_num());
				fflush(0);
				fazerTarefa(4, id_thread_externa);
			}
		}
	}

    return 0;
}