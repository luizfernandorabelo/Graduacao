CC = gcc
PROG_NAME = miniGoogleBot
OBJECTS = site.o bufferSites.o servidor.o csvManager.o googleBotIO.o palavrasChave.o
FLAGS = -std=c99 -Wall -Werror -I ./includes

all: compile 

compile:
	@$(CC) -c ./sources/site.c $(FLAGS) 
	@$(CC) -c ./sources/servidor.c $(FLAGS) 
	@$(CC) -c ./sources/csvManager.c $(FLAGS)
	@$(CC) -c ./sources/googleBotIO.c $(FLAGS)
	@$(CC) -c ./sources/bufferSites.c $(FLAGS) 
	@$(CC) -c ./sources/palavrasChave.c $(FLAGS)
	@$(CC) -o $(PROG_NAME) ./sources/main.c $(OBJECTS) $(FLAGS) 

run:
	@./$(PROG_NAME)

clean: 
	@rm -r $(OBJECTS)

zip:
	@zip -r $(PROG_NAME).zip Makefile inputs.txt README.txt Comentarios.pdf ./sources ./includes