COMPILER = g++
VERSION = ""
FLAGS = -O3 -g -std=c++0x -DVERSION=\"${VERSION}\"
SOURCE = all_gene_topo.cpp

.PHONY: all
all: clean_all topo topo_dbg

topo:
	${COMPILER} ${FLAGS} -DNDEBUG -o topo ${SOURCE} main.cpp

topo_dbg:
	${COMPILER} ${FLAGS} -o topo_dbg ${SOURCE} main.cpp

.PHONY: clean
clean:
	rm -f topo topo_dbg

.PHONY: clean_all
clean_all: clean
	rm -f *.o
