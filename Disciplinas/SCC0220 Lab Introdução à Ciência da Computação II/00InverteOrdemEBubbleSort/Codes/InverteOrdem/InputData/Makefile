PROGNAME = inverteOrdem
NEXECUTIONS = 1000

all: compile

compile:
	@gcc -o $(PROGNAME) $(PROGNAME).c ./Util/*.c -I ./Util

run:
	@./$(PROGNAME) 1 $(NEXECUTIONS)
	@./$(PROGNAME) 10 $(NEXECUTIONS)
	@./$(PROGNAME) 100 $(NEXECUTIONS)
	@./$(PROGNAME) 1000 $(NEXECUTIONS)
	@./$(PROGNAME) 2000 $(NEXECUTIONS)
	@./$(PROGNAME) 5000 $(NEXECUTIONS)
	@./$(PROGNAME) 10000 $(NEXECUTIONS)

plot: 
	@gnuplot "plotdata" -p

clean:
	@rm -r $(PROGNAME) 
	@rm ./OutputData/*.txt
