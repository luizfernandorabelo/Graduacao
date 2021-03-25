CC = gcc
PROG_NAME = pontocirculo
SOURCES = ./sources/main.c ./sources/point.c ./sources/circle.c
HEADERS = ./includes 
COMPILATION_FLAGS = -lm -Wall -Werror -I

all: compile

compile:
	@$(CC) -o $(PROG_NAME) $(SOURCES) $(COMPILATION_FLAGS) $(HEADERS)

run:
	@./$(PROG_NAME)

zip: 
	@zip -r $(PROG_NAME).zip Makefile sources/*.c includes/*.h 

clean:
	@rm -r $(PROG_NAME)
