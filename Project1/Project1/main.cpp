#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "canvas.cpp"
#include "donut.cpp"
void showCursor(_In_ DWORD nStdHandle, bool bolean)
{
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = bolean;
    cursor.dwSize = sizeof(cursor);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &cursor);
}

int main() {

    cls();
    
    //showCursor(STD_OUTPUT_HANDLE, 0);
    u32 r1, r2;
    u32 vd, od;
    
    usize heigth = 70, width = 100;

    f64 fps;
    f64 duration;

    bool ligth;
    cout << "�����뻷���Բ�ܰ뾶:\n";
    cout << "�����뻷��Ļ��뾶:\n";
    cout << "�����뻷����������Ļ����:\n";
    cout << "�������ӵ�����Ļ����:\n";
    cout << "��������Ļ��:\n";
    cout << "��������Ļ��:\n";
    cout << "����������֡��:\n";
    cout << "���������ʱ��:\n";
    cout << "�������Ƿ�򿪹���:\n";

    gotoxy(sizeof("�����뻷���Բ�ܰ뾶:\n"), 0);
    cin >> r2;
    
    gotoxy(sizeof("�����뻷��Ļ��뾶:\n"), 1);
    cin >> r1;
    gotoxy(sizeof("�����뻷����������Ļ����:\n"), 2);
    cin >> od;
    gotoxy(sizeof("�������ӵ�����Ļ����:\n"), 3);
    cin >> vd;
    gotoxy(sizeof("��������Ļ��:\n"), 4);
    cin >> width;
    gotoxy(sizeof("��������Ļ��:\n"), 5);
    cin >> heigth;
    gotoxy(sizeof("����������֡��\n"), 6);
    cin >> fps;
    gotoxy(sizeof("���������ʱ��\n"), 7);
    cin >> duration;
    gotoxy(sizeof("�������Ƿ�򿪹���(1/0)\n"), 8);
    cin >> ligth;
    system("pause");
    Canvas canvas = Canvas(heigth, width);
    Donut torus = Donut(r1, r2, vd, od, width, heigth);


    auto sleep_duration = 1000.0 / fps; 
    auto start_ts = clock();

    while (1)
    {
        showCursor(STD_OUTPUT_HANDLE,0);
        auto c_ts = clock();
        canvas.buffer_2_screen_raw(torus.next_frame_with_xy_rotate(ligth));
        while (1)
        {
            if ((f64)(clock() - c_ts) >= sleep_duration) {
                //showCursor(STD_OUTPUT_HANDLE, 0);
                break;
            }
        }
        if ((f64)(clock() - start_ts) / CLOCKS_PER_SEC >= duration) {
            break;
        }
    }

}
