#include <iostream>
#include <windows.h>  // 仅 Windows 系统有效

int main() {
    // 根据终端编码选择一行：
    SetConsoleOutputCP(65001);  // 终端是 UTF-8 时用这个
    // SetConsoleOutputCP(936);   // 终端是 GBK 时用这个

    std::cout << "测试中文输出" << std::endl;  // 这里替换为你的中文内容
    return 0;
}