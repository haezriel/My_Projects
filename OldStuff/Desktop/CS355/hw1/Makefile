CC=gcc
COPTS=-g -std=c99 -pedantic -Wall

ALL: scanner interpreter
clean:
	-rm -rf *.o *.dSYM scanner core *~

scanner: scanner.c
	$(CC) $(COPTS) -DTEST_SCANNER $^ -o $@

interpreter: scanner.o symtab.o turtle.o interpreter.o
	$(CC) $(COPTS) $^ -o $@ -lm
.c.o:
	$(CC) -c $(COPTS) $<

scanner.o: scanner.c scanner.h
scanner.o: scanner.c scanner.h
symtab.o: symtab.c symtab.h
interpreter.o: interpreter.c scanner.h symtab.h turtle.h
turtle.o: turtle.c turtle.h
