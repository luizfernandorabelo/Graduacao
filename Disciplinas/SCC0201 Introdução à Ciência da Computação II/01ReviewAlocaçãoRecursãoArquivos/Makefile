CC = gcc
PROG_NAME = review
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
	@./$(PROG_NAME) < ./Casos/caso1.in > ./Casos/caso1.myout
run2:
	@./$(PROG_NAME) < ./Casos/caso2.in > ./Casos/caso2.myout
run3:
	@./$(PROG_NAME) < ./Casos/caso3.in > ./Casos/caso3.myout
run4:
	@./$(PROG_NAME) < ./Casos/caso4.in > ./Casos/caso4.myout
run5:
	@./$(PROG_NAME) < ./Casos/caso5.in > ./Casos/caso5.myout
run6:
	@./$(PROG_NAME) < ./Casos/caso6.in > ./Casos/caso6.myout
run7:
	@./$(PROG_NAME) < ./Casos/caso7.in > ./Casos/caso7.myout
run8:
	@./$(PROG_NAME) < ./Casos/caso8.in > ./Casos/caso8.myout

grind1:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/caso1.in > ./Casos/caso1.myout 
grind2:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/caso2.in > ./Casos/caso2.myout 
grind3:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/caso3.in > ./Casos/caso3.myout 
grind4:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/caso4.in > ./Casos/caso4.myout 
grind5:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/caso5.in > ./Casos/caso5.myout 
grind6: 
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/caso6.in > ./Casos/caso6.myout 
grind7:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/caso7.in > ./Casos/caso7.myout 
grind8:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/caso8.in > ./Casos/caso8.myout 

diff1:
	diff ./Casos/caso1.myout ./Casos/caso1.out
diff2:
	diff ./Casos/caso2.myout ./Casos/caso2.out
diff3:
	diff ./Casos/caso3.myout ./Casos/caso3.out
diff4:
	diff ./Casos/caso4.myout ./Casos/caso4.out
diff5:
	diff ./Casos/caso5.myout ./Casos/caso5.out
diff6:
	diff ./Casos/caso6.myout ./Casos/caso6.out
diff7:
	diff ./Casos/caso7.myout ./Casos/caso7.out
diff8:
	diff ./Casos/caso8.myout ./Casos/caso8.out 
