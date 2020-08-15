CC = gcc
PROG_NAME = filtro
COMPILATION_FLAGS = -lm -Wall -Werror
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes


# Targets Principais:
all: compile

compile:
	@$(CC) -o $(PROG_NAME) $(PROG_NAME).c $(COMPILATION_FLAGS)

run:
	@./$(PROG_NAME)


#Targets para Verificação dos Casos de Teste:
run1:
	@./$(PROG_NAME) < ./Casos/Caso1/1.in > ./Casos/Caso1/1.myout
run2:
	@,/$(PROG_NAME) < ./Casos/Caso2/2.in > ./Casos/Caso2/2.myout
run3:
	@./$(PROG_NAME) < ./Casos/Caso3/3.in > ./Casos/Caso3/3.myout
run4:
	@./$(PROG_NAME) < ./Casos/Caso4/4.in > ./Casos/Caso4/4.myout
run5:
	@./$(PROG_NAME) < ./Casos/Caso5/5.in > ./Casos/Caso5/5.myout
run6:
	@./$(PROG_NAME) < ./Casos/Caso6/6.in > ./Casos/Caso6/6.myout
run7:
	@./$(PROG_NAME) < ./Casos/Caso7/7.in > ./Casos/Caso7/7.myout
run8:
	@./$(PROG_NAME) < ./Casos/Caso8/8.in > ./Casos/Caso8/8.myout
run9:
	@./$(PROG_NAME) < ./Casos/Caso9/9.in > ./Casos/Caso9/9.myout
run10:
	@./$(PROG_NAME) < ./Casos/Caso10/10.in > ./Casos/Caso10/10.myout
run11:
	@./$(PROG_NAME) < ./Casos/Caso11/11.in > ./Casos/Caso11/11.myout
run12:
	@./$(PROG_NAME) < ./Casos/Caso12/12.in > ./Casos/Caso12/12.myout
run13:
	@./$(PROG_NAME) < ./Casos/Caso13/13.in > ./Casos/Caso13/13.myout
run14:
	@./$(PROG_NAME) < ./Casos/Caso14/14.in > ./Casos/Caso14/14.myout

grind1:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/Caso1/1.in > ./Casos/Caso1/1.myout
grind2:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/Caso2/2.in > ./Casos/Caso2/2.myout
grind3:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/Caso3/3.in > ./Casos/Caso3/3.myout
grind4:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/Caso4/4.in > ./Casos/Caso4/4.myout
grind5:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/Caso5/5.in > ./Casos/Caso5/5.myout
grind6: 
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/Caso6/6.in > ./Casos/Caso6/6.myout
grind7:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/Caso7/7.in > ./Casos/Caso7/7.myout
grind8:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/Caso8/8.in > ./Casos/Caso8/8.myout
grind9:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/Caso9/9.in > ./Casos/Caso9/9.myout
grind10:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/Caso10/10.in > ./Casos/Caso10/10.myout
grind11:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/Caso11/11.in > ./Casos/Caso11/11.myout
grind12:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/Caso12/12.in > ./Casos/Caso12/12.myout
grind13:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/Caso13/13.in > ./Casos/Caso13/13.myout
grind14:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/Caso14/14.in > ./Casos/Caso14/14.myout

diff1:
	diff ./Casos/Caso1/1.myout ./Casos/Caso1/1.out
diff2:
	diff ./Casos/Caso2/2.myout ./Casos/Caso2/2.out
diff3:
	diff ./Casos/Caso3/3.myout ./Casos/Caso3/3.out
diff4:
	diff ./Casos/Caso4/4.myout ./Casos/Caso4/4.out
diff5:
	diff ./Casos/Caso5/5.myout ./Casos/Caso5/5.out
diff6:
	diff ./Casos/Caso6/6.myout ./Casos/Caso6/6.out
diff7:
	diff ./Casos/Caso7/7.myout ./Casos/Caso7/7.out
diff8:
	diff ./Casos/Caso8/8.myout ./Casos/Caso8/8.out 
diff9:
	diff ./Casos/Caso9/9.myout ./Casos/Caso9/9.out
diff10:
	diff ./Casos/Caso10/10.myout ./Casos/Caso10/10.out 
diff11:
	diff ./Casos/Caso11/11.myout ./Casos/Caso11/11.out 
diff12:
	diff ./Casos/Caso12/12.myout ./Casos/Caso12/12.out 
diff13:
	diff ./Casos/Caso13/13.myout ./Casos/Caso13/13.out 
diff14:
	diff ./Casos/Caso14/14.myout ./Casos/Caso14/14.out 
