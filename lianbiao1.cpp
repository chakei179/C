#include<stdio.h>
#include<iostream>
typedef struct node{
    int date;
    struct node *next;
}lnode,*linklist;

int initlist(linklist & l){
    l= new lnode;
    l->next=NULL;
return 0;
}

int tianjia(linklist &l,int i,int e){
    lnode *p,*s;
    int j;
    p=l;
    j=0;
    while (j<i-1&&p)
    {
        p=p->next;
        j++;
    }
    if (j>i-1||p==NULL)return 0;
    s=new lnode;
    s->date=e;
    s->next=p->next;
    p->next=s;
    return 0;
}



int shuchu(linklist l){
    linklist p;
    p=l->next;
    while (p)
    {
    printf("%d\n",p->date);
    p=p->next;
    }
    return 0;
}
  
int deleta(linklist&l,int i ,int e){
    linklist p,q;
    int j;
    p=l;
    j=0;
    while (j<i-1&&p->next)
    {
        j++;
        p=p->next;
    }
    if (j>i-1||p->next==NULL)
    return 0;
    q=p->next;
    e=q->date;
    p->next=q->next;
    
    return e;
}

int main(){
    linklist la;
    initlist(la);
    tianjia(la,1,11);
    tianjia(la,1,22);
    tianjia(la,2,45);
    tianjia(la,2,38);
    tianjia(la,3,78);
    shuchu(la);
    deleta(la,2,0);
    shuchu(la);

}