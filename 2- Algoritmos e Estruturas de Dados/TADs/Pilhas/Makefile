CC = gcc
FLAGS = -Wall -Werror -Wextra -lm
SET = item.c pilhaTeste.c
PROG_NAME = exec

all:
	$(CC) -c *.c

sequencial:
	$(CC) -o $(PROG_NAME) $(SET) pilhaSequencial.c

encadeada:
	$(CC) -o $(PROG_NAME) $(SET) pilhaEncadeada.c

run:
	./$(PROG_NAME)

clean:
	rm -r *.o