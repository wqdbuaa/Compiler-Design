#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
//--------------------------------------------------------------------------------------------------------------------------------------------------
//lexicalAnalyzer1.h
/*global signal*/
ifstream infile;
/*file objects*/
string filename;//target file
int ll = 0;//line length
int cc = 0;//character count
int lc = 1;//line count
int lc_real = 0;// real line number
string line;/*line pointers*/
char ch = '\0';//current char that under procession
char ch_last = '\0';
int ch_count= 0;
int sym = 0;
string symbol = "";//current symbol
int num = 0;//if symbol is number, the value of it.
string id = "";//if symbol is others, the configuration of it
enum  symbols_list {
    intcon = 1, charcon,
    constsy, voidsy, mainsy , whilesy , switchsy , casesy, defaultsy, scanfsy, printfsy, returnsy , ifsy, elsesy, //reserved word
	//
    idsy = 20,
    integer , character, unsinteger,
    strings,
    plussy, minussy,
    starsy , dividesy,
    comma, period, colon, semicolon, lparent , lbracket, lbrace, rparent , rbracket, rbrace ,//38
    lss, leq , gtr, geq, eql , neq, asn, //45

    arraycon, uintcon, voidcon, stringcon,//49
	newline//53 it means new line
};//all the memorial words.
/*symbols list*/
int temp_ch = 0;
//--------------------------------------------------------------------------------------------------------------------------------------------------
//Tables.h
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
int isGlobal = 0;// flag about whether the current variable is a global 
//--------------------------------------------------------------------------------------------------------------------------------------------------
//IntermediateCodeGenerator.h
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
string current_function = "global";
string cdt1 = ""; string cdt2 = ""; string lgcSign = "";//temp logical items
vector<string> paras; // vector for the parameters
vector<string> read_series; // vector for the read statement items
//--------------------------------------------------------------------------------------------------------------------------------------------------
//SyntaxAnalyzer13.h
int if_else_pair = 0;// a flag stands for the pair of if and else.
int para_count = 0;
int syn_sym = 0;
string syn_symbol = "";
int syn_typ_sym = 0;// to document the type of the definition, char or int
int sym_buff[5] = {0, 0, 0, 0, 0};// symbol read buff
int num_buff[5] = {0, 0, 0, 0, 0};// number value read buff
int pnum = 0;// register for the number of parameter of a function
string watch_a = "";
string watch_b = "";
string watch_c = "";
string watch_d = "";
string watch_e = "";
ofstream outfile("syntax_output.txt");
//--------------------------------------------------------------------------------------------------------------------------------------------------
//ErrorDetect.h
enum errsyntype{
    invalid_token,
    wrong_type,
    miss_semi, 
    not_a_const,
    err_para,
    miss_lparent,
    miss_rparent,
    miss_lbrace,
    miss_rbrace,
    miss_rbracket,
    invalid_ident,
    miss_func,
    not_array,
    undefined_identifier,
    no_ret_val,
    miss_asn,
    bad_asn,
    if_else_not_pair,
    cdt_incomplete,
    switch_failed,
    case_failed,
    miss_colon,
    not_ret_func,
    para_incompatible, 
    bad_scf,
    bad_prt,
    bad_ret_val,//return type is not the right type
    bad_func_definition,
    bad_definition,
    duplicated_definition,
    bad_dcl_head,
    bad_expression,
    default_failed,
    bad_const_definition,
    bad_para_table,
    //if cst definition is behind the var definition, an error occurs
    bad_cst_var_sequence,
    bad_ret_stc,//bad return1() sentence
    bad_vlu_para_table,//bad value parameter table
    bad_stm_cln//bad statement colomn
};
ofstream errorlog("errorLog.txt");
//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------




// functions
//--------------------------------------------------------------------------------------------------------------------------------------------------
//lexicalAnalyzer1.h
void changeUpToLow();
bool get_char();
bool isSpace();
bool isLetter();
bool isDigit();
bool isColon();
bool isComma();
bool isSemi();
bool isPeriod();
bool isEqu();
bool isNot();
bool isGtr();
bool isLss();
bool isPlus();
bool isMinus();
bool isDivi();
bool isStar();
bool isLpar();
bool isRpar();
bool isLbrkt();
bool isRbrkt();
bool isLBrc();
bool isRBrc();
bool isSinQuo();
bool isDouQuo();
bool isRevSlash();
bool isNewLine();
void catToken();
void clearToken();
void retract();
int reserver();
void transNum();
int get_sym();
//--------------------------------------------------------------------------------------------------------------------------------------------------
//Tables.h
void enter_tab(string s, int o, int tt, int r, int l, int n, int a);
void enter_tab(string s, int o, int tt, int r, int a, string b);
int position(string ab);
int position(string n, string b);
int position_dup(string n, string b, int ii);
void enter_atab(int typel, int n);
void enter_ftab(string n, int pn);
void table_print(int stw);
//--------------------------------------------------------------------------------------------------------------------------------------------------
//IntermediateCodeGenerator.h
string num2str(int i);
int get_addr(string n, string b);
string chsLgcOprt();
void clearCdtTemp();
string temp_var_gen();
string jmp_lab_gen();
void itmd_add(string o, string o1, string o2, string r);
void itmd_add(string o, string o1, string o2, string r, int index);
void itmd_add(string o, string o1, string o2);
void itmd_add(string o, string o1, int p);
void itmd_add();
void itmd_print(int stw);
void clearParts();
void addAssStcPart(string i);
void clearAssStc();
//--------------------------------------------------------------------------------------------------------------------------------------------------
//SyntaxAnalyzer13.h
void clearSS();
int syn_get_sym();
void syn_get_sym(int i);
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
bool    isCaseTable(string *cp, string *lo);
bool    isCaseSubStatement(string *cp, string *lo);
bool    IsDefault();
bool    isRetFuncCallStatement();
bool    isNotFuncCallStatement();
bool    isVluParaTable();
bool    isStmColumn();
bool    isReadStatement();
bool    isWrtStatement();
bool    isRtrStatement();
//--------------------------------------------------------------------------------------------------------------------------------------------------
//ErrorDetect.h
int isIn(int a, int c[], int r);
void error(int type);
void testSkip(int c[], int r);
void testToken(int c[], int r, int e);
//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------------------------------------------------