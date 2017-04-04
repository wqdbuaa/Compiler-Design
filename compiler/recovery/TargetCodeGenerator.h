#include "G:\School Files Noooooooootice\CompilerDesign\compiler\compiler\IntermediateCodeGenerator.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;
struct TargetCode{
	int order;
	string ist;//instruction type, add, sub and so on;
	string rd;// rd
	string rs;// rs
	string rt;// rt, but that doesn't necessarily means that the order of three element is stational
	// it varies according to the instruction
};
struct ParaOffset{
	string name;
	int offset;
};// parameter and its offset
TargetCode tgt_code[1000]; int tc = 0; // target code array and the tc is the pointer  of the target code
ParaOffset par_ofst[30]; int po = 0; // parameter offset pointer
//_________________________________________________________________________________________________________
void tgt_add(string a, string b, string c, string d){//add target code
	tgt_code[tc].order = tc;
	tgt_code[tc].ist = a;
	tgt_code[tc].rd = b;
	tgt_code[tc].rs = c;
	tgt_code[tc].rt = d;
	tc++;
}
void po_add(string n, int o){
	par_ofst[po].name = n;
	par_ofst[po].offset = o;
	po++;
}
int position_par_ofst(string n){
	for (int i = 0; i < po; i++){
		if (par_ofst[i].name == n){
			return i;
		}
	}
	return -1;
}
int isWithinFunction(int i){
// if this intermediate code is within a function?
	int down = i;
	int up = i;
	string funcName = "";
	for (; up >= 0;up--){
		if (itmd_code[up].op == "func"){
			funcName = itmd_code[up].result;
			break;
		}
	}
	for (; down <= ic; down++){
		if (itmd_code[down].op == "end"){
			if (itmd_code[down].result == funcName){
				return 1;
			}
			else {
				return 0;
			}
		}
	}
	return 0;
}
//_________________________________________________________________________________________________________
void tgt_print(int stw){//print the codes
	ofstream outfilePE("TgtCodeOutput.asm");
	for (int i = 0; i < tc; i++){
		outfilePE  << setw(3)<< tgt_code[i].order << setw(stw) << tgt_code[i].ist <<  setw(stw) << tgt_code[i].rd  <<  setw(stw) << tgt_code[i].rs  << setw(stw) << tgt_code[i].rt  <<endl;
	}
	outfilePE.close();
}
string const2str(string c){
	string cc = c;
	if (c[0] == '\''){//character
		return num2str(int(cc[1]));
	}
	else{
		return cc;
	}
}
//_________________________________________________________________________________________________________
int func_flag = 0; //meating the function, so there should be a "j main
int ret_p = 0;//return pointer
int interval = t + 5;// the interval
string func_sequence[20]; int fs = 0; // function sequence, and fs is the corresponding pointer
void tgt_codes_gen(){//generate target code
	for (int tcp = 0; tcp < ic; tcp++){//tcp means target code pointer
		string first = itmd_code[tcp].op;
		string second = itmd_code[tcp].operand1;
		string third = itmd_code[tcp].operand2;
		string fourth = itmd_code[tcp].result;

		/*if (first == "const"){
			IdentifierTable temp = tableItemScan(fourth);
			if (temp.blg == "    "){//global constant
				int index = temp.order;
				if (second == "int"){
					tgt_add("addi", "$1", "$0", third);
					tgt_add("sw", "$1", num2str(index * 4) + "($0)", "    ");
				}
				else if(second == "char"){
					tgt_add("addi", "$1", "$0", num2str(int(third[1])) );
					tgt_add("sw", "$1", num2str(index * 4) + "($0)", "    ");
				}
			}
			else {// local constant

			}
		}*/
		if (first == "const"){
			int index = position(fourth);
			if (second == "int"){
				tgt_add("addi", "$t0", "$0", third);
				tgt_add("sw", "$t0", num2str(index * 4) + "($0)", "    ");
			}
			else if(second == "char"){
				tgt_add("addi", "$t0", "$0", num2str(int(third[1])) );
				tgt_add("sw", "$t0", num2str(index * 4) + "($0)", "    ");
			}
		}
		else if (first == "func"){// function zone
			if (func_flag == 0){
				tgt_add("j", "main", "    ", "    ");
				func_flag = 1;
				{func_sequence[fs] = "main"; fs++;}

			}
			else {
				tgt_add(fourth, ":", "    ", "    ");// the lab of the function
				{func_sequence[fs] = fourth; fs++;}

				tgt_add("sw", "$ra", num2str( ret_p * -4) + "($sp)"); ret_p++; 
				//find function position and offset
				int index = position(fourth);//name of the function
				int pmn = ftab[tab[index].ref].para_num;
				int od = tab[index].order;//off set
				//
				tgt_add("add", "$t8", "$fp", "$0");//former fp
				tgt_add("addi", "$fp", "$fp", num2str(interval * 4) );//move the frame pointer
				for (int i = 0, j = 4; i < pmn; i++, j++){
					tcp++;
					tgt_add("lw", "$" + num2str(j), num2str((od + i * interval) * 4) + "($t8)", "    ");
					IdentifierTable a = tableItemScan(itmd_code[tcp].result, func_sequence[fs - 1]);
					tgt_add("sw", "$" + num2str(j), num2str(a.order * 4) + "($fp)", "    ");
				}
				
			}
		}
		else if (first == "return"){
			int index = position(fourth);
			if (index >= 0){//if is a variable or constant
				tgt_add("add", "$t8", "$fp", "$0");//former fp
				tgt_add("subi", "$fp", "$fp", num2str(interval * 4) );//remove the frame pointer
				tgt_add("lw", "$t7", num2str(tab[index].order * 4) + "($t8)", "    ");
				tgt_add("sw", "$t7", num2str(tab[index].order * 4) + "($fp)", "    ");
			}	
			else{//just a integer or char, like 1 or 'a'
				if (fourth[0] == '\''){// character
					tgt_add("addi", "$t8", "$0", num2str(int(fourth[1])) );//t8 serves as temporary reservoir
				}
				else{// number, int, uint`````
					tgt_add("addi", "$t8", "$0", fourth);
				}
			}
			fs--;//remove the current function
			ret_p--;
			tgt_add("lw", "$ra", num2str( ret_p * -4) + "($sp)");
			tgt_add("jr", "$ra", "    ", "    ");
		}
		else if (first == "end"){
			;
		}
		else if (first == "+" || first == "-" || first == "*" || first == "/"){
			int index1 = position(second, func_sequence[fs]);
			int index2 = position(third, func_sequence[fs]);
			int index3 = position(fourth, func_sequence[fs]);
			if (index1 >= 0 && index2 >= 0){
				tgt_add("lw", "$t0", num2str(tab[index1].order * 4) + "($fp)", "    ");
				tgt_add("lw", "$t1", num2str(tab[index2].order * 4) + "($fp)", "    ");
				
				//
			}
			else if (index1 >= 0 && index2 < 0){
				tgt_add("lw", "$t0", num2str(tab[index1].order * 4) + "($fp)", "    ");
				tgt_add("addi", "$t1", const2str(third), "$0");
				/*tgt_add("add", "$t2", "$t0", "$t1");
				tgt_add("sw", "$t2", num2str(tab[index3].order * 4) + "($fp)", "    ");*/
			}
			else if (index1 < 0 && index2 >= 0){
				tgt_add("addi",  "$t0", const2str(second), "$0");
				tgt_add("lw", "$t1", num2str(tab[index2].order * 4) + "($fp)", "    ");
				/*tgt_add("add", "$t2", "$t0", "$t1");
				tgt_add("sw", "$t2", num2str(tab[index3].order * 4) + "($fp)", "    ");*/
			}
			else if (index1 < 0 && index2 < 0){
				tgt_add("addi", "$t0", const2str(second), "$0");
				tgt_add("addi", "$t1", const2str(third), "$0");
				/*tgt_add("add", "$t2", "$t0", "$t1");
				tgt_add("sw", "$t2", num2str(tab[index3].order * 4) + "($fp)", "    ");*/
			}
			//
			if (first == "+"){ 
				tgt_add("add", "$t2", "$t0", "$t1");
				tgt_add("sw", "$t2", num2str(tab[index3].order * 4) + "($fp)", "    ");
			}
			else if (first == "-"){ 
				tgt_add("sub", "$t2", "$t0", "$t1");
				tgt_add("sw", "$t2", num2str(tab[index3].order * 4) + "($fp)", "    ");
			}
			if (first == "*"){ 
				tgt_add("mul", "$t2", "$t0", "$t1");
				tgt_add("sw", "$t2", num2str(tab[index3].order * 4) + "($fp)", "    ");
			}
			if (first == "/"){ 
				tgt_add("div", "$t2", "$t0", "$t1");
				tgt_add("sw", "$t2", num2str(tab[index3].order * 4) + "($fp)", "    ");
			}
		}
	}
}
/*
if (temp.blg == "    "){

		
			if (first == "const"){
				int index = position(fourth);
				if (second == "int"){
					tgt_add("addi", "$1", "$0", third);
					tgt_add("sw", "$1", num2str(index * 4) + "($0)", "    ");
				}
				else if(second == "char"){
					tgt_add("addi", "$1", "$0", num2str(int(third[1])) );
					tgt_add("sw", "$1", num2str(index * 4) + "($0)", "    ");
				}
			}
		}


		else if (first == "int"){
			if (third == "    "){
				//
			}
			else{
				//
			}
		}	
		else if (first == "char"){
			if (third == "    "){
				//
			}
			else{
				//
			}
		}
		else if (first == "func"){
			tgt_add(fourth, ":", "    ", "    ");
			//int start = 4;//4th GPR
			tcp++;
			for ( ; itmd_code[tcp].op == "para" || 
					itmd_code[tcp].op == "int" ||
					itmd_code[tcp].op == "char"; tcp++){
				po_add(itmd_code[tcp].result, itmd_code[tcp].go_to);
			}	

		}
		else if (first == "para"){

		}
		else if (first == "+") {
			int index1 = position(second); int index2 = position(third);

		}

*/