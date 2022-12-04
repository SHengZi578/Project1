#pragma once
#include <Windows.h>

#define TAU 6.283185307179586
#define i32 __int32
#define i64 __int64
#define u32 unsigned __int32
#define f32 float
#define f64 double
#define usize size_t
void static gotoxy(short x, short y) {
	//COORD是Windows API中定义的一种结构体类型，表示控制台屏幕上的坐标。
	//上面语句是定义了COORD类型的变量coord，并以形参x和y进行初始化。
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y });
	//GetStdHandle(STD_OUTPUT_HANDLE); 获取控制台输出句柄
	//然后用SetConsoleCursorPosition设置控制台(cmd)光标位置
}
void static cls() { system("cls"); }