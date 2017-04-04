#include <iostream>
#include <string>
#include "D:\compiler\compiler\Optimizer.h"
#include <stdio.h>
using namespace std;
/*
Reference tree:
lexicalAnalyzer.h
Tables.h
IntermediateCodeGenerator.h
TargetCodeGenerator.h
SyntaxAnalyzer.h
ErrorDetect.h
Optimizer.h
Main.cpp
*/
/*
bool    isProgram();
bool    isCstDeclare();
bool    IsIntCstDefinition();
bool    isCharCstDefinition();
bool    IsDclHead();
bool    isVarDeclare();
bool    isVarDefinition();
bool    isConst();
bool    isRetFuncDefinition();
bool    isNotFuncDefinition();
bool    isCpdStatement();
bool    isParameter();
bool    isPrmTable();
bool    isMainFunction();
bool    isExpression();
bool    isItem();
bool    isFactor();
bool    isStatement();
bool    isAssignment();
bool    isIfStatement();
bool    isCondition();
bool    isLoopStatement();
bool    isCaseStatement();
bool    isCaseTable();
bool    isCaseSubStatement();
bool    isDefault();
bool    isRetFuncCallStatement();
bool    isNotFuncCallStatement();
bool    isVluParaTable();
bool    isStmColumn();
bool    isReadStatement();
bool    isWrtStatement();
bool    isRtrStatement();

*/
int main()
{   
    
    cout << "input the filename: ";
    cin>>filename;

    /*filename = "syntax_input_test.txt";*/
	//infile.open(filename.c_str(), ios::in | ios::binary);
    infile.open(filename);

	for (int i = 1; i < 5; i++){
		int k = get_sym();
		for (;sym == newline;){
			lc++;
			k = get_sym();
		}
        if (k){
            sym_buff[i] = sym;
            if (i == 1){
                watch_b = id;
            }
            else if (i == 2){
                watch_c = id;
            }
            else if (i == 3){
                watch_d = id; 
            }
            else if (i == 4){
                watch_e = id;
            }
        }
        else{
            sym_buff[i] = 0;
            if (i == 1){
                watch_b = "";
            }
            else if (i == 2){
                watch_c = "";
            }
            else if (i == 3){
                watch_d = ""; 
            }
            else if (i == 4){
                watch_e = "";
            }
        }
    }

	syn_get_sym(1);


    cout << isProgram() << endl;
    generate_basic_blocks();
    cout << "if you wanna optimize your Intermediate code? use 0, 1 and so on to choose the type. " << endl;
    int type = 0;
    do{
        cin >> type;
        optimizing(type);
		if (type != 0)
			cout << "wanna do more optimization? " << endl;
    }while (type != 0);
    
	itmd_print(20);
    table_print(15);
    
	tgt_codes_gen();
	tgt_print(20);

    infile.close();
	outfile.close();
    errorlog.close();
	cout << "\n\n\n\n\n\n" << endl;
    return 0;
}

    /*while(getline(infile, line)){
        cout << line << " " << line.length() << endl;
        cout << infile.eof() << endl;
    }*/
