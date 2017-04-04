const int num_0 = 0, num_1 = 1, num_2 = 2;
const int num_3 = 3;
int s[20];
int num_v1, num_v2, num_v3;
int num_v4;
int num_v5;
int FiB(int n)
{
    if( n < 1 )
    {
        num_v2 = num_v2 + 1;
        return (-1);
    }
    if(n == 1)
    {
        num_v2 = num_v2 + 1;
        return (1);
    }
    else 
    if (n == 2)
    {
        num_v2 = num_v2 + 1;
        return (1);
    }
    num_v2 = num_v2 + 1;
    return (Fib(n - 1)+Fib(n - 2));
}
void hanoi(int i,char x,char y,char z){ 
  if(i == 1){ 
    printf(x);
    printf("->");
    printf(z);
    printf("\n"); 
  }else{ 
    hanoi(i - 1,x,z,y); 

    printf(x);
    printf("->");
    printf(z);
    printf("\n"); 

    hanoi(i - 1,y,x,z); 
    num_v1 = num_v1 + 1;
    return;
  } 
} 
void swap(int i,int j)
{
    int temp;
    temp=s[i];
    s[i]=s[j];
    s[j]=temp;
    num_v3 = num_v3 + 1;
    return ;
}
void QuickSort(int low,int high)
{
    int i;
    int last;
    if(low<high)
    {
        last=low;
        i = low+1;
        while (i<= high){
            if(s[i]<s[low])
            {
                last = last + 1;
                swap(last,i);
            }
            i = i+1;
        }
        swap(last,low);
        QuickSort(low,last-1);
        QuickSort(last+1,high);
    }
    return ;
    num_v4 = num_v4 + 1;
}
void main()
{
    int i;
    num_v1 = 0;
    num_v2 = 0;
    num_v3 = 0;
    num_v4 = 0;
    num_v5 = 0;

    s[0] = 4;
    s[1] = 2;
    s[2] = 9;
    s[3] = 1;
    s[4] = 5;
    s[5] = 6;
    s[6] = 8;
    s[7] = 7;
    s[8] = 3;
    printf("before sort :");i = 0; 
    while(i < 8)
    {
        printf(" ",s[i]);i = i + 1;
    }
    QuickSort(0,8);
    printf("after sort :");i = 0; 
    while(i < 8 )
    {
        printf(" ",s[i]);i= i + 1 +hanoi;
    }
    printf("\n", hanoi);
    hanoi(3, 'a', 'b', 'c');
    
    printf("\n hanoi tower return how many times? ", num_v1);
    printf("\n fib return how many times? ", num_v2);
    printf("\n swap return how many times? ", num_v3);
    printf("\n QuIcksORT tower return how many times? ", num_v4);
printf("\n----------------------------------------");
    switch(12* (15)*(-87 +86 *84) + s[3]){
        case 1:
            printf("\n not this value!!!!");
        case 'b':
            printf("\n not this value too!!!!");
        case 'c':
            printf("\n not this value too!!!!");
        case 1284664:
            printf("\n Ok !!!");
        default:
            printf("\n so be it.");

    }
printf("\n----------------------------------------");
    switch(3){
        case 1:
            printf("\n should not be output");
    }
printf("\n----------------------------------------");
    return;
}