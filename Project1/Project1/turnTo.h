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
	//COORD��Windows API�ж����һ�ֽṹ�����ͣ���ʾ����̨��Ļ�ϵ����ꡣ
	//��������Ƕ�����COORD���͵ı���coord�������β�x��y���г�ʼ����
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x, y });
	//GetStdHandle(STD_OUTPUT_HANDLE); ��ȡ����̨������
	//Ȼ����SetConsoleCursorPosition���ÿ���̨(cmd)���λ��
}
void static cls() { system("cls"); }