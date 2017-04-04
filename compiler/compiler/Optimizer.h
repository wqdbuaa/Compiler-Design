#include "D:\compiler\compiler\ErrorDetect.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>//不要忘记包含此头文件
#include <math.h>
using namespace std;

struct BasicBlock{
	int head;
	int rear;
};
BasicBlock basic_block[1000]; int bb = 0;// that is the basic blocks; 
//
int const2num(string c){
	string cc = c;
	if (cc[0] == '\''){//character
		return (int)cc[1];
	}
	else{
		return str2Num(cc);
	}
}
void change_itmd_code(int pos, string a, string b, string c, string d){
	itmd_code[pos].op = a;
	itmd_code[pos].operand1 = b;
	itmd_code[pos].operand2 = c;
	itmd_code[pos].result = d;
}
void clear_itmd_code(int j){
	itmd_code[j].op = "    ";
	itmd_code[j].operand1 = "    ";
	itmd_code[j].operand2 = "    ";
	itmd_code[j].result = "    ";
}
void print_basic_block(){
	ofstream outfilePE("BasicBlockDivision.txt");
	for (int i = 0; i < bb; i++){
		outfilePE 
		<< setw(3) << basic_block[i].head
		<< setw(3) << basic_block[i].rear
		<< endl ; 
	}
}
void generate_basic_blocks(){
	for (int tpp = 0; tpp < ic; tpp++){
		/*string first = itmd_code[tpp].op;
		string second = itmd_code[tpp].operand1;
		string third = itmd_code[tpp].operand2;
		string fourth = itmd_code[tpp].result;*/
		if (itmd_code[tpp].op == "+" || 
			itmd_code[tpp].op == "-" || 
			itmd_code[tpp].op == "*" || 
			itmd_code[tpp].op == "/" || 
			itmd_code[tpp].op == "!" || 
			itmd_code[tpp].op == "<<" || 
			itmd_code[tpp].op == ">>" ){/*itmd_code[tpp].op == "[]=" || itmd_code[tpp].op == "[]->" || || itmd_code[tpp].op == "="*/
			// the head of the 
			basic_block[bb].head = tpp;
			for (int ok = 1;tpp < ic && ok == 1; tpp++){
				if (
					itmd_code[tpp].op == "+" || 
					itmd_code[tpp].op == "-" || 
					itmd_code[tpp].op == "*" || 
					itmd_code[tpp].op == "/" || 
					itmd_code[tpp].op == "!" || 
					itmd_code[tpp].op == "<<" || 
					itmd_code[tpp].op == ">>" 
					/*itmd_code[tpp].op == "+" || itmd_code[tpp].op == "-" || itmd_code[tpp].op == "*" || itmd_code[tpp].op == "/" ||
					itmd_code[tpp].op == "[]=" || itmd_code[tpp].op == "[]->" || itmd_code[tpp].op == "!" || itmd_code[tpp].op == "="*/){
					ok = 1;
				}
				else{
					ok = 0;
				}
			}
			basic_block[bb].rear = tpp - 2;
			tpp -= 1;
			bb++;
		}
	}
	//cout << "basic blocks has been divided" << endl;
	print_basic_block();
	return;
}
bool isNumString(string a){
	for (int i = 0; i < a.length(); i++){
		if (!(a[i] >= '0' && a[i] <= '9')){
			return false;
		}
	}
	return true;
}
bool fun(int v){
	// if a num is 2^?  
    bool flag = 0;  
    if((v>0)&&(v&(v-1))==0)  
        flag = 1;  
    return flag;  
}  
int log2(int i){
	return int(log((double)i)/log((double)2));
}
//
void Peephole(){	
	for (int tpp = 0; tpp < ic; tpp++){
		string first = itmd_code[tpp].op;
		string second = itmd_code[tpp].operand1;
		string third = itmd_code[tpp].operand2;
		string fourth = itmd_code[tpp].result;
		if (first == "+" || first == "-" || first == "*" || first == "/" ){
			/*first == "[]=" ||
			first == "[]->"*/
			int index1 = position(second);
			int index2 = position(third);
			if (index1 < 0 && index2 < 0){
				// it means that those two operands are all average constant. 
				//use the assignment sentence immediately
				int new_result = 0;
				int new_oprd1 = const2num(second), new_oprd2 = const2num(third);
				if (first == "+"){
					new_result = new_oprd1 + new_oprd2;
				}
				else if (first == "-"){
					new_result = new_oprd1 - new_oprd2;
				}
				else if (first == "*"){
					new_result = new_oprd1 * new_oprd2;
				}
				else if (first == "/"){
					new_result = new_oprd1 / new_oprd2;
				}
				else ;
				//
				change_itmd_code(tpp, "=", fourth, "    ", num2str(new_result));
			}
		}
		/*if ((first == "*" || first == "/") && fun(str2Num(third)) ){
			if (first == "*")
				change_itmd_code(tpp, "<<", second, num2str(log2(str2Num(third))), fourth);
			else if (first == "/")
				change_itmd_code(tpp, ">>", second, num2str(log2(str2Num(third))), fourth);
			else ;
		}
		if ((first == "*") && fun(str2Num(second)) ){
			if (first == "*")
				change_itmd_code(tpp, "<<", third, num2str(log2(str2Num(second))), fourth);
			else ;
		}*/
	}
	for (int tpp = 0; tpp < ic; tpp++){
		string first = itmd_code[tpp].op;
		string second = itmd_code[tpp].operand1;
		string third = itmd_code[tpp].operand2;
		string fourth = itmd_code[tpp].result;
		if (first == "*"){
			if ( isNumString(third) && fun(str2Num(third))){
					change_itmd_code(tpp, "<<", second, num2str(log2(str2Num(third))), fourth);
			
			}
			else if ( isNumString(second) && fun(str2Num(second))){
					change_itmd_code(tpp, "<<", third, num2str(log2(str2Num(second))), fourth);
			
			}
		}
		/*if ((first == "*" || first == "/") ){
			if ( isNumString(third) && fun(str2Num(third))){
				if (first == "*")
					change_itmd_code(tpp, "<<", second, num2str(log2(str2Num(third))), fourth);
				else if (first == "/")
					change_itmd_code(tpp, ">>", second, num2str(log2(str2Num(third))), fourth);
				else ;
			}
			else if ( isNumString(second) && fun(str2Num(second))){
				if (first == "*")
					change_itmd_code(tpp, "<<", third, num2str(log2(str2Num(second))), fourth);
				else ;
			}
		}*/
	}
	cout << "Peephole optimizing has done." << endl;
	return;
}
void EliminatePublicSubExpression(){
	for (int ppap = 0; ppap < bb; ppap++){
		// for each basic blocks;
		int hd = basic_block[ppap].head;
		int rr = basic_block[ppap].rear;
		for (int i = hd; i <= rr; i++){
		// check each one of the code line in this basic block
			string first = itmd_code[i].op;
			string second = itmd_code[i].operand1;
			string third = itmd_code[i].operand2;
			string fourth = itmd_code[i].result;
			if (fourth[0] == '#'){
				// is the temporary variable
				int j = 0;
				int has_loc_pub_var_flag = 0;
				for (j = i + 1; j < ic; j++){
					if (
						itmd_code[j].op == first && 
						itmd_code[j].operand1 == second &&
						itmd_code[j].operand2 == third &&
						itmd_code[j].result[0] == '#' 
						){
						has_loc_pub_var_flag = 1;
						for (int k = j + 1; k < ic; k++){
							if (itmd_code[k].operand1 == itmd_code[j].result ){
								itmd_code[k].operand1 = itmd_code[i].result;
							}
							if (itmd_code[k].operand2 == itmd_code[j].result){
								itmd_code[k].operand2 = itmd_code[i].result;
							}
						}
						//looking for the latter sentence using the j's temp+_var
						if (has_loc_pub_var_flag){
							clear_itmd_code(j);
						}
						else{
							;
						}
					}
				}
				//looking for the first same temp_var
				
			}
		}
	}
	cout << "eliminate public subexpression has done." << endl;
}
void ElmtDupLab(){
	// eliminate duplicate labels
	for (int i = 0; i < ic; i++){	
		if (itmd_code[i].op == "lab"){
			string target_lab = itmd_code[i].result;
			for (int j = i+1; j < ic; j++){
				if (itmd_code[j].op == "lab"){
					string temp_lab = itmd_code[j].result;
					for (int k = i - 1; k >= 0; k--){
						if (itmd_code[k].op == "jmp" && itmd_code[k].result == temp_lab){
							itmd_code[k].result = target_lab;
						}
					}
					clear_itmd_code(j);
				}
				else{
					break;
				}
			}
		}
	}
	cout << "Duplicate labs have been eliminated." << endl;
	return;
}
//
void optimizing(int type){
	if (type == 0){
		return;
	}
	else if (type == 1){
		Peephole();
		return;
	}
	else if (type == 2){
		EliminatePublicSubExpression();
		return;
	}
	else if (type == 3){
		ElmtDupLab();
		return;
	}
	else 
		return;
}
/*void EliminatePublicSubExpression(){
	for (int ppap = 0; ppap < bb; ppap++){
		// for each basic blocks;
		int hd = basic_block[ppap].head;
		int rr = basic_block[ppap].rear;
		for (int i = hd; i <= rr; i++){
		// check each one of the code line in this basic block
			string first = itmd_code[i].op;
			string second = itmd_code[i].operand1;
			string third = itmd_code[i].operand2;
			string fourth = itmd_code[i].result;
			if (fourth[0] == '#'){
				// is the temporary variable
				int j = 0;
				int has_loc_pub_var_flag = 0;
				for (j = i + 1; j <= rr; j++){
					if (itmd_code[j].op == first && 
						itmd_code[j].operand1 == second &&
						itmd_code[j].operand2 == third &&
						itmd_code[j].result[0] == '#' 
						){
						has_loc_pub_var_flag = 1;
						break;
					}
				}
				//looking for the first same temp_var
				for (int k = j + 1; k <= rr; k++){
					if (itmd_code[k].operand1 == itmd_code[j].result ){
						itmd_code[k].operand1 = itmd_code[i].result;
					}
					if (itmd_code[k].operand2 == itmd_code[j].result){
						itmd_code[k].operand2 = itmd_code[i].result;
					}
				}
				//looking for the latter sentence using the j's temp+_var
				if (has_loc_pub_var_flag){
					clear_itmd_code(j);
				}
				else{
					;
				}
			}
		}
	}
}*/