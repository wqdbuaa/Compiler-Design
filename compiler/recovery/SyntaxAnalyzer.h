#include "G:\School Files Noooooooootice\CompilerDesign\compiler\compiler\lexicalAnalyzer.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
//int get_sym()
/*
enum  symbols_list {
    intcon = 1, charcon,
    constsy, voidsy, mainsy , whilesy , switchsy , casesy, defaultsy, scanfsy, printfsy, returnsy , ifsy, elsesy, //reserved word
    idsy = 20,
    integer , character,
    strings,
    plussy, minussy,
    starsy , dividesy,
    comma, period, colon, semicolon, lparent , lbracket, lbrace, rparent , rbracket, rbrace ,
    lss, leq , gtr, geq, eql , neq, asn
};//all the memorial words.
*/
string syn_symbol = "";// stands for the syntax type
void clearSS(){
	syn_symbol = "";
}

int syn_typ_sym = 0;// to document the type of the definition, char or ints
bool isIntCstDefinition(){
	clearSS();
	if (sym == intcon){// if the current sym is int
		get_sym();
		if (sym == idsy){
			get_sym();
			if (sym == asn){
				get_sym();
				if (sym == unsinteger || sym == integer){
					get_sym();
					if (sym == comma){
						isIntCstDefinition();
					}
					else{
						//get_sym();
						//printf("this is an constant definition\n");
						syn_symbol = "this is an integer constant definition\n";
						return true;
					}
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;

	}
	else if (sym == comma){// if the current sym is int
		get_sym();
		if (sym == idsy){
			get_sym();
			if (sym == asn){
				get_sym();
				if (sym == unsinteger || sym == integer){
					get_sym();
					if (sym == comma){
						isIntCstDefinition();
					}
					else{
						//get_sym();
						//printf("this is an integer constant definition\n");
						syn_symbol = "this is an integer constant definition\n";
						return true;
					}
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;

	}
	else{
		return false;
	}
}
bool isCharCstDefinition(){
	clearSS();
	if (sym == charcon){// if the current sym is int
		get_sym();
		if (sym == idsy){
			get_sym();
			if (sym == asn){
				get_sym();
				if (sym == character){
					get_sym();
					if (sym == comma){
						isCharCstDefinition();
					}
					else{
						//get_sym();
						//printf("this is a character constant definition\n");
						syn_symbol = "this is a character constant definition\n";
						return true;
					}
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;

	}
	else if (sym == comma){// if the current sym is int
		get_sym();
		if (sym == idsy){
			get_sym();
			if (sym == asn){
				get_sym();
				if (sym == character){
					get_sym();
					if (sym == comma){
						isCharCstDefinition();
					}
					else{
						//get_sym();
						//printf("this is a character constant definition\n");
						syn_symbol = "this is a character constant definition\n";
						return true;
					}
				}
				else
					return false;
			}
			else
				return false;
		}
		else
			return false;

	}
	else{
		return false;
	}
}
bool isCstDeclarePart(){
	clearSS();
    if (sym == constsy){
        get_sym();
        if (sym == intcon){
            if (isIntCstDefinition()){
                if (sym == semicolon){
                    //printf("part\n");
                    return true;
                }
                else{
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else if (sym == charcon){
            if (isCharCstDefinition()){
                get_sym();
                if (sym == semicolon){
                    //printf("part\n");
                    return true;
                }
                else{
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
bool isCstDeclare(){
	//preread requested
	//preread next
	clearSS();
	for (bool flag = false;;get_sym()){
		if (sym == constsy){
			if (isCstDeclarePart()){
				flag = true;
			}
			else{
				return false;// if we process the sentence like "const 112;", return false directedly
			}
		}
		else{
			if (flag) syn_symbol = "constant declaration has been detected\n";
			return flag;// contains the condition of both true and false. 
		}
	}
	/*clearSS();
    for (bool flag = false;;get_sym()){
        if (sym == constsy){
            if (!isCstDeclarePart()){
                if (flag == true){
                    //printf("this is constant declaration\n");
                    syn_symbol = "this is constant declaration\n";
                }
                return flag;
            }
            else{
                flag = true;
            }
        }
        else{
            if (flag == true){
                //printf("constant declaration has been detected!\n");
                syn_symbol = "constant declaration has been detected!\n";
            }
            return flag;
        }
    }*/
}
bool isDclHead(){
	//preread requested
	//preread next
	clearSS();
	if (sym == intcon){
		get_sym();
		if(sym == idsy){
			get_sym();// preread
			//cout << "int type declare head has been detected.\n";
			syn_symbol = "int type declare head has been detected.\n";
			return true;
		}
		else {
			return false;
		}
	}
	else if (sym == charcon){
		get_sym();//preread
		if (sym == idsy){
			get_sym();
			//cout << "char type declare head has been detected.\n";
			syn_symbol = "char type declare head has been detected.\n";
			return true;
		}
		else{
			return false;
		}

	}
	else{
		return false;
	}
}
bool isVarDefinition(){
	//preread requested
	//not preread next, till the ';' then stop reading sym
	//compound int and char type
	clearSS();
	if (sym == intcon || sym == charcon ||sym == comma){
		// document the type
		if (sym == intcon) syn_typ_sym = intcon;
		else if (sym == charcon) syn_typ_sym = charcon;
		//
		get_sym();
		if (sym == idsy){
			get_sym();
			if (sym == comma){
				isVarDefinition();
			}
			else if (sym == lbracket){
				get_sym();
				if (sym == unsinteger){
					get_sym();
					if (sym == rbracket){
						get_sym();
						if (sym == comma){
							if(isVarDefinition()){
								return true;
							}
							else {
								return false;
							}
						}
						else{
							if (syn_typ_sym == intcon) syn_symbol = "int variable definition detected.\n";
							else if (syn_typ_sym == charcon) syn_symbol = "char variable definition detected.\n";
							//syn_typ_sym = 0;
							return true;
						}
					}
					else{
						return false;
					}
				}
				else{
					return false;
				}
			}
			else{
				if (syn_typ_sym == intcon) syn_symbol = "int variable definition detected.\n";
				else if (syn_typ_sym == charcon) syn_symbol = "char variable definition detected.\n";
				//syn_typ_sym = 0;
				return true;
			}
		}
		else{
			return false;
		}
	}
	else {
		return false;
	}
}
bool isVarDeclarePart(){
	clearSS();
	if (sym == intcon || sym == charcon){
		if (isVarDefinition()){
			if (sym == semicolon){
				return true;
			}
			else{
				return false;
			}
		}
		else{
			return false;
		}
	}
	else {
		return false;
	}
}
bool isVarDeclare(){
	//preread required
	//preread next symbol
	for (bool flag = false;;get_sym()){
		clearSS();
		if (sym == intcon || sym == charcon){
			if (isVarDeclarePart()){
				flag = true;
			}
			else{
				return false;// if we process the sentence like "int 112;", return false directedly
			}
		}
		else{
			if (flag) syn_symbol = "variable declaration has been detected\n";
			return flag;// contains the condition of both true and false. 
		}
	}
}
bool isProgram(){

	return false;
}
