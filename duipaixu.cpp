#include<stdio.h>
#include<iostream>


void duipaixu(int arr[],int n){
    for (int i = n/2; i >=1 ; i--)
    {
        int j=i;
        int temp=arr[j];
        while (j*2<=n)
        {
            int k=j*2;
            if (k+1<=n&&arr[k]<arr[k+1])
            {
                k=k+1;
            }
            if (arr[k]>temp)
            {
                arr[j]=arr[k];
                j=k;
            }
            else
            {
                break;
            }
            
        }
        arr[j]=temp;
        
    }
    for (int i = n; i >1 ; i--)
    {
        int t=arr[1];
        arr[1]=arr[i];
        arr[i]=t;
        int j=1;
        int temp=arr[j];
        while (j*2<=i-1)
        {
            int k=j*2;
            if (k+1<=i-1&&arr[k]<arr[k+1])
            {
                k=k+1;
            }
            if (arr[k]>temp)
            {
                arr[j]=arr[k];
                j=k;
            }
            else
            {
                break;
            }
            
        }
        arr[j]=temp;
        
    }
    
}
int main(){
    int arr[11]={0,5,2,88,1,6,8,11,44,2,7};
    duipaixu(arr,10);
    for (int i = 1; i < 11; i++)
    {
        printf("%d ",arr[i]);
    }
}