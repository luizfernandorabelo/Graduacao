# Notas:
#     - shiftando um número em n casas para a esquerda, estamos multiplicando por 2^n
#     - shiftando um número em n casas para a direita, estamos dividindo por 2^n

.text
    .globl main
    
    main: li $t0, 1000    # carregando o valor 1000 no registrador $t0
    sll $s0, $t0, 1       # shiftando o valor de $t0 1 vez para a esquerda e guardando o resultado no registrador $s0
    sll $s1, $t0, 2       # shiftando o valor de $t0 2 vezes para a esquerda e guardando o resultado no registrador $s1
    sll $s2, $t0, 3       # shiftando o valor de $t0 3 vezes para a esquerda e guardando o resultado no registrador $s2
    
    srl $s3, $t0, 1       # shiftando o valor de $t0 1 vez para a direita e guardando o resultado no registrador $s3
    srl $s4, $t0, 2       # shiftando o valor de $t0 2 vezes para a direita e guardando o resultado no registrador $s4
    srl $s5, $t0, 3       # shiftando o valor de $t0 3 vezes para a direita e guardando o resultado no registrador $s5

    li $v0, 10            # carregando código para finalizar o programa
    syscall               # finalizando o programa
