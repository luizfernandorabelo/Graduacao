CC = gcc
PROG_NAME = dec2bin 
SOURCES = ./sources/main.c ./sources/item.c ./sources/pilhaEncadeada.c
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
