CC = gcc
PROG_NAME = pgmManager 
SOURCES = ./src/*.c
INCLUDES = ./inc
COMPILATION_FLAGS = -lm -Wall -Werror -I
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: compile

compile:
	@$(CC) -o $(PROG_NAME) $(SOURCES) $(COMPILATION_FLAGS) $(INCLUDES)

run:
	@./$(PROG_NAME)

clean:
	@rm -r $(PROG_NAME)

zip:
	@zip -r pgm.zip Casos inc src Makefile


run1:
	@./$(PROG_NAME) < ./Casos/1/1.in > ./Casos/1/1.myout
run2:
	@./$(PROG_NAME) < ./Casos/2/2.in > ./Casos/2/2.myout
run3:
	@./$(PROG_NAME) < ./Casos/3/3.in > ./Casos/3/3.myout
run4:
	@./$(PROG_NAME) < ./Casos/4/4.in > ./Casos/4/4.myout
run5:
	@./$(PROG_NAME) < ./Casos/5/5.in > ./Casos/5/5.myout
run6:
	@./$(PROG_NAME) < ./Casos/6/6.in > ./Casos/6/6.myout
run7:
	@./$(PROG_NAME) < ./Casos/7/7.in > ./Casos/7/7.myout
run8:
	@./$(PROG_NAME) < ./Casos/8/8.in > ./Casos/8/8.myout
run9:
	@./$(PROG_NAME) < ./Casos/9/9.in > ./Casos/9/9.myout
run10:
	@./$(PROG_NAME) < ./Casos/10/10.in > ./Casos/10/10.myout
