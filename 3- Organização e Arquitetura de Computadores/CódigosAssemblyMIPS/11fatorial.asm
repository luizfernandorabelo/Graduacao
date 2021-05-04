.data
    .align 0
        out_1: .asciiz "Digite um número: "    # armazenando out_1 como string na memória
        out_2: .asciiz "Fatorial é "           # armazenando out_2 como string na memória

.text
    .globl main
    
    main:
        li $v0, 4                         # carregando código para imprimir uma string
        la $a0, out_1                     # carregando &out_1 da memória para registrador $a0
        syscall                           # imprimindo string

        li $v0, 5                         # carregando código para ler um inteiro
        syscall                           # lendo inteiro (vai para o registrador $v0)
        
        move $t0, $v0                     # movendo o conteúdo do registrador $v0 para $t0
        subi $t1, $t0, 1                  # guardando a diferença entre o conteúdo de $v0 e 1 no registrador $t1
        li $t2, 1                         # carregando 1 para o registrador $t2 (será "contador")

        # TODO: tratamento para valores menores que 1 
        
        factorial:
            bgt $t2, $t1, factorial_end   # pulando para o fim do fatorial se o conteúdo de $t2 for maior que o de $t1
            mul $s0, $t0, $t2             # multiplicando o conteúdo de $t0 pelo de $t2 e guradando em $s0
            move $t0, $s0                 # movendo o conteúdo de $s0 para $t0
            addi $t2, $t2, 1              # adicionando 1 ao conteúdo do registrador $t2
            j factorial                   # voltando ao laço do fatorial
        factorial_end:
        
        li $v0, 4                         # carregando código para imprimir uma string
        la $a0, out_2                     # carregando &out_2 da memória para registrador $a0
        syscall                           # imprimindo string
        
        li $v0, 1                         # carregando código para imprimir inteiro
        move $a0, $t0                     # movendo o conteúdo do registrador $t0 para $a0
        syscall                           # imprimindo inteiro
        
        li $v0, 10                        # carregando código para finalizar o programa
        syscall                           # finalizando o programa
