#include <stdio.h>
#include <cuda.h>

__global__ void hello_world(int chamada) {
    printf("Hello World da GPU da %d° chamada, bloco = %d e trhead = %d\n", chamada, blockIdx.x, threadIdx.x);
}

int main(void) {

    int blocos, threads;

    blocos = 1; threads = 10;
    hello_world<<<blocos,threads>>>(1);
    cudaDeviceSynchronize();  // barreira

    blocos = 10; threads = 1;
    hello_world<<<blocos,threads>>>(2);
    cudaDeviceSynchronize();  // barreira 

    printf("Hello World da CPU\n");

    cudaDeviceSynchronize();  // barreira 

    return 0;
}
