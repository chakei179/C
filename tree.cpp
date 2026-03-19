#include<iostream>
#include<stdio.h>


 typedef struct tnode{
    char date;
    struct tnode *lch;
    struct tnode *rch;   
}treenode,*bitree;



int   createtree(bitree &t){
    char ch;
    scanf("%c",&ch);
    if (ch=='#'){
        t=NULL;
    return 0;
    }
else{t=new treenode;
    t->date=ch;
    createtree(t->lch);
    createtree(t->rch);
    return 1;}
}

int  pretree(bitree &t){
    if (t==NULL){
        return 0;
    }
  else{
   printf("%c",t->date);
   pretree(t->lch);
   pretree(t->rch);
   return 1;}
}

int intree(bitree &t){
    if (t== NULL)
    {
        return 0;
    }
    else
    {
    intree(t->lch);
    printf("%c",t->date);
    intree(t->rch);
    return 1;

    }
    
}


int main(){
    bitree tree;
    createtree(tree);
    pretree(tree);
    printf("\n");
    intree(tree);
}
