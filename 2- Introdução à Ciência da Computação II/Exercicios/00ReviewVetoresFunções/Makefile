CC = gcc
PROG_NAME = review
COMPILATION_FLAGS = -lm -Wall -Werror
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: compile

compile:
	@$(CC) -o $(PROG_NAME) $(PROG_NAME).c $(COMPILATION_FLAGS)

run:
	@./$(PROG_NAME)

clean:
	@rm -r $(PROG_NAME)
	@rm -r ./Casos/*.myout 