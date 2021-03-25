CC = gcc
PROG_NAME = uspotify
SOURCES = ./sources/*.c
INCLUDES = ./includes
COMPILATION_FLAGS = -lm -Wall -Werror -I
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: compile

compile:
	@$(CC) -o $(PROG_NAME) $(SOURCES) $(COMPILATION_FLAGS) $(INCLUDES)

run:
	@./$(PROG_NAME)

grind:
	@valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) 

clean:
	@rm -r $(PROG_NAME)

zip:
	@zip -r uspotify.zip $(SOURCES) $(INCLUDES) Makefile Comentarios.pdf
