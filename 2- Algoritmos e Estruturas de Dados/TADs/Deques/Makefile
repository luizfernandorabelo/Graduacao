CC = gcc
FLAGS = -Wall -Werror -Wextra -lm
SET = item.c dequeTeste.c
PROG_NAME = exec

all:
	$(CC) -c *.c

sequencial:
	$(CC) -o $(PROG_NAME) $(SET) dequeSequencialCircular.c

encadeada:
	$(CC) -o $(PROG_NAME) $(SET) dequeEncadeadaCircular.c

run:
	./$(PROG_NAME)

clean:
	rm -r *.o