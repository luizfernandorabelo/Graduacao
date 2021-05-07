.data
    .align 0
        # Armazenando as strings out(1-4) na memória 
        out_1: .asciiz "Digite um inteiro qualquer: " 
        out_2: .asciiz "Esse inteiro é positivo!"
        out_3: .asciiz "Esse inteiro é negativo!"
        out_4: .asciiz "Zero é um número neutro!"
        

.text
    .globl main

    main:

        la $a0, out_1                     # carregando o endereço da primeira string da memória para $a0
        jal print_message                 # imprimindo a string em apontada por $a0

        jal read_integer                  # lendo um inteiro da entrada padrão (vai para $v0)

        beq $v0, $zero, input_zero        # se a entrada do usuário for zero, vai para o label input_zero

        move $a0, $v0                     # copiando o conteúdo de $v0 para $a0
        jal is_positive                   # verificando se a entrada foi positiva (resultado booleano vai para $v0)

        beq $v0, $zero, input_negative    # se a entrada for negativa, vai para o label input_negative

        j input_positive                  # se não, vai para o label input_positive

        input_positive:
            la $a0, out_2                 # carregando o endereço da segunda string da memória para $a0
            j input_end                   # pulando para o label input_end
        input_negative:
            la $a0, out_3                 # carregando o endereço da terceira string da memória para $a0
            j input_end                   # pulando para o label input_end
        input_zero:
            la $a0, out_4                 # carregando o endereço da quarta string da memória para $a0
        input_end:

        jal print_message                 # imprimindo a string em apontada por $a0

        jal finish_program                # finalizando o programa


# Funções Complementares

    read_integer:
        li $v0, 5                         # carregando código para ler um inteiro
        syscall                           # lendo inteiro (vai para $v0)
        jr $ra                            # retornando para o endereço de retorno da função
    
    is_positive:
        bgt $a0, $zero, true              # se o conteúdo de $a0 for zero, pula para a label true
        j false                           # se não, pula para a label false
        true:
            li $v0, 1                     # carregando o valor 1 para $v0 (representando verdadeiro)
            j end                         # pulando para a label end
        false:
            li $v0, 0                     # carregando o valor 0 para $v0 (representando falso)
        end:
            jr $ra                        # retornando para o endereço de retorno da função
    
    print_message:
        li $v0, 4                         # carregando código para imprimir uma string
        syscall                           # imprimindo string (endereço em $a0)
        jr $ra                            # retornando para o endereço de retorno da função

    finish_program:
        li $v0, 10                        # carregando código para finalizar o programa 
        syscall                           # finalizando o programa
