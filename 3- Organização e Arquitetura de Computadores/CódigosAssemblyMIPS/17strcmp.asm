.data
    .align 0
        string_1: .asciiz "abcdefghik"    # guardando string_1 na memória
        string_2: .asciiz "abcdefghil"    # guardando string_2 na memória

.text
    .globl main

    main:

        la $a0, string_1                             # carregando &string1 para $a0
        la $a1, string_2                             # carregando &string2 para $a1
        jal str_cmp                                  # chamando strcmp para as strings nos endereços apontados pelos registradores $a0 e $a1

        move $a0, $v0                                # copiando o resultado da comparação para o registrador $a0
        jal print_integer                            # imprimindo o conteúdo do registrador $a0

        jal finish_program                           # finalizando o programa


    # Funções Complementares:

    str_len:

        li $v0, 0                                    # inicializando o registrador de retorno com 0

        str_len_loop:
            lb $t0, 0 ($a0)                          # armazenando em $t0 o caractere da string no endereço apontado por $a0
            beq $t0, $zero, str_len_end_loop         # pulando para o fim do loop se o caractere armazenado em $t0 for '\0' (fim de string)
            addi $v0, $v0, 1                         # incrementando o valor de retorno
            addi $a0, $a0, 1                         # incrementando o valor do endereço do caractere atual
            j str_len_loop                           # voltando para o início do loop
        str_len_end_loop:

        jr $ra                                       # retornando para o endereço de retorno da função

    
    str_cmp:

        # Deveremos chamar a função str_len e, por isso, é necessário guardar os valores de $a0 e $ra na stack para que eles não sejam sobrescritos
        # Guardaremos também na stack os comprimentos das strings apontadas por $a0 e $a1

        # NOTA: Não é realmente necessário chamar a função str_len para resolvermos o problema. Fiz dessa forma para treinar a manipulação do stack pointer 

        addi $sp, $sp, -8                            # decrementando stack pointer (empilhando 2 inteiros)
        sw $ra, 4 ($sp)                              # guardando o conteúdo de $ra na stack
        sw $a0, 0 ($sp)                              # guardando o conteúdo de $a0 na stack

        jal str_len                                  # calculando comprimento da string em $a0 (vai para $v0)
        addi $sp, $sp, -4                            # decrementando stack pointer (empilhando 1 inteiro)
        sw $v0, 0 ($sp)                               # armazenando o comprimento da string na stack

        move $a0, $a1                                # copiando o conteúdo de $a1 (endereço da segunda string passada por parâmetro) para $a0 
        jal str_len                                  # calculando comprimento da string em $a0 (vai para $v0)
        addi $sp, $sp, -4                            # decrementando stack pointer (empilhando 1 inteiro)
        sw $v0, 0 ($sp)                               # armazenando o comprimento da string na stack 

        # Como não chamaremos nenhuma função nova, podemos desempilhar tudo o que foi salvo na stack

        lw $t1, 0 ($sp)                              # recuperando comprimento da segunda string e armazenando em $t1
        lw $t0, 4 ($sp)                              # recuperando comprimento da primeira string e armazenando em $t0
        lw $a0, 8 ($sp)                              # recuperando o conteúdo original de $a0 e re-armazenando em $a0
        lw $ra, 12($sp)                              # recuperando o endereço de retorno inicial da função e re-armazenando em $ra
        addi $sp, $sp, 16                            # incrementando stack pointer (desempilhando 4 inteiros)

        li $v0, 0                                    # inicializando o conteúdo do registrador de retorno com 0

        str_cmp_loop:

            beq $t0, $zero, str_cmp_end_loop         # pulando para o label de fim do loop se for fim da string apontada por $a0
            beq $t1, $zero, str_cmp_end_loop         # pulando para o label de fim do loop se for fim da string apontada por $a1
            
            lb $t2, 0 ($a0)                          # carregando o caractere atual apontado por $a0 para $t2
            lb $t3, 0 ($a1)                          # carregando o caractere atual apontado por $a1 para $t3

            blt $t2, $t3, str_cmp_negative           # pulando para retorno negativo se o caractere atual da primeira string for menor que o atual da segunda
            bgt $t2, $t3, str_cmp_positive           # pulando para retorno positivo se o caractere atual da primeira string for maior que o atual da segunda

            addi $a0, $a0, 1                         # incrementando o endereço do caractere atual apontado por $a0
            addi $a1, $a1, 1                         # incrementando o endereço do caractere atual apontado por $a1
            addi $t0, $t0, -1                        # decrementando o número de caracteres restantes a serem analizados na primeira string
            addi $t1, $t1, -1                        # decrementando o número de caracteres restantes a serem analizados na segunda string

            j str_cmp_loop                           # pulando para o início do loop

        str_cmp_end_loop:
            blt $t0, $t1, str_cmp_negative           # pulando para retorno negativo se o comprimento da primeira string for menor que o da segunda
            bgt $t0, $t1, str_cmp_positive           # pulando para retorno positivo se o comprimento da primeira string for maior que o da segunda
            j str_cmp_return                         # pulando para o fim da função

        str_cmp_negative:
            li $v0, -1                               # carregando o valor -1 no registrador de retorno da função
            j str_cmp_return                         # pulando para o fim da função
        
        str_cmp_positive:
            li $v0, 1                                # carregando o valor 1 no registrador de retorno da função
            j str_cmp_return                         # pulando para o fim da função

        str_cmp_return:
            jr $ra                                   # retornando para o endereço de retorno da função

        
    print_integer:
        li $v0, 1                                    # carregando código para imprimir um inteiro
        syscall                                      # imprimindo inteiro em $a0
        jr $ra                                       # retornando para o endereço de retorno da função


    finish_program:
        li $v0, 10                                   # carregando código para finalizar o programa 
        syscall                                      # finalizando o programa
