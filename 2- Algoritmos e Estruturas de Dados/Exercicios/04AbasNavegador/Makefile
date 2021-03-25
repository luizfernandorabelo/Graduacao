CC = gcc
PROG_NAME = abas
SOURCES = ./sources/main.c ./sources/aba.c ./sources/listaDuplaEncadeada.c 
HEADERS = ./includes 
COMPILATION_FLAGS = -lm -Wall -Werror -I

all: compile

compile:
	@$(CC) -o $(PROG_NAME) $(SOURCES) $(COMPILATION_FLAGS) $(HEADERS)

run:
	@./$(PROG_NAME)

zip: 
	@zip -r $(PROG_NAME).zip Makefile $(SOURCES) $(HEADERS) 

clean:
	@rm -r $(PROG_NAME)
