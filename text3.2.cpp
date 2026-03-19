#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>  // 用于计时（Windows系统）

// 联系人结构体
typedef struct {
    char name[20];   // 姓名
    char phone[12];  // 电话号码（11位）
} Contact;

// 顺序表结构体
typedef struct {
    Contact *data;   // 存储联系人数据
    int length;      // 当前联系人数量
    int capacity;    // 容量
} SeqList;

// 单链表节点
typedef struct Node {
    Contact data;
    struct Node *next;
} Node, *LinkList;

// 初始化顺序表
SeqList* InitSeqList(int capacity) {
    SeqList *list = (SeqList*)malloc(sizeof(SeqList));
    list->data = (Contact*)malloc(sizeof(Contact) * capacity);
    list->length = 0;
    list->capacity = capacity;
    return list;
}

// 初始化单链表
LinkList InitLinkList() {
    LinkList head = (Node*)malloc(sizeof(Node));
    head->next = NULL;  // 头节点不存储数据
    return head;
}

// 顺序表插入联系人
void InsertSeqList(SeqList *list, Contact c) {
    if (list->length >= list->capacity) {
        printf("顺序表已满，无法插入！\n");
        return;
    }
    list->data[list->length++] = c;
}

// 单链表插入联系人（尾插法）
void InsertLinkList(LinkList head, Contact c) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = c;
    newNode->next = NULL;
    
    Node *p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newNode;
}

// 顺序表按姓名删除联系人
void DeleteSeqList(SeqList *list, char *name) {
    int i;
    for (i = 0; i < list->length; i++) {
        if (strcmp(list->data[i].name, name) == 0) {
            // 前移覆盖
            for (int j = i; j < list->length - 1; j++) {
                list->data[j] = list->data[j + 1];
            }
            list->length--;
            printf("删除成功！\n");
            return;
        }
    }
    printf("未找到该联系人！\n");
}

// 单链表按姓名删除联系人
void DeleteLinkList(LinkList head, char *name) {
    Node *p = head;
    while (p->next != NULL) {
        if (strcmp(p->next->data.name, name) == 0) {
            Node *temp = p->next;
            p->next = temp->next;
            free(temp);
            printf("删除成功！\n");
            return;
        }
        p = p->next;
    }
    printf("未找到该联系人！\n");
}

// 顺序表按序号查找（顺序查找）
Contact* SeqFindByIndex(SeqList *list, int index) {
    if (index < 0 || index >= list->length) {
        return NULL;
    }
    return &list->data[index];
}

// 单链表按序号查找（顺序查找）
Contact* LinkFindByIndex(LinkList head, int index) {
    Node *p = head->next;
    int i = 0;
    while (p != NULL && i < index) {
        p = p->next;
        i++;
    }
    return (p != NULL) ? &(p->data) : NULL;
}

// 顺序表按姓名二分查找（需先排序）
Contact* SeqBinaryFind(SeqList *list, char *name) {
    int left = 0, right = list->length - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(list->data[mid].name, name);
        if (cmp == 0) {
            return &list->data[mid];
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return NULL;
}

// 单链表按电话号码查找（选做功能）
Contact* LinkFindByPhone(LinkList head, char *phone) {
    Node *p = head->next;
    while (p != NULL) {
        if (strcmp(p->data.phone, phone) == 0) {
            return &(p->data);
        }
        p = p->next;
    }
    return NULL;
}

// 顺序表按电话号码查找（选做功能）
Contact* SeqFindByPhone(SeqList *list, char *phone) {
    for (int i = 0; i < list->length; i++) {
        if (strcmp(list->data[i].phone, phone) == 0) {
            return &list->data[i];
        }
    }
    return NULL;
}

// 显示联系人数量
int GetCountSeq(SeqList *list) {
    return list->length;
}
int GetCountLink(LinkList head) {
    int count = 0;
    Node *p = head->next;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

// 销毁顺序表
void DestroySeqList(SeqList *list) {
    free(list->data);
    free(list);
}

// 销毁单链表
void DestroyLinkList(LinkList head) {
    Node *p = head->next;
    while (p != NULL) {
        Node *temp = p;
        p = p->next;
        free(temp);
    }
    free(head);
}

// 顺序表排序（用于二分查找前的准备）
void SortSeqList(SeqList *list) {
    for (int i = 0; i < list->length - 1; i++) {
        for (int j = 0; j < list->length - 1 - i; j++) {
            if (strcmp(list->data[j].name, list->data[j + 1].name) > 0) {
                Contact temp = list->data[j];
                list->data[j] = list->data[j + 1];
                list->data[j + 1] = temp;
            }
        }
    }
}

// 生成随机联系人（用于批量插入）
void GenerateRandomContacts(Contact *contacts, int n) {
    char *firstNames[] = {"Zhang", "Li", "Wang", "Zhao", "Chen", "Liu", "Yang", "Huang", "Zhou", "Wu"};
    char *lastNames[] = {"Wei", "Qiang", "Yong", "Jie", "Min", "Hui", "Hong", "Bin", "Jun", "Fang"};
    
    for (int i = 0; i < n; i++) {
        // 随机生成姓名
        sprintf(contacts[i].name, "%s%s", 
                firstNames[rand() % 10], 
                lastNames[rand() % 10]);
        // 随机生成11位电话号码
        sprintf(contacts[i].phone, "138%08d", rand() % 100000000);
    }
}

// 性能测试函数（返回查找耗时，单位：毫秒）
double TestSeqIndexFind(SeqList *list, int index) {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    
    // 执行10000次查找（放大耗时）
    for (int i = 0; i < 10000; i++) {
        SeqFindByIndex(list, index);
    }
    
    QueryPerformanceCounter(&end);
    return (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000;
}

double TestLinkIndexFind(LinkList head, int index) {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    
    for (int i = 0; i < 10000; i++) {
        LinkFindByIndex(head, index);
    }
    
    QueryPerformanceCounter(&end);
    return (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000;
}

double TestSeqBinaryFind(SeqList *list, char *name) {
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    
    for (int i = 0; i < 10000; i++) {
        SeqBinaryFind(list, name);
    }
    
    QueryPerformanceCounter(&end);
    return (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000;
}

// 显示主界面
void ShowMenu() {
    printf("\n======= 手机通讯录管理系统 =======\n");
    printf("1. 初始化通讯录\n");
    printf("2. 批量插入20+联系人\n");
    printf("3. 删除联系人（按姓名）\n");
    printf("4. 按序号查找联系人\n");
    printf("5. 按姓名查找联系人（二分查找）\n");
    printf("6. 显示联系人总数\n");
    printf("7. 销毁通讯录\n");
    printf("8. 按电话号码查找联系人（选做）\n");
    printf("9. 查找性能分析与比较\n");
    printf("0. 退出系统\n");
    printf("=================================\n");
    printf("请输入操作编号：");
}

int main() {
    SeqList *seqList = NULL;
    LinkList linkList = NULL;
    int choice;
    int initFlag = 0;  // 标记是否已初始化
    
    while (1) {
        ShowMenu();
        scanf("%d", &choice);
        getchar();  // 吸收回车
        
        switch (choice) {
            case 1: {  // 初始化通讯录
                if (initFlag) {
                    printf("通讯录已初始化，是否重新初始化？(1-是 0-否)：");
                    int reInit;
                    scanf("%d", &reInit);
                    if (reInit == 0) break;
                    // 销毁旧数据
                    DestroySeqList(seqList);
                    DestroyLinkList(linkList);
                }
                seqList = InitSeqList(100);  // 容量100
                linkList = InitLinkList();
                initFlag = 1;
                printf("初始化成功！\n");
                break;
            }
            
            case 2: {  // 批量插入20+联系人
                if (!initFlag) {
                    printf("请先初始化通讯录！\n");
                    break;
                }
                int n;
                printf("请输入插入联系人数量（>=20）：");
                scanf("%d", &n);
                if (n < 20) {
                    printf("数量必须>=20！\n");
                    break;
                }
                Contact *contacts = (Contact*)malloc(sizeof(Contact) * n);
                GenerateRandomContacts(contacts, n);
                
                // 插入顺序表
                for (int i = 0; i < n; i++) {
                    InsertSeqList(seqList, contacts[i]);
                }
                // 插入链表
                for (int i = 0; i < n; i++) {
                    InsertLinkList(linkList, contacts[i]);
                }
                // 对顺序表排序（为二分查找做准备）
                SortSeqList(seqList);
                free(contacts);
                printf("成功插入%d名联系人！\n", n);
                break;
            }
            
            case 3: {  // 删除联系人
                if (!initFlag) {
                    printf("请先初始化通讯录！\n");
                    break;
                }
                char name[20];
                printf("请输入要删除的联系人姓名：");
                scanf("%s", name);
                DeleteSeqList(seqList, name);
                DeleteLinkList(linkList, name);
                SortSeqList(seqList);  // 删除后重新排序
                break;
            }
            
            case 4: {  // 按序号查找
                if (!initFlag) {
                    printf("请先初始化通讯录！\n");
                    break;
                }
                int index;
                printf("请输入查找的序号：");
                scanf("%d", &index);
                
                // 顺序表查找
                Contact *seqContact = SeqFindByIndex(seqList, index);
                if (seqContact) {
                    printf("顺序表查找结果：姓名=%s，电话=%s\n", 
                           seqContact->name, seqContact->phone);
                } else {
                    printf("顺序表中未找到该序号的联系人！\n");
                }
                
                // 链表查找
                Contact *linkContact = LinkFindByIndex(linkList, index);
                if (linkContact) {
                    printf("链表查找结果：姓名=%s，电话=%s\n", 
                           linkContact->name, linkContact->phone);
                } else {
                    printf("链表中未找到该序号的联系人！\n");
                }
                break;
            }
            
            case 5: {  // 按姓名二分查找（仅顺序表支持）
                if (!initFlag) {
                    printf("请先初始化通讯录！\n");
                    break;
                }
                char name[20];
                printf("请输入要查找的联系人姓名：");
                scanf("%s", name);
                
                Contact *contact = SeqBinaryFind(seqList, name);
                if (contact) {
                    printf("查找结果：姓名=%s，电话=%s\n", 
                           contact->name, contact->phone);
                } else {
                    printf("未找到该联系人！\n");
                }
                break;
            }
            
            case 6: {  // 显示联系人总数
                if (!initFlag) {
                    printf("请先初始化通讯录！\n");
                    break;
                }
                printf("顺序表联系人总数：%d\n", GetCountSeq(seqList));
                printf("链表联系人总数：%d\n", GetCountLink(linkList));
                break;
            }
            
            case 7: {  // 销毁通讯录
                if (!initFlag) {
                    printf("请先初始化通讯录！\n");
                    break;
                }
                DestroySeqList(seqList);
                DestroyLinkList(linkList);
                initFlag = 0;
                printf("通讯录已销毁！\n");
                break;
            }
            
            case 8: {  // 按电话号码查找（选做）
                if (!initFlag) {
                    printf("请先初始化通讯录！\n");
                    break;
                }
                char phone[12];
                printf("请输入要查找的电话号码：");
                scanf("%s", phone);
                
                // 顺序表查找
                Contact *seqContact = SeqFindByPhone(seqList, phone);
                if (seqContact) {
                    printf("顺序表查找结果：姓名=%s，电话=%s\n", 
                           seqContact->name, seqContact->phone);
                } else {
                    printf("顺序表中未找到该号码的联系人！\n");
                }
                
                // 链表查找
                Contact *linkContact = LinkFindByPhone(linkList, phone);
                if (linkContact) {
                    printf("链表查找结果：姓名=%s，电话=%s\n", 
                           linkContact->name, linkContact->phone);
                } else {
                    printf("链表中未找到该号码的联系人！\n");
                }
                break;
            }
            
            case 9: {  // 性能分析与比较
                if (!initFlag || GetCountSeq(seqList) < 20) {
                    printf("请先初始化并插入至少20名联系人！\n");
                    break;
                }
                int index = GetCountSeq(seqList) / 2;  // 中间位置索引
                char *testName = seqList->data[index].name;  // 测试用姓名
                
                printf("性能测试中...（执行10000次查找）\n");
                double seqIndexTime = TestSeqIndexFind(seqList, index);
                double linkIndexTime = TestLinkIndexFind(linkList, index);
                double binaryTime = TestSeqBinaryFind(seqList, testName);
                
                printf("\n======= 性能测试结果（单位：毫秒）=======\n");
                printf("顺序表按序号查找：%.4fms\n", seqIndexTime);
                printf("链表按序号查找：%.4fms\n", linkIndexTime);
                printf("顺序表二分查找（按姓名）：%.4fms\n", binaryTime);
                printf("========================================\n");
                printf("结论：\n");
                printf("1. 顺序表按序号查找效率远高于链表（随机访问优势）\n");
                printf("2. 二分查找效率远高于普通顺序查找（适用于有序数据）\n");
                break;
            }
            
            case 0: {  // 退出系统
                if (initFlag) {
                    DestroySeqList(seqList);
                    DestroyLinkList(linkList);
                }
                printf("谢谢使用，再见！\n");
                return 0;
            }
            
            default:
                printf("输入错误，请重新输入！\n");
        }
        system("pause");  // 暂停等待用户查看结果
        system("cls");    // 清屏（Windows系统）
    }
}