/*
 * hybrid-Lambda is used to simulate gene trees given species network under
 * coalescent process.
 *
 * Copyright (C) 2010 -- 2015 Sha (Joe) Zhu
 *
 * This file is part of hybrid-Lambda.
 *
 * hybrid-Lambda is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*! \file all_gene_topo.hpp
 *  \brief Header file for all_gene_topo.cpp */


#include <iostream>
#include <vector>
#include <string>
#include <cassert>
//#include <deque>

#ifndef NDEBUG
#define dout std::cout
#else
#pragma GCC diagnostic ignored "-Wunused-value"
#define dout 0 && std::cout
#endif

#ifndef NDEBUG
#define GeneTopoListdout (std::cout << "      GeneTopoList ")
#else
#pragma GCC diagnostic ignored "-Wunused-value"
#define GeneTopoListdout 0 && (std::cout << "      GeneTopoList ")
#endif

using namespace std;

class GeneTopoList {
    friend class HybridCoal;
    friend class TopoApp;
    friend class TestGeneTopoList;
    //deque < string > TreeList;
    vector < string > TreeList;
    vector < string > TipLabels;
    vector < string > TreeList_tmp;
    size_t Parenthesis_balance_index_backwards( string &in_str, size_t i );
    size_t end_of_label_or_bl( string &in_str, size_t i );
    string str_tmp;
    string add_new_taxa_at_int(string &in_str, size_t i, string &newly_added );
    string add_new_taxa_at_tip(string &in_str, size_t i, string &newly_added, string added_to );
    string extract_label( string &in_str, size_t i);
    
    void run();
    void init();
    void core();
    void extract_TipLabels_from_TreeStr ( string &tree_str );
    void finalize();

    //GeneTopoList ( size_t NumberOfTaxa );
    //GeneTopoList ( string tree_str );
    GeneTopoList (){};
    GeneTopoList ( vector < string > &TipLabels_in );
    ~GeneTopoList(){};
};


class TopoApp {
    int argc_;
    int argc_i;
    char * const* argv_;
    string tmp_input_str;
    string prefix;
    GeneTopoList * topo_list_;

    void init(){
        argc_i = 1;
        topo_list_ = new GeneTopoList();
    }

    void parse(){
        if ( argc_ == 1 ){
            cout << "USEAGE: ./topo a b c d e "<<endl;
            return;
        }

        while ( argc_i < argc_ ){
            std::string argv_i ( argv_[argc_i] );
            topo_list_->TipLabels.push_back( argv_i );
            argc_i++;
        }
    }

    void finalize(){
        if ( topo_list_->TipLabels.size() > 1 ) {
            topo_list_ ->run();
        } {
            cout << " Please provide at least two taxon names." <<endl;
        }
        for ( size_t i = 0; i < topo_list_->TreeList.size(); i++){
            cout << topo_list_->TreeList[i] << endl;
        }
    }


  public:
    TopoApp ( int argc, char *argv[] ) : argc_(argc), argv_(argv) {
        this->init();
        this->parse();
        this->finalize();
    }
    ~TopoApp () { delete this->topo_list_; }
};

