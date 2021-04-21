SOURCES = main.c ./Util/*.c
UTIL = ./Util/

all:
	@gcc -o exec $(SOURCES) -I $(UTIL)
	
run:
# n e p devem ser declarados na linha de comando. Exemplo: ./exec n=4 p=0.375
	@./exec $(n) ${p} 