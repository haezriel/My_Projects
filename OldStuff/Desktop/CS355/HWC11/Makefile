ifeq "$(shell uname)" "Darwin"
CXX=clang++
else
CXX=g++
endif
CXXOPTS=-Wall -std=c++11
ALL=grid1 grid2 binomial

all: $(ALL)

JUNK=*.o *~ *.dSYM *.gch

clean:
	-rm -rf $(JUNK)

clobber:
	-rm -rf $(JUNK) $(ALL)

grid1: grid.cpp CharGrid1.cpp CharGrid1.h 
	$(CXX) $(CXXOPTS) -DCHARGRID1 grid.cpp CharGrid1.cpp -o $@

grid2: grid.cpp CharGrid2.h 
	$(CXX) $(CXXOPTS) -DCHARGRID2 grid.cpp -o $@

binomial: binomial.cpp
	$(CXX) $(CXXOPTS) $^ -o $@
