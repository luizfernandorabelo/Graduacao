CC = gcc
PROG_NAME = buscas
SOURCES = main.c ./Util/myNumber.c ./Util/mySearch.c ./Util/numberArrayAloc.c
HEADERS = ./Util 
COMPILATION_FLAGS = -lm -Wall -Werror -I

all: compile

compile:
	@$(CC) -o $(PROG_NAME) $(SOURCES) $(COMPILATION_FLAGS) $(HEADERS)

run:
	@./$(PROG_NAME)

zip: 
	@zip -r $(PROG_NAME).zip Makefile Comentario.pdf AnaliseFormal.pdf $(SOURCES) $(HEADERS) 

clean:
	@rm -r $(PROG_NAME)
