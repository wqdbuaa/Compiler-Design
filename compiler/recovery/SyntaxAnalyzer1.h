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

bool	isProgram();
bool	isCstDeclare();
bool	IsIntCstDefinition();
bool	isCharCstDefinition();
bool	IsDclHead();
bool	isVarDeclare();
bool	isVarDefinition();
bool	isConst();
bool	isRetFuncDefinition();
bool 	isNotFuncDefinition();
bool	isCpdStatement();
bool	isParameter();
bool	isPrmTable();
bool 	isMainFunction();
bool	isExpression();
bool	isItem();
bool	isFactor();
bool	isStatement();
bool	isAssignment();
bool	isIfStatement();
bool	isCondition();
bool 	isLoopStatement();
bool	isCaseStatement();
bool	isCaseTable();
bool	isCaseSubStatement();
bool	IsDefault();
bool	isRetFuncCallStatement();
bool	IsNotFuncCallStatement();
bool	IsVluParaTable();
bool	isStmColumn();
bool	isReadStatement();
bool	isWrtStatement();
bool	IsRtrStatment();



bool isCstDefinition(){
	//preread required
	//read till ";"
	clearSS();
	if (sym == intcon || sym == charcon || sym == comma){// if the current sym is int

		if (sym == intcon) syn_typ_sym = intcon;
		else if (sym == charcon) syn_typ_sym = charcon;

		get_sym();
		if (sym == idsy){
			get_sym();
			if (sym == asn){
				get_sym();
				if (
					(syn_typ_sym == intcon && (sym == unsinteger || sym == integer))
					||
					(syn_typ_sym == charcon && (sym == character))
					){
					get_sym();
					if (sym == comma){
						if (isCstDefinition()){
							return true;
						}
						return false;
					}
					else{
						//get_sym();
						//printf("this is an constant definition\n");
						if (syn_typ_sym == intcon) syn_symbol = "int const definition detected.\n";
						else if (syn_typ_sym == charcon) syn_symbol = "char const definition detected.\n";
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
        if (sym == intcon || sym == charcon){
            if (isCstDefinition()){
                if (sym == semicolon){
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
bool isConst(){
	// preread required
	// preread next sym
	clearSS();
	if (sym == integer || sym == unsinteger || sym == character){
		get_sym();//
		syn_symbol = "const has been detected.\n";
		return true;
	}
	else{
		return false;
	}
}
bool isPrmTable(){
	//preread needed
	//read till ")"
	clearSS();
	if (sym == intcon || sym == charcon){
		if (sym == intcon) syn_typ_sym = intcon;
		else if (sym == charcon) syn_typ_sym = charcon;
		get_sym();
		if (sym == idsy){
			get_sym();
			if (sym == comma){
				get_sym();
				if (isPrmTable()){
					return true;
				}
				else{
					return false;
				}
			}
			else{
				syn_symbol = "parameter table has been detected.\n";
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
bool isParameter(){
	// preread needed
	// read till ")"
	if (isPrmTable()){
		syn_symbol = "parameter has been detected.\n";
		return true;
	}
	else {
		return false;
	}
}
bool isDclHead(){
	//preread requested
	//preread next
	clearSS();
	if (sym == intcon){
		get_sym();
		if(sym == idsy){
			syn_typ_sym == intcon;
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
			syn_typ_sym == charcon;
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
bool isRetFuncDefinition(){
	//preread required
	//preread next sym
	clearSS();
	if (isDclHead()){
		if (sym == lparent){
			get_sym();
			if (isParameter()){
				if (sym == rparent){
					get_sym();
					if (sym == lbrace){
						get_sym();
						if (isCpdStatement()){
							if (sym == rbrace){
								get_sym();
								syn_symbol = "function definition with return value has been detected.\n";
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
					else {
						return false;
					}
				}
				else {
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
	else {
		return false;
	}
}
bool isNotFuncDefinition(){
	// preread required
	// preread next sym
	clearSS();
	if (sym == voidsy){
		get_sym();
		if (sym == idsy){
			get_sym();
			if (sym == lparent){
				get_sym();
				if (isParameter()){
					if (sym == rparent){
						get_sym();
						if (sym == lbrace){
							get_sym();
							if (isCpdStatement()){
								if (sym == rbrace){
									get_sym();
									syn_symbol = "function definition without return value has been detected\n";
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
						else{
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
bool isCpdStatement(){
	//start with something , preread required
	// sym read till "}"
	clearSS();
	if (isCstDeclare()){
		if (isCpdStatement()){
			get_sym();
			//syn_symbol = "compound statements has beed detected.\n";
			return true;
		}
		else{
			return false;
		}
	}
	else if (isVarDeclare()){
		if (isCpdStatement()){
			get_sym();
			//syn_symbol = "compound statements has been detected.\n"
			return true;
		}
		else{
			return false;
		}
	}
	else if (isStmColumn()){
		syn_symbol = "compound statements has been detected.\n";
		return true;
	}
	else{
		return false;
	}
}
bool isMainFunction(){
	//preread sym
	//not preread, because it is the end
	clearSS();
	if (sym == voidsy){
		get_sym();
		if (sym == mainsy){
			get_sym();
			if (sym == lparent){
				get_sym();
				if (sym == rparent){
					get_sym();
					if (sym == lbrace){
						get_sym();
						if (isCpdStatement()){
							if (sym == rbrace){
								syn_symbol = "main function has been detected.\n";
								return true;
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
				else{
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
	else {
		return false;
	}
}
bool isExpression(){
	//preread needed
	//not preread, read till some character, such as ")"
	clearSS();
	if (sym == plussy || sym == minussy){
		get_sym();
		if (isItem()){
			if (sym == plussy || sym == minussy){
				if (isExpression()){
					syn_symbol = "expression has been detected.\n";
					return true;
				}
				else{
					return false;
				}
				/*get_sym();
				if (isItem()){
					syn_symbol = "expression has been detected\n";
					return true;
				}
				else{
					return false;
				}*/
			}
			else{
				//get_sym();????
				syn_symbol = "expression has been detected.\n";
				return true;
			}
		}	
		else {
			return false;
		}	
	}
	else if (isItem()){
		if (sym == plussy || sym == minussy){
			if (isExpression()){
				syn_symbol = "expression has been detected.\n";
				return true;
			}
			else{
				return false;
			}
		}
		else{
			syn_symbol = "expression has been detected.\n";
			return true;
		}
	}
	else{
		return false;
	}
}
bool isItem(){
	// preread needed
	// preread next sym, implicitedly
	clearSS();
	if (isFactor()){
		//get_sym();
		if (sym == starsy || sym == dividesy){
			get_sym();
			if (isFactor()){
				syn_symbol = "an item has been detected";
				return true;
			}
			else{
				return false;
			}
		}
		else{
			syn_symbol = "an item has been detected";
			return true;
		}
	}
	else {
		return false;
	}
}
bool isFactor(){
	// preread needed
	// preread, for now
	clearSS();
	if (sym == idsy){
		get_sym();
		if (sym == lbracket){
			get_sym();
			if (isExpression()){
				if (sym == rbracket){
					get_sym();
					syn_symbol = "factor has been detected";
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else{
			syn_symbol = "factor has been detected.\n";
			return true;
		}
	}
	/*else if (sym){

	}*/
	else if (sym == integer || sym == unsinteger || sym == character){
		get_sym();
		syn_symbol = "factor has been detected.\n";
		return true;
	}
	/*else if (sym == character){

	}*/
	else if (isRetFuncCallStatement()){// presume that isRetFuncCallStatment will preread next sym
		syn_symbol = "factor has been detected.\n";
		return true;
	}
	else if (sym == lparent){	
		get_sym();
		if (isExpression()){
			if (sym == rparent){
				get_sym();
				syn_symbol = "factor has been detected.\n";
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
	else {
		return false;
	}
}
bool isStatement(){
	//preread required
	//preread implicitly
}
bool isAssignment(){
	//preread needed
	//preread implicit
	if (sym == idsy){
		get_sym();
		if (sym == asn){
			get_sym();
			if (isExpression()){//preread has actually been done, ")" etc.
				syn_symbol = "assignment has been detected\n";
				return true;
			}
			else{
				return false;
			}
		}
		else if (sym == lbracket){
			get_sym();
			if (isExpression()){
				if (sym == rbracket){
					get_sym();
					if (sym == asn){
						get_sym();
						if (isExpression()){//preread has actually been done, ")" etc.
							syn_symbol = "assignment has been detected\n";
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
				else{
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
	else{
		return false;
	}
}
bool isIfStatement(){
	//preread needed
	//preread implicitly
	if (sym == ifsy){
		get_sym();
		if (sym == lparent){
			get_sym();
			if (isCondition()){//presume that will preread implicitly
				if (sym == rparent){
					get_sym();
					if (isStatement()){//presume that will preread implicitly
						if (sym == elsesy){
							get_sym();
							if (isStatement()){
								syn_symbol = "if statement has been detected.\n";
								return true;
							}
							else{
								return false;
							}
						}	
						else{
							syn_symbol = "if statement has been detected.\n";
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
bool isCondition(){
	//preread needed
	//preread next implicitly
	if (isExpression()){//preread implicit
		if (sym == leq || sym == neq || sym == eql ||
			sym == lss || sym == geq || sym == gtr
			){
			get_sym();
			if(isExpression()){
				syn_symbol = "condition has been detected.\n";
				return true;
			}
			else{
				return false;
			}
		}
		else{
			syn_symbol = "condition has been detected.\n";
			return true;
		}
	}
	else {
		return false;
	}
}
bool isLoopStatement(){
	//preread required
	//preread implicitly
	if (sym == whilesy){
		get_sym();
		if (sym == lparent){
			get_sym();
			if (isCondition()){
				if (sym == rparent){
					get_sym();
					if (isStatement()){// preread implicitly
						syn_symbol = "while loop has been detected.\n";
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
bool isCaseStatement(){
	//preread required
	//
	if (sym == switchsy){
		get_sym();
		if (sym == lparent){
			get_sym();
			if (isExpression()){
				if (sym == rparent){
					get_sym();
					if (sym == lbrace){
						get_sym();
						if (isCaseTable()){//implicitly preread
							???????????
						}
						else {
							?????????????
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
bool isCaseTable(){
	//preread case is needed
	// explicitly preread
	if (isCaseSubStatement()){
		get_sym()//read the sym next to ";",?????????????????? 
		if (isCaseTable()){
			syn_symbol = "a case table has been detected.\n";
			return true;
		}
		else{
			syn_symbol = "a case table has been detected.\n";
			return true;
		}
	}
	else{
		return false;
	}
}
bool isCaseSubStatement(){
	//implicit preread
	if (sym == casesy){
		get_sym();
		if (sym == integer || sym == unsinteger 
			|| sym == character){
			get_sym();
			if (sym == colon){
				get_sym();
				if (isStatement()){//preread implicitly
					syn_symbol = "a case substatement has been detected.\n";
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
		else{
			return false;
		}
	}
	else{
		return false;
	}
}
bool IsDefault(){
	//implicit preread
	if (sym == defaultsy){
		get_sym();
		if (sym == colon){
			get_sym();
			if (isStatement()){//implicit read
				syn_symbol = "a default has been detected.\n";
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
	else{
		return false;
	}
}
bool isProgram(){

	return false;
}
