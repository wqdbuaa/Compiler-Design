const int num_1=1,num_2=-2,num_0=0;
const int num_a=0;
const char ch_add='+',ch_0 = '0',ch__='_',ch_star='*',ch_sub='-', ch_slash='/';
const char ch_B = 'B';
int num1;
int num3,num4,num_array1[10];
int num5;



//你开你关，关键词出现
char ch_c,ch_d,ch2,ch_array1[2];
char ch_minus;
int easy_int(){
	return (1);
}
char easy_char(){
	return ('T');
}
int ret_int() {
	const int ret_int_1=15, ret_int_2= 0;
	const char ret_int_3='a';
	printf(" ", ch_b);
	printf(" ", num_array1[0]);
	printf(" ", 15);
	printf(" ", 'P');
	printf(" ", easy_int());
	printf(" ", (15 *16/ 4));

	return (ret_int_1);
}
char ret_Char(char b){
	int ret_char_1;
	char ret_char_2,ret_char_3;
	ret_char_1 = 48;
	printf("   ", ret_char_1 / 4);
	printf("   ", easy_char() * (15 + 4 *9));
	return (ret_char_1);

}
void para_is_void(int a, int b, int c, int d){
	printf ("\n    ", 'a' + ch_B-num_array1[0]    +easy_int());
	printf ("\n    ", - (a * 48-15+9/3) + b-c    +d);
}
int Fib(int n)
{
    if( n < 1 )
    {
        return (-1);
    }
    if(n == 1)
    {
        return (1);
    }
    else 
    if (n == 2)
    {
        return (1);
    }
    return (Fib(n - 1)+Fib(n - 2));
}
void main(){
	int recur_num1;
	int read_num1;
	char read_char1;
	int read_num2, read_num3[20];
	char read_char2, read_char3[20];
printf("----------------------------------------\n");
	num_array1[0] = 18+15 - 14 -1;
	printf("\n");
	printf(num_array1[0]);
	num3 = -10 -8*88+56   /(1 +1);
	printf("\n");
	printf(num3);
	num4 = 10 + fiB(5*3/(2--1));
	printf("\n");
	printf(num4);
	num5 = num_array1[0];
	printf(num5);
	printf("\n");
printf("----------------------------------------\n");
	printf("\n please input 2: ");
	scanf(num5);
	if (1 < num5)
		printf("condition is a logic \n");;

	printf(" not in the if \n");

	if (easy_int()){
		printf("condition is an expression \n", fiB(6));
	}
	else{
		printf("there must be an error. \n");
	}

	if (0){
		printf("there must be error \n");;
	}
	else{
		printf("condition is an constant, actually it is an expression \n");;
	}

	printf("\n please input 5: ");
	scanf(num1);
	if (num1 > 0){
		printf(" condition: greater \n");;
	}
	if (num1 <10){
		printf(" condition: less \n");
	}
	if (num1 >= 1){
		printf(" condition: greater and equal \n");
	}
	if (num1 <=9){
		printf(" condition: less than equal \n");
	}
	if (num1 !=-2){
		printf(" condition: not equal \n");
	}
	if (num1 == 5){
		printf(" condition: equal \n");
	}
printf("----------------------------------------\n");
	recur_num1 = 5;
	while(recur_num1 < 10){
		printf(recur_num1);
		recur_num1 = recur_num1 + 1;
	}
	printf("\n this is a recur sentence");
printf("-----------------------------------------\n");
	{
		num1 = ret_int() *(15/3)+3;
		printf(" ");
		printf(num1);
		printf(" \n");
		scanf(read_num2);
	}
		printf(" statement column \n");
printf("------------------------------------------\n");
	scanf(num1);
	scanf(read_num2, read_char1);
	num_array1[1] = read_num2;
	read_num3[0] = num1;
	para_is_void(2, 8, num1, num_array1[1]);
	printf("\n   ", read_num3[0]);
	printf("\n no return value function call sentence");
printf("-----------------------------------------\n");
	printf("\n this is an type1 output: ",fiB(10));
	read_num2= easy_char();
	printf("\n type2 output: ", read_num2);
	printf("\n no return value function call sentence");
printf("-----------------------------------------\n");
	scanf(read_num1);
	scanf(read_num2, read_char1);
	printf("\n you can see the input: ", read_num1);
	printf("\n you can see the input: ", read_num2);
	printf("\n you can see the input: ", read_char1);
printf("-----------------------------------------\n");
	printf(easy_char());
	printf("qwefasvasdg     ",num_a + 15-14-1);
	printf("      !#$%^&*()/*-+,.0123456789:;<>=?@ABCDEFGHIJKLLMNOPQRSTUVWXYZ[\]^_'abcdefghijklmnopqrstuvwxyz{|}~   \n");
	printf("\n print sentence.");
printf("-----------------------------------------\n");
`	printf("\n please input -1 or 0: ");
	scanf(read_num1);
	switch (read_num1 + 1){
		case 0:
			{	
				printf("\n case 0 ~~~~ ");
			}
		case 1:
			printf("\n case 1 ~~~~ ");
	}
	
	printf("\n please input: +, -, *, /: ");
	scanf(read_char1);
	switch (read_char1){
		case '+':
			{	
				printf("\n case + ~~~~ ");
			}
		case '-':
			printf("\n case - ~~~~ ");
		case '*':
			printf("\n case * ~~~~ ");
		case '/':
			printf("\n case / ~~~~ ");
		default:
			printf("\n default !!! ");
	}

	printf("\n please wait for output: ");
	switch ('a'){
		case 'a':
			printf("\n this is the case ");
		case 'b':
			printf("\n there must be error \n");
	}
	
	switch(3){
        case 1:
            printf("\n should not be output");
    }
printf("-----------------------------------------\n");
	return;
}
