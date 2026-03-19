#include<stdio.h>
#include<iostream>
#define N 10

typedef struct erfen_search {
    int arr[N];
    int length;  
} er;


int bisearch(er &a, int target) {
    int lef = 0;
    int rt = a.length - 1;  

    while (lef <= rt) {
        int mid = lef + (rt - lef) / 2;  
        if (a.arr[mid] == target) {
            return mid;
        } else if (target < a.arr[mid]) {  
            rt = mid - 1;
        } else {
            lef = mid + 1;
        }
    }
    return -1;  
}

int main() {
    er list1;
    list1.arr[0] = 11;
    list1.arr[1] = 22;
    list1.arr[2] = 33;
    list1.arr[3] = 44;
    list1.arr[4] = 55;
    list1.arr[5] = 66;
    list1.arr[6] = 77;
    list1.arr[7] = 88;
    list1.length = 8;

    int jieguo = bisearch(list1, 77);

    printf("查找的地址结果是%d\n", jieguo);  
    
    return 0;  
}