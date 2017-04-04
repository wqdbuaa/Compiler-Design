#include "G:\School Files Noooooooootice\CompilerDesign\compiler\compiler\ErrorDetect.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
/*
enum  symbols_list {
    intcon = 1, charcon,
    constsy, voidsy, mainsy , whilesy , switchsy , casesy, defaultsy, scanfsy, printfsy, returnsy , ifsy, elsesy, //reserved word
    arraycon,
    idsy = 20,
    integer , character, unsinteger,
    strings,
    plussy, minussy,
    starsy , dividesy,
    comma, period, colon, semicolon, lparent , lbracket, lbrace, rparent , rbracket, rbrace ,
    lss, leq , gtr, geq, eql , neq, asn
};//all the memorial words.
*/
/*
enum type{
	constant = 1, variable, function, parameter
};
*/
// stands for the syntax type
int syn_sym = 0;
string syn_symbol = "";
//clear the syntax information for next syntax analysis result string to be input 
void clearSS(){
	syn_symbol = "";
}
//that is a trade-off, holy s**t, I have to move it here
ofstream outfile("syntax_output.txt");
//those are some exclusive globals that served as some identifier to 
//characters under prossessing currently. Those cannot be seen in any kind 
//output, but it is vital for the debug procedures.
int syn_typ_sym = 0;// to document the type of the definition, char or int
int sym_buff[5] = {0, 0, 0, 0, 0};// symbol read buff
string watch_a = "";
string watch_b = "";
string watch_c = "";
string watch_d = "";
string watch_e = "";
int num_buff[5] = {0, 0, 0, 0, 0};// number value read buff
int pnum = 0;// register for the number of parameter of a function
//an function exclusive to the syntax analysis module. It is designed to 
//adapt to the condition with several preread syms.
int syn_get_sym(){
	watch_a = watch_b;
	watch_b = watch_c;
	watch_c = watch_d;
	watch_d = watch_e;
	for (int i = 1; i < 5; i++){
		sym_buff[i - 1] = sym_buff[i];
		num_buff[i - 1] = num_buff[i];
	}
	if (get_sym()){
		sym_buff[4] = sym;
		num_buff[4] = num;
		watch_e = id;
	}
	else{
		sym_buff[4] = 0;
		num_buff[4] = num_buff[4];
		watch_e = "";
	}
	syn_sym = sym_buff[0];
	// look a;
	return syn_sym;
}// what we watch is a everytime when we want to debug
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
bool	isNotFuncCallStatement();
bool	isVluParaTable();
bool	isStmColumn();
bool	isReadStatement();
bool	isWrtStatement();
bool	isRtrStatement();

/*
struct IdentifierTable
{
	string name;
	int obj;
	int typ;
	int ref;
	int normal;
	int adr;

	int lev;
};
struct ArrayTable
{
	int eltyp;
	int range;
};
*/


