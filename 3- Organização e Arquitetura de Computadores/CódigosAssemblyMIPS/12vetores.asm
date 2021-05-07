.data
    .align 2
        vetor0: .word 1, 2, 3        # carregando vetor0 como um vetor com os valores 1, 2 e 3 na memória
        vetor1: .word 4, 5, 6        # carregando vetor1 como um vetor com os valores 4, 5 e 6 na memória
        vetor2: .word 0, 0, 0        # carregando vetor2 como um vetor zerado na memória

.text
    .globl main

    main:
        la $t0, vetor0               # carregando o endereço do primeiro byte do vetor0 em $t0
        la $t1, vetor1               # carregando o endereço do primeiro byte do vetor1 em $t1
        la $t2, vetor2               # carregando o endereço do primeiro byte do vetor2 em $t2

        li $t3, 2                    # carregando o valor 2 para o registrador $t3 (contador decrescente)

        loop:
            lw $t4, 0 ($t0)          # carregando o inteiro do endereço apontado $t0 para $t4
            lw $t5, 0 ($t1)          # carregando o inteiro do endereço apontado $t1 para $t5
            add $t6, $t4, $t5        # adicionando os conteúdos de $t4 e $t5 e guardando em $t6
            sw $t6, 0 ($t2)          # armazenando o conteúdo de $t6 no endereço de memória apontado por $t2

            addi $t0, $t0, 4         # adicionando 4 ao conteúdo do registrador $t0 (apontando para a próxima posição de memória)
            addi $t1, $t1, 4         # adicionando 4 ao conteúdo do registrador $t1 (apontando para a próxima posição de memória)
            addi $t2, $t2, 4         # adicionando 4 ao conteúdo do registrador $t2 (apontando para a próxima posição de memória)
            addi $t3, $t3, -1        # decrementando o valor de $t3 (contador decrescente)  
            bge $t3, $zero, loop     # voltando para o início do loop se o conteúdo de $t3 for >= 0

        li $v0, 10                   # carregando código para finalizar o programa
        syscall                      # finalizando o programa
