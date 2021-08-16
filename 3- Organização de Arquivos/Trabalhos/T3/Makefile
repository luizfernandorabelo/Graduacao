SRC = ./sources
INC = ./includes
EXE = trabalho3
FLAGS = -Wall -Werror -I

all: compile

compile:
	@gcc -o $(EXE) $(SRC)/*.c $(FLAGS) $(INC) -g

run:
	@./$(EXE)

zip:
	@zip -r Trabalho3 $(SRC) $(INC) Makefile