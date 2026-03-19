#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ========== 数组模拟法 ==========
void printCircleArray(int people[], int isOut[], int n, int curIndex) {
    printf("当前环形状态：");
    for (int i = 0; i < n; i++) {
        if (isOut[i] == 1) {
            printf("[%d] ", people[i]);
        } else {
            if (i == curIndex) {
                printf("(%d)* ", people[i]);
            } else {
                printf("(%d) ", people[i]);
            }
        }
    }
    printf("\n");
}

void josephusArray(int n, int m, int showProcess) {
    int *people = (int*)malloc(n * sizeof(int));
    int *isOut = (int*)calloc(n, sizeof(int));
    int count = 0, index = 0, outNum = 0;
    for (int i = 0; i < n; i++) {
        people[i] = i + 1;
    }
    if (showProcess) printf("===== 数组模拟法可视化过程 =====\n");
    while (outNum < n - 1) {
        if (showProcess) printCircleArray(people, isOut, n, index);
        if (isOut[index] == 0) {
            count++;
            if (showProcess) printf("当前报数：%d\n", count);
            if (count == m) {
                isOut[index] = 1;
                if (showProcess) printf("淘汰人员：%d\n", people[index]);
                outNum++;
                count = 0;
            }
        }
        index = (index + 1) % n;
        if (showProcess) printf("-------------------------\n");
    }
    for (int i = 0; i < n; i++) {
        if (isOut[i] == 0) {
            printf("数组模拟法最终幸存者为：%d\n", people[i]);
            break;
        }
    }
    free(people);
    free(isOut);
}

// ========== 循环链表法 ==========
typedef struct Node {
    int id;
    struct Node* next;
} Node;

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
    pre->next = head;
    return head;
}

void printCircleList(Node* head) {
    if (head == NULL) return;
    Node* p = head;
    printf("当前链表状态：");
    do {
        printf("%d->", p->id);
        p = p->next;
    } while (p != head);
    printf("%d\n", head->id);
}

void josephusList(int n, int m, int showProcess) {
    Node* head = createCircularList(n);
    if (head == NULL) return;
    Node* p = head;
    Node* q = NULL;
    int count = 0;
    if (showProcess) printf("===== 循环链表法可视化过程 =====\n");
    while (p->next != p) {
        if (showProcess) printCircleList(p);
        count++;
        if (showProcess) printf("当前报数节点：%d，报数计数：%d\n", p->id, count);
        if (count == m) {
            if (showProcess) printf("淘汰节点：%d\n", p->id);
            q->next = p->next;
            Node* temp = p;
            p = q->next;
            free(temp);
            count = 0;
        } else {
            q = p;
            p = p->next;
        }
        if (showProcess) printf("-------------------------\n");
    }
    printf("循环链表法最终幸存者为：%d\n", p->id);
    free(p);
}

// ========== 递推公式法 ==========
int josephusFormula(int n, int m, int showProcess) {
    int survivor = 0;
    if (showProcess) {
        printf("===== 递推公式法可视化过程 =====\n");
        printf("边界条件：f(1,%d)=%d\n", m, survivor);
    }
    for (int i = 2; i <= n; i++) {
        int prev = survivor;
        survivor = (survivor + m) % i;
        if (showProcess) {
            printf("f(%d,%d)=(f(%d,%d)+%d)%%%d=(%d+%d)%%%d=%d\n", 
                   i, m, i-1, m, m, i, prev, m, i, survivor);
        }
    }
    int result = survivor + 1;
    printf("递推公式法最终幸存者为：%d\n", result);
    return result;
}

// ========== 主函数（含时间统计） ==========
int main() {
    int n, m;
    printf("请输入总人数n和报数淘汰值m：");
    while (scanf("%d%d", &n, &m) != 2 || n <= 0 || m <= 0) {
        printf("输入不合法！请重新输入正整数n和m：");
        // 清空输入缓冲区
        while (getchar() != '\n');
    }

    // 测试数组模拟法
    clock_t start = clock();
    josephusArray(n, m, 0); // 0=不显示过程，1=显示过程
    clock_t end = clock();
    printf("数组模拟法耗时：%.3f 毫秒\n\n", (double)(end - start) / CLOCKS_PER_SEC * 1000);

    // 测试循环链表法
    start = clock();
    josephusList(n, m, 0);
    end = clock();
    printf("循环链表法耗时：%.3f 毫秒\n\n", (double)(end - start) / CLOCKS_PER_SEC * 1000);

    // 测试递推公式法
    start = clock();
    josephusFormula(n, m, 0);
    end = clock();
    printf("递推公式法耗时：%.3f 毫秒\n", (double)(end - start) / CLOCKS_PER_SEC * 1000);

    return 0;
}