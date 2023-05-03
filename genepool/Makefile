CXXFLAGS = -g -std=c++17 -Wall -Wextra -Werror -Wno-unused-parameter
CXX      = g++

# These targets don't create any files:
.PHONY: clean

# Magic Variables!
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#  $@ is the name of the target
#  $+ is a list of all the dependencies
#  $< is the first dependency

genepool: main.o GenePool.o Person.o Query.o
	${CXX} $(CXXFLAGS) -o $@ $+


main.o: main.cpp GenePool.h Person.h Query.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

GenePool.o: GenePool.cpp GenePool.h Person.h Enums.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Person.o: Person.cpp Person.h Enums.h
	${CXX} $(CXXFLAGS) -c -o $@ $<

Query.o: Query.cpp Query.h GenePool.h Person.h Enums.h
	${CXX} $(CXXFLAGS) -c -o $@ $<


clean:
	rm -f genepool main.o GenePool.o Person.o Query.o
