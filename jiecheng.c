#include<stdio.h>

int fn(int i){
int j;
int s=1;
for (j=1;j<= i ;j++)
{
  s=s*j;

}
 return s;
}

int main (void){int i;
    int g ;
int sum=0;
    scanf( "%d", &i);
    g =fn(i);
    for ( int a=1;a<=i;a++){
    sum=sum+fn(a);
    }
    printf("ijiecheng%5d\n",sum);
    printf("%d\n",g);
}