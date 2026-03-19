#include <stdio.h>

// 数组模拟约瑟夫问题
void josephusArray(int n, int m) {
    int people[1000];  // 存储人员编号
    int isOut[1000] = {0};  // 标记是否被淘汰，0为未淘汰，1为已淘汰
    int count = 0;  // 报数计数器
    int index = 0;  // 当前遍历索引
    int outNum = 0;  // 已淘汰人数

    // 初始化人员编号
    for (int i = 0; i < n; i++) {
        people[i] = i + 1;
    }

    printf("数组模拟法淘汰顺序：");
    while (outNum < n - 1) {
        if (isOut[index] == 0) {
            count++;
            // 报数到m，标记淘汰
            if (count == m) {
                isOut[index] = 1;
                printf("%d ", people[index]);
                outNum++;
                count = 0;
            }
        }
        index = (index + 1) % n;  // 环形遍历
    }

    // 查找幸存者
    for (int i = 0; i < n; i++) {
        if (isOut[i] == 0) {
            printf("\n最终幸存者为：%d\n", people[i]);
            break;
        }
    }
}

int main() {
    int n, m;
    printf("请输入总人数n和报数淘汰值m：");
    scanf("%d%d", &n, &m);
    if (n <= 0 || m <= 0) {
        printf("输入数据不合法，需为正整数！\n");
        return 1;
    }
    josephusArray(n, m);
    return 0;
}