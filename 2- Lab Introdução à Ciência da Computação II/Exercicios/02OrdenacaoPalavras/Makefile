PROG_NAME = ordenaPalavras 
SOURCES = ordenaPalavras.c ./Util/*.c
INCLUDE = ./Util
INFO_FILES = targetsMakefile.txt Comentario.pdf ./Graficos ./Inputs ./PlotData ./Tempos
COMPILATION_FLAGS = -Wall -Werror -lm -I
EXECUTIONS_NUMBER = 10

all: compile 

compile:
	@gcc -o $(PROG_NAME) $(SOURCES) $(COMPILATION_FLAGS) $(INCLUDE) -DRUN_CODES

run:
	./$(PROG_NAME)

time:
	@gcc -o $(PROG_NAME) $(SOURCES) $(COMPILATION_FLAGS) $(INCLUDE) -DCOUNT_TIME
	@./$(PROG_NAME) 14k.txt $(EXECUTIONS_NUMBER) 1
	@./$(PROG_NAME) 14k.txt $(EXECUTIONS_NUMBER) 2
	@./$(PROG_NAME) 14k.txt $(EXECUTIONS_NUMBER) 3
	@./$(PROG_NAME) 29k.txt $(EXECUTIONS_NUMBER) 1
	@./$(PROG_NAME) 29k.txt $(EXECUTIONS_NUMBER) 2
	@./$(PROG_NAME) 29k.txt $(EXECUTIONS_NUMBER) 3
	@./$(PROG_NAME) 58k.txt $(EXECUTIONS_NUMBER) 1
	@./$(PROG_NAME) 58k.txt $(EXECUTIONS_NUMBER) 2
	@./$(PROG_NAME) 58k.txt $(EXECUTIONS_NUMBER) 3
	@./$(PROG_NAME) 116k.txt $(EXECUTIONS_NUMBER) 1
	@./$(PROG_NAME) 116k.txt $(EXECUTIONS_NUMBER) 2
	@./$(PROG_NAME) 116k.txt $(EXECUTIONS_NUMBER) 3

plot: 
	@gnuplot "./PlotData/plotdataBubble" -p
	@gnuplot "./PlotData/plotdataInsertion" -p
	@gnuplot "./PlotData/plotdataMerge" -p

zip: 
	@zip -r $(PROG_NAME) Makefile $(INFO_FILES) $(SOURCES) $(INCLUDE) 

clean:
	@rm -r ./Tempos/*.txt
