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

/*! \file all_gene_topo.cpp
 *     \brief  Enumerate all possible tree topologies for given number of taxon */

#include "all_gene_topo.hpp"

//GeneTopoList::GeneTopoList( string tree_str ){
GeneTopoList::GeneTopoList( vector < string > &TipLabels_in ){
    this->TipLabels = TipLabels_in;
    //this->extract_TipLabels_from_TreeStr ( tree_str );
    assert ( this->TipLabels.size() >= 2 ) ;
    this->run();
}


void GeneTopoList::run(){
    this->init();
    this->core();
    this->finalize();
}


void GeneTopoList::core(){
    if ( this->TipLabels.size() == 2 ) return;
    for ( size_t tip_i = 2; tip_i < this->TipLabels.size() ; tip_i++ ){
        
        this->TreeList_tmp.clear();
        for ( size_t i = 0 ; i < this->TreeList.size(); i++ ){
            this->str_tmp = this->TreeList[i];
            for ( size_t i_str_len = 1; i_str_len < this->str_tmp.size(); ){
                if ( isalpha( this->str_tmp[i_str_len] ) || isdigit( this->str_tmp[i_str_len]) ){
                    string label = extract_label( this->str_tmp, i_str_len);
                    string new_topo = add_new_taxa_at_tip( str_tmp, i_str_len, this->TipLabels[tip_i], label);
                    GeneTopoListdout << new_topo << endl;
                    TreeList_tmp.push_back(new_topo);
                    i_str_len = label.size() + i_str_len;
                }
                else{
                    if ( this->str_tmp[i_str_len]==')' ){
                        string new_topo = add_new_taxa_at_int( str_tmp, i_str_len, this->TipLabels[tip_i]);
                        GeneTopoListdout << new_topo << endl;
                        TreeList_tmp.push_back( new_topo );
                    }
                    i_str_len++;
                }
            }
        }
        
        this->TreeList.clear();
        this->TreeList = this->TreeList_tmp;
    }
}

size_t GeneTopoList::Parenthesis_balance_index_backwards( string &in_str, size_t i ){
    size_t j = i;
    int num_b = 0;
    for ( ; j > 0 ; j-- ){
        if      ( in_str[j] == '(' ) num_b--;
        else if ( in_str[j] == ')' ) num_b++;
        else continue;
        if ( num_b == 0 ) break;
    }
    return j;
}


void GeneTopoList::finalize(){
    for ( size_t i = 0 ; i < this->TreeList.size(); i++ ){
        this->TreeList[i] += ";";
    }
}


string GeneTopoList::add_new_taxa_at_tip(string &in_str, size_t i, string &newly_added, string added_to ){
    string out_str = in_str;
    string new_cherry = "(" + newly_added + "," + added_to + ")";
    out_str.replace( i, added_to.size(), new_cherry );
    return out_str;
}


string GeneTopoList::add_new_taxa_at_int(string &in_str, size_t i, string &newly_added ){
    string out_str = in_str;
    size_t rev_dummy_i = this->Parenthesis_balance_index_backwards( in_str, i);
    size_t substr_len = i - rev_dummy_i + 1;
    string new_add_in = in_str.substr( rev_dummy_i, substr_len);
    new_add_in = "(" + new_add_in + "," + newly_added + ")";
    out_str.replace( rev_dummy_i, substr_len, new_add_in);
    return out_str;
}


string GeneTopoList::extract_label( string &in_str, size_t i ){
    size_t j = this->end_of_label_or_bl(in_str, i);
    return in_str.substr( i, j + 1 - i );
}


size_t GeneTopoList::end_of_label_or_bl( string &in_str, size_t i ){
    for ( size_t j = i; j < in_str.size(); j++){
        if      ( in_str[j+1] == ',' )    return j;
        else if ( in_str[j+1] == ')' )    return j;
        else if ( in_str[j+1] == ':' )    return j;
        else if ( in_str[j+1] == ';' )    return j;
        else continue;
    }
}


void GeneTopoList::extract_TipLabels_from_TreeStr( string &in_str ){
    for ( size_t i = 1; i < in_str.size(); ){
        if ( isalpha(in_str[i]) || isdigit(in_str[i]) ){
            string label = extract_label( in_str, i );
            GeneTopoListdout << label << endl;
            this->TipLabels.push_back(label);
            i += label.size();
        } else {
            i++;
        }
    }
}


void GeneTopoList::init(){
    string init_topo = "(" + this->TipLabels[0] + "," + this->TipLabels[1] + ")";
    GeneTopoListdout << init_topo << endl;
    this->TreeList.push_back ( init_topo );
}
