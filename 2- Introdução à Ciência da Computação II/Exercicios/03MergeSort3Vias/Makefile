CC = gcc
PROG_NAME = merge3 
SRC = merge3.c
COMPILATION_FLAGS = -lm -Wall -Werror
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: compile

compile:
	@$(CC) -o $(PROG_NAME) $(SRC) $(COMPILATION_FLAGS)

run:
	@./$(PROG_NAME)

clean:
	@rm -r $(PROG_NAME)
	@rm -r ./Casos/*.myout 