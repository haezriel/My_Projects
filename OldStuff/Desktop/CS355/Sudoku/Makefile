ifeq "$(shell uname)" "Darwin"
CXX=clang++
else
CXX=g++
endif
#CPPFLAGS=-std=c++11 -Wall -g
CPPFLAGS=-std=c++11 -O3
ALL=solvesudoku

all: $(ALL)

JUNK=*.o *~ *.dSYM *.gch *.zip *.gz

clean:
	-rm -rf $(JUNK)

clobber:
	-rm -rf $(JUNK) $(ALL)

.cpp.o:
	$(CXX) -c $(CPPFLAGS) $<

solvesudoku.o: solvesudoku.cpp SudokuGrid.h

solvesudoku: solvesudoku.o
	$(CXX) $(CPPFLAGS) $^ -o $@

zip:
	zip ss.zip README.txt Makefile *.{cpp,h}

archive:
	tar czvf ss.tar.gz README.txt Makefile *.{cpp,h}
