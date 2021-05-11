.data
    .align 0
        out_1: .asciiz "Digite um número (0,999]: "    # armazenando out_1 como string na memória
        out_2: .asciiz "\nNúmero invertido: "          # armazenando out_2 como string na memória

.text
    .globl main

    main:

        li $t0 999                         # carregando o valor 999 (valor máximo) para $t0

        check_input:
            la $a0, out_1                  # carregando o endereço de memória da primeira string para $a0
            jal print_message              # imprimindo string apontada por $a0
            jal read_integer               # lendo um inteiro da entrada padrão (vai para $v0)
            ble $v0, $zero, check_input    # voltando para o label check_input se o valor digitado for menor ou igual a zero
            bgt $v0, $t0, check_input      # voltando para o label check_input se o valor digitado for maior que o conteúdo de $t0 (999)

        move $s0, $v0                      # carregando o conteúdo de $v0 (inteiro lido) para $s0 
        
        la $a0, out_2                      # carregando o endereço de memória da segunda string para $a0
        jal print_message                  # imprimindo string apontada por $a0

        move $a0, $s0                      # carregando o conteúdo de $s0 (inteiro lido) para $a0 
        jal reverse_number                 # obtendo o inteiro com a ordem dos dígitos invertida (vai para $v0) 
        
        move $a0, $v0                      # carregando o conteúdo de $v0 (inteiro invertido) para $a0 
        jal print_integer                  # imprimindo o inteiro em $a0

        jal finish_program                 # finalizando o programa



    # Funções Complementares: 

    print_message:
        li $v0, 4                          # carregando código para imprimir uma string
        syscall                            # imprimindo string (endereço em $a0)
        jr $ra                             # retornando para o endereço de retorno da função


    read_integer:
        li $v0, 5                          # carregando código para ler um inteiro
        syscall                            # lendo inteiro (vai para $v0)
        jr $ra                             # retornando para o endereço de retorno da função

    
    print_integer:
        li $v0, 1                          # carregando código para imprimir um inteiro
        syscall                            # imprimindo inteiro em $a0
        jr $ra                             # retornando para o endereço de retorno da função
    

    reverse_number:
        move $v0, $zero                    # inicializando o conteúdo de $v0 com 0 (o valor final será o número invertido)
        move $t1, $a0                      # copiando o número passado como parâmetro para o registrador $t1
        move $t2, $zero                    # inicializando o conteúdo de $t2 com 0 (representará o "índice" do dígito atual)
        li $t3, 10                         # inicializando o conteúdo de $t3 com 10 (será constante)

        loop:
            ble $t1, $zero, loop_end       # pulando para o fim do loop se não houver mais nenhum dígito em $t1

            div $t1, $t3                   # dividindo o conteúdo de $t1 (o que falta inverter) pelo de $t3 (10)
            mflo $t1                       # guardando o quociente da divisão em $t1
            mfhi $t4                       # guardando o resto da divisão em $t4 (dígito atual)

            # Devemos calcular o peso do novo dígito, o qual será 10 ^ (2 - "índice" do dígito atual), ou seja, $t3 ^ (2 - $t2)

            li $t5, 2                      # inicializando o conteúdo de $t5 com 2 
            sub $t5, $t5, $t2              # e subtraindo $t2. $t5 será o expoente inicial
            li $t6, 1                      # inicializando o conteúdo de $t6 com 1 (potência de 10 atual)

            pow:
                beq $t5, $zero, pow_end    # pulando para o fim da potenciação se o conteúdo de $t5 (valor do expoente) for 0
                mul $t6, $t6, $t3          # guardando em $t6 (potência de 10 atual) a multiplicação de seu conteúdo por $t3 (10)
                addi $t5, $t5, -1          # decrementando o valor de $t5 (expoente)
                j pow                      # pulando para o label pow
            pow_end:

            mul $t4, $t4, $t6              # multiplicando o valor de $t4 (dígito atual) pelo de $t6 (potência de 10 calculada)
            add $v0, $v0, $t4              # adicionando o dígito atual com seu peso em $v0 (onde ficará armazenado o número final invertido)

            addi $t2, $t2, 1               # incrementando o valor de $t2 ("índice" do dígito atual)

            j loop                         # pulando para o label pool
        loop_end:

        jr $ra                             # retornando para o endereço de retorno da função


    finish_program:
        li $v0, 10                         # carregando código para finalizar o programa 
        syscall                            # finalizando o programa
