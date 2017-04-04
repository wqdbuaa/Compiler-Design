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
TargetCode tgt_code[1000]; int tc = 0; // target code array and the tc is the pointer  of the target code
int glo_bound = 0; //global boundary
int glo_edge = 0; // global's edge, if less than this, it means it is global.
string current_function = "    ";
void tgt_add(string a, string b, string c, string d){
	tgt_code[tc].ist = a;
	tgt_code[tc].rd = b;
	tgt_code[tc].rs = c;
	tgt_code[tc].rt = d;
	tc++;
}
string const2str(string c){
	string cc = c;
	if (cc[0] == '\''){//character
		return num2str((int)cc[1]);
	}
	else{
		return cc;
	}
}
int tcp = 0;
string first = "    ";
string second == "    ";
string third = "    ";
string fourth = "    ";

void tgt_codes_gen(){
	for (tcp = 0; tcp < ic; tcp++){		
		first = itmd_code[tcp].op; 
		second = itmd_code[tcp].operand1;
		third = itmd_code[tcp].operand2;
		fourth = itmd_code[tcp].result;
		// const 
		if (first == "const"){// constant
			if (current_function == "    "){
				current_function == "global";
				glo_bound++;
			}
			else if (current_function == "global"){
				glo_bound++;
				int index = position(fourth);
				int offseet_adr = tab[index].adr;
				if (second == "int"){
					tgt_add("addi", "$t0", "$0", third);
					tgt_add("sw", "$t0", num2str(offseet_adr * 4) + "($0)", "    ");
					tgt_add("addi", "$fp", "$0", offseet_adr * 4);
				}
				else if(second == "char"){
					tgt_add("addi", "$t0", "$0", const2str(third));
					tgt_add("sw", "$t0", num2str(offseet_adr * 4) + "($0)", "    ");
					tgt_add("addi", "$fp", "$0", offseet_adr * 4);
				}
			}
			else{
				int idx = position(fourth, current_function);
				int offset = tab[idx].adr;
				if (second == "int"){
					tgt_add("addi", "$t0", "$0", third);
					tgt_add("sw", "$t0", num2str(offseet * 4) + "($fp)", "    ");
					tgt_add("addi", "$fp", "$0", offseet * 4);
				}
				else if(second == "char"){
					tgt_add("addi", "$t0", "$0", const2str(third));
					tgt_add("sw", "$t0", num2str(offseet * 4) + "($fp)", "    ");
					tgt_add("addi", "$fp", "$0", offseet * 4);
				}
			}
		}
		else if (first  == "int" || first == "char"){// variable
			//no action, now
			if (current_function == "    "){
				current_function == "global";
				glo_bound++;
			}
			else if (current_function == "global"){
				glo_bound++;
			}
			int idx = position(fourth);
			int offseet_adr = tab[idx].adr;
			/*if (third != "    "){// if is array

			}
			else{// not a array
				int idx = position(fourth);
				int offseet_adr = tab[idx].adr;
				if (second == "int")
			}	*/
		}
		else if (first == "main"){//main lab
			current_function = "main";
			tgt_add("main", ":", "    ", "    ");
		}
		else if(first == "="){//assignment
			// get offset
			int idx1 = position(second, current_function);
			int offset1 = tab[idx1].adr;
			int idx2 = position(result, current_function);
			if (idx2 >= 0){// variable to variable
				int offset2 = tab[idx2].adr;
				tgt_add("lw", "$t0", num2str(offset2 * 4) + "($fp)", "    ");
				tgt_add("sw", "$t0", num2str(offset1 * 4) + "($fp)", "    ");
			}
			else{// constant to variable
				tgt_add("addi", "$t0", "$0", const2str(result));
				tgt_add("sw", "$t0", num2str(offset1 * 4) + "($fp)", "    ");
			}
		}
		else if (first == "+" || first == "-" || first == "*" || first == "/"){// + - * /
			int index1 = position(second, current_function);
			int index2 = position(third, current_function);
			int index3 = position(fourth, current_function);
			if (index1 >= 0 && index2 >= 0){
				tgt_add("lw", "$t0", num2str(tab[index1].adr * 4) + "($fp)", "    ");
				tgt_add("lw", "$t1", num2str(tab[index2].adr * 4) + "($fp)", "    ");
				
				//
			}
			else if (index1 >= 0 && index2 < 0){
				tgt_add("lw", "$t0", num2str(tab[index1].adr * 4) + "($fp)", "    ");
				tgt_add("addi", "$t1", const2str(third), "$0");
				/*tgt_add("add", "$t2", "$t0", "$t1");
				tgt_add("sw", "$t2", num2str(tab[index3].order * 4) + "($fp)", "    ");*/
			}
			else if (index1 < 0 && index2 >= 0){
				tgt_add("addi",  "$t0", const2str(second), "$0");
				tgt_add("lw", "$t1", num2str(tab[index2].adr * 4) + "($fp)", "    ");
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
				tgt_add("sw", "$t2", num2str(tab[index3].adr * 4) + "($fp)", "    ");
			}
			else if (first == "-"){ 
				tgt_add("sub", "$t2", "$t0", "$t1");
				tgt_add("sw", "$t2", num2str(tab[index3].adr * 4) + "($fp)", "    ");
			}
			if (first == "*"){ 
				tgt_add("mul", "$t2", "$t0", "$t1");
				tgt_add("sw", "$t2", num2str(tab[index3].adr * 4) + "($fp)", "    ");
			}
			if (first == "/"){ 
				tgt_add("div", "$t2", "$t0", "$t1");
				tgt_add("sw", "$t2", num2str(tab[index3].adr * 4) + "($fp)", "    ");
			}
		}
		else if (first == "[]="){
			int idx1 = position(first, current_function);
			int offset1 = tab[idx1].adr;
			int idx2 = position(second, current_function);
			if (idx2 >= 0){
				int offset2 = tab[idx2].adr;
				tgt_add("lw", "$t1", num2str(offset2 * 4) + "($fp)", "    ");

			}
			else {

			}
		}

	}
}