bool isCstDefinition(){
	//preread required
	//read till ";"
	clearSS();
	clearParts();
	if (syn_sym == intcon ||syn_sym == charcon || syn_sym == comma){// if the current syn_sym is int

		if (syn_sym == intcon) {
			syn_typ_sym = intcon;
		}
		else if (syn_sym == charcon) {
			syn_typ_sym = charcon;
		}
		syn_get_sym();
		if (syn_sym == idsy){
			enter_tab(watch_a, constant, syn_typ_sym, -1, -1);//table enter flag
			//parts[0] = watch_a;//op1
			string result = watch_a;
			syn_get_sym();
			if (syn_sym == asn){
				//parts[1] = watch_a;//op
				syn_get_sym();
				if (
					(syn_typ_sym == intcon && (syn_sym == unsinteger || syn_sym == integer))
					||
					(syn_typ_sym == charcon && (syn_sym == character))
					){
					tab[t - 1].adr = num_buff[0];//table item change
					if (syn_typ_sym == intcon ){
						itmd_add("const", "int", watch_a, result);//intermediate code generating
						temp_var_cur = result;
					}
					else{
						itmd_add("const", "char", watch_a, result);//intermediate code generating
						temp_var_cur = result;
					}
					
					//parts[2] = watch_a;//op2
					//itmd_add(parts[1], parts[0], parts[2], temp_var_gen())//

					/*if (syn_sym == integer){
						enter_tab(watch_a, constant, intcon, -1, num_buff[0]);//table enter flag
					}
					else if(syn_sym == unsinteger){
						enter_tab(watch_a, constant, uintcon, -1, num_buff[0]);//table enter flag
					} 
					else if (syn_sym == character){
						enter_tab(watch_a, constant, charcon, -1, num_buff[0]);//table enter flag
					}*/

					syn_get_sym();
					if (syn_sym == comma){
						if (isCstDefinition()){
							return true;
						}
						return false;
					}
					else{
						if (syn_typ_sym == intcon) {
							syn_symbol = "int const definition detected.\n";
							outfile << syn_symbol;
						}
						else if (syn_typ_sym == charcon){
							syn_symbol = "char const definition detected.\n";
							outfile << syn_symbol;
						} 
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
    if (syn_sym == constsy){
        syn_get_sym();
        if (syn_sym == intcon || syn_sym == charcon){
            if (isCstDefinition()){
                if (syn_sym == semicolon){
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
	for (bool flag = false;;syn_get_sym()){
		if (syn_sym == constsy){
			if (isCstDeclarePart()){
				flag = true;
			}
			else{
				return false;// if we process the sentence like "const 112;", return false directedly
			}
		}
		else{
			if (flag){
				syn_symbol = "constant declaration has been detected\n";		
				outfile << syn_symbol;		
			} 
			return flag;// contains the condition of both true and false. 
		}
	}
}
bool isVarDefinition(){
	//preread requested
	//not preread next, till the ';' then stop reading syn_sym
	//compound int and char type
	clearSS();
	if (syn_sym == intcon || syn_sym == charcon ||syn_sym == comma){
		// document the type
		if (syn_sym == intcon) syn_typ_sym = intcon;
		else if (syn_sym == charcon) syn_typ_sym = charcon;
		//
		syn_get_sym();
		if (syn_sym == idsy){
			enter_tab(watch_a, variable, syn_typ_sym, -1, -1);//table enter flag
			string result = watch_a;
			syn_get_sym();
			if (syn_sym == comma){
				if (syn_typ_sym == intcon){
					itmd_add("int", "   ", "   ", result);
					temp_var_cur = result;
				}//intermediate code generating
				else if (syn_typ_sym == charcon){
					itmd_add("char", "   ", "   ", result);
					temp_var_cur = result;
				}//intermediate code generating
				isVarDefinition();
			}
			else if (syn_sym == lbracket){
				syn_get_sym();
				if (syn_sym == unsinteger){

					/*enter_tab(watch_a, constant, uintcon, -1, num_buff[0]);//table enter flag*/
					string oprd2 = watch_a;
					syn_get_sym();
					if (syn_sym == rbracket){
						{
							enter_atab(tab[t - 1].typ, num_buff[0]);
							tab[t - 1].typ = arraycon;
							tab[t - 1].ref = a - 1;

							if (syn_typ_sym == intcon){
								itmd_add("int", "   ", oprd2, result);
								temp_var_cur = result;
							}//intermediate code generating
							else if (syn_typ_sym == charcon){
								itmd_add("char", "   ", oprd2, result);
								temp_var_cur = result;
							}//intermediate code generating
							
						}//table enter flag; table item change
					//enter an array 
						syn_get_sym();
						if (syn_sym == comma){
							if(isVarDefinition()){
								return true;
							}
							else {
								return false;
							}
						}
						else{
							if (syn_typ_sym == intcon) {
								syn_symbol = "int variable definition detected.\n";
								outfile << syn_symbol;
							}
							else if (syn_typ_sym == charcon) {
								syn_symbol = "char variable definition detected.\n";
								outfile << syn_symbol;
							}
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
				if (syn_typ_sym == intcon) {
					itmd_add("int", "   ", "   ", result);
					temp_var_cur = result;
					syn_symbol = "int variable definition detected.\n";
					outfile << syn_symbol;
				}//intermediate code generating
				else if (syn_typ_sym == charcon) {
					itmd_add("char", "   ", "   ", result);
					temp_var_cur = result;
					syn_symbol = "char variable definition detected.\n";
					outfile << syn_symbol;
				}//intermediate code generating
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
	if (syn_sym == intcon || syn_sym == charcon){
		if (isVarDefinition()){
			if (syn_sym == semicolon){
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
	for (bool flag = false;;syn_get_sym()){
		clearSS();
		if (syn_sym == intcon || syn_sym == charcon){
			if ((sym_buff[2] == comma  || sym_buff[2] == lbracket || sym_buff[2] == semicolon )&& isVarDeclarePart()){
				flag = true;
			}
			else if (sym_buff[2] == lparent){
				return flag;// if we process the sentence like "int 112;", return false directedly
			}
			else{
				return false;
			}
		}
		else{
			if (flag) {
				syn_symbol = "variable declaration has been detected\n";
				outfile << syn_symbol;
			}
			return flag;// contains the condition of both true and false. 
		}
	}
}
bool isConst(){
	// preread required
	// preread next syn_sym
	clearSS();
	if (syn_sym == integer || syn_sym == unsinteger || syn_sym == character){
		
		/*if (syn_sym == integer){
			enter_tab(watch_a, constant, intcon, -1, num_buff[0]);//table enter flag
		}
		else if(syn_sym == unsinteger){
			enter_tab(watch_a, constant, uintcon, -1, num_buff[0]);//table enter flag
		} 
		else if (syn_sym == character){
			enter_tab(watch_a, constant, charcon, -1, num_buff[0]);//table enter flag
		}*/

		syn_get_sym();//
		syn_symbol = "const has been detected.\n";
		outfile << syn_symbol;
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
	if (syn_sym == intcon || syn_sym == charcon){
		if (syn_sym == intcon) syn_typ_sym = intcon;
		else if (syn_sym == charcon) syn_typ_sym = charcon;
		syn_get_sym();
		if (syn_sym == idsy){
			enter_tab(watch_a, parameter, syn_typ_sym, -1, -1);//table enter flag
			{
				if (syn_typ_sym == intcon){
					itmd_add("para", "int", "    ", watch_a);
					//temp_var_cur = watch_a;
				}
				else if (syn_typ_sym == charcon){
					itmd_add("para", "char", "    ", watch_a);
					//temp_var_cur = watch_a;
				}
				//temp_var_cur = watch_a;
				//intermediate code generating
			}
			syn_get_sym();
			if (syn_sym == comma){
				pnum++;
				syn_get_sym();
				if (isPrmTable()){
					return true;
				}
				else{
					return false;
				}
			}
			else{
				pnum++;
				syn_symbol = "parameter table has been detected.\n";
				outfile << syn_symbol;
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
		outfile << syn_symbol;
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
	if (syn_sym == intcon){
		syn_get_sym();
		if(syn_sym == idsy){
			syn_typ_sym = intcon;
			enter_tab(watch_a, variable, intcon, -1, -1);//table enter flag
			{
				itmd_add("func", "int", "    ", watch_a);
				//temp_var_cur = watch_a;
				temp_func_cur = watch_a;
			}//intermediate code generating
			syn_get_sym();// preread
			//outfile << "int type declare head has been detected.\n";
			syn_symbol = "int type declare head has been detected.\n";
			outfile << syn_symbol;
			return true;
		}
		else {
			return false;
		}
	}
	else if (syn_sym == charcon){
		syn_get_sym();//preread
		if (syn_sym == idsy){
			syn_typ_sym = charcon;
			enter_tab(watch_a, variable, charcon, -1, -1);//table enter flag
			{
				itmd_add("func", "char", "    ", watch_a);
				//temp_var_cur = watch_a;
				temp_func_cur = watch_a;
			}//intermediate code generating
			syn_get_sym();
			//outfile << "char type declare head has been detected.\n";
			syn_symbol = "char type declare head has been detected.\n";
			outfile << syn_symbol;
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
	//preread next syn_sym
	clearSS();
	if (isDclHead()){
		if (syn_sym == lparent){
			syn_get_sym();
			if (isParameter()){
				if (syn_sym == rparent){
					{	// parameters have been added into the
						// tab, so t - aa - 1 
						int aa = pnum;
						pnum = 0;
						enter_ftab(tab[t - aa - 1].name, aa);
						tab[t - aa - 1].obj = function;
						tab[t - aa - 1].ref = fp - 1;
					}//table enter flag
					syn_get_sym();
					if (syn_sym == lbrace){
						syn_get_sym();
						if (isCpdStatement()){
							if (syn_sym == rbrace){
								{
									itmd_add("end", "    ", "    ", temp_func_cur);
									//temp_var_cur = temp_func_cur;
								}//intermediate code generating
								syn_get_sym();
								syn_symbol = "function definition with return value has been detected.\n";
								outfile << syn_symbol;
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
			else if (syn_sym == rparent){
				{	
					enter_ftab(tab[t - 1].name, pnum);
					tab[t - 1].obj = function;
					tab[t - 1].ref = fp - 1;
				}//table enter flag
				syn_get_sym();
				if (syn_sym == lbrace){
					syn_get_sym();
					if (isCpdStatement()){
						if (syn_sym == rbrace){
							{
								itmd_add("end", "    ", "    ", temp_func_cur);
								//temp_var_cur = temp_func_cur;
							}//intermediate code generating
							syn_get_sym();
							syn_symbol = "function definition with return value has been detected\n";
							outfile << syn_symbol;
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
	else {
		return false;
	}
}
bool isNotFuncDefinition(){
	// preread required
	// preread next syn_sym
	clearSS();
	if (syn_sym == voidsy && sym_buff[1] != mainsy){
		syn_get_sym();
		if (syn_sym == idsy){
			temp_func_cur = watch_a;
			enter_tab(watch_a, variable, voidcon, -1, -1);//table enter flag
			syn_get_sym();
			if (syn_sym == lparent){
				syn_get_sym();
				if (isParameter()){
					if (syn_sym == rparent){
						{	// parameters have been added into the
							// tab, so t - aa - 1 
							int aa = pnum;
							pnum = 0;
							enter_ftab(tab[t - aa - 1].name, aa);
							tab[t - aa - 1].obj = function;
							tab[t - aa - 1].ref = fp - 1;
						}//table enter flag
						syn_get_sym();
						if (syn_sym == lbrace){
							syn_get_sym();
							if (isCpdStatement()){
								if (syn_sym == rbrace){
									{
										itmd_add("end", "    ", "    ", temp_func_cur);
										//temp_var_cur = temp_func_cur;
									}//intermediate code generating
									syn_get_sym();
									syn_symbol = "function definition without return value has been detected\n";
									outfile << syn_symbol;
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
				else if (syn_sym == rparent){
					{	
						enter_ftab(tab[t - 1].name, pnum);
						tab[t - 1].obj = function;
						tab[t - 1].ref = fp - 1;
					}//table enter flag
					syn_get_sym();
					if (syn_sym == lbrace){
						syn_get_sym();
						if (isCpdStatement()){
							if (syn_sym == rbrace){
								{
									itmd_add("end", "    ", "    ", temp_func_cur);
									//temp_var_cur = temp_func_cur;
								}//intermediate code generating
								syn_get_sym();
								syn_symbol = "function definition without return value has been detected\n";
								outfile << syn_symbol;
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
	// syn_sym read till "}"
	clearSS();
	if (isCstDeclare()){
		if (isVarDeclare()){
			if (isCpdStatement()){
				syn_symbol = "compound statements has been detected.\n";
				outfile << syn_symbol;
				return true;
			}
			else{
				return false;
			}
		}
		else{
			if (isCpdStatement()){
				syn_symbol = "compound statements has been detected.\n";
				outfile << syn_symbol;
				return true;
			}
			else{
				return false;
			}
		}
	}
	else if (isVarDeclare()){
		if (isCstDeclare()){
			return false;
		}
		else{
			if (isCpdStatement()){
				syn_symbol = "compound statements has been detected.\n";
				outfile << syn_symbol;
				return true;
			}
			else{
				return false;
			}
		}
	}
	else if (isStmColumn()){
		syn_symbol = "compound statements has been detected.\n";
		outfile << syn_symbol;
		return true;
	}
	else{
		return true;//void statement
	}
}
bool isMainFunction(){
	//preread syn_sym
	//not preread, because it is the end
	clearSS();
	if (syn_sym == voidsy){
		syn_get_sym();
		if (syn_sym == mainsy){
			enter_tab(watch_a, variable, voidcon, -1, -1);//table enter flag
			syn_get_sym();
			if (syn_sym == lparent){
				syn_get_sym();
				if (syn_sym == rparent){
					syn_get_sym();
					{	
						enter_ftab(tab[t - 1].name, pnum);
						pnum = 0;
						tab[t - 1].obj = mainfunc;
						tab[t - 1].ref = fp - 1;
					}//table enter flag
					if (syn_sym == lbrace){
						syn_get_sym();
						if (isCpdStatement()){
							if (syn_sym == rbrace){
								syn_symbol = "main function has been detected.\n";
								outfile << syn_symbol;
								return true;
							}
							else {
								return false;
							}
						}
						else if (syn_sym == rbrace){//void main () {}
							syn_symbol = "main function has been detected.\n";
							outfile << syn_symbol;
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
	else {
		return false;
	}
}
bool isExpression(){
	//preread needed
	//not preread, read till some character, such as ")"
	clearSS();
	clearParts();
	if (syn_sym == plussy ){
		addAssStcPart(watch_a);//assign sentence record added
		syn_get_sym();
		if (isItem()){
			string oprd1 = temp_var_cur;// may be a loose end
			if (syn_sym == plussy || syn_sym == minussy){
				string oprt= (syn_sym == plussy ? "+" : "-");
				//addAssStcPart(watch_a);//assign sentence record added
				syn_get_sym();
				if (isExpression()){
					{
						itmd_code[ic].order = ic;
						itmd_code[ic].operand1 = oprd1;
						itmd_code[ic].op = oprt;
						itmd_code[ic].operand2 = temp_var_cur;
						temp_var_cur = temp_var_gen();
						itmd_code[ic].result = temp_var_cur;
						ic++;
					}//intermediate code generating
					syn_symbol = "expression has been detected.\n";
					outfile << syn_symbol;
					return true;
				}
				else{
					return false;
				}
				/*syn_get_sym();
				if (isItem()){
					syn_symbol = "expression has been detected\n";
					return true;
				}
				else{
					return false;
				}*/
			}
			else{
				//syn_get_sym();????
				syn_symbol = "expression with add symbol head has been detected.\n";
				outfile << syn_symbol;
				return true;
			}
		}	
		else {
			return false;
		}	
	}
	else if (syn_sym == minussy){
		addAssStcPart(watch_a);//assign sentence record added
		syn_get_sym();
		if (isItem()){
			{
				itmd_code[ic].order = ic;
				itmd_code[ic].operand1 = temp_var_cur;
				itmd_code[ic].op = "!";
				itmd_code[ic].operand2 = "";
				temp_var_cur = temp_var_gen();
				itmd_code[ic].result = temp_var_cur;
				ic++;
			}//intermediate code generating
			string oprd1 = temp_var_cur;// may be a loose end
			if (syn_sym == plussy || syn_sym == minussy){
				//addAssStcPart(watch_a);//assign sentence record added
				string oprt= (syn_sym == plussy ? "+" : "-");
				//addAssStcPart(watch_a);//assign sentence record added
				syn_get_sym();
				if (isExpression()){
					{
						itmd_code[ic].order = ic;
						itmd_code[ic].operand1 = oprd1;
						itmd_code[ic].op = oprt;
						itmd_code[ic].operand2 = temp_var_cur;
						temp_var_cur = temp_var_gen();
						itmd_code[ic].result = temp_var_cur;
						ic++;
					}//intermediate code generating
					syn_symbol = "expression has been detected.\n";
					outfile << syn_symbol;
					return true;
				}
				else{
					return false;
				}
			}
			else{
				//syn_get_sym();????
				syn_symbol = "expression with minus symbol has been detected.\n";
				outfile << syn_symbol;
				return true;
			}
		}	
		else {
			return false;
		}
	}
	else if (isItem()){
		string oprd1 = temp_var_cur;// may be a loose end
		if (syn_sym == plussy || syn_sym == minussy){
			string oprt= (syn_sym == plussy ? "+" : "-");
			//addAssStcPart(watch_a);//assign sentence record added
			syn_get_sym();
			if (isExpression()){
				{
					itmd_code[ic].order = ic;
					itmd_code[ic].operand1 = oprd1;
					itmd_code[ic].op = oprt;
					itmd_code[ic].operand2 = temp_var_cur;
					temp_var_cur = temp_var_gen();
					itmd_code[ic].result = temp_var_cur;
					ic++;
				}//intermediate code generating
				syn_symbol = "expression ordinary has been detected.\n";
				outfile << syn_symbol;
				return true;
			}
			else{
				return false;
			}
			/*syn_get_sym();
			if (isItem()){
				syn_symbol = "expression has been detected\n";
				return true;
			}
			else{
				return false;
			}*/
		}
		else{
			//syn_get_sym();????
			syn_symbol = "expression has been detected.\n";
			outfile << syn_symbol;
			return true;
		}
	}
	else{
		return false;
	}
}
bool isItem(){
	// preread needed
	// preread next syn_sym, implicitedly
	clearSS();
	if (isFactor()){
		//syn_get_sym();
		string oprd1 = temp_var_cur;// may be a loose end
		if (syn_sym == starsy || syn_sym == dividesy){
			addAssStcPart(watch_a);//assign sentence record added
			string oprt= (syn_sym == starsy ? "*" : "/");
			syn_get_sym();
			if (isFactor()){
				{
					itmd_code[ic].order = ic;
					itmd_code[ic].operand1 = oprd1;
					itmd_code[ic].op = oprt;
					itmd_code[ic].operand2 = temp_var_cur;
					temp_var_cur = temp_var_gen();
					itmd_code[ic].result = temp_var_cur;
					ic++;
				}//intermediate code generating
				syn_symbol = "an item has been detected.\n";
				outfile << syn_symbol;
				return true;
			}
			else{
				return false;
			}
		}
		else{
			syn_symbol = "an item has been detected.\n";
			outfile << syn_symbol;
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
	if (syn_sym == idsy){
		addAssStcPart(watch_a);//assign sentence record added
		temp_var_cur = watch_a;
		string oprd1 = watch_a;
		syn_get_sym();
		if (syn_sym == lbracket){
			addAssStcPart(watch_a);//assign sentence record added
			syn_get_sym();
			if (isExpression()){
				if (syn_sym == rbracket){
					{
						itmd_code[ic].order = ic;
						itmd_code[ic].operand1 = oprd1;
						itmd_code[ic].op = "[]";
						itmd_code[ic].operand2 = temp_var_cur;
						temp_var_cur = temp_var_gen();
						itmd_code[ic].result = temp_var_cur;
						ic++;
					}//intermediate code generating
					addAssStcPart(watch_a);//assign sentence record added
					syn_get_sym();
					syn_symbol = "factor array item has been detected.\n";
					outfile << syn_symbol;
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
		else if (syn_sym == lparent){
			addAssStcPart(watch_a);//assign sentence record added
			syn_get_sym();
			if (isVluParaTable()){
				if (syn_sym == rparent){
					addAssStcPart(watch_a);//assign sentence record added
					syn_get_sym();
					syn_symbol = "factor function call with para & return value statement has been detected.\n";
					outfile << syn_symbol;
					return true;
				}
				else {
					return false;
				}
			}
			else if (syn_sym == rparent){
				addAssStcPart(watch_a);//assign sentence record added
				syn_get_sym();
				syn_symbol = "factor function call with no pare & return value statement has been detected.\n";
				outfile << syn_symbol;
				return true;
			}
			else{
				return false;
			}
		}
		else{
			//temp_var_cur = watch_a;
			syn_symbol = "factor identifier has been detected.\n";
			outfile << syn_symbol;
			return true;
		}
	}
	/*else if (syn_sym){

	}*/
	else if (syn_sym == integer || syn_sym == unsinteger || syn_sym == character){
		/*if (syn_sym == integer){
			enter_tab(watch_a, constant, intcon, -1, num_buff[0]);//table enter flag
		}
		else if(syn_sym == unsinteger){
			enter_tab(watch_a, constant, uintcon, -1, num_buff[0]);//table enter flag
		}
		else{
			enter_tab(watch_a, constant, charcon, -1, num_buff[0]);//table enter flag
		}*/

		//enter_tab(watch_a, constant, int tt, int r, int a)---------------------------------------------------
		addAssStcPart(watch_a);//assign sentence record added
		temp_var_cur = watch_a;
		syn_get_sym();
		syn_symbol = "factor constant has been detected.\n";
		outfile << syn_symbol;
		return true;
	}
	else if (syn_sym == lparent){
		addAssStcPart(watch_a);//assign sentence record added	
		syn_get_sym();
		if (isExpression()){
			if (syn_sym == rparent){
				addAssStcPart(watch_a);//assign sentence record added
				syn_get_sym();
				syn_symbol = "factor expression has been detected.\n";
				outfile << syn_symbol;
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
	//preread explicitly or implicitly
	clearSS();
	if (isIfStatement()){
		syn_symbol = "a statement has been detected.\n";
		outfile << syn_symbol;
		return true;
	}
	else if(isLoopStatement()){
		syn_symbol = "a statement has been detected.\n";
		outfile << syn_symbol;
		return true;
	}
	else if(syn_sym == lbrace){
		syn_get_sym();
		if (isStmColumn()){
			if (syn_sym == rbrace){
				syn_get_sym();
				syn_symbol = "a statement has been detected.\n";
				outfile << syn_symbol;
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
	else if (syn_sym == idsy){
		syn_get_sym();
		if (syn_sym == lparent){//ret value or not ret value function call
			syn_get_sym();
			if (isVluParaTable()){
				if (syn_sym == rparent){
					syn_get_sym();
					if (syn_sym == semicolon){
						syn_get_sym();
						syn_symbol = "a statement has been detected.\n";
						outfile << syn_symbol;
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
			else if (syn_sym == rparent){
				syn_get_sym();
				if (syn_sym == semicolon){
					syn_get_sym();
					syn_symbol = "a statement has been detected.\n";
					outfile << syn_symbol;
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
		else if (syn_sym == asn){
			syn_get_sym();
			if (isExpression()){//preread has actually been done, ")" etc.
				if (syn_sym == semicolon){
					syn_get_sym();
					syn_symbol = "a statement has been detected.\n";
					outfile << syn_symbol;
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
		else if (syn_sym == lbracket){
			syn_get_sym();
			if (isExpression()){
				if (syn_sym == rbracket){
					syn_get_sym();
					if (syn_sym == asn){
						syn_get_sym();
						if (isExpression()){//preread has actually been done, ")" etc.
							if (syn_sym == semicolon){
								syn_get_sym();
								syn_symbol = "a statement has been detected.\n";
								outfile << syn_symbol;
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

	}
	else if (isReadStatement() ||
			 isWrtStatement()  
			 ){
		if (syn_sym == semicolon){
			syn_get_sym();
			syn_symbol = "a statement has been detected.\n";
			outfile << syn_symbol;
			return true;
		}
		else{
			return false;
		}
	}
	else if (isCaseStatement()){
			syn_symbol = "a statement has been detected.\n";
			outfile << syn_symbol;
			return true;
	}
	else if (isRtrStatement()){
		if (syn_sym == semicolon){
			syn_get_sym();
			syn_symbol = "a statement has been detected.\n";
			outfile << syn_symbol;
			return true;
		}
		else{
			return false;
		}
	}
	else if (syn_sym == semicolon){
		syn_get_sym();
		syn_symbol = "void statement has been detected.\n";
		outfile << syn_symbol;
		return true;
	}
	else {
		return false;
	}
}
bool isAssignment(){
	//preread needed
	//preread implicit
	clearSS();
	clearAssStc();
	if (syn_sym == idsy){
		string oprd1 = watch_a;
		addAssStcPart(watch_a);//assign sentence record added
		syn_get_sym();
		if (syn_sym == asn){
			addAssStcPart(watch_a);//assign sentence record added
			syn_get_sym();
			if (isExpression()){//preread has actually been done, ")" etc.
				{
					itmd_code[ic].order = ic;
					itmd_code[ic].operand1 = oprd1;
					itmd_code[ic].op = "=";
					itmd_code[ic].operand2 = "    ";
					itmd_code[ic].result = temp_var_cur;
					ic++;
				}//intermediate code generating
				syn_symbol = "assignment has been detected\n";
				outfile << syn_symbol;
				return true;
			}
			else{
				return false;
			}
		}
		else if (syn_sym == lbracket){
			addAssStcPart(watch_a);//assign sentence record added
			syn_get_sym();
			if (isExpression()){
				string oprd2 = temp_var_cur;
				if (syn_sym == rbracket){
					addAssStcPart(watch_a);//assign sentence record added
					/*{
						itmd_code[ic].order = ic;
						itmd_code[ic].operand1 = oprd1;
						itmd_code[ic].op = "[]=";
						itmd_code[ic].operand2 = temp_var_cur;
						temp_var_cur = temp_var_gen();
						itmd_code[ic].result = temp_var_cur;
						ic++;
						oprd1 = temp_var_cur;
					}//intermediate code generating*/
					syn_get_sym();
					if (syn_sym == asn){
						addAssStcPart(watch_a);//assign sentence record added
						syn_get_sym();
						if (isExpression()){//preread has actually been done, ")" etc.
							{
								itmd_code[ic].order = ic;
								itmd_code[ic].operand1 = oprd1;
								itmd_code[ic].op = "[]=";
								itmd_code[ic].operand2 = oprd2;//temp_var_cur
								temp_var_cur = temp_var_gen();
								itmd_code[ic].result = temp_var_cur;
								ic++;
							}//intermediate code generating
							syn_symbol = "assignment has been detected\n";
							outfile << syn_symbol;
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
	clearSS();
	if (syn_sym == ifsy){
		syn_get_sym();
		if (syn_sym == lparent){
			syn_get_sym();
			if (isCondition()){//presume that will preread implicitly
				if (syn_sym == rparent){
					syn_get_sym();
					if (isStatement()){//presume that will preread implicitly
						if (syn_sym == elsesy){
							syn_get_sym();
							if (isStatement()){
								syn_symbol = "if statement has been detected.\n";
								outfile << syn_symbol;
								return true;
							}
							else{
								return true;//void statement
							}
						}	
						else{
							syn_symbol = "if statement has been detected.\n";
							outfile << syn_symbol;
							return true;
						}
					}
					else{
						return true;//void statement
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
	clearSS();
	if (isExpression()){//preread implicit
		if (syn_sym == leq || syn_sym == neq || syn_sym == eql ||
			syn_sym == lss || syn_sym == geq || syn_sym == gtr
			){
			syn_get_sym();
			if(isExpression()){
				syn_symbol = "condition has been detected.\n";
				outfile << syn_symbol;
				return true;
			}
			else{
				return false;
			}
		}
		else{
			syn_symbol = "condition has been detected.\n";
			outfile << syn_symbol;
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
	clearSS();
	if (syn_sym == whilesy){
		syn_get_sym();
		if (syn_sym == lparent){
			syn_get_sym();
			if (isCondition()){
				if (syn_sym == rparent){
					syn_get_sym();
					if (isStatement()){// preread implicitly
						syn_symbol = "while loop has been detected.\n";
						outfile << syn_symbol;
						return true;
					}
					else{
						return true;//void statement
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
	//preread implicitly
	clearSS();
	if (syn_sym == switchsy){
		syn_get_sym();
		if (syn_sym == lparent){
			syn_get_sym();
			if (isExpression()){
				if (syn_sym == rparent){
					syn_get_sym();
					if (syn_sym == lbrace){
						syn_get_sym();
						if (isCaseTable()){//implicitly preread
							if (IsDefault()){
								if (syn_sym == rbrace){
									syn_get_sym();
									syn_symbol = "a case statement has been detected.\n";
									outfile << syn_symbol;
									return true;	
								}							
							}
							else{
								if (syn_sym == rbrace){
									syn_get_sym();
									syn_symbol = "a case statement has been detected.\n";
									outfile << syn_symbol;
									return true;
								}
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
	clearSS();
	if (isCaseSubStatement()){
		//syn_get_sym()//read the syn_sym next to ";",?????????????????? 
		if (isCaseTable()){
			syn_symbol = "a case table has been detected.\n";
			outfile << syn_symbol;
			return true;
		}
		else{
			syn_symbol = "a case table has been detected.\n";
			outfile << syn_symbol;
			return true;
		}
	}
	else{
		return false;
	}
}
bool isCaseSubStatement(){
	//implicit preread
	clearSS();
	if (syn_sym == casesy){
		syn_get_sym();
		if (syn_sym == integer || syn_sym == unsinteger 
			|| syn_sym == character){

			/*if (syn_sym == integer){
				enter_tab(watch_a, constant, intcon, -1, num_buff[0]);//table enter flag
			}
			else if(syn_sym == unsinteger){
				enter_tab(watch_a, constant, uintcon, -1, num_buff[0]);//table enter flag
			} 
			else if (syn_sym == character){
				enter_tab(watch_a, constant, charcon, -1, num_buff[0]);//table enter flag
			}*/

			syn_get_sym();
			if (syn_sym == colon){
				syn_get_sym();
				if (isStatement()){//preread implicitly
					syn_symbol = "a case substatement has been detected.\n";
					outfile << syn_symbol;
					return true;
				}
				else{
					return true;//void statement
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
	clearSS();
	if (syn_sym == defaultsy){
		syn_get_sym();
		if (syn_sym == colon){
			syn_get_sym();
			if (isStatement()){//implicit read
				syn_symbol = "a default has been detected.\n";
				outfile << syn_symbol;
				return true;
			}
			else{
				return true;//void statement
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
bool isRetFuncCallStatement(){
	//preread explicitly
	clearSS();
	if (syn_sym == idsy){	
		temp_func_cur = watch_a;
		syn_get_sym();
		if (syn_sym == lparent){
			syn_get_sym();
			if (isVluParaTable()){
				if (syn_sym == rparent){
					{
						temp_var_cur = temp_var_gen();
						itmd_add("call", temp_func_cur, "    ", temp_var_cur);//intermediate code generating
					}
					syn_get_sym();
					syn_symbol = "function call with return value statement has been detected.\n";
					outfile << syn_symbol;
					return true;
				}
				else {
					return false;
				}
			}
			else if (syn_sym == rparent){
				{
					temp_var_cur = temp_var_gen();
					itmd_add("call", temp_func_cur, "    ", temp_var_cur);//intermediate code generating
				}
				syn_get_sym();
				syn_symbol = "function call with return value statement has been detected.\n";
				outfile << syn_symbol;
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
bool isNotFuncCallStatement(){
	//preread explicitly
	clearSS();
	if (syn_sym == idsy){	
		temp_func_cur = watch_a;
		syn_get_sym();
		if (syn_sym == lparent){
			syn_get_sym();
			if (isVluParaTable()){
				if (syn_sym == rparent){
					{
						itmd_add("call", temp_func_cur, "    ", "    ");//intermediate code generating
					}
					syn_get_sym();
					syn_symbol = "function call without return value statement has been detected.\n";
					outfile << syn_symbol;
					return true;
				}
				else {
					return false;
				}
			}
			else if (syn_sym == rparent){
				{
					itmd_add("call", temp_func_cur, "    ", "    ");//intermediate code generating
				}
				syn_get_sym();
				syn_symbol = "function call without return value statement has been detected.\n";
				outfile << syn_symbol;
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
bool isVluParaTable(){
	//preread implicit
	clearSS();
	if (isExpression()){
		paras.push_back(temp_var_cur);
		if (syn_sym == comma){
			syn_get_sym();
			if (isVluParaTable()){
				for ( int i = 0; i < paras.size(); i++ ) {
					string tc = paras[ i ].c_str();
					itmd_add("calpar", "  ", "  ", tc);
			    }
		    	paras.clear();//these sentences is not so useful//
				syn_symbol = "value parameter table has been detected.\n";
				outfile << syn_symbol;
				return true;
			}
			else{
				return false;
			}
		}
		else{
			for ( int i = 0; i < paras.size(); i++ ) {
				string tc = paras[ i ].c_str();
		        itmd_add("calpar", "  ", "  ", tc);
		    }
		    paras.clear();
			syn_symbol = "value parameter table has been detected.\n";
			outfile << syn_symbol;
			return true;
		}
	}
	else{
		return false;
	}
}
bool isStmColumn(){
	// preread implicit
	clearSS();
	if (isStatement()){
		if (isStmColumn()){
			syn_symbol = "statement colunm has been detected.\n";
			outfile << syn_symbol;
			return true; 
		}
		else {
			syn_symbol = "statement colunm has been detected.\n";
			outfile << syn_symbol;
			return true;
		}
	}
	else{
		return true;//void statement
	}
}
bool isSrsIdsy(){//is series of idsy?
	// preread implicitly
	clearSS();
	if (syn_sym == idsy){
		syn_get_sym();
		if (syn_sym == comma){
			syn_get_sym();
			if (isSrsIdsy()){
				return true;
			}
			else{
				return false;
			}
		}
		else{
			return true;
		}
	}
	else{
		return false;
	}
}
bool isReadStatement(){
	//preread implicitly
	clearSS();
	if (syn_sym == scanfsy){
		syn_get_sym();
		if (syn_sym == lparent){
			syn_get_sym();
			if (isSrsIdsy()){
				if (syn_sym == rparent){
					syn_get_sym();
					syn_symbol = "a read statement has been detected.\n";
					outfile << syn_symbol;
					return true;
				}
				else{
					return false;
				}
			}
			else{

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
bool isWrtStatement(){
	// explicitly
	clearSS();
	if (syn_sym == printfsy){
		syn_get_sym();
		if (syn_sym == lparent){
			syn_get_sym();
			if (syn_sym == strings){

				//enter_tab(watch_a, constant, intcon, -1, num_buff[0]);//table enter flag

				syn_get_sym();
				if (syn_sym == comma){
					syn_get_sym();
					if (isExpression()){
						if (syn_sym == rparent){
							syn_get_sym();
							syn_symbol = "a write statement has been detected.\n";
							outfile << syn_symbol;
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
				else if (syn_sym == rparent){
					syn_get_sym();
					syn_symbol = "a write statement has been detected.\n";
					outfile << syn_symbol;
					return true;
				}
				else {
					return false;
				}
			}
			else {
				if (isExpression()){
					if (syn_sym == rparent){
						syn_get_sym();
						syn_symbol = "a write statement has been detected.\n";
						outfile << syn_symbol;
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
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}
bool isRtrStatement(){
	clearSS();
	if (syn_sym == returnsy){
		syn_get_sym();
		if (syn_sym == lparent){
			syn_get_sym();
			if (isExpression()){
				if (syn_sym == rparent){
					syn_get_sym();
					syn_symbol = "a return statement has been detected.\n";
					outfile << syn_symbol;
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
			syn_symbol = "a return statement has been detected.\n";
			outfile << syn_symbol;
			return true;
		}
	}
	else{
		return false;
	}

}
bool isProgram(){
	clearSS();
	if (isCstDeclare()){
		if (isVarDeclare()){
			if (isProgram()){
				syn_symbol = "a program with const and variable declaration has been detected.\n";
				outfile << syn_symbol;
				return true;
			}
			else{
				return false;
			}
		}
		else{
			if (isProgram()){
				syn_symbol = "a program with const without variable has been detected.\n";
				outfile << syn_symbol;
				return true;
			}
			else{
				return false;
			}
		}
	}
	else if (isVarDeclare()){
		if (isCstDeclare()){
			return false;
		}
		else {
			if (isProgram()){
				syn_symbol = "a program with variable but const declaration has been detected.\n";
				outfile << syn_symbol;
				return true;
			}
			else{
				return false;
			}
		}

	}
	else if (isRetFuncDefinition() || isNotFuncDefinition()){
		if (isProgram()){
			syn_symbol = "a program with some function definition has been detected.\n";
			outfile << syn_symbol;
			return true;
		}
		else{
			return false;
		}
	}
	else if (isMainFunction()){
		syn_symbol = "a program core has been detected.\n";
		outfile << syn_symbol;
		return true;
	}
	else{
		return false;
	}
}
