#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int E;
struct List {
    E *arr;       // 动态数组
    int capacity; // 容量（最大可存储元素数）
    int size;     // 当前元素个数
};

typedef struct List *ArrayList;

// 初始化顺序表（注意：传入的是结构体指针，直接操作原结构体）
_Bool initList(ArrayList list) {
    list->arr = (E*)malloc(sizeof(E) * 10); // 初始容量10
    if (list->arr == NULL) return 0;        // 内存分配失败返回false
    list->capacity = 10;
    list->size = 0;
    return 1;
}

// 插入元素到指定索引（索引从1开始，符合题目逻辑）
_Bool insertList(ArrayList list, E element, int index) {
    // 1. 检查索引合法性（1 <= index <= size+1）
    if (index < 1 || index > list->size + 1) return 0;
    // 2. 容量不足时扩容（扩容为原来的1.5倍）
    if (list->size >= list->capacity) {
        int newCapacity = list->capacity + list->capacity / 2;
        E *newArr = (E*)realloc(list->arr, newCapacity * sizeof(E));
        if (newArr == NULL) return 0; // 扩容失败返回false
        list->arr = newArr;
        list->capacity = newCapacity;
    }
    // 3. 元素后移（从最后一个元素开始，到插入位置结束）
    for (int i = list->size; i > index - 1; i--) {
        list->arr[i] = list->arr[i - 1];
    }
    // 4. 插入元素并更新size
    list->arr[index - 1] = element;
    list->size++;
    return 1;
}

// 打印顺序表（无递归，正常遍历）
void printList(ArrayList list) {
    printf("当前列表元素（共%d个）：", list->size);
    for (int i = 0; i < list->size; ++i) {
        printf("%d ", list->arr[i]); // 元素用空格分隔
    }
    printf("\n");
}

// 释放顺序表内存（避免内存泄漏）
void freeList(ArrayList list) {
    if (list->arr != NULL) {
        free(list->arr);
        list->arr = NULL; // 避免野指针
        list->capacity = 0;
        list->size = 0;
    }
}

int main() {
    struct List list; // 定义结构体变量（栈上分配）
    if (initList(&list)) { // 传入结构体地址，初始化
        printf("顺序表初始化成功！初始容量：%d\n", list.capacity);
        for (int i = 0; i < 30; ++i) {
            // 插入元素：值为i*10，索引为i+1（从1开始）
            if (insertList(&list, i * 10, i + 1)) {
                printList(&list); // 打印插入后的列表
                printf("当前容量：%d\n", list.capacity); // 打印当前容量
                printf("------------------------\n");
            } else {
                printf("插入第%d个元素失败！\n", i + 1);
                break;
            }
        }
        freeList(&list); // 释放内存
    } else {
        printf("顺序表初始化失败，无法启动程序\n");
    }
    return 0;
}