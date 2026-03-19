#include <iostream>
#include <stdio.h>
#define max 5  

typedef struct stack {
   // int elem[max];  
   int *elem;
   int size;
    int top;
} zhan;


int chushizhan(zhan &s) {
    s.elem=new int [max];
    s.size= max;
    s.top = 0;
    return 0;
}


int ruzhan(zhan &s, int e) {
    if (s.top > max - 1) {  
        printf("ZHANMAN,ERROR!"); 
        return 0;
    } else {
        s.elem[s.top] = e;
        s.top++;
        return 0;
    }
}

int chuzhan(zhan &s) {
    int e;
    if (s.top == 0) {
        printf("ZHANKONG,ERROR!"); 
        return 0; 
    } else {
        s.top--;  
        e = s.elem[s.top];
        return e;
    }
}

int getzhan(zhan &s) {
    if (s.top == 0) {  
        printf("ZHANKONG,ERROR!");
        return 0;
    }
    int e = s.elem[s.top - 1];  
    return e;
}

int main() {
    zhan sa;
    int e;
    chushizhan(sa);
    ruzhan(sa, 20);
    ruzhan(sa, 10);  
    
    e = getzhan(sa);  
    printf("%d\n", e);  
    
    e = chuzhan(sa);  
    printf("%d\n", e);  
     e = chuzhan(sa);  
    printf("%d\n", e);
    return 0;
}