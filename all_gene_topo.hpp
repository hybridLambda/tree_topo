/*
 * hybrid-Lambda is used to simulate gene trees given species network under 
 * coalescent process.
 * 
 * Copyright (C) 2010 -- 2014 Sha (Joe) Zhu
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
 * 	\brief Header file for all_gene_topo.cpp */


#include <iostream>
#include <vector>
#include <string>
#include <cassert>
//#include <deque>

using namespace std;

class GeneTopoList {
    private:
        vector < string > TipLabels;
        void extract_TipLabels_from_TreeStr ( string &tree_str );
        //deque < string > TreeList;
        vector < string > TreeList;
        vector < string > TreeList_tmp;
        string str_tmp;
        size_t end_of_label_or_bl( string &in_str, size_t i );
        string extract_label( string &in_str, size_t i);
        void init();
        string add_new_taxa_at_int(string &in_str, size_t i, string &newly_added );
        string add_new_taxa_at_tip(string &in_str, size_t i, string &newly_added, string added_to );
        size_t Parenthesis_balance_index_backwards( string &in_str, size_t i );
    public:
        //GeneTopoList ( size_t NumberOfTaxa );
        GeneTopoList ( string tree_str );
        ~GeneTopoList(){};
};

