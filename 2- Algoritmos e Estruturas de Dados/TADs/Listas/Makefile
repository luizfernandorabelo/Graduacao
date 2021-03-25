CC = gcc
FLAGS = -Wall -Werror -Wextra -lm
SET = item.c listaTeste.c
PROG_NAME = exec

all:
	$(CC) -c *.c

sequencial:
	$(CC) -o $(PROG_NAME) $(SET) listaSequencial.c

encadeada:
	$(CC) -o $(PROG_NAME) $(SET) listaEncadeada.c

dupla-encadeada:
	$(CC) -o $(PROG_NAME) $(SET) listaDuplaEncadeada.c

encadeada-circular:
	$(CC) -o $(PROG_NAME) $(SET) listaEncadeadaCircular.c

run:
	./$(PROG_NAME)

clean:
	rm -r *.o