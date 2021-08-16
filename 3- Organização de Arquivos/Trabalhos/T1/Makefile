SRC = ./sources
INC = ./includes
EXE = trabalho1 
FLAGS = -Wall -Werror -I

all: compile

compile:
	@gcc -o $(EXE) $(SRC)/*.c $(FLAGS) $(INC)

run:
	@./$(EXE)

zip:
	@zip -r Trabalho1 $(SRC) $(INC) Makefile