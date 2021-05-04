.data
    .align 0
        # Strings que serão impressas na saída:
        out_1: .asciiz "Digite o seu nome: "     # armazenando out_1 como string na memória
        out_2: .asciiz "Digite a sua idade: "    # armazenando out_2 como string na memória
        out_3: .asciiz "Seu nome é "             # armazenando out_3 como string na memória
        out_4: .asciiz "Você tem "               # armazenando out_4 como string na memória
        out_5: .asciiz " anos!"                  # armazenando out_5 como string na memória
        
        # String que será lida na entrada:
        inp_1: .space 30                         # reservando 30 bytes para o nome que será entrado pelo usuário

.text
    .globl main
    
    main:
        li $v0, 4        # carregando código para imprimir uma string
        la $a0, out_1    # carregando &out_1 da memória para registrador $a0
        syscall          # imprimindo string
    
        li $v0, 8        # carregando código para ler uma string
        la $a0, inp_1    # carregando para o registrador $a0 o endereço em que a string de entrada será armazenada
        la $a1, 30       # carregando para o registrador $a1 o número de bytes da string de entrada
        syscall          # lendo string
        
        li $v0, 4        # carregando código para imprimir uma string
        la $a0, out_2    # carregando &out_2 da memória para registrador $a0
        syscall          # imprimindo string

        li $v0, 5        # carregando código para ler um inteiro
        syscall          # lendo inteiro (vai para o registrador $v0)
        
        move $t0, $v0    # movendo o conteúdo do registrador $v0 para $t0
        
        li $v0, 4        # carregando código para imprimir uma string
        la $a0, out_3    # carregando &out_3 da memória para registrador $a0
        syscall          # imprimindo string
        
        la $a0, inp_1    # carregando &inp_1 da memória para registrador $a0
        syscall          # imprimindo string
        
        la $a0, out_4    # carregando &out_4 da memória para registrador $a0
        syscall          # imprimindo string
        
        li $v0, 1        # carregando código para imprimir inteiro
        move $a0, $t0    # movendo o conteúdo do registrador $t0 para $a0
        syscall          # imprimindo inteiro
        
        li $v0, 4        # carregando código para imprimir uma string
        la $a0, out_5    # carregando &out_5 da memória para registrador $a0
        syscall          # imprimindo string

        li $v0, 10       # carregando código para finalizar o programa
        syscall          # finalizando o programa
