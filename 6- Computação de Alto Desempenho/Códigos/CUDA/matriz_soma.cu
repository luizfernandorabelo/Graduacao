#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define DIMENSAO 16  // dimensão da matriz
#define THREADS 5    // quantidade de threads por dimensão  

__global__ void soma(int *a, int *b, int *c) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    int j = blockIdx.y * blockDim.y + threadIdx.y;
    if (i < DIMENSAO && j < DIMENSAO)
        c[i * DIMENSAO + j] = a[i * DIMENSAO + j] + b[i * DIMENSAO + j];
}

int main(void) {

    int *a_host, *b_host, *c_host;
    int *a_device, *b_device, *c_device;

    // Alocação das "matrizes" na CPU:
    a_host = (int *) malloc(DIMENSAO * DIMENSAO * sizeof(int));
    b_host = (int *) malloc(DIMENSAO * DIMENSAO * sizeof(int));
    c_host = (int *) malloc(DIMENSAO * DIMENSAO * sizeof(int));

    // Alocação das "matrizes" na GPU (em sua memória global):
    cudaMalloc(&a_device, DIMENSAO * DIMENSAO * sizeof(int));
    cudaMalloc(&b_device, DIMENSAO * DIMENSAO * sizeof(int));
    cudaMalloc(&c_device, DIMENSAO * DIMENSAO * sizeof(int));

    // Preenchimento de a e b na CPU:
    for (int i = 0; i < DIMENSAO * DIMENSAO; i++) {
        a_host[i] = +i;
        b_host[i] = -i;
    }

    // Cópia de a e b para a GPU:
    cudaMemcpy(a_device, a_host, DIMENSAO * DIMENSAO * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(b_device, b_host, DIMENSAO * DIMENSAO * sizeof(int), cudaMemcpyHostToDevice);

    // Definição da quantidade de threads por bloco:
    dim3 threadsPorBloco(
        THREADS,  // eixo x
        THREADS   // eixo y
    );

    // Definição da quantidade de blocos por grade:
    dim3 blocosPorGrade(
        (DIMENSAO + threadsPorBloco.x - 1) / threadsPorBloco.x,  // eixo x
        (DIMENSAO + threadsPorBloco.y - 1) / threadsPorBloco.y   // eixo y
    );

    soma<<<blocosPorGrade,threadsPorBloco>>>(a_device, b_device, c_device);
        
    // Cópia de c para a CPU:
    cudaMemcpy(c_host, c_device, DIMENSAO * DIMENSAO * sizeof(int), cudaMemcpyDeviceToHost);

    // Impressão do resultado:
    for (int i = 0; i < DIMENSAO * DIMENSAO; i++) {
        printf("%d ", c_host[i]);
        if (i % DIMENSAO == DIMENSAO - 1) printf("\n");
    }
    printf("\n");

    free(a_host);
    free(b_host);
    free(c_host);

    // Liberação de memória da GPU:
    cudaFree(a_device);
    cudaFree(b_device);
    cudaFree(c_device);

    return 0;
}
