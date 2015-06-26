COMPILER = g++
VERSION = ""
FLAGS = -O3 -g -std=c++0x -DVERSION=\"${VERSION}\"
SOURCE = all_gene_topo.cpp

.PHONY: all
all: topo topo_dbg

topo: all_gene_topo.hpp all_gene_topo.cpp main.cpp
	${COMPILER} ${FLAGS} -DNDEBUG -o topo ${SOURCE} main.cpp

topo_dbg: all_gene_topo.hpp all_gene_topo.cpp main.cpp
	${COMPILER} ${FLAGS} -o topo_dbg ${SOURCE} main.cpp

# Tester flags
unittests_CXXFLAGS = -DUNITTEST -DNDEBUG -std=c++0x -DVERSION=\"${VERSION}\"
unittests_LDADD = -lcppunit -ldl

test_src = test_topo.cpp  ${SOURCE}

unittest: all_gene_topo.hpp all_gene_topo.cpp test_runner.cpp  test_topo.cpp
	${COMPILER} ${unittests_CXXFLAGS} ${test_src} test_runner.cpp -o unittest ${unittests_LDADD}

.PHONY: clean
clean:
	rm -f topo topo_dbg

.PHONY: clean_all
clean_all: clean
	rm -f *.o
