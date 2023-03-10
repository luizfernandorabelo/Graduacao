#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define TAM 100
#define ESCALAR 2
#define THREADS_POR_BLOCO 256

/* 
    Região de memória constante no device. É usada
    somente para leitura. Seu acesso é mais rápido
    que o da memória global e compartilhada.
*/
__device__ __constant__ int escalar_device;

__global__ void multiplicar_por_escalar(int *vetor) {
    int indice = blockIdx.x * blockDim.x + threadIdx.x;
    if (indice < TAM) vetor[indice] = vetor[indice] * escalar_device;
}

int main(void) {

    int *vetor_host, *vetor_device;

    // Inicialização de vetor no host:
    vetor_host = (int *) malloc(TAM * sizeof(int));
    for (int i = 0; i < TAM; i++)
        vetor_host[i] = i + 1;
    
    // Alocação e cópia para o device:
    cudaMalloc(&vetor_device, TAM * sizeof(int));
    cudaMemcpy(vetor_device, vetor_host, TAM * sizeof(int), cudaMemcpyHostToDevice);

    // Cópia do escalar para a memória constante do device:
    int escalar_host = ESCALAR;
    cudaMemcpyToSymbol(escalar_device, &escalar_host, sizeof(int));

    int blocos_por_grade = (TAM + THREADS_POR_BLOCO - 1) / THREADS_POR_BLOCO;

    multiplicar_por_escalar<<<blocos_por_grade,THREADS_POR_BLOCO>>>(vetor_device);

    // Cópia do resultado do device para o host:
    cudaMemcpy(vetor_host, vetor_device, TAM * sizeof(int), cudaMemcpyDeviceToHost);

    // Impressão do resultado:
    for (int i = 0; i < TAM; i++)
        printf("%d ", vetor_host[i]);
    printf("\n");

    free(vetor_host);

    // Liberação de memória no device:
    cudaFree(vetor_device);

    return 0;
}
