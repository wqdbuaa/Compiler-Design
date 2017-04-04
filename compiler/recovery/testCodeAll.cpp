#include <stdio.h>
const int con_glo_int0 = 1, con_glo_int1 = 2;//常量定义
const char con_glo_char0 = 'a', con_glo_char0 = 'b';//类型标识符
/*常量说明*/
int var_glo_int0, var_glo_int1, var_glo_intA[10];
char var_glo_char0, var_glo_char1, var_glo_charA[20];//变量定义
/*变量说明*/
int ret_val(int a, int b){//参数以及参数表
	return (a + b);/*返回语句*/
}
char ret_char(){
	return 'h';
}
/*有返回值函数定义*/
void ret_none(int a, char b){//声明头部
	return ;
}
void ret_no_para(){
	return ;
}
/*无返回值函数定义*/
int Fib(int n)
{
    if( n < 1 )
    {
        return -1;
    }
    if(n == 1)
    {
        return 1;
    }
    else 
    if (n == 2)
    {
    	return 1;
    }
    return Fib(n-1)+Fib(n-2);
}
/*递归调用*/
void main(){
	const int con_loc_int0 = 1, con_loc_int1 = 2;//；类型标识符
	const char con_loc_char0 = 'a', con_loc_char1 = 'b';//常量，程序中太多了
	/*常数声明*/ 
	int var_loc_int0, var_loc_int1;
	int var_loc_intA[10], var_loc_int_input, times;
	char var_loc_char0, var_loc_char1;//标识符
	char var_loc_charA[20], var_loc_char_input;

	/*变量声明*/
	var_loc_int0 = 1; var_loc_int1 = 0;//赋值语句；整数0
	/*赋值语句*/
	if (var_loc_int0 < var_loc_int1) {//条件
		printf("_abcdefghijklmnopqrstuvwxyz...ascii codes");//字符串
	}
	if (var_loc_int0 > var_loc_int1){//条件
		printf("ABCDEFGHIJKLMNOPQRSTUVWXYZ...and some other ascii codes");//字符串
	}
	else{
		Fib(5);//递归调用
	}
	/*条件语句*/
	//scanf(times);
	times = 2;
	while (var_loc_int0 <= times) {//条件；无符号整数
		var_loc_int0 = var_loc_int0 + 1;
	}
	/*循环语句*/
	{
		if (var_loc_int0 >= 5){//条件；整数
			var_glo_int1 = -2;//整数：带符号
		 	var_loc_intA[-var_loc_int1] = var_loc_int1;//表达式;因子：标识符
		 	var_loc_intA[1] = var_loc_intA[2];//因子：＜标识符＞‘[’＜表达式＞‘]’
		 	var_glo_int1 = 15 * -20;//因子：整数
		 	var_glo_int0 = ret_val(1, 2) + (var_loc_int0 + var_loc_int1);//有返回值的函数调用语句；因子：有返回值的函数调用语句和（表达式）
		}
		else 
		if(var_loc_int0 != var_loc_int1){//条件
			ret_none(1, '_');//没有返回值的函数调用语句
		}
		else 
		if (var_loc_int0 == var_loc_int1){//条件
			ret_no_para();//＜值参数表＞:空
		}//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	}
	/*语句列*/
	ret_val(var_loc_int0, var_loc_int1);
	/*有参数的函数调用*/
	ret_none(5, 'a');
	/*无参数的函数调用*/
	var_glo_int1 = 1 + 2;//赋值语句
	var_glo_intA[1 * 2] = var_loc_int0 + var_loc_int1;//赋值语句，乘法运算符：乘号
	/*赋值语句part2*/
	//scanf(var_loc_int_input, var_loc_char_input);//
	/*读语句*/
	printf("%d\n", var_loc_int0 + 2);
	printf("you are the best\n");
	//printf('a' + 'b');//因子：字符；表达式作为输出
	/*写语句*/
	 ;
	/*空*/
	var_loc_int_input = 5;
	var_loc_intA[0] = 1;//赋值语句
	switch (var_loc_intA[0]){
		case 1:
			var_loc_int_input = var_loc_intA[1] - 0;//加法运算符：减号;项的运算
		case 2:
			var_loc_int0 = var_glo_int0 / 1;//赋值语句，乘法运算符：除号
		case 3:
			var_loc_int_input = +var_loc_int_input - 0;
		case 4:
			var_loc_int_input = -var_loc_int_input - 0;//表达式
		case 5:
			var_loc_int_input = var_loc_int_input * 0;//因子是标识符，因子是整数
		case 6:
			var_loc_int_input = var_loc_int_input / 1;//因子是整数
		case 7:
			var_loc_int_input = var_loc_intA[0] * Fib(5);//因子是数组的标识，因子是有返回值函数调用语句
		case 8:
			var_loc_int_input = var_loc_int_input - (5 - 12 * 16);//因子是(表达式)；并且表达式中还有两种项
		case 9:
			var_loc_int_input = var_loc_int_input - 0;//以上是非零数字
		case 0:
			var_loc_int_input = var_loc_int_input - 0;//零
			/*情况子语句*/
		/*情况表*/
		default:
			ret_no_para();//值参数表：空
		/*缺省*/

	}
	var_loc_charA[0] = '+';//字符：加法运算符;感觉勉强也可以算常量吧··毕竟常量就是整数或是字符orz
	switch (var_loc_charA[0]){
		case '/'://字符：乘法运算符
			var_loc_int_input = var_loc_int_input - 0;//加法运算符：减号
		case 'a'://字符：字母
			var_loc_int0 = var_glo_int0 / 1;//赋值语句，乘法运算符：除号
		case '3'://字符：数字
			var_loc_int_input = var_loc_int_input - 0;
		default:
			ret_none(1 + 2, 'b');//无返回值函数调用语句;值参数表：有表达式；

		/*缺省*/

	}
	/*情况语句*/

	/**/
	return ;
	/*返回语句*/
	/*以上就有一个复合语句，复合语句其实就是{}之间的语句*/
	/*以上感觉有无数的语句列*/
}
