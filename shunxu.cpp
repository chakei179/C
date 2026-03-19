#include<stdio.h>
#define MAXSIZE 100
#include<iostream>
#include <algorithm>
typedef struct shu
{
    int elem[MAXSIZE];
    int length;
}Sqlist;

int charu(Sqlist &l ,int i ,int e){
    int j;
    if(i<1||i>l.length){
        printf("weizhibuhefa\n");
    }
    if(l.length==MAXSIZE){
       printf("yijingmanle!\n"); 
    }
    for ( j=l.length;j>=i;j--)
    {l.elem[j]=l.elem[j-1];
        
    }
    l.elem[i-1]=e;
    l.length++;
    return 0;
}


int shuchu(Sqlist l){
    int i;
    for ( i = 0; i < l.length; i++)
    {
        printf("%d\n",l.elem[i]);
    }
    return 0;
}
int deletlist(Sqlist &l,int i ,int &e){

    int j;
    if (i<1||i>l.length)
    {
        printf("当前为空链表/n");

    }
   e=l.elem[i-1];
   for (j=i;j<=l.length; j++)
   {
    l.elem[j-1]=l.elem[j];
   }
    l.length--;
    return 0;
}



int main(void){
    Sqlist la;
    la.length=0;
    la.elem[0]=3;
    la.length=1;
    charu(la,1,33);
    charu(la,1,356);
    charu(la,1,44);
    charu(la,1,79);
    shuchu(la);
    deletlist(la,2,la.elem[0]);
    shuchu(la);

}
