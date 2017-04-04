#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <sstream>
using namespace std;

/*global signal*/

ifstream infile;
/*file objects*/

string filename;//target file
int ll = 0;//line length
int cc = 0;//character count
int lc = 0;//line count
string line;
/*line pointers*/

char ch = '\0';//current char that under procession
int sym = 0;
string symbol = "";//current symbol
int num = 0;//if symbol is number, the value of it.
string id = "";//if symbol is others, the configuration of it
enum  symbols_list {
    intcon = 1, charcon,
    constsy, voidsy, mainsy , whilesy , switchsy , casesy, defaultsy, scanfsy, printfsy, returnsy , ifsy, elsesy, //reserved word
    
    idsy = 20,
    integer , character, unsinteger,
    strings,
    plussy, minussy,
    starsy , dividesy,
    comma, period, colon, semicolon, lparent , lbracket, lbrace, rparent , rbracket, rbrace ,//38
    lss, leq , gtr, geq, eql , neq, asn, //45

    arraycon, uintcon, voidcon, stringcon//49
};//all the memorial words.
/*symbols list*/
int temp_ch = 0;
bool get_char(){
    if ( ll == cc ){
        if (!infile.eof()){
            getline(infile,line);//get a new line
			lc++;
            ll = line.length();
            cc = 0;
        }
        else{
            return 0;//the end of the file
        }
    }//cope with two kinds of situation: the beginning or finishing processing one line
	if (line == ""){
		return 0;
	}
    ch = line.at(cc);
    if (ch >= 65 && ch <= 90){
        ch += 32;
    }
    cc++;
    return 1;
}
/*get char*/

