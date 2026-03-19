#include<stdio.h>
#include<iostream>
#define MAXSIZE 100
//通讯录结构体
typedef struct {
char phone_name[20];
char phone_number[15];
}phonebook;
//顺序表结构体
typedef struct {
    phonebook *data;
    int length;
    int listsize;
}sqlist;
//初始化顺序表
void initlist(sqlist &L){
    L.data=new phonebook[MAXSIZE];
    L.length=0;
    L.listsize=MAXSIZE;
}
//插入元素
int insertlist(sqlist &l,int i,phonebook e){
    int j;
    if(i<1||i>l.listsize+1){
        printf("位置不合法，请重新输入，兄弟！\n");
        return -1;
    }

    if(l.length==l.listsize){
        printf("顺序表满了，兄弟，别插了！\n");
        return -1;
    }
    if(l.length==0){
        l.data[0]=e;
        l.length++;
        return 0;
    }
    else{
    for(j=l.length;j>=i;j--){
        l.data[j]=l.data[j-1];
    }
}
}