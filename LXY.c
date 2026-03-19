#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#define MAX_METEORS 10  // 流星数量
#define ROWS 24         // 屏幕总行数（含地面）
#define COLS 81         // 屏幕总列数（含字符串结束符'\0'）
#define GROUND_ROWS 5   // 地面总行数
// 关键：定义最后一行地面的数组索引（屏幕最下方的地面行）
#define LAST_GROUND_ROW (ROWS - 1)  

// 流星属性数组
char meteorChars[MAX_METEORS];   // 流星显示的字符（A-Z）
int meteorColors[MAX_METEORS];   // 流星颜色（1-15，控制台16色）
int meteorRows[MAX_METEORS];     // 流星当前行位置（1-based）
int meteorCols[MAX_METEORS];     // 流星当前列位置（1-based）
int meteorSpeeds[MAX_METEORS];   // 流星下落速度（1-4，数值越大越快）

char screen[ROWS][COLS];  // 屏幕缓存：存储天空（空格）和地面（#）
int isLastGroundFirstClear = 0;  // 标记：最后一行地面是否出现第一个#消失

// 初始化屏幕：天空为空格，地面（含最后一行）为#
void initScreen() {
	// 初始化天空区域（上方非地面部分）
	for (int i = 0; i < ROWS - GROUND_ROWS; i++) {
		for (int j = 0; j < COLS - 1; j++) {
			screen[i][j] = ' ';
		}
		screen[i][COLS - 1] = '\0';  // 字符串结束符
	}
	// 初始化地面区域（包含最后一行地面）
	for (int i = ROWS - GROUND_ROWS; i < ROWS; i++) {
		for (int j = 0; j < COLS - 1; j++) {
			screen[i][j] = '#';  // 所有地面行初始均为#
		}
		screen[i][COLS - 1] = '\0';
	}
}

// 检查列位置是否已被其他流星占用（避免初始重叠）
int isColUsed(int col, int meteorsCount) {
	for (int i = 0; i < meteorsCount; i++) {
		if (meteorCols[i] == col) {
			return 1;  // 已占用
		}
	}
	return 0;  // 未占用
}

// 初始化首批流星数据
void initMeteors() {
	srand((unsigned int)time(NULL));  // 随机数种子（确保每次运行不同）
	for (int i = 0; i < MAX_METEORS; i++) {
		meteorChars[i] = rand() % 26 + 'A';  // 随机A-Z字符
		meteorColors[i] = rand() % 15 + 1;    // 随机1-15颜色（排除黑色）
		meteorRows[i] = 1;                  // 初始行：屏幕顶部（1-based）
		// 生成不重复的列位置（1-80，避免流星初始重叠）
		int col;
		do {
			col = rand() % 80 + 1;
		} while (isColUsed(col, i));
		meteorCols[i] = col;
		meteorSpeeds[i] = rand() % 4 + 1;  // 随机速度1-4
	}
}

// 显示屏幕：含彩色流星、天空和地面
void display() {
	system("cls");  // 清屏（刷新画面，避免残影）
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // 控制台颜色控制句柄
	
	for (int i = 0; i < ROWS; i++) {  // 遍历每一行（0-based）
		for (int j = 0; j < COLS - 1; j++) {  // 遍历每一列（0-based）
			int isMeteor = 0;
			int color = 7;  // 默认颜色：浅灰色（天空/地面基础色）
			char currentChar = ' ';  // 当前位置要显示的字符
			
			// 检查当前位置是否有流星（匹配流星的1-based行列）
			for (int m = 0; m < MAX_METEORS; m++) {
				if (meteorRows[m] == i + 1 && meteorCols[m] == j + 1 && meteorChars[m] != ' ') {
					isMeteor = 1;
					color = meteorColors[m];
					currentChar = meteorChars[m];  // 记录流星字符（解决作用域问题）
					break;
				}
			}
			
			SetConsoleTextAttribute(hConsole, color);  // 设置字符颜色
			printf("%c", isMeteor ? currentChar : screen[i][j]);  // 显示流星或基础画面
		}
		printf("\n");  // 换行，开始下一行
	}
	SetConsoleTextAttribute(hConsole, 7);  // 恢复默认颜色（避免后续输出异常）
}

