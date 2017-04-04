int easy_int(){
	return 1;
}
char easy_char(){
	return ;
}
int ret_int_no_para() {
	const int ret_int_1=15;
	printf(" \n", 123);
	printf("\n");
}
int ret_int_with_para(int ret_int_1) {
	printf(" \n"  456);
	printf("\n");
	return (ret_int_1);
}

int ret_int_with_many_para(int a, int b) {
	printf(" \n", 456);
	printf("\n");
	return (a + b);
}
char ret_Char_no_para(){
	int ret_char_1;
	char ret_char_2,ret_char_3;
	ret_char_1 = 48;
	printf("   \n", ret_char_1 / 4);
	printf("   \n", easy_char() * (15 + 4 *9));
	return (ret_char_1);
}
char ret_char_with_para(char b){
	int ret_char_1;
	char ret_char_2,ret_char_3;
	ret_char_1 = 48;
	printf("   \n", b);
	return (b);
}
char ret_char_with_many_para(char b, char c){
	int ret_char_1;
	char ret_char_2,ret_char_3;
	ret_char_1 = 48;
	printf("   ", b);
	printf("   ", c);
	return (b + c);
}
void void_no_para(){
	printf(" no return value and no parameter. \n");
	return;
}
void void_with_para(char k){
	printf(" no return value and one parameter. \n", k - 6);
}
void void_with_many_para(int b, char q){
	printf(" no return value and several parameter. \n", b + q);
}
void main(){
	int recurNum1;
	int readNum1;
	char readChar1;
	int readNum2, numArray[20];
	char readChar2, chArray[20];
	int num1, num2, num3, num4, num5;
	char ch1, ch2, ch3, ch4, ch5;

	char ch1;
printf("----------------------------------------\n");
	{
		printf("this is a statement column.\n");
		num3 = -10 -8*88+56   /(1 +1);
		num4 = num3 +2;
		numArray[0] = 15*87/15-86;
		num5 = numArray[0] + num4;
		printf(num5);
	}
	{

	}
	printf("empty statement column. \n");
	{
		;
	}
	printf("nearly empty statement column. \n");
printf("----------------------------------------\n");
	ret_int_no_para();
	ret_int_with(18);
	ret_int_with_many_para(19, 20);

	ret_char_NO_para();
	ret_char_WitH_para('a');
	ret_char_with_many_para('a', );
printf("----------------------------------------\n");
	void_no_para();
	void_with_para('A');
	void_with_many_para(10);
}