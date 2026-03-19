#include<stdio.h>
#include<iostream>

void maopao(int arr[],int n){
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n-i; j++)
        {
            if (arr[j]>arr[j+1])
            {
                int hh=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=hh;
            }
            
        }
        
    }
}




void quicksort(int arr[],int left,int right){
    if (left>=right)
    {
        return;
    }
    int i=left;
    int j=right;
    int key=arr[left]; 
    while (i<j)
    {
        while (i<j&&arr[j]>=key)
        {
            j--;
        }
        arr[i]=arr[j];
        while (i<j&&arr[i]<=key)
        {
            i++;
        }
        arr[j]=arr[i];
    }
    arr[i]=key;
    quicksort(arr,left,i-1);
    quicksort(arr,i+1,right);
    
}


int main(){
    int arr[11]={0,5,2,88,1,6,8,11,44,2,7};
    // maopao(arr,11);
    quicksort(arr,1,10);
    for (int i = 1; i < 11; i++)
    {
        printf("%d ",arr[i]);
    }
}
