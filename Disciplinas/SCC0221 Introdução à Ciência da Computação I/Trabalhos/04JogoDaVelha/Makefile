CC = gcc
PROG_NAME = velha
COMPILATION_FLAGS = -lm -Wall -Werror
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes


# Targets Principais:
all: compile

compile:
	@$(CC) -o $(PROG_NAME) $(PROG_NAME).c $(COMPILATION_FLAGS)

run:
	@./$(PROG_NAME)

clean:
	@rm -r $(PROG_NAME)
	@rm -r ./Casos/*.myout 


#Targets para Verificação dos Casos de Teste:
run1:
	@./$(PROG_NAME) < ./Casos/1.in > ./Casos/1.myout
run2:
	@./$(PROG_NAME) < ./Casos/2.in > ./Casos/2.myout
run3:
	@./$(PROG_NAME) < ./Casos/3.in > ./Casos/3.myout
run4:
	@./$(PROG_NAME) < ./Casos/4.in > ./Casos/4.myout
run5:
	@./$(PROG_NAME) < ./Casos/5.in > ./Casos/5.myout
run6:
	@./$(PROG_NAME) < ./Casos/6.in > ./Casos/6.myout
run7:
	@./$(PROG_NAME) < ./Casos/7.in > ./Casos/7.myout

grind1:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/1.in > ./Casos/1.myout 
grind2:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/2.in > ./Casos/2.myout 
grind3:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/3.in > ./Casos/3.myout 
grind4:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/4.in > ./Casos/4.myout 
grind5:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/5.in > ./Casos/5.myout 
grind6: 
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/6.in > ./Casos/6.myout 
grind7:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/7.in > ./Casos/7.myout 

diff1:
	diff ./Casos/1.myout ./Casos/1.out
diff2:
	diff ./Casos/2.myout ./Casos/2.out
diff3:
	diff ./Casos/3.myout ./Casos/3.out
diff4:
	diff ./Casos/4.myout ./Casos/4.out
diff5:
	diff ./Casos/5.myout ./Casos/5.out
diff6:
	diff ./Casos/6.myout ./Casos/6.out
diff7:
	diff ./Casos/7.myout ./Casos/7.out
