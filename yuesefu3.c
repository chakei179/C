#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ==================== 通用工具函数 ====================
// 清空输入缓冲区
void clearInputBuffer() {
    while (getchar() != '\n');
}

// ==================== 数组模拟法实现 ====================
void printCircleArray(int people[], int isOut[], int n, int curIndex) {
    printf("┌─────────────────────────────────────┐\n");
    printf("│ 当前环形状态：");
    for (int i = 0; i < n; i++) {
        if (isOut[i] == 1) {
            printf("[%d] ", people[i]); // 已淘汰人员
        } else {
            if (i == curIndex) {
                printf("(%d)* ", people[i]); // 当前报数人员
            } else {
                printf("(%d) ", people[i]); // 未淘汰人员
            }
        }
    }
    printf("│\n");
    printf("└─────────────────────────────────────┘\n");
}

void josephusArrayTest(int n, int m) {
    int people[1000];
    int isOut[1000] = {0};
    int count = 0, index = 0, outNum = 0;
    
    // 初始化人员编号
    for (int i = 0; i < n; i++) {
        people[i] = i + 1;
    }
    
    printf("\n=====================================\n");
    printf("========= 数组模拟法测试结果 =========");
    printf("\n=====================================\n");
    printf("测试用例：总人数n=%d，报数淘汰值m=%d\n", n, m);
    printf("-------------------------------------\n");
    
    // 核心逻辑
    while (outNum < n - 1) {
        printCircleArray(people, isOut, n, index);
        
        if (isOut[index] == 0) {
            count++;
            printf("│ 当前报数：%d                          │\n", count);
            
            if (count == m) {
                isOut[index] = 1;
                printf("│ 淘汰人员：%d                          │\n", people[index]);
                outNum++;
                count = 0;
            }
        }
        
        index = (index + 1) % n;
        printf("-------------------------------------\n");
    }
    
    // 查找并输出幸存者
    for (int i = 0; i < n; i++) {
        if (isOut[i] == 0) {
            printf("=====================================\n");
            printf("数组模拟法最终幸存者：%d\n", people[i]);
            printf("=====================================\n");
            break;
        }
    }
}

// ==================== 循环链表法实现 ====================
typedef struct Node {
    int id;
    struct Node* next;
} Node;

// 创建循环链表
Node* createCircularList(int n) {
    if (n <= 0) return NULL;
    Node* head = (Node*)malloc(sizeof(Node));
    head->id = 1;
    Node* pre = head;
    
    for (int i = 2; i <= n; i++) {
        Node* cur = (Node*)malloc(sizeof(Node));
        cur->id = i;
        pre->next = cur;
        pre = cur;
    }
    pre->next = head; // 形成循环
    return head;
}

// 打印链表状态
void printCircleList(Node* head) {
    if (head == NULL) return;
    Node* p = head;
    printf("┌─────────────────────────────────────┐\n");
    printf("│ 当前链表状态：");
    do {
        printf("%d->", p->id);
        p = p->next;
    } while (p != head);
    printf("%d │\n", head->id);
    printf("└─────────────────────────────────────┘\n");
}

// 链表法核心逻辑
void josephusListTest(int n, int m) {
    Node* head = createCircularList(n);
    if (head == NULL) return;
    
    Node* p = head;
    Node* q = NULL; // 前驱节点
    int count = 0;
    
    printf("\n=====================================\n");
    printf("========= 循环链表法测试结果 =========");
    printf("\n=====================================\n");
    printf("测试用例：总人数n=%d，报数淘汰值m=%d\n", n, m);
    printf("-------------------------------------\n");
    
    while (p->next != p) { // 只剩一个节点时停止
        printCircleList(p);
        count++;
        printf("│ 当前报数节点：%d，报数计数：%d       │\n", p->id, count);
        
        if (count == m) {
            printf("│ 淘汰节点：%d                          │\n", p->id);
            q->next = p->next; // 删除当前节点
            Node* temp = p;
            p = q->next;
            free(temp); // 释放内存
            count = 0;
        } else {
            q = p;
            p = p->next;
        }
        printf("-------------------------------------\n");
    }
    
    printCircleList(p);
    printf("=====================================\n");
    printf("循环链表法最终幸存者：%d\n", p->id);
    printf("=====================================\n");
    free(p);
}

