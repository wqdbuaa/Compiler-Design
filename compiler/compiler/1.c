void main(){
	const int num_0 = 0; 
	const int num_1 = -1;
	const char ch_a = 'a';
	const char ch_Minus = '-'; 
	int recurNum1;
	int readNum1;
	char readChar1;
	int readNum2, numArray[20];
	char readChar2, chArray[20];
	int num1, num2, num3, num4, num5;
	char ch1, ch2, ch3, ch4, ch5;
	
	
//你开我关，关键词不出现	
printf("----------------------------------------\n");
	chArray[0] = 98;
	printf(chArray[0]);
	num3 = - 10 -8*88+56   /(1 +1);
	printf("  ", num3);
	num4 = + 10;
	printf("   ", num4);
	numArray[1] = 108;
	printf("   ", numArray[1]);
	ch1 = 12 + numArray[1]- 8 + 2*1;
	printf("    ", ch1);
printf("----------------------------------------\n");
	num5 = 2;
	if (1 < num5)
		printf("condition is a logic \n"); printf(" not in the if, this should appear. \n");;

	if (num_1){
		printf("condition is an expression \n");
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
		num2 = 0+158-65 +48* (-1+ 9);
		if (num2 != 7){
			printf("inside the if: there is another if. \n");
		}
		else
			;
		printf(" condition: greater \n");;
	}
	if (num1 <10){
		ch1 = 'a'; 
		while (ch1 == 'a'){
			ch2 = 'b' + 'a'- 'Z';
			ch1 = ch1 - 1;
		}
		printf(" condition: less \n ", ch1);
	}
	if (num1 >= 1){
		scanf(num2, ch3, num3, ch4);
		printf(" condition: greater and equal \n");
		printf(ch3+  num3 * num2);
		printf("\n");
	}
	if (num1 <=9){
		printf(" condition: less then equal \n");
	}
	if (num1 !=-2){}
		printf(" void sentence\n");
	if (num1 == 5){
		printf(" condition: equal \n");
	}
printf("----------------------------------------\n");
	numArray[1]= 3;
	while (numArray[1])
		numArray[1] = numArray[1]-1;
	printf("this is using expression as condition\n");

	num1 = 8;num2 = 1;
	while (num1 < 10)
		if (num2 > 0){
			num2 = num2-1;
		}
		else{
			num1 = num1 + 1;
			num2 = num2 - 1;
		}
	printf(" num1 = \n", num1);
	printf(" num2 = \n", num2);

	ch1 = 'b';
	while (ch1 == 'b')
		switch (ch1){
			case 1:
				printf("error\n");
			case 'b':
				ch1 = ch1+  3;
			default:
				printf("error\n");
		}
	printf("end of this while loop");
}
