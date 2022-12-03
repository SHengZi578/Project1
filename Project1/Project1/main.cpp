#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
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
    system("pause");
    showCursor(STD_OUTPUT_HANDLE, 0);
    usize heigth = 80, width = 80;
    Canvas canvas = Canvas(width, heigth);
    Donut torus = Donut(30, 15, 25, 80, width, heigth);


    auto sleep_duration = 1000.0 / 30; // fps 30
    auto start_ts = clock();

    while (1)
    {
        auto c_ts = clock();
        canvas.buffer_2_screen_raw(torus.next_frame_with_xy_rotate(1));
        while (1)
        {
            if ((f64)(clock() - c_ts) >= sleep_duration) {
                showCursor(STD_OUTPUT_HANDLE, 0);
                break;
            }
        }
        if ((f64)(clock() - start_ts) / CLOCKS_PER_SEC >= 300) {
            break;
        }
    }

}