// ==================== 递推公式法实现 ====================
int josephusFormulaTest(int n, int m) {
    int survivor = 0; // 0起始索引
    
    printf("\n=====================================\n");
    printf("========= 递推公式法测试结果 =========");
    printf("\n=====================================\n");
    printf("测试用例：总人数n=%d，报数淘汰值m=%d\n", n, m);
    printf("-------------------------------------\n");
    printf("│ 递推过程：                          │\n");
    printf("│ 边界条件：f(1,%d) = %d               │\n", m, survivor);
    
    for (int i = 2; i <= n; i++) {
        int prev = survivor;
        survivor = (survivor + m) % i;
        printf("│ f(%d,%d) = (f(%d,%d)+%d)%%%d = (%d+%d)%%%d = %d │\n",
               i, m, i-1, m, m, i, prev, m, i, survivor);
    }
    
    int result = survivor + 1; // 转换为1起始编号
    printf("-------------------------------------\n");
    printf("│ 0起始索引幸存者：%d                 │\n", survivor);
    printf("│ 1起始编号幸存者：%d                 │\n", result);
    printf("=====================================\n");
    printf("递推公式法最终幸存者：%d\n", result);
    printf("=====================================\n");
    
    return result;
}

// ==================== 效率测试函数 ====================
void testEfficiency(int n, int m) {
    clock_t start, end;
    double timeCost;
    
    printf("\n=====================================\n");
    printf("========= 算法效率测试结果 ==========");
    printf("\n=====================================\n");
    printf("测试用例：总人数n=%d，报数淘汰值m=%d\n", n, m);
    
    // 数组模拟法效率测试
    start = clock();
    for (int i = 0; i < 100; i++) { // 重复100次放大耗时
        int people[1000] = {0};
        int isOut[1000] = {0};
        int count = 0, index = 0, outNum = 0;
        for (int j = 0; j < n; j++) people[j] = j+1;
        while (outNum < n-1) {
            if (isOut[index] == 0) {
                count++;
                if (count == m) {
                    isOut[index] = 1;
                    outNum++;
                    count = 0;
                }
            }
            index = (index + 1) % n;
        }
    }
    end = clock();
    timeCost = (double)(end - start) / CLOCKS_PER_SEC * 10; // 还原单次耗时
    printf("数组模拟法耗时：%.4f 毫秒\n", timeCost);
    
    // 循环链表法效率测试
    start = clock();
    for (int i = 0; i < 100; i++) {
        Node* head = createCircularList(n);
        if (head == NULL) continue;
        Node* p = head;
        Node* q = NULL;
        int count = 0;
        while (p->next != p) {
            count++;
            if (count == m) {
                q->next = p->next;
                Node* temp = p;
                p = q->next;
                free(temp);
                count = 0;
            } else {
                q = p;
                p = p->next;
            }
        }
        free(p);
    }
    end = clock();
    timeCost = (double)(end - start) / CLOCKS_PER_SEC * 10;
    printf("循环链表法耗时：%.4f 毫秒\n", timeCost);
    
    // 递推公式法效率测试
    start = clock();
    for (int i = 0; i < 10000; i++) { // 重复10000次放大耗时
        int survivor = 0;
        for (int j = 2; j <= n; j++) {
            survivor = (survivor + m) % j;
        }
    }
    end = clock();
    timeCost = (double)(end - start) / CLOCKS_PER_SEC / 100; // 还原单次耗时
    printf("递推公式法耗时：%.4f 毫秒\n", timeCost);
    printf("=====================================\n");
}

// ==================== 主函数 ====================
int main() {
    // 固定测试用例1：基础功能测试（n=5, m=3）
    int n1 = 5, m1 = 3;
    printf("========= 约瑟夫问题测试演示 =========\n");
    printf("测试用例1：基础功能验证（n=5, m=3）\n");
    
    // 执行三种算法的功能测试
    josephusArrayTest(n1, m1);
    josephusListTest(n1, m1);
    josephusFormulaTest(n1, m1);
    
    // 固定测试用例2：效率对比测试（n=1000, m=10）
    int n2 = 1000, m2 = 10;
    printf("\n测试用例2：算法效率对比（n=1000, m=10）\n");
    testEfficiency(n2, m2);
    
    // 自定义测试（可选）
    int n, m;
    printf("\n是否进行自定义测试？(1=是，0=否)：");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        printf("请输入自定义总人数n和报数淘汰值m：");
        while (scanf("%d%d", &n, &m) != 2 || n <= 0 || m <= 0) {
            printf("输入不合法！请重新输入正整数：");
            clearInputBuffer();
        }
        josephusArrayTest(n, m);
        josephusListTest(n, m);
        josephusFormulaTest(n, m);
        testEfficiency(n, m);
    }
    
    return 0;
}