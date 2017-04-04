#include "D:\compiler\compiler\Tables.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>//不要忘记包含此头文件
using namespace std;

string num2str(int i)
{
	stringstream ss;
	ss << i;
	return ss.str();
}
struct EleType4{
	int order;
	string op;
	string operand1;
	string operand2;
	string result;
	int go_to;
};//data structure
EleType4 itmd_code[1000]; int ic = 0; // ic is the pointer to the last intermediate code.
string temp_var_head = "#"; int temp_var_index = 0;// for the generation of the temp_var
string temp_var_cur = "";// latest temporary variable
string jmp_lab_head = "Lab"; int jmp_lab_index = 0;// jump label 
string jmp_lab_cur1 = "";// enter if
string jmp_lab_cur2 = "";// enter else
string parts[4] = {"", "", "", ""};// parts of the up-comming itmd-code //not useful
string ass_stc[1000]; int as = 0;//assignment sentences's table and its the pointer.
string temp_str = "";//temporary string, just in case of the array symbol //not useful
string pol[500]; int pp = 0;//poland hou zhui expression
string temp_func_cur = "";// current function name;
string temp_typ_cur = "";// current type 
string temp_var_case = "";// temporary variable for case sentences


//________________________________________________________________________

string current_function = "global";
int get_addr(string n, string b){// get offset address
	int tt = -1;
	for(int i = 0; i < ic; i++){
		if (itmd_code[i].op != "const" && 
			itmd_code[i].op != "int" &&
			itmd_code[i].op != "char" )
		{
			tt = i;
			break;
		}
	}	
	int idx = position(n, b);
	if (0 <= idx && idx < tt){
		isGlobal = 1;
		return tab[idx].adr;
	}
	else if (idx >= tt){
		int aa = tab[idx].adr;//55;
		int sss = tab[position(b, b)].adr;//48;
		int ret_Valll = aa - sss - 1;//start from 0
		isGlobal = 0;
		return ret_Valll;
	}
	else {
		isGlobal = 0;
		return -1;
	}

}
//______________________________________________________________
string cdt1 = ""; string cdt2 = ""; string lgcSign = "";//temp logical items
string chsLgcOprt(){//choose logical operator
	if (lgcSign == "<"){
		return "bge";
	}
	else if (lgcSign == ">"){
		return "ble";
	}
	else if (lgcSign == "<="){
		return "bgt";
	}
	else if (lgcSign == ">="){
		return "blt";
	}
	else if (lgcSign == "=="){
		return "bne";
	}
	else if (lgcSign == "!="){
		return "beq";
	}
	else {
		return "";
	}
}
void clearCdtTemp(){//clear temporary condition items
	cdt2 = "";
	cdt1 = "";
	lgcSign = "";
}
//____________________________________________

string temp_var_gen(){
	string temp_var = temp_var_head + num2str(temp_var_index);
	temp_var_index++;
	enter_tab(temp_var, temporary, -1, -1, mem_offset++, current_function);//enter a temporary variable
	return temp_var;
}//new temporary variable generation
string jmp_lab_gen(){
	string jmp_lab = jmp_lab_head + num2str(jmp_lab_index);
	jmp_lab_index++;
	return jmp_lab;
}
vector<string> paras; // vector for the parameters
vector<string> read_series; // vector for the read statement items
void itmd_add(string o, string o1, string o2, string r){
	itmd_code[ic].order = ic;
	itmd_code[ic].op = o;
	itmd_code[ic].operand1 = o1;
	itmd_code[ic].operand2 = o2;
	itmd_code[ic].result = r;
	itmd_code[ic].go_to = -1;
	ic++;
}//for other kind of sentences
void itmd_add(string o, string o1, string o2, string r, int index){
	itmd_code[ic].order = ic;
	itmd_code[ic].op = o;
	itmd_code[ic].operand1 = o1;
	itmd_code[ic].operand2 = o2;
	itmd_code[ic].result = r;
	itmd_code[ic].go_to = index;
	ic++;
}//for other kind of sentences
void itmd_add(string o, string o1, string o2){
	itmd_code[ic].order = ic;
	itmd_code[ic].op = o;
	itmd_code[ic].operand1 = o1;
	itmd_code[ic].operand2 = o2;
	itmd_code[ic].result = "";
	itmd_code[ic].go_to = -1;
	ic++;
}// for assign
void itmd_add(string o, string o1, int p){
	itmd_code[ic].order = ic;
	itmd_code[ic].op = o;
	itmd_code[ic].operand1 = o1;
	itmd_code[ic].operand2 = "";
	itmd_code[ic].result = "";
	itmd_code[ic].go_to = p;
	ic++;
}//for jmp
void itmd_add(){
	;
}// for the scanf and printf
void itmd_print(int stw){
	ofstream outfilePE("Ele4Exps.txt");
	for (int i = 0; i < ic; i++){
		//cout << itmd_code[i].order << "	" << itmd_code[i].op << "	" <<itmd_code[i].operand1 << "	" <<itmd_code[i].operand2 << "	" <<itmd_code[i].result /*<< "	" << itmd_code[i].go_to << "	" */<< endl;
		outfilePE  /*<< setw(3)<< itmd_code[i].order*/ 
		<< setw(8) << itmd_code[i].op 
		<<  setw(stw) << itmd_code[i].operand1 
		<<  setw(stw) << itmd_code[i].operand2 
		<< setw(stw) << itmd_code[i].result 
		//<< setw(4) << itmd_code[i].go_to
		<<endl;
	}
	outfilePE.close();
	cout << "intermediate codes has been output." << endl;
}
void clearParts(){
	for (int i = 0; i < 4; i++){
		parts[i] = "";
	}
	return;
}

void addAssStcPart(string i){
	ass_stc[as] = i;
	as++;
} 
void clearAssStc(){
	as = 0;
	return;
}//pointer point to the head
