// ŷ = a * x̂ + ŷ 

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define TAM 16

__global__ void saxpy(int *x, int *y, int a) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i < TAM) y[i] = a * x[i] + y[i];
}

int main(void) {

    int *x_host, *y_host, *x_device, *y_device;

    // Preenchimento de x "identidade" (para facilitar teste):
    x_host = (int *) malloc(TAM * sizeof(int));
    for (int i = 0; i < TAM; i++)
        x_host[i] = i + 1;

    // Alocação e cópia para o device:
    cudaMalloc(&x_device, TAM * sizeof(int));
    cudaMemcpy(x_device, x_host, TAM * sizeof(int), cudaMemcpyHostToDevice);

    // Preenchimento de y com zeros (para facilitar teste):
    y_host = (int *) calloc(TAM, sizeof(int));

    // Alocação e cópia para o device:
    cudaMalloc(&y_device, TAM * sizeof(int));
    cudaMemcpy(y_device, y_host, TAM * sizeof(int), cudaMemcpyHostToDevice);

    int threads_por_bloco = 256;
    int total_blocos = (TAM + threads_por_bloco - 1) / threads_por_bloco;  // mínimo = 1 bloco

    saxpy<<<total_blocos,threads_por_bloco>>>(x_device, y_device, 2);

    // Cópia do resultado do device para o host:
    cudaMemcpy(y_host, y_device, TAM * sizeof(int), cudaMemcpyDeviceToHost);
    
    // Impressão do resultado:
    for (int i = 0; i < TAM; i++)
        printf("%d ", y_host[i]);
    printf("\n");

    free(x_host);
    free(y_host);

    // Liberação de memória do device:
    cudaFree(x_device);
    cudaFree(y_device);

    return 0;
}
