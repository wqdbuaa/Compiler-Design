int s[20];
int num;
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
void swap(int i,int j)
{
    int temp;
    temp=s[i];
    s[i]=s[j];
    s[j]=temp;
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
}
void main()
{   

    const int num_1 = 1, num_2 = 2;
    int numArray[10];
    int recurNum, num_output;
    int num2, num1, num3;
    char ch_output;
    int i;
    s[0] = 4;
    s[1] = 2;
    s[2] = 9;
    s[3] = 1;
    s[4] = 5;
    s[5] = 6;
    s[6] = 8;
    s[7] = 7;
    s[8] = 3;
    printf("\nbefore sort :");i = 0; 
    while(i < 8)
    {
        printf("\n ",s[i]);i = i + 1;
    }
    QuickSort(0,8);
    printf("\nafter sort :");i = 0; 
    while(i < 8 )
    {
        printf("\n ",s[i]);i= i + 1;
    }
    printf("\n", fib(10));
printf("\n----------------------------------------");
    num1 = 11;
    num2 = 12;
    num3 = num1 + num2;
    num_output = num1 * num_1+ num3/num_2;
    printf("\n !#$%^&*()/*-+,.0123456789:;<>=?@ABCDEFGHIJKLLMNOPQRSTUVWXYZ[\]^_'abcdefghijklmnopqrstuvwxyz{|}~");
    printf("\n asdfasdfasdf ", -num1 +4 *s[5] - fIb(10)   -'b'*2);
    printf("\n", s[5]);
    printf("\n");
    printf(-num1 +4 *s[5] - (fIb(10)   -'b')*2);
printf("\n----------------------------------------");
    scanf(num1, ch_output);
    printf("\n", num1 + ch_output);
    return;
}