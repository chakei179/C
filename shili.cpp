#include <windows.h>
int main() {
    SetConsoleOutputCP(65001); // 终端切换为 UTF-8
    printf("中文内容\n");
    return 0;
}