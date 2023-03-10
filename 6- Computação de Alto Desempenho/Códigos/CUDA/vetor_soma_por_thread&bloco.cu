#include <stdio.h>
#include <cuda.h>

#define TAM 10000
#define THREADS_POR_BLOCO 128

__global__ void soma(int *a, int *b, int *c) {
    int indice = blockIdx.x * blockDim.x + threadIdx.x;
    if (indice < TAM) c[indice] = a[indice] + b[indice];
}

int main(void) {

    int *a_host, *b_host, *c_host;
    int *a_device, *b_device, *c_device;

    // Alocação dos arrays da CPU:
    a_host = (int *) malloc(TAM * sizeof(int));
    b_host = (int *) malloc(TAM * sizeof(int));
    c_host = (int *) malloc(TAM * sizeof(int));

    // Alocação dos arrays da GPU:
    cudaMalloc(&a_device, TAM * sizeof(int));
    cudaMalloc(&b_device, TAM * sizeof(int));
    cudaMalloc(&c_device, TAM * sizeof(int));

    // Preenchimento de a e b da CPU:
    for (int i = 0; i < TAM; i++) {
        a_host[i] = -i;
        b_host[i] = i * i;
    }

    // Cópia de a e b da CPU para a GPU:
    cudaMemcpy(a_device, a_host, TAM * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(b_device, b_host, TAM * sizeof(int), cudaMemcpyHostToDevice);

    int blocos_por_grade = (TAM + THREADS_POR_BLOCO - 1) / THREADS_POR_BLOCO;

    soma<<<blocos_por_grade,THREADS_POR_BLOCO>>>(a_device, b_device, c_device);

    // Cópia de c da GPU para a CPU:
    cudaMemcpy(c_host, c_device, TAM * sizeof(int), cudaMemcpyDeviceToHost);

    // Saída com parte do resultado:
    for (int i = 0; i < TAM; i += 500)
        printf("Índice %d: %d + %d = %d\n", i, a_host[i], b_host[i], c_host[i]);
    printf("\n");

    free(a_host);
    free(b_host);
    free(c_host);

    // Liberação de memória do device:
    cudaFree(a_device);
    cudaFree(b_device);
    cudaFree(c_device);

    return 0;
}

