SOURCES = ./sources
INCLUDES = ./includes
FLAGS = -Wall -Werror -I
EXEC = exec

all:
	@gcc -o $(EXEC) $(SOURCES)/*.c $(FLAGS) $(INCLUDES)

run:
	@./$(EXEC)

zip:
	@zip -r Ex3 $(SOURCES) $(INCLUDES) Makefile