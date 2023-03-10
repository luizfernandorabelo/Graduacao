#include <stdio.h>
#include <cuda.h>

__device__ int soma_chamada_device(int a, int b) {
    return a + b;
}

__global__ void soma_chamada_host(int a, int b, int *c) {
    *c = soma_chamada_device(a, b);
}

int main(void) {

    int a = 2, b  = 7;
    int c_host, *c_device;

    // Alocação de memória no device:
    cudaMalloc(&c_device, sizeof(int));

    soma_chamada_host<<<1,1>>>(a, b, c_device);

    /*
        A função "cudaMemcpy" possui uma barreira implícita,
        sendo, então, desnecessário colocar "cudaDeviceSynchronize"
        após a chamada do kernel a ser executado no device. 
    */

    // Cópia de memória do device para a da cpu:
    cudaMemcpy(&c_host, c_device, sizeof(int), cudaMemcpyDeviceToHost);

    printf("%d + %d = %d\n", a, b, c_host);

    // Liberação de memória no device:
    cudaFree(c_device);

    return 0;
}
