CC = gcc
PROG_NAME = cesar
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
run8:
	@./$(PROG_NAME) < ./Casos/8.in > ./Casos/8.myout
run9:
	@./$(PROG_NAME) < ./Casos/9.in > ./Casos/9.myout
run10:
	@./$(PROG_NAME) < ./Casos/10.in > ./Casos/10.myout
run11:
	@./$(PROG_NAME) < ./Casos/11.in > ./Casos/11.myout
run12:
	@./$(PROG_NAME) < ./Casos/12.in > ./Casos/12.myout
run13:
	@./$(PROG_NAME) < ./Casos/13.in > ./Casos/13.myout
run14:
	@./$(PROG_NAME) < ./Casos/14.in > ./Casos/14.myout

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
grind8:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/8.in > ./Casos/8.myout 
grind9:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/9.in > ./Casos/9.myout 
grind10:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/10.in > ./Casos/10.myout 
grind11:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/11.in > ./Casos/11.myout 
grind12:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/12.in > ./Casos/12.myout 
grind13:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/13.in > ./Casos/13.myout 
grind14:
	valgrind $(VALGRIND_FLAGS) ./$(PROG_NAME) < ./Casos/14.in > ./Casos/14.myout 

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
diff8:
	diff ./Casos/8.myout ./Casos/8.out
diff9:
	diff ./Casos/9.myout ./Casos/9.out
diff10:
	diff ./Casos/10.myout ./Casos/10.out
diff11:
	diff ./Casos/11.myout ./Casos/11.out
diff12:
	diff ./Casos/12.myout ./Casos/12.out
diff13:
	diff ./Casos/13.myout ./Casos/13.out
diff14:
	diff ./Casos/14.myout ./Casos/14.out

