#include "D:\compiler\compiler\SyntaxAnalyzer13.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
/*
enum errsyntype{
	invalid_token,
	wrong_type,
	miss_semi,
};

*/
ofstream errorlog("errorLog.txt");
//___________________________________________________________
int isIn(int a, int c[], int r){
	for (int i = 0; i < r; i++){
		if (a == c[i]){
			return i;
		}
	}
	return -1;
}

//__________________________________________________________________
void error(int type){//find errors
	switch (type){
		case invalid_token:
			errorlog << "near line " << lc <<  " the token \"" + watch_a + "\": is inproper here." << endl;
			cout << "near line " << lc <<  " the token \"" + watch_a + "\": is inproper here." << endl;
			break;
		case wrong_type:
			errorlog << "near line " << lc << " unmatched type when \"" + watch_a + "\": detected." << endl;
			cout << "near line " << lc << " unmatched type when \"" + watch_a + "\": detected." << endl;
			break; 
		case miss_semi:
			cout << "near line " << lc << " the token " + watch_a + ": there might be a \';\' missing\n";
			errorlog << "near line " << lc << " the token " + watch_a + ": there might be a \';\' missing\n";
			break;
		case not_a_const:
			cout << "near line " << lc << " the token: " << watch_a << ": is not a constant.";
			errorlog << "near line " << lc << " the token: " << watch_a << ": is not a constant.";
			break;
		case err_para:
			cout << "near line " << lc << " the token " + watch_a +": there should be some parameters, but not.";
			errorlog << "near line " << lc << " the token " + watch_a +": there should be some parameters, but not.";
			break;
		case miss_lparent:
			cout << "near line " << lc << " the token " + watch_a +": there may be a '(' missing. " << endl;
			errorlog << "near line " << lc << " the token " + watch_a +": there may be a '(' missing. " << endl;
			break;
		case miss_rparent:
			cout << "near line " << lc << " the token " + watch_a +": there may be a ')' missing. " << endl;
			errorlog << "near line " << lc << " the token " + watch_a +": there may be a ')' missing. " << endl;
			break;
		case miss_lbrace:
			cout << "near line " << lc << " the token " + watch_a +": there may be a '{' missing. \n";
			errorlog << "near line " << lc << " the token " + watch_a +": there may be a '{' missing. \n";
			break;
		case miss_rbrace:
			cout << "near line " << lc << " the token " + watch_a +": there may be a '}' missing. \n";
			errorlog << "near line " << lc << " the token " + watch_a +": there may be a '}' missing. \n";
			break;
		case invalid_ident:
			cout << "near line " << lc << " the token " + watch_a + ": is not a valid identifier.\n";
			errorlog << "near line " << lc << " the token " + watch_a + ": is not a valid identifier.\n";
			break;
		case miss_func:
			cout << "near line " << lc << " the token " + watch_a + ": is not a valid function identifier.\n";
			errorlog << "near line " << lc << " the token " + watch_a + ": is not a valid function identifier.\n";
			break;
		case not_array:
			cout << "near line " << lc << " the token " + watch_a + ": is not a valid array identifier.\n";
			errorlog << "near line " << lc << " the token " + watch_a + ": is not a valid array identifier.\n";
			break;
		case miss_rbracket:
			cout << "near line " << lc << " the token " + watch_a + ": there might be a \']\' missing.\n";
			errorlog << "near line " << lc << " the token " + watch_a + ": there might be a \']\' missing.\n";
			break;
		case undefined_identifier:
			cout << "near line " << lc << " the token " + watch_a + ": hasn't been defined yet.\n";
			errorlog << "near line " << lc << " the token " + watch_a + ": hasn't been defined yet.\n";
			break;
		case no_ret_val:
			cout << "near line " << lc << " the token " + watch_a + ": is not a function with return value.\n";
			errorlog << "near line " << lc << " the token " + watch_a + ": is not a function with return value.\n";
			break;
		case miss_asn:
			cout << "near line " << lc << " the token " + watch_a + ": there might be a \'=\' missing.\n";
			errorlog << "near line " << lc << " the token " + watch_a + ": there might be a \'=\' missing.\n";
			break;
		case bad_asn:
			cout << "near line " << lc << " the token " + watch_a + ": it cannot be assigned.\n";
			errorlog << "near line " << lc << " the token " + watch_a + ": it cannot be assigned.\n";
			break;
		case if_else_not_pair:
			cout << "near line " << lc << " the token " + watch_a + " : show up without a former \'if\'.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : show up without a former \'if\'.\n";
			break;
		case cdt_incomplete:
			cout << "near line " << lc << " the token " + watch_a + " : there is a incomplete condition\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : there is a incomplete condition\n";
			break;
		case switch_failed:
			cout << "near line " << lc << " the token " + watch_a + " : switch statement failed\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : switch statement failed\n";
			break;
		case case_failed:
			cout << "near line " << lc << " the token " + watch_a + " : case subsentence failed\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : case subsentence failed\n";
			break;
		case miss_colon:
			cout << "near line " << lc << " the token " + watch_a + " : there might be a \':\' missing.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : there might be a \':\' missing.\n";
			break;
		case para_incompatible:
			cout << "near line " << lc << " the token " + watch_a + " : the number of parameters is not right.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : the number of parameters is not right.\n";
			break;
		case bad_scf:
			cout << "near line " << lc << " the token " + watch_a + " : the scanf sentence failed.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : the scanf sentence failed.\n";
			break;
		case bad_prt:
			cout << "near line " << lc << " the token " + watch_a + " : the printf sentence failed.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : the printf sentence failed.\n";
			break;
		case bad_ret_val:
			cout << "near line " << lc << " the token " + watch_a + " : return value is not so suitable.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : return value is not so suitable.\n";
			break;
		case bad_definition:
			cout << "near line " << lc << " the token " + watch_a + " : constant definition and variable definition is not in the right place.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : constant definition and variable definition is not in the right place.\n";
			break;
		case duplicated_definition:
			cout << "near line " << lc << " the token " + watch_a + ": has been defined.\n";
			errorlog << "near line " << lc << " the token " + watch_a + ": has been defined.\n";
			break;
		case bad_dcl_head:
			cout << "near line " << lc << " the token " + watch_a + " : declare head has failed.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : declare head has failed.\n";
			break;
		case bad_expression:
			cout << "near line " << lc << " the token " + watch_a + " : expression has failed.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : expression has failed.\n";
			break;
		case bad_func_definition:
			cout << "near line " << lc << " the token " + watch_a + " : function definition has failed.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : function definition has failed.\n";
			break;
		case default_failed:
			cout << "near line " << lc << " the token " + watch_a + " : default has failed.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : default has failed.\n";
			break;
		case bad_const_definition:
			cout << "near line " << lc << " the token " + watch_a + " : a constant definition has failed.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : a constant definition has failed.\n";
			break;
		case bad_para_table:
			cout << "near line " << lc << " the token " + watch_a + " : a parameter table has failed.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : a parameter table has failed.\n";
			break;
		case bad_cst_var_sequence:
			cout << "near line " << lc << " the token " + watch_a + " : a constant definition is behind the variable definition.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : a constant definition is behind the variable definition.\n";
			break;
		case bad_ret_stc:
			cout << "near line " << lc << " the token " + watch_a + " : a return sentence has failed.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : a return sentence has failed.\n";
			break;
		case bad_vlu_para_table:
			cout << "near line " << lc << " the token " + watch_a + " : a value parameter table has failed.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : a value parameter table has failed.\n";
			break;
		case bad_stm_cln:
			cout << "near line " << lc << " the token " + watch_a + " : statement column has failed.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : statement column has failed.\n";
			break;
		case bad_var_definition:
			cout << "near line " << lc << " the token " + watch_a + " : there may be a bad variable definition.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : there may be a bad variable definition.\n";
			break;
		case not_ret_func:
			cout << "near line " << lc << " the token " + watch_a + " : this is not a function.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : this is not a function.\n";
			break;
		case miss_ret_val:
			cout << "near line " << lc << " the token " + watch_a + " : return sentence miss.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : return sentence miss.\n";
			break;
		case miss_ret_val_1:
			cout << "near line " << lc << " the token " + watch_a + " : return value miss.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : return value miss.\n";
			break;
		case else_without_if:
			cout << "near line " << lc << " the token " + watch_a + " : an else without if.\n";
			errorlog << "near line " << lc << " the token " + watch_a + " : an else without if.\n";
			break;
	}
}
void testSkip(int c[], int r){// jump the wrong token to the next may-be right one
	int has_next = 1;// if there are still has some tokens that can be read.
	for (   ;has_next;has_next = syn_get_sym(1)){// if syn_get_sym() return 0
		if (isIn(syn_sym, c, r) >= 0){
			return;
		}
	}
	return;
}
//
void testToken(int c[], int r, int e){// correst the errors and report it 
	// what'st in the c is the may-be next correct token
	int has_next = 1;// if there are still has some tokens that can be read.
	int find_flag = 0;
	for (   ;has_next;has_next = syn_get_sym(1)){// if syn_get_sym() return 0
		if (isIn(syn_sym, c, r) >= 0){
			return;
		}
		else{
			if (find_flag <= 0){	
				error(e);
				find_flag++;
			}
		}
	}
	return;
}