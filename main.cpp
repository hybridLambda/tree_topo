#include "all_gene_topo.hpp"

int main ( int argc, char *argv[] ) {
    try {
        TopoApp ( argc, argv );
	}
	catch ( const exception &e ){
	    std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
