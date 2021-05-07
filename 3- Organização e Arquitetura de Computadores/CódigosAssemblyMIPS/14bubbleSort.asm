.data
    .align 0
        out_1: .asciiz "Vetor desordenado: "   # armazenando out_1 como string na memória
        out_2: .asciiz "\nVetor ordenado: "    # armazenando out_2 como string na memória

    .align 2
        array: .word  7, 5, 2, 1, 1, 3, 4      # carregando o array que será ordenado para a memória


.text
    .globl main

    main:
        li $s0, 7                              # carregando o valor 7 para $s0 (length do array)

        la $a0, out_1                          # carregando endereço da primeira string da memória para $a0
        jal print_message                      # imprimindo a string apontada por $a0

        jal print_array                        # imprimindo o vetor da memória

        jal bubble_sort                        # ordenando o vetor e regravando na memória 

        la $a0, out_2                          # carregando endereço da segunda string da memória para $a0
        jal print_message                      # imprimindo a string apontada por $a0

        jal print_array                        # imprimindo o vetor da memória

        jal finish_program                     # finalizando o programa
    
    
    # Funções Complementares:

    print_message:
        li $v0, 4                              # carregando código para imprimir uma string
        syscall                                # imprimindo string (endereço em $a0)
        jr $ra                                 # retornando para o endereço de retorno da função


    print_array:
        li $v0, 1                              # carregando código para imprimir inteiro
        li $t0, 0                              # inicializando o conteúdo de $t0 (variável "contadora") com 0
        la $t3, array                          # carregando endereço de momória do primeiro byte do array para $t3 

        print_loop:
            beq $t0, $s0, print_loop_end       # se os conteúdos de $t0 e $s0 forem iguais, pula para a label print_loop_end ($s0 = length do vetor) 

            lw $a0, 0 ($t3)                    # carregando o inteiro do vetor na posição apontada por $t3 para $a0
            syscall                            # imprimindo o inteiro em $a0

            addi $t0, $t0, 1                   # incrementando o conteúdo de $t0 (variável "contadora")
            addi $t3, $t3, 4                   # incrementando o endereço atual do vetor
            j print_loop                       # voltando para o começo do loop
        print_loop_end:

        jr $ra                                 # retornando para o endereço de retorno da função
    
    
    bubble_sort:
        li $t0, 0                              # inicializando o conteúdo de $t0 (variável i) com 0                            
        bubble_loop1:
            beq $t0, $s0, bubble_loop1_end     # pulando para o label bubble_loop1_end se os conteúdos $t0 e $s0 forem iguais ($s0 = length do vetor)

            addi $t1, $s0, -1                  # inicializando o conteúdo de $t1 (variável j) com length do vetor - 1
            la $t2, array                      # carregando o endereço de memória do primeiro byte do array para $t2
            addi $t2, $t2, 24                  # incrementando o conteúdo de $t2 para o endereço do último inteiro do vetor

            bubble_loop2:
                beq $t0, $t1, bubble_loop2_end # pulando para o label bubble_loop2_end se os conteúdo de $t0 e $t1 forem iguais (i==j)

                lw $t3, 0 ($t2)                # carregando para o registrador $t3 o conteúdo do vetor no endereço apontado por $t2
                lw $t4, -4 ($t2)               # carregando para o registrador $t3 o conteúdo do vetor no endereço apontado por $t2 - 4

                bgt $t4, $t3, swap             # pulando para o label swap se o conteúdo de $t4 for maior que o de $t3
                j swap_end                     # pulando para o label swap_end caso contrário

                swap:
                    sw $t3, -4 ($t2)           # escrevendo o conteúdo do registrador $t3 na posição de memória apontada por $t2 - 4
                    sw $t4, 0 ($t2)            # escrevendo o conteúdo do registrador $t4 na posição de memória apontada por $t2
                swap_end:

                addi $t2, $t2, -4              # decrementando o endereço atual do vetor
                addi $t1, $t1, -1              # decrementando o conteúdo de $t1 (variável j)
                j bubble_loop2                 # pulando para o label bubble_loop2
            bubble_loop2_end:

            addi $t0, $t0, 1                   # incrementando o conteúdo de $t0 (variável i)
            j bubble_loop1                     # pulando para o label bubble_loop1
        bubble_loop1_end:

        jr $ra                                 # retornando para o endereço de retorno da função


    finish_program:
        li $v0, 10                             # carregando código para finalizar o programa 
        syscall                                # finalizando o programa
