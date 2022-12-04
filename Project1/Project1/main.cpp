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
    cout << "请输入环面的圆管半径:\n";
    cout << "请输入环面的环半径:\n";
    cout << "请输入环面中心与屏幕距离:\n";
    cout << "请输入视点与屏幕距离:\n";
    cout << "请输入屏幕宽:\n";
    cout << "请输入屏幕高:\n";
    cout << "请输入期望帧数:\n";
    cout << "请输入持续时间:\n";
    cout << "请输入是否打开光照:\n";

    gotoxy(sizeof("请输入环面的圆管半径:\n"), 0);
    cin >> r2;
    
    gotoxy(sizeof("请输入环面的环半径:\n"), 1);
    cin >> r1;
    gotoxy(sizeof("请输入环面中心与屏幕距离:\n"), 2);
    cin >> od;
    gotoxy(sizeof("请输入视点与屏幕距离:\n"), 3);
    cin >> vd;
    gotoxy(sizeof("请输入屏幕宽:\n"), 4);
    cin >> width;
    gotoxy(sizeof("请输入屏幕宽:\n"), 5);
    cin >> heigth;
    gotoxy(sizeof("请输入期望帧数\n"), 6);
    cin >> fps;
    gotoxy(sizeof("请输入持续时间\n"), 7);
    cin >> duration;
    gotoxy(sizeof("请输入是否打开光照(1/0)\n"), 8);
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
