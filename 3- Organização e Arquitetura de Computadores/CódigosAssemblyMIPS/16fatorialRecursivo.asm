.data
    .align 0
        out_1: .asciiz "Digite um número positivo: "    # armazenando out_1 como string na memória
        out_2: .asciiz "Fatorial é "                    # armazenando out_2 como string na memória

.text
    .globl main
    
    main:

        read_positive_integer:
            la $a0, out_1                            # carregando &out_1 da memória para registrador $a0
            jal print_string                         # imprimindo string apontada por $a0

            li $v0, 5                                # carregando código para ler um inteiro
            syscall                                  # lendo inteiro (vai para o registrador $v0)
            blt $v0, $zero, read_positive_integer    # voltando para ler inteiro novamente se o valor digitado for negativo
        
        move $a0, $v0                                # carregando o conteúdo de $v0 (inteiro lido) para $a0
        jal factorial                                # calculando o fatorial do conteúdo de $a0 (retorno vai para $v0)

        move $s0, $v0                                # copiando o conteúdo de $v0 (fatorial calculdo) para $s0

        la $a0, out_2                                # carregando &out_2 da memória para registrador $a0
        jal print_string                             # imprimindo string apontada por $a0
        
        move $a0, $s0                                # copiando o conteúdo de $s0 (fatorial calculdado) para $a0
        jal print_integer                            # imprimindo conteúdo de $a0
        
        jal finish_program                           # finalizando o programa


    factorial:

        li $v0, 1                                    # carregando o valor 1 para $v0 (valor de retorno inicial)

        recursive_call:
        
            addi $sp, $sp, -8                        # decrementando o stack pointer (empilhando 2 inteiros)

            sw $ra, 4 ($sp)                          # guardando o endereço de retorno da função na stack
            sw $a0, 0 ($sp)                          # guardando o argumento da função (n atual) na stack

            beq $a0, $zero, return                   # finalizando a chamada recursiva se o valor de $a0 for 0

            addi $a0, $a0, -1                        # decrementando o argumento atual da função (para calcular fatorial de n - 1)
            jal recursive_call                       # continuando com a chamada recursiva

            lw, $a0, 0 ($sp)                         # recuperando o valor do argumento (n atual) da stack 
            mul $v0, $v0, $a0                        # multiplicando os conteúdos de $v0 por $a0 e guardando em $v0

        return:
            lw $ra, 4 ($sp)                          # recuperando o valor do argumento (n atual) da stack 
            lw $a0, 0 ($sp)                          # recuperando o valor do endereço de retorno da stack 
            addi $sp, $sp, 8                         # incrementando o stack pointer (desempilhando 2 inteiros)
            jr $ra                                   # retornando para o endereço de retorno da função


    print_string:
        li $v0, 4                                    # carregando código para imprimir uma string
        syscall                                      # imprimindo string (endereço em $a0)
        jr $ra                                       # retornando para o endereço de retorno da função


    print_integer:
        li $v0, 1                                    # carregando código para imprimir um inteiro
        syscall                                      # imprimindo inteiro em $a0
        jr $ra                                       # retornando para o endereço de retorno da função


    finish_program:
        li $v0, 10                                   # carregando código para finalizar o programa 
        syscall                                      # finalizando o programa
