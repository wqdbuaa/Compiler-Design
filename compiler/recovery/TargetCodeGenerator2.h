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
TargetCode tgt_data[100]; int td = 0; // target code .data
int str_idx = 0;// index for the string number
int glo_bound = 0; //global boundary
int glo_edge = 0; // global's edge, if less than this, it means it is global.
void tgt_add(string a, string b, string c, string d){
	tgt_code[tc].ist = a;
	tgt_code[tc].rd = b;
	tgt_code[tc].rs = c;
	tgt_code[tc].rt = d;
	tc++;
}
void tgt_add_data(string a, string b, string c, string d){// add .data zone information, 
	tgt_data[td].ist = a;
	tgt_data[td].rd = b;
	tgt_data[td].rs = c;
	tgt_data[td].rt = d;
	td++;
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
int str2Num(string ssss){
	int n;
	stringstream ss(ssss);
	ss>>n;
	return n;
}
int count_interval(){// the whole identifier table size, together with some free spaces
					//at least 5;
	int last1 = tab[t - 1].adr;
	if ( tab[t - 1].typ == arraycon){
		 int size = atab[tab[t - 1].ref].range;
		 return last1 + size + 5; 
	}
	else
		return last1 + 5;
}
int tcp = 0;
string first = "    ";
string second = "    ";
string third = "    ";
string fourth = "    ";
int para_index_sp = 0; //parameter index for the sp. start from 1
int para_read_index_sp = 0;// call parameter
int end_of_definition_flag = 0;// end of definition, there should be a "j main"

int  get_addr_in_func(string n, string b){// get parameter offset within the function
	int index_para = get_addr(n,b);//parameter's position
	int index_func = get_addr(b,b);//function's position

	return index_para - index_func - 1;
}
void tgt_print(int space){
	ofstream outfile("tgtCodeOutput.asm");
	for (int i = 0; i < td; i++){
		outfile 
			/*<< setw(space)*/<< tgt_data[i].ist 
			<< /*setw(space)*/ "	"<< tgt_data[i].rd  
			<< /*setw(space)*/ "	"<< tgt_data[i].rs  
			<< /*setw(space)*/ "	"<< tgt_data[i].rt
			<< endl;
	}//.data 
	outfile << ".text:" << endl;
	for (int i = 0; i < tc; i++){
		outfile 
			/*<< setw(space)*/<< tgt_code[i].ist 
			<< /*setw(space)*/ "	"<< tgt_code[i].rd  
			<< /*setw(space)*/ "	"<< tgt_code[i].rs  
			<< /*setw(space)*/ "	"<< tgt_code[i].rt
			<< endl;
	}//other codes
	outfile << "end_program :" << endl; 
	outfile.close();
}
void tgt_codes_gen(){
	current_function = "    ";
	tgt_add_data(".data", ":", "    ", "    ");
	int interval = count_interval() * 4;// overall interval
	for (tcp = 0; tcp < ic; tcp++){		
		first = itmd_code[tcp].op; 
		second = itmd_code[tcp].operand1;
		third = itmd_code[tcp].operand2;
		fourth = itmd_code[tcp].result;
		// const 
		if (first == "const"){// constant
			if (current_function == "    "){
				current_function = "global";
			}
			if (current_function == "global"){
				glo_bound++;
				
				int offseet_adr =get_addr(fourth, current_function);
				if (second == "int"){
					tgt_add("addi", "$t0", "$0", third);
					tgt_add("sw", "$t0", num2str(offseet_adr * 4) + "($0)", "    ");
					tgt_add("addi", "$fp", "$0", num2str(offseet_adr * 4));
					tgt_add("#", "global int constant", "    ","    ");
				}
				else if(second == "char"){
					tgt_add("addi", "$t0", "$0", const2str(third));
					tgt_add("sw", "$t0", num2str(offseet_adr * 4) + "($0)", "    ");
					tgt_add("addi", "$fp", "$0", num2str(offseet_adr * 4) );
					tgt_add("#", "global char constant", "    ","    ");
				}
			}
			else{
				int idx = position(fourth, current_function);
				int offseet = tab[idx].adr;
				if (second == "int"){
					tgt_add("addi", "$t0", "$0", third);
					tgt_add("sw", "$t0", num2str(offseet * 4) + "($fp)", "    ");

					tgt_add("#", "local int constant", "    ","    ");
					//tgt_add("addi", "$fp", "$0", num2str(offseet * 4) );
				}
				else if(second == "char"){
					tgt_add("addi", "$t0", "$0", const2str(third));
					tgt_add("sw", "$t0", num2str(offseet * 4) + "($fp)", "    ");
					tgt_add("#", "locan char constant", "    ","    ");
					//tgt_add("addi", "$fp", "$0", num2str(offseet * 4) );
				}
			}
		}
		else if (first == "func"){
			end_of_definition_flag++;
			if (end_of_definition_flag == 1){
				tgt_add("j", "main", "    ", "    ");
			}
			tgt_add(fourth, ":", "    ", "    ");
			current_function = fourth;
			if (current_function != "main"){// main, no need to add interval
				tgt_add("addi", "$fp", "$fp", num2str(interval));
				tgt_add("sw", "$ra", "-4($fp)", "    ");//new start
				tgt_add("#", fourth + " function zone", "    ","    ");
			}
			else {// main function
				tgt_add("addi", "$fp", "$fp", "12");// main function stack should be offered some place for return value
				tgt_add("la", "$ra", "end_program", "    ");
				tgt_add("sw", "$ra", "-4($fp)", "    ");//new start
				tgt_add("#", "main zone", "    ","    ");
			}
		}
		else if (first == "para"){
			int offset0 = get_addr(current_function, current_function);
			int offset1 = get_addr(fourth, current_function);
			if (isGlobal){
				;////////////////////////
				isGlobal = 0;
			}
			else if (!isGlobal && offset1 >= 0){
				tgt_add("lw", "$a" + num2str(para_read_index_sp % 4), num2str(para_read_index_sp * -4) + "($sp)", "    ");
				int index = position(fourth, current_function);
				/*if (para_read_index_sp == para_index_sp){
					para_read_index_sp = 0;
					//para_index_sp = 0;
				}*////finished the procedure of parameter transportings
				tgt_add("sw", "$a" + num2str(para_read_index_sp %4), num2str(offset1 * 4) + "($fp)", "    ");
				tgt_add("#", "parameter manipulation", "    ","    ");
				para_read_index_sp++;
			}
			else{
				;//////////////////
			}
		}
		else if (first == "return"){
			if (fourth != "    "){
				int offset1 = get_addr(fourth, current_function);
				if (isGlobal){
					//??????????????????????????????
					isGlobal = 0;
				}
				else if (!isGlobal && offset1 >= 0){
					tgt_add("lw", "$t0",  num2str(offset1 * 4) + "($fp)", "    ");

					tgt_add("#", "get the return value", "    ","    ");
//?????????????????????????????????????????????????????????
				}
				else{
//???????????????????????????????????????????
					tgt_add("li", "$t0", const2str(fourth), "    ");

					tgt_add("#", "get the return value immediate number", "    ","    ");
				}
				tgt_add("sw", "$t0", "-8($fp)", "    ");

					tgt_add("#", "save the value in the running stack", "    ","    ");
			}
			else{
				;///////
			}
			tgt_add("lw", "$ra", "-4($fp)", "    ");
			tgt_add("jr", "$ra", "    ", "    ");
			tgt_add("#", "jump back", "    ","    ");
		}
		else if (first  == "int" || first == "char"){// variable
			//no solid action, now
			if (current_function == "global"){
				if (current_function == "    "){
					current_function == "global";
					glo_bound++;
				}
				else if (current_function == "global"){
					glo_bound++;
				}
				int offset2 = get_addr(fourth, current_function);
				tgt_add("addi", "$fp", "$0", num2str(offset2 * 4));
				if (third == "    "){
					tgt_add("#", "find variable", fourth,"    ");

				}
				else{
					tgt_add("addi", "$fp", "$fp", num2str(str2Num(third) * 4));
					tgt_add("#", "find variable", fourth,"    ");
				}
			}
			else{// normal variable in main, do nothing 
				tgt_add("#", "find variable", fourth,"    ");
			}
			/*int idx = position(fourth);
			int offseet_adr = tab[idx].adr;
			tgt_add("#", "find variable ", fourth,"    ");*/
			/*if (third != "    "){// if is array

			}
			else{// not a array
				int idx = position(fourth);
				int offseet_adr = tab[idx].adr;
				if (second == "int")
			}	*/
		}
		/*else if (first == "main"){//main lab
			current_function = "main";
			tgt_add("main", ":", "    ", "    ");
		}*/
		else if(first == "="){//assignment
			// get offset
			int offset2 = get_addr(fourth, current_function);
			if (isGlobal){
				tgt_add("lw", "$t0", num2str(offset2 * 4) + "($zero)", "    ");
				isGlobal = 0;
			}
			else if (offset2 >= 0){
				tgt_add("lw", "$t0", num2str(offset2 * 4) + "($fp)", "    ");
			}
			else{
				tgt_add("li", "$t0", const2str(fourth), "    ");
			}

			int offset1 = get_addr(second, current_function);
			if (isGlobal){
				tgt_add("sw", "$t0", num2str(offset1 * 4) + "($zero)", "    ");
				isGlobal = 0;
			}
			else if (offset1 >= 0){
				tgt_add("sw", "$t0", num2str(offset1 * 4) + "($fp)", "    ");
			}
			tgt_add("#", "assignment sentence", "    ","    ");
			/*int offset2 = get_addr(result, current_function);
			if (offset2 >= 0){// variable to variable
				if (isGlobal){

				}
				else{
					tgt_add("lw", "$t0", num2str(offset2 * 4) + "($fp)", "    ");
					tgt_add("sw", "$t0", num2str(offset1 * 4) + "($fp)", "    ");
				}
			}

			else{// constant to variable
				tgt_add("addi", "$t0", "$0", const2str(result));
				tgt_add("sw", "$t0", num2str(offset1 * 4) + "($fp)", "    ");
			}*/
		}
		else if (first == "+"){
			//
			int offset1 = get_addr(second, current_function);
			if (isGlobal){
				tgt_add("lw", "$t0", num2str(offset1 * 4) + "($zero)", "    ");
				isGlobal = 0;
			}
			else if (!isGlobal && offset1 >= 0){
				tgt_add("lw", "$t0", num2str(offset1 * 4) + "($fp)", "    ");
			}
			else if (offset1 < 0){
				tgt_add("li", "$t0", const2str(second), "    ");
			}
			//
			int offset2 = get_addr(third, current_function);
			if (isGlobal){
				tgt_add("lw", "$t1", num2str(offset2 * 4) + "($zero)", "    ");
				isGlobal = 0;
			}
			else if (!isGlobal && offset2 >= 0){
				tgt_add("lw", "$t1", num2str(offset2 * 4) + "($fp)", "    ");
			}
			else if (offset2 < 0){
				tgt_add("li", "$t1", const2str(third), "    ");
			}
			//
			tgt_add("add", "$t2", "$t0", "$t1");
			int offset3 = get_addr(fourth, current_function);//temporary
			tgt_add("sw", "$t2", num2str(offset3 * 4) + "($fp)", "    ");
			tgt_add("#", "add", "    ","    ");

		}
		else if (first == "-"){
			int offset1 = get_addr(second, current_function);
			if (isGlobal){
				tgt_add("lw", "$t0", num2str(offset1 * 4) + "($zero)", "    ");
				isGlobal = 0;
			}
			else if (!isGlobal && offset1 >= 0){
				tgt_add("lw", "$t0", num2str(offset1 * 4) + "($fp)", "    ");
			}
			else if (offset1 < 0){
				tgt_add("li", "$t0", const2str(second), "    ");
			}
			//
			int offset2 = get_addr(third, current_function);
			if (isGlobal){
				tgt_add("lw", "$t1", num2str(offset2 * 4) + "($zero)", "    ");
				isGlobal = 0;
			}
			else if (!isGlobal && offset2 >= 0){
				tgt_add("lw", "$t1", num2str(offset2 * 4) + "($fp)", "    ");
			}
			else if (offset2 < 0){
				tgt_add("li", "$t1", const2str(third), "    ");
			}
			//
			tgt_add("sub", "$t2", "$t0", "$t1");
			int offset3 = get_addr(fourth, current_function);//temporary
			tgt_add("sw", "$t2", num2str(offset3 * 4) + "($fp)", "    ");
			tgt_add("#", "subtract", "    ","    ");
		}
		else if (first == "*"){
			int offset1 = get_addr(second, current_function);
			if (isGlobal){
				tgt_add("lw", "$t0", num2str(offset1 * 4) + "($zero)", "    ");
				isGlobal = 0;
			}
			else if (!isGlobal && offset1 >= 0){
				tgt_add("lw", "$t0", num2str(offset1 * 4) + "($fp)", "    ");
			}
			else if (offset1 < 0){
				tgt_add("li", "$t0", const2str(second), "    ");
			}
			//
			int offset2 = get_addr(third, current_function);
			if (isGlobal){
				tgt_add("lw", "$t1", num2str(offset2 * 4) + "($zero)", "    ");
				isGlobal = 0;
			}
			else if (!isGlobal && offset2 >= 0){
				tgt_add("lw", "$t1", num2str(offset2 * 4) + "($fp)", "    ");
			}
			else if (offset2 < 0){
				tgt_add("li", "$t1", const2str(third), "    ");
			}
			//
			tgt_add("mul", "$t2", "$t0", "$t1");
			int offset3 = get_addr(fourth, current_function);//temporary
			tgt_add("sw", "$t2", num2str(offset3 * 4) + "($fp)", "    ");
			tgt_add("#", "multiply", "    ","    ");
		}
		else if (first == "/"){
			int offset1 = get_addr(second, current_function);
			if (isGlobal){
				tgt_add("lw", "$t0", num2str(offset1 * 4) + "($zero)", "    ");
				isGlobal = 0;
			}
			else if (!isGlobal && offset1 >= 0){
				tgt_add("lw", "$t0", num2str(offset1 * 4) + "($fp)", "    ");
			}
			else if (offset1 < 0){
				tgt_add("li", "$t0", const2str(second), "    ");
			}
			//
			int offset2 = get_addr(third, current_function);
			if (isGlobal){
				tgt_add("lw", "$t1", num2str(offset2 * 4) + "($zero)", "    ");
				isGlobal = 0;
			}
			else if (!isGlobal && offset2 >= 0){
				tgt_add("lw", "$t1", num2str(offset2 * 4) + "($fp)", "    ");
			}
			else if (offset2 < 0){
				tgt_add("li", "$t1", const2str(third), "    ");
			}
			//
			tgt_add("div", "$t2", "$t0", "$t1");
			int offset3 = get_addr(fourth, current_function);//temporary
			tgt_add("sw", "$t2", num2str(offset3 * 4) + "($fp)", "    ");
			tgt_add("#", "divide", "    ","    ");
		}
		else if (first == "[]="){
			//
			int offset1 = get_addr(second, current_function);
			int isGlobalTemp = 0;
			if (isGlobal){
				isGlobalTemp = isGlobal;
				isGlobal = 0;
			}
			tgt_add("li", "$t0", num2str(offset1), "    ");
			//
			int offset2 = get_addr(third, current_function);
			if (isGlobal){
				tgt_add("lw", "$t1", num2str(offset2 * 4) + "($zero)", "    ");
				isGlobal = 0;
			}
			else if (!isGlobal && offset2 >= 0){
				tgt_add("lw", "$t1", num2str(offset2 * 4) + "($fp)", "    ");
			}
			else if (offset2 < 0){
				tgt_add("li", "$t1", third, "    ");
			}
			//
			tgt_add("add", "$t2", "$t0", "$t1");
			tgt_add("li", "$t3", "4", "    ");
			tgt_add("mul", "$t3", "$t3", "$t2");
			if (isGlobalTemp) {
				tgt_add("add", "$t3", "$t3", "$zero");
			}
			else{
				tgt_add("add", "$t3", "$t3", "$fp");
			}
			//
			int offset3 = get_addr(fourth, current_function);//temporary
			if (isGlobal){
				tgt_add("lw", "$t4", num2str(offset3 * 4) + "($zero)", "    ");
				isGlobal = 0;
			}
			else if (!isGlobal && offset3 >= 0){
				tgt_add("lw", "$t4", num2str(offset3 * 4) + "($fp)", "    ");
			}
			else if (offset3 < 0){
				tgt_add("li", "$t4", fourth, "    ");
			}
			//
			tgt_add("sw", "$t4", "($t3)", "    ");
			tgt_add("#", "assign value to the array element", "    ","    ");
		}
		else if (first == "[]->"){
			//
			int offset1 = get_addr(second, current_function);
			int isGlobalTemp = 0;
			if (isGlobal){
				isGlobalTemp = isGlobal;
				isGlobal = 0;
			}
			tgt_add("li", "$t0", num2str(offset1), "    ");
			//
			int offset2 = get_addr(third, current_function);
			if (isGlobal){
				tgt_add("lw", "$t1", num2str(offset2 * 4) + "($zero)", "    ");
				isGlobal = 0;
			}
			else if (!isGlobal && offset2 >= 0){
				tgt_add("lw", "$t1", num2str(offset2 * 4) + "($fp)", "    ");
			}
			else{
				tgt_add("li", "$t1", third, "    ");
			}
			//
			tgt_add("add", "$t2", "$t0", "$t1");
			tgt_add("li", "$t5", "4", "    ");
			tgt_add("mul", "$t2", "$t2", "$t5"); 
			if (isGlobalTemp){
				tgt_add("add", "$t2", "$t2", "$zero");
				tgt_add("lw", "$t3", "($t2)", "    ");
			}
			else{
				tgt_add("add", "$t2", "$t2", "$fp");
				tgt_add("lw", "$t3", "($t2)", "    ");
			}
			//
			int offset3 = get_addr(fourth, current_function);
			if (isGlobal){
				isGlobal = 0;
				tgt_add("sw", "$t3", num2str(offset3 * 4) + "($zero)",  "    ");
			}
			else if (!isGlobal && offset3 >= 0){
				tgt_add("sw", "$t3", num2str(offset3 * 4) + "($fp)", "    ");
			}
			tgt_add("#", "assign array element value to a identifier", "    ","    ");
		}
		else if (first == "!"){// means "not"
			int offset1 = get_addr(second, current_function);
			if (isGlobal){
				tgt_add("lw", "$t0", num2str(offset1 * 4) + "($zero)", "    ");
			}
			else if (!isGlobal && offset1 >= 0){
				tgt_add("lw", "$t0", num2str(offset1 * 4) + "($fp)", "    ");
			}
			//
			tgt_add("sub", "$t1", "$0", "$t0");
			//
			int offset2 = get_addr(fourth, current_function);
			if (isGlobal){
				isGlobal = 0;
				tgt_add("sw", "$t1", num2str(offset2 * 4) + "($zero)", "    ");
			}
			else {
				tgt_add("sw", "$t1", num2str(offset2 * 4) + "($fp)", "    ");
			}
			tgt_add("#", "opposite value", "    ","    ");

		}
		else if (first == "lab"){// label
			tgt_add(fourth, ":","    ", "    ");
		}
		else if(first == "bge" || 
				first == "ble" || 
				first == "bgt" || 
				first == "bne" || 
				first == "blt" || 
				first == "beq" ){// logical symbol
			//
			int offset1 = get_addr(second, current_function);
			if (isGlobal){
				isGlobal = 0;
				tgt_add("lw", "$t0", num2str(offset1 * 4) + "($zero)", "    ");
			}
			else if (!isGlobal && offset1 >= 0){
				tgt_add("lw", "$t0", num2str(offset1 * 4) + "($fp)", "    ");
			}
			else {
				tgt_add("li", "$t0", const2str(second), "    ");
			}
			//
			int offset2 = get_addr(third, current_function);
			if (isGlobal){
				isGlobal = 0;
				tgt_add("lw", "$t1", num2str(offset2 * 4) + "($zero)", "    ");
			}
			else if (!isGlobal && offset2 >= 0){
				tgt_add("lw", "$t1", num2str(offset2 * 4) + "($fp)", "    ");
			}
			else {
				tgt_add("li", "$t1", const2str(third), "    ");
			}
			//
			tgt_add(first, "$t0", "$t1", fourth);

			tgt_add("#", "logical judgement", first,"    ");
		}
		else if(first == "jmp"){// jump without any condition
			tgt_add("j", "    ", "    ", fourth);

			tgt_add("#", "jump", "    ","    ");
		}
		else if (first == "fupa"){
			int offset1 = get_addr(fourth, current_function);
			if (isGlobal){
				tgt_add("lw", "$t0", num2str(offset1 * 4) + "($zero)", "    ");
			}
			else if (!isGlobal && offset1 >= 0){
				tgt_add("lw", "$t0", num2str(offset1 * 4) + "($fp)", "    ");
			}
			else {
				tgt_add("li", "$t0", const2str(fourth), "    ");
			}
			//
			tgt_add("sw", "$t0", num2str(para_index_sp * -4) + "($sp)", "    ");
			para_index_sp++;
			tgt_add("#", "value parameter", "    ","    ");
		}
		else if (first == "call"){// jump to the function
			int offset1 = 0;
			if (fourth != "    "){
				offset1 = get_addr(fourth, current_function);//temporary variable, return value
				//tgt_add("li", "$t8", num2str(offset1 * 4));
				tgt_add("jal", "    ", "    ", second);
				//current_function = second;
				//jump back
				tgt_add("lw", "$v0", "-8($fp)", "    ");
				tgt_add("subi", "$fp", "$fp", num2str(interval));
				tgt_add("sw", "$v0", num2str(offset1 * 4) + "($fp)", "    ");//return value
				para_index_sp = 0;
				tgt_add("#", "call function", "with return value","    ");
			}
			else{
				
				tgt_add("jal", "    ", "    ", second);
				//current_function = second;
				//jump back
				//tgt_add("lw", "$v0", "-8($fp)", "    ");
				tgt_add("subi", "$fp", "$fp", num2str(interval));
				//tgt_add("sw", "$v0", num2str(offset1 * 4) + "($fp)", "    ");//return value
				para_index_sp = 0;
				tgt_add("#", "call function", "without return value","    ");
			}
			
		}
		else if (first == "prt"){
			if (fourth == "prt_typ_1"){// string and expression
				string temp = "str" + num2str(str_idx);
				str_idx++;
				tgt_add_data(temp + ":", ".asciiz", second, "    ");
				tgt_add("li", "$v0", "4", "    ");
				tgt_add("la", "$a0", temp, "    ");
				tgt_add("syscall", "    ","    ","    ");
				//
				int index1 = get_addr(third, current_function);
				if (isGlobal){
					tgt_add("lw", "$a0", num2str(index1 * 4) + "($zero)", "    ");
				}
				else if (!isGlobal && index1 >= 0){
					tgt_add("lw", "$a0", num2str(index1 * 4) + "($fp)", "    ");
				}
				else{
					tgt_add("li", "$a0", third, "    ");
				}
				//
				int ty = tab[index1].typ;
				if (ty == charcon){//char output
					tgt_add("li", "$v0", "11", "    ");
					tgt_add("syscall", "    ","    ","    ");
				}
				else{// int and temperory regarded as int output
					tgt_add("li", "$v0", "1", "    ");
					tgt_add("syscall", "    ","    ","    ");
				}
				tgt_add("#", "print sentence type 1", "    ","    ");

			}
			else if (fourth == "prt_typ_2"){//string only
				string temp = "str" + num2str(str_idx);
				str_idx++;
				tgt_add_data(temp + ":", ".asciiz", second, "    ");
				tgt_add("li", "$v0", "4", "    ");
				tgt_add("la", "$a0", temp, "    ");
				tgt_add("syscall", "    ","    ","    ");
				tgt_add("#", "print sentence type 2", "    ","    ");
			}
			else if (fourth == "prt_typ_3"){//expression only
				int index1 = get_addr(third, current_function);
				if (isGlobal){
					tgt_add("lw", "$a0", num2str(index1 * 4) + "($zero)", "    ");
					isGlobal = 0;
				}
				else if (!isGlobal && index1 >= 0){
					tgt_add("lw", "$a0", num2str(index1 * 4) + "($fp)", "    ");
				}
				else{
					tgt_add("li", "$a0", third, "    ");
				}
				//
				int ty = tab[index1].typ;
				if (ty == charcon){//char output
					tgt_add("li", "$v0", "11", "    ");
					tgt_add("syscall", "    ","    ","    ");
				}
				else{// int and temperory regarded as int output
					tgt_add("li", "$v0", "1", "    ");
					tgt_add("syscall", "    ","    ","    ");
				}

				tgt_add("#", "print sentence type 3", "    ","    ");
			}
		}
		else if (first == "scf"){
			tgt_add("li", "$v0", "12", "    ");
			tgt_add("syscall", "    ","    ","    ");//$v0 will filled with a value
			int index1 = get_addr(fourth, current_function);
			if (isGlobal){
				isGlobal = 0;
				tgt_add("sw", "$v0", num2str(index1 * 4) + "($zero)","    ");
			}
			else if(!isGlobal && index1 >= 0) {
				tgt_add("sw", "$v0", num2str(index1 * 4) + "($fp)", "    ");
			}

				tgt_add("#", "read sentence", "    ","    ");
		}
		else if (first == "end"){
			para_read_index_sp = 0;

			tgt_add("#", "end the funtion definition", fourth,"    ");
		}

	}
	return;
}


		/*else if (first == "+" || first == "-" || first == "*" || first == "/"){// + - * /
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
				tgt_add("add", "$t2", "$t0", "$t1");
				tgt_add("sw", "$t2", num2str(tab[index3].order * 4) + "($fp)", "    ");
			}
			else if (index1 < 0 && index2 >= 0){
				tgt_add("addi",  "$t0", const2str(second), "$0");
				tgt_add("lw", "$t1", num2str(tab[index2].adr * 4) + "($fp)", "    ");
				/*tgt_add("add", "$t2", "$t0", "$t1");
				tgt_add("sw", "$t2", num2str(tab[index3].order * 4) + "($fp)", "    ");
			}
			else if (index1 < 0 && index2 < 0){
				tgt_add("addi", "$t0", const2str(second), "$0");
				tgt_add("addi", "$t1", const2str(third), "$0");
				tgt_add("add", "$t2", "$t0", "$t1");
				tgt_add("sw", "$t2", num2str(tab[index3].order * 4) + "($fp)", "    ");
			}
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
		}*/