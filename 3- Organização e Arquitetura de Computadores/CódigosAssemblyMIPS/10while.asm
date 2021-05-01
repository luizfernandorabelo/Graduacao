.data
	
	out_1: .asciiz "Contando de 0 a 10: " 	  # armazenando out_1 como string na memória


.text .globl main

    main:

		li $v0, 4                     # carregando código para imprimir uma string
		la $a0, out_1                 # carregando &out_1 da memória para registrador $a0
		syscall 	                  # imprimindo string

        li $v0, 1                     # caregando código para imprimir um inteiro
        
        li $t0, 0                     # carregando o registrador $t0 com 0
        li $t1, 11                    # carregando o registrador $t1 com 11

        while:
            beq $t0, $t1, while_end   # pulando para while_end se os conteúdos de $t0 e $t1 forem iguais
            move $a0, $t0             # carregando o conteúdo de $t0 para $a0
            syscall                   # imprimindo o conteúdo de $t0
            addi $t0, $t0, 1          # incrementando o conteúdo de $t0 em 1
            j while                   # voltando para o while
        while_end:

		
        li $v0, 10                    # carregando código para finalizar o programa
        syscall                       # finalizando o programa
