.data
	
	out_1: .asciiz "Digite um número: " 	  # armazenando out_1 como string na memória
	out_2: .asciiz "Esse número é par " 	  # armazenando out_2 como string na memória
	out_3: .asciiz "Esse número é ímpar"      # armazenando out_3 como string na memória
	

.text .globl main

	main: 
		
		li $v0, 4                     # carregando código para imprimir uma string
		la $a0, out_1                 # carregando &out_1 da memória para registrador $a0
		syscall 	                  # imprimindo string
		
		li $v0, 5	                  # carregando código para ler um inteiro
		syscall		                  # lendo inteiro (vai para o registrador $v0)
		
		li $t0, 2                     # carregando valor 2 para o registrador $t0
		
		div $v0, $t0                  # dividindo $v0 por $t0 (o resultado vai para os registradors hi e lo)
	
		mfhi $s0                      # carregando o resto da divisão para o registrador $s0
			
		li $v0, 4                     # carregando código para imprimir uma string
				
		beq $s0, $zero, branch_even   # pulando para branch_even se o conteúdo de $s0 for zero
		j branch_odd                  # pulando para branch_odd caso contrário
	
	
		branch_even:
			
			la $a0, out_2	          # carregando &out_2 da memória para registrador $a0
			syscall 		          # imprimindo string
			
     		j branch_end              # pulando para o final do programa
		
		branch_odd:
		
			la $a0, out_3	          # carregando &out_3 da memória para registrador $a0
			syscall 		          # imprimindo string
		
		branch_end:
		
			li $v0, 10                # carregando código para finalizar o programa
			syscall                   # finalizando o programa
