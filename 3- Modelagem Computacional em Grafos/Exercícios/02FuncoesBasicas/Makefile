SOURCES = main.cpp ./Util/*.cpp
INCLUDES = ./Util
EXEC = exec

all:
	@g++ -o $(EXEC) $(SOURCES) -I $(INCLUDES) -Wall -Werror

run:
	@./$(EXEC)

zip:
	@zip -r Ex02 main.cpp $(INCLUDES) Makefile