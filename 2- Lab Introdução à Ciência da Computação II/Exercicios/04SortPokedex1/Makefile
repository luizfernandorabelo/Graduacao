MAIN = Main.c
BINARY = main
LIB = pokemon/PokeDex.c pokemon/Pokemon.c pokemon/Poketype.c

all:
	@gcc -Wall $(MAIN) Sorting.c -L. -l_pokemon -o $(BINARY)

run:
	@./$(BINARY)

obj:
	@gcc -Wall -pedantic -Werror -Wextra -c -fPIC $(LIB)

lib:
	@ar -rc lib_pokemon.a *.o

ranlib:
	@ranlib lib_pokemon.a

debug:
	@gcc -DDEBUG -Wall $(MAIN) -L. -l_pokemon -o $(BINARY)

valgrind:
	@valgrind --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

zip:
	@zip -r pokesort *.c *.h Makefile lib_pokemon.a

clean:
	@rm *.o