bool isSpace(){
    if (ch == ' ' || ch == '\r' || ch == '\t'){
        return 1;
    }
    else{
        return 0;
    }
}
/* whether the current character is space, return, or tab. */
bool isLetter(){
	if ((ch >= 65 && ch <= 90)
		|| (ch >= 97 && ch < 122) || ch == '_')
		return true;
	else
		return false;
}
/**/
bool isDigit(){
	if (ch >= 48 && ch <= 57)
		return true;
	else
		return false;
}
/**/
bool isColon(){
	if (ch == ':')
		return true;
	else
		return false;
}
/**/
bool isComma(){
	if (ch == ',')
		return true;
	else
		return false;
}
/**/
bool isSemi(){
	if (ch == ';')
		return true;
	else
		return false;
}
/**/
bool isPeriod(){
    if (ch == '.')
		return true;
    else
		return false;
}
/**/
bool isEqu(){
	if (ch == '=')
		return true;
	else
		return false;
}
/**/
bool isNot(){
	if (ch == '!')
		return true;
	else
		return false;
}
/**/
bool isGtr(){
	if (ch == '>')
		return true;
	else
		return false;
}
/**/
bool isLss(){
	if (ch == '<')
		return true;
	else
		return false;
}
/**/
bool isPlus(){
	if (ch == '+')
		return true;
	else
		return false;
}
/**/
bool isMinus(){
	if (ch == '-')
		return true;
	else
		return false;
}
/**/
bool isDivi(){
	if (ch == '/')
		return true;
	else
		return false;
}
/**/
bool isStar(){
	if (ch == '*')
		return true;
	else
		return false;
}
/**/
bool isLpar(){
	if (ch == '(')
		return true;
	else
		return false;
}
/**/
bool isRpar(){
	if (ch == ')')
		return true;
	else
		return false;
}
/**/
bool isLbrkt(){
	if (ch == '[')
		return true;
	else
		return false;
}
/**/
bool isRbrkt(){
	if (ch == ']')
		return true;
	else
		return false;
}
/**/
bool isLBrc(){
	if (ch == '{')
		return true;
	else
		return false;
}
/**/
bool isRBrc(){
	if (ch == '}')
		return true;
	else
		return false;
}
/**/
bool isSinQuo(){
    if (ch == '\'')
        return true;
    else
        return false;
}
bool isDouQuo(){
    if (ch == '\"')
        return true;
    else
        return false;
}
void catToken(){
	id += ch;;
	return;
}
/**/
void clearToken(){
	id = "";
	return ;
}
/**/
void retract(){
	cc--;
	ch = line.at(cc - 1);
	return;
}
/**/
int reserver(){
	if (id == "int")
		return 1;
	else if (id == "char")
		return 2;
	else if (id == "const")
		return 3;
	else if (id == "void")
		return 4;
	else if (id == "main")
		return 5;
	else if (id == "while")
		return 6;
	else if (id == "switch")
		return 7;
	else if (id == "case")
		return 8;
	else if (id == "default")
		return 9;
	else if (id == "scanf")
		return 10;
	else if (id == "printf")
		return 11;
	else if (id == "return")
		return 12;
	else if (id == "if")
		return 13;
	else if (id == "else")
		return 14;
	else// is identifier
		return 0;
}
/**/
void transNum(){
	stringstream ss(id);
	ss>>num;
}
int get_sym(){
    clearToken();//clear the former token
    if (!get_char())
		return 0;// cannot keep processing, end of file.

    while (isSpace()){
        if (!get_char())
			return 0;
    }//skip the space

    if (isLetter()){
		while( isLetter() || isDigit()){
            catToken();
            if (!get_char()) {
                return 0;//应对的是这种情况：如果读到最后是文末，也能返回。
            }
        }
		retract();//???????????????????????????????????????????????????????????????????
		int resultValue = reserver();
		if (resultValue == 0) {symbol = "idsy"; sym = idsy;}
		else {symbol = id + "sy"; sym = resultValue;}
	}
	/*ident and reserved*/
    else if (isDigit()){
        if (ch != '0'){
    		while (isDigit()){
    			catToken(); 
                if (!get_char()) {
                    return 0;
                }
    		}
    		retract();
    		transNum();
    		symbol = "unsinteger";
    		sym = unsinteger;
        }
        else if (ch == '0'){
            catToken();
            transNum();
            symbol = "unsinteger";
            sym = unsinteger;
        }

	}//unsigned integer
    else if (isPlus() || isMinus()){
        string pn = "";
        if (isPlus()) pn = "+";
        else pn = "-";//determined the sign

        get_char();
        if (isDigit()){
            while (isDigit()){
                catToken(); 
                if (!get_char()) {
                    return 0;
                }
            }
            retract();
            transNum();
            id = pn + id;
            symbol = "integer";
            sym = integer;
        }

        else {
            retract();
            if (isPlus()){
                catToken();
                symbol = "plussy";
                sym = plussy;
            }
            else{
                catToken();
                symbol = "minussy";
                sym = minussy;
            }
        }
    }
    /*integer and plussy and minussy*/
    else if (isSinQuo()){
        string temp = "'";
        get_char();
        if (isPlus() || isMinus() || isStar() || isDivi() || isLetter() || isDigit()){
            temp += ch;
            temp_ch = ch;
            if (!get_char()) {
                return 0;
            }
            if (isSinQuo()){
                temp += "'";
                id = temp;
                symbol = "character";
                sym = character;
                num = temp_ch;
            }
        }
    }
    /*character*/
    else if (isDouQuo()){
        catToken();
        if (!get_char()) {
            return 0;
        }
        while(ch == 32 || ch == 33 || (ch >= 35 && ch <= 126)){
            catToken();
            if (!get_char()) {
                return 0;
            }
        }
        if (ch == '\"'){
            catToken();
            symbol = "strings";
            sym = strings;
        }
    }
    /*strings*/
    else if (isStar()) {symbol = "starsy"; sym = starsy; id += ch;}
    else if (isDivi()) {symbol = "dividesy"; sym = dividesy; id += ch;}
    /*star multiple and divide*/
    else if (isComma()) {symbol = "comma";sym = comma; id += ch;}
    else if (isPeriod()) {symbol = "period"; sym = period;  id += ch;}
    else if (isColon()) {symbol = "colon"; sym = colon;  id += ch;}
    else if (isSemi()) {symbol = "semicolon"; sym = semicolon;  id += ch;}
    else if (isLpar()) {symbol = "lparent"; sym = lparent;  id += ch;}
    else if (isLbrkt()) {symbol = "lbracket"; sym = lbracket;  id += ch;}
    else if (isLBrc()) {symbol = "lbrace"; sym = lbrace;  id += ch;}
    else if (isRpar()) {symbol = "rparent"; sym = rparent;  id += ch;}
    else if (isRbrkt()) {symbol = "rbracket"; sym = rbracket;  id += ch;}
    else if (isRBrc()) {symbol = "rbrace"; sym = rbrace;  id += ch;}
    /*comma, period, colon, semicolon, lparent, lbracket, lbrace, rparent, rbracket, rbrace,*/
    else if (isLss()){
        catToken();
        if (!get_char()) {
            return 0;
        }
        if (ch == '='){
            catToken();
            symbol = "leq";
            sym = leq;
        }
        else{
            retract();
            symbol = "lss";
            sym = lss;
        }
    }
    else if (isGtr()){
        catToken();
        if (!get_char()) {
            return 0;
        }
        if (ch == '='){
            catToken();
            symbol = "geq";
            sym = geq;
        }
        else{
            retract();
            symbol = "gtr";
            sym = gtr;
        }
    }
    else if (isNot()){
        catToken();
        if (!get_char()) {
            return 0;
        }
        if (ch == '='){
            catToken();
            symbol = "neq";
            sym = neq;
        }
        else{
            retract();
        }
    }
    else if (isEqu()){
        catToken();
        if (!get_char()) {
            return 0;
        }
		if (ch == '='){
			catToken();
			symbol = "eql";
			sym = eql;
		}
		else {
			retract();
			symbol = "asn";
			sym = asn;
		}
    }
    /*lss, leq, gtr, geq, eql, neq*/
    return 1;
}