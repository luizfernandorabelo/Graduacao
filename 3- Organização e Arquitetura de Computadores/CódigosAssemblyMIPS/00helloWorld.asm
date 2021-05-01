.data # Segmento de Dados na Memória Principal

	message: .asciiz "Hello, world!" # armazenando string "Hello, world!" na variável 'message'


.text # Área de Instruções do Programa
	
	.globl main # criando um rótulo global para o ponto de entrada do processo

	main:
	
		li $v0, 4         # carregando código para impressão de string
		la $a0, message   # colocando a mensagem como argumento de função
		syscall           # executando a operação cujo código está no registrador $v0
		
		li $v0, 10        # carregando código para finalizar o programa
		syscall           # executando a operação cujo código está no registrador $v0
		