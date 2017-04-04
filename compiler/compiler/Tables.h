#include "D:\compiler\compiler\lexicalAnalyzer1.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>//不要忘记包含此头文件
using namespace std;


enum kind{
	constant = 1, 
	variable, 
	function, 
	mainfunc,
	parameter, 
	temporary
};
struct IdentifierTable
{
	int order;
	string name;//name
	int obj;//kind of identifier: constant, variable, function, parameter. typel seems like kind of useless
	int typ;//type of identifier: charcon or intcon, arraycon, arraycon, uintcon, voidcon
	int ref;//point to the position in the array table and function table, otherwise, -1
	int adr;// it varies, default is -1, if is const, will be changed to the corresponding values
	string blg;// what function it belongs to.
	//int normal;//-1, 0, 1, 1 true, 0 false, -1 null
	//int lev;//lev is not critical
};//the identifier table
struct ArrayTable
{
	int eltyp;//intcon, charcon
	int range;// range of the array
};
struct FunctionTable
{
	string name;
	int para_num;
	int layer_index;
};
int level = 0;// the level of the program, global variable

IdentifierTable tab[1000]; int t = 0; // current pointer of the tab 
ArrayTable atab[100]; int a = 0;// current pointer of the atab
FunctionTable ftab[100]; int fp = 0;//current pointer of the function table: ftab

int mem_offset = 0;// the memory offset, prepare for the .adr 
//string current_function = "global";// what the current function is.

void enter_tab(string s, int o, int tt, int r, int l, int n, int a){
	tab[t].name = s;
	tab[t].obj = o;
	tab[t].typ = tt;
	tab[t].ref = r;
	tab[t].adr = a;	
	//tab[t].normal = n;
	//tab[t].lev = l;
	t++;
}
void enter_tab(string s, int o, int tt, int r, int a, string b){
	// for int const
	tab[t].order = t;
	tab[t].name = s;
	tab[t].obj = o;
	tab[t].typ = tt;
	tab[t].ref = r;
	tab[t].adr = a;	
	tab[t].blg = b;
	//tab[t].lev = level;
	//tab[t].normal = -1;
	t++;
}
/*void enter_tab(string s, int o, int tt, int r, int n, char a){
	// for char const
	tab[t].name = s;
	tab[t].obj = o;
	tab[t].typ = tt;
	tab[t].ref = r;
	tab[t].lev = level;
	tab[t].normal = n;
	tab[t].adr = a;	
	t++;
}*/
int isGlobal = 0;// flag about whether the current variable is a global	
int position(string ab){
	int i = 0;
	for (i = 0; i <	t; i++){
		if (ab == tab[i].name){
			return i;
		}
	}
	return -1;
}// don't adopt any kind of algorithm, it can be change later on
int position(string n, string b){
	//priority is find the constant
	string nn = n;
	string bb = b;
	int i = 0;
	int global_position = -1;
	int local_position = -1;
	for (i = 0; i < t; i++){
		if (nn == tab[i].name && tab[i].blg == "global"){
			global_position = i;
			break;
			//return i;
		}
	}
	for (i = 0; i < t; i++){
		if (nn == tab[i].name && bb == tab[i].blg){
			local_position = i;
			break;
			//return i;
		}
	}
	if (local_position >= 0){
		return local_position;
	}
	else if (local_position < 0 && global_position >= 0){
		return global_position;
	}
	else {
		return -1;
	}
	return -1;
}
int position_dup(string n, string b, int ii){
	//justify that whether a certain identifier is duplicate-defined
	// in a confined area
	int i = 0;
	for (i = 0; i <	t; i++){
		if (n == tab[i].name && b == tab[i].blg){
			return i;
		}
	}
	return -1;
}
//_____________________________________________________________________________
void enter_atab(int typel, int n){
	atab[a].eltyp = typel;
	atab[a].range = n;
	a++;
}
//_____________________________________________________________________________
void enter_ftab(string n, int pn){
	ftab[fp].name = n;
	ftab[fp].para_num = pn;
	ftab[fp].layer_index = 0;
	fp++;
}
//_____________________________________________________________________________
void table_print(int stw){
	ofstream tabfile("Table Output.txt");
	tabfile << "identifier table" << endl;
	for (int kk = 0; kk < t; kk++){
        tabfile 
        << setw(3) << tab[kk].order 
        << setw(stw) << tab[kk].name 
        << setw(stw) <<  tab[kk].obj 
        << setw(stw) <<  tab[kk].typ 
        << setw(stw) <<  tab[kk].ref 
        << setw(stw) <<  tab[kk].adr 
        << setw(stw) <<  tab[kk].blg 
        << endl;
    }
    tabfile << "array table" << endl;
    for (int i = 0; i < a; i++){
    	tabfile << setw(stw) << atab[i].eltyp << setw(stw) <<  atab[i].range << endl;
    }
    tabfile << "function table" << endl;
    for (int i = 0; i < fp; i++){
    	tabfile << setw(stw) << ftab[i].name << setw(stw) <<  ftab[i].para_num << endl;
    }
    tabfile.close();
	cout << "tables has been output" << endl;
}
//________________________
