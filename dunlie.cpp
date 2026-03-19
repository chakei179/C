#include<iostream>
#include<stdio.h>
#include <stdlib.h> 
#include <windows.h>

typedef struct QNode {
    int data;
    struct QNode *next;  
} QNode;


typedef struct {
    QNode *f;  
    QNode *r;  
} Queue;


void initq(Queue *q) {  
    q->f = (QNode*)malloc(sizeof(QNode));
    if (q->f == NULL) {  
        printf("内存分配失败，初始化队列失败\n");
        exit(1); 
    }
    q->f->next = NULL;  
    q->r = q->f;        
}


void enQ(Queue *q, int e) {
    
    QNode *p = (QNode*)malloc(sizeof(QNode));
    if (p == NULL) {
        printf("入队失败\n");
        exit(1);
    }
    p->data = e;       
    p->next = NULL;    
    q->r->next = p;    
    q->r = p;          
}


int deQ(Queue *q) {
    if (q->f == q->r) {  
        printf("队空，无法出队\n");
        return -1;
    }
    QNode *p = q->f->next;  
    int e = p->data;        
    q->f->next = p->next;   
    
   
    if (q->r == p) {
        q->r = q->f;
    }
    free(p); 
    return e;
}


int main() {
    Queue q;
    initq(&q);  
    
    
    enQ(&q, 10);
    enQ(&q, 20);
    enQ(&q, 30);
    
   printf("输入成功！");
   
    return 0;
}