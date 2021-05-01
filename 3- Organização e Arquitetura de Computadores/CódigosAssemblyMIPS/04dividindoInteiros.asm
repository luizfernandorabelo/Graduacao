.data 
	
	integer1: .word 10   # armazenando um int32 na memória
	integer2: .word 3    # armazenando um int32 na memória


.text .globl main
	
	main:
	
		lw $t0, integer1   # carregando integer1 da memória para o registrador $t0
		lw $t1, integer2   # carregando integer2 da memória para o registrador $t1
				
		div $t0, $t1       # dividindo $t0 por $t1 (o resultado vai para os registradors hi e lo)
	
		mflo $s0           # carregando o resultado inteiro da divisão para o registrador $s0
		mfhi $s1           # carregando o resto da divisão para o registrador $s1
	
		li $v0, 10         # carregando código para finalizar o programa
		syscall            # finalizando o programa
