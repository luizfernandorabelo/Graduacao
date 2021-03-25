CC = gcc
FLAGS = -Wall -Werror -Wextra -lm
SET = item.c filaTeste.c
PROG_NAME = exec

all:
	$(CC) -c *.c

sequencial:
	$(CC) -o $(PROG_NAME) $(SET) filaSequencialCircular.c

encadeada:
	$(CC) -o $(PROG_NAME) $(SET) filaEncadeadaCircular.c

run:
	./$(PROG_NAME)

clean:
	rm -r *.o