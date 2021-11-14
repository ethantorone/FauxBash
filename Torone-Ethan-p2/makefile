COMP = gcc
FLAGS = -Wall -pedantic-errors

compile:
	$(COMP) $(FLAGS) -o head head.c
	$(COMP) $(FLAGS) -o tail tail.c
	$(COMP) $(FLAGS) -o true true.c
	$(COMP) $(FLAGS) -o false false.c
	$(COMP) $(FLAGS) -o wc wc.c
	$(COMP) $(FLAGS) -o env env.c
clean:
	rm -f head
	rm -f tail
	rm -f true
	rm -f false
	rm -f wc
	rm -f env