// 核心判断：检查最后一行地面是否出现第一个#消失
void checkLastGroundFirstClear() {
	if (isLastGroundFirstClear == 0) {  // 仅未触发时检查，避免重复判断
		for (int j = 0; j < COLS - 1; j++) {
			// 最后一行地面（LAST_GROUND_ROW）出现第一个空格，即第一个#消失
			if (screen[LAST_GROUND_ROW][j] == ' ') {
				isLastGroundFirstClear = 1;  // 标记触发终止条件
				break;  // 找到后立即退出，无需继续遍历
			}
		}
	}
}

// 模拟流星雨：下落+碰撞+重生+终止判断
void simulateMeteors() {
	// 循环运行，直到最后一行地面出现第一个#消失
	while (!isLastGroundFirstClear) {
		for (int i = 0; i < MAX_METEORS; i++) {  // 遍历每个流星
			// 流星消失后，重新生成新流星（持续补充，避免断流）
			if (meteorChars[i] == ' ') {
				meteorChars[i] = rand() % 26 + 'A';  // 重新生成字符
				meteorColors[i] = rand() % 15 + 1;    // 重新生成颜色
				meteorRows[i] = 1;                  // 重置到屏幕顶部
				// 重新生成不重复的列位置
				int col;
				do {
					col = rand() % 80 + 1;
				} while (isColUsed(col, i));
				meteorCols[i] = col;
				meteorSpeeds[i] = rand() % 4 + 1;  // 重新生成速度
				continue;  // 处理下一个流星，跳过当前下落逻辑
			}
			
			// 流星按速度逐行下落
			for (int s = 0; s < meteorSpeeds[i]; s++) {
				int oldRow = meteorRows[i];  // 流星当前行（1-based）
				int newRow = oldRow + 1;     // 下落一行后的行（1-based）
				int col = meteorCols[i];     // 流星列位置（1-based，垂直下落不变）
				
				// 擦除流星原位置（避免残影，转换为数组0-based索引）
				if (oldRow - 1 >= 0) {
					screen[oldRow - 1][col - 1] = ' ';
				}
				
				// 情况1：流星超出屏幕底部（1-based行>总行数），标记为消失
				if (newRow > ROWS) {
					meteorChars[i] = ' ';
					break;
				}
				
				// 情况2：流星撞到地面（当前位置是#）
				if (screen[newRow - 1][col - 1] == '#') {
					screen[newRow - 1][col - 1] = ' ';  // 清除被撞的#
					// 关键：仅当撞到的是最后一行地面时，才检查是否触发终止条件
					if (newRow - 1 == LAST_GROUND_ROW) {
						checkLastGroundFirstClear();  // 检查是否是最后一行第一个#消失
					}
					meteorChars[i] = ' ';  // 流星碰撞后消失
					break;  // 停止当前流星下落，处理下一次重生
				}
				
				// 情况3：正常下落，更新流星位置到新行
				screen[newRow - 1][col - 1] = meteorChars[i];
				meteorRows[i] = newRow;  // 记录流星新行位置
			}
		}
		
		display();  // 刷新屏幕画面
		Sleep(50);  // 控制帧率（50ms=20帧/秒，数值越大画面越卡顿）
	}
}

// 主函数：程序入口
int main() {
	initScreen();    // 初始化屏幕（天空+地面）
	initMeteors();   // 初始化首批流星
	display();       // 首次显示初始画面
	simulateMeteors();// 启动流星雨循环（直到触发终止条件）
	// 终止后提示（恢复默认颜色，确保提示清晰）
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("程序终止\n");
	return 0;
}