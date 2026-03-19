#include<stdio.h>
#include<iostream>
#define N 10


typedef struct ta {
    int elem[N];
    int length;
} SeqList; 

int Search(SeqList list, int key) {
    for (int i = 0; i < list.length; i++) {
        if (list.elem[i] == key) { 
            return i;  
        }
    }
    return -1;  
}

int main() {
   
    SeqList list;
    list.length = 5;  
    list.elem[0] = 12;
    list.elem[1] = 34;
    list.elem[2] = 56;
    list.elem[3] = 78;
    list.elem[4] = 90;

    int key;
    printf("请输入查找的值");
    scanf("%d", &key);

    int a = Search(list, key);
    if (a != -1) {
        
        printf("已经找到，地址为%d", a);
    } else {
        printf("没有找到");
    }

    return 0;
}