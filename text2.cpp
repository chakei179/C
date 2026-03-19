#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHAR 26
#define MAX_NODE 51

typedef struct HuffmanNode {
    int weight;
    char ch;
    struct HuffmanNode *left, *right;
} HuffmanNode;

typedef struct {
    char ch;
    char code[20];
} HuffmanCode;

void countWeights(char *plainText, int *weights) {
    memset(weights, 0, MAX_CHAR * sizeof(int));
    int len = strlen(plainText);
    for (int i = 0; i < len; i++) {
        if (isalpha(plainText[i])) {
            char lowerCh = tolower(plainText[i]);
            weights[lowerCh - 'a']++;
        }
    }
}

HuffmanNode* createNode(int weight, char ch) {
    HuffmanNode *node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    node->weight = weight;
    node->ch = ch;
    node->left = node->right = NULL;
    return node;
}

int initHuffmanNodes(HuffmanNode **nodes, int *weights, char *chars) {
    int count = 0;
    for (int i = 0; i < MAX_CHAR; i++) {
        if (weights[i] > 0) {
            chars[count] = 'a' + i;
            nodes[count] = createNode(weights[i], chars[count]);
            count++;
        }
    }
    return count;
}

HuffmanNode* buildHuffmanTree(HuffmanNode **nodes, int nodeCount) {
    while (nodeCount > 1) {
        int min1 = 0, min2 = 1;
        if (nodes[min1]->weight > nodes[min2]->weight) {
            int temp = min1;
            min1 = min2;
            min2 = temp;
        }
        for (int i = 2; i < nodeCount; i++) {
            if (nodes[i]->weight < nodes[min1]->weight) {
                min2 = min1;
                min1 = i;
            } else if (nodes[i]->weight < nodes[min2]->weight) {
                min2 = i;
            }
        }
        HuffmanNode *newNode = createNode(nodes[min1]->weight + nodes[min2]->weight, '\0');
        newNode->left = nodes[min1];
        newNode->right = nodes[min2];
        nodes[min1] = newNode;
        nodes[min2] = nodes[nodeCount - 1];
        nodeCount--;
    }
    return nodes[0];
}

void generateHuffmanCode(HuffmanNode *root, char *code, int depth, HuffmanCode *huffCodes, int *codeCount) {
    if (root->left == NULL && root->right == NULL) {
        code[depth] = '\0';
        strcpy(huffCodes[*codeCount].code, code);
        huffCodes[*codeCount].ch = root->ch;
        (*codeCount)++;
        return;
    }
    code[depth] = '0';
    generateHuffmanCode(root->left, code, depth + 1, huffCodes, codeCount);
    code[depth] = '1';
    generateHuffmanCode(root->right, code, depth + 1, huffCodes, codeCount);
}

void plainToCipher(char *plainText, HuffmanCode *huffCodes, int codeCount, char *cipherText) {
    cipherText[0] = '\0';
    int len = strlen(plainText);
    for (int i = 0; i < len; i++) {
        if (!isalpha(plainText[i])) continue;
        char lowerCh = tolower(plainText[i]);
        for (int j = 0; j < codeCount; j++) {
            if (huffCodes[j].ch == lowerCh) {
                strcat(cipherText, huffCodes[j].code);
                break;
            }
        }
    }
}

void freeHuffmanTree(HuffmanNode *root) {
    if (root == NULL) return;
    freeHuffmanTree(root->left);
    freeHuffmanTree(root->right);
    free(root);
}

void printWeights(int *weights) {
    printf("=== 字母权值统计（不区分大小写）===\n");
    for (int i = 0; i < MAX_CHAR; i++) {
        if (weights[i] > 0) {
            printf("字母 '%c'：出现 %d 次\n", 'a' + i, weights[i]);
        }
    }
    printf("\n");
}

void printHuffmanCodes(HuffmanCode *huffCodes, int codeCount) {
    printf("=== 哈夫曼编码表 ===\n");
    for (int i = 0; i < codeCount; i++) {
        printf("字母 '%c'：%s\n", huffCodes[i].ch, huffCodes[i].code);
    }
    printf("\n");
}

int main() {
    char plainText[] = "In this course, we mainly learned some basic data structures, like: Linked List, Stack, Queue, Binary Tree and Graph.";
    int weights[MAX_CHAR] = {0};
    countWeights(plainText, weights);
    printWeights(weights);

    HuffmanNode *nodes[MAX_CHAR];
    char chars[MAX_CHAR];
    int nodeCount = initHuffmanNodes(nodes, weights, chars);
    if (nodeCount <= 0) {
        printf("明文中无有效字母！\n");
        return 1;
    }

    HuffmanNode *root = buildHuffmanTree(nodes, nodeCount);

    HuffmanCode huffCodes[MAX_CHAR];
    int codeCount = 0;
    char code[20];
    generateHuffmanCode(root, code, 0, huffCodes, &codeCount);
    printHuffmanCodes(huffCodes, codeCount);

    char cipherText[1024] = {0};
    plainToCipher(plainText, huffCodes, codeCount, cipherText);
    printf("=== 哈夫曼编码密文 ===\n%s\n", cipherText);

    freeHuffmanTree(root);
    return 0;
}