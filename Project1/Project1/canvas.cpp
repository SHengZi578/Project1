#pragma once
#include <math.h>
#include <vector>
#include "turnTo.h"
#include <iostream>
using namespace std;

class Canvas {
public:
	i32 length, width;
	Canvas(i32 length, i32 width) {
		this->length = length;
		this->width = width;
	}

	void buffer_2_screen_raw(const vector<vector<char>>& pixel_buf) {
		cls();
		bool isEmpty = 0;
		for (usize y = 0; y < this->length; y++) {
			for (usize x = 0; x < this->width; x++) {
				if (pixel_buf[x][y] == '\0') {
					//cout << "  ";
					isEmpty = 1;
				}
				else {
					if (isEmpty) {
						gotoxy(x * 2, y);
						isEmpty = 0;
					}
					cout << pixel_buf[x][y] << " ";
				}
			}
			cout << endl;
		}
	}
};