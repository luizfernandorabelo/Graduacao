.data 
	
	out_1: .asciiz "O valor aproximado de PI é "       # guardando out_1 como string na memória
	out_2: .asciiz "\nDigite um outro número real: "   # guardando out_2 como string na memória
	out_3: .asciiz "Você digitou o número: "           # guardando out_3 como string na memória
	
	PI: .double 3.14159                                # guardando PI como double na memória
	ZEROlf: .double 0.0                                # guardando ZEROlf como double na memória
 
 
.text .globl main
		
		main:
		
			ldc1 $f30, ZEROlf       # carregando o conteúdo de ZEROlf para os registradores $f30/31 (terão papel similar ao $zero)
		
			li $v0, 4               # carregando código para imprimir string
			la $a0, out_1           # carregando &out_1 da memória para o registrador $a0
			syscall                 # imprimindo string

			li $v0, 3               # carregando código para imprimir double
			ldc1 $f12, PI           # carregando o conteúdo de PI para os registradores $f12/13
			syscall                 # imprimindo double
		
			li $v0, 4               # carregando código para imprimir string
			la $a0, out_2           # carregando &out_2 da memória para o registrador $a0
			syscall                 # imprimindo string
		
			li $v0, 7               # carregando código para ler double
			syscall                 # lendo double (o valor vai para os registradores $f0/1)
			
			li $v0, 4               # carregando código para imprimir string
			la $a0, out_3           # carregando &out_3 da memória para o registrador $a0
			syscall                 # imprimindo string
			
			li $v0, 3               # carregando código para imprimir double
			add.d $f12, $f0, $f30   # movendo $f0/1 para $f12/13 (*$f30/31 = 0)
			syscall                 # imprimindo double
		
			li $v0, 10              # carregando código para finalizar o programa
			syscall                 # finalizando o programa
			