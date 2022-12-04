#pragma once
#include <math.h>
#include <vector>
#include "turnTo.h"
using namespace std;
static char LUMINANCE_CHARS[12] = { '.', ',', '-', '~', ':', ';', '=', '!', '*', '#', '$', '@' };
static f32 RESO = 0.05;

class Donut {
public:
	f32 r1, r2;
	u32 viewer_distance, object_distance;
	usize scr_width, scr_height;
	f32 delta, a_radian;
	f32 light_source[3];
	Donut(u32 r1, u32 r2, u32 vd, u32 od, usize sw, usize sl) {
		this->r1 = r1;
		this->r2 = r2;
		viewer_distance = vd;
		object_distance = od;
		scr_width = sw;
		scr_height = sl;
		delta = 0.0;
		a_radian = 0.0;
		light_source[0] = 1.0, light_source[1] = 0.0, light_source[2] = 1.0;
	}

	// zx平面画圆，围绕z轴转动
	// r2*cos(psi)*cos(the) + r1*cos(psi), -r2*sin(psi)*cos(the) - r1*sin(psi), r2*sin(the)
//#[allow(dead_code)]
	vector<vector<char>> regulated_pixels() {
		vector<vector<i32>>  zbuf(this->scr_width, vector<i32>(this->scr_height, -123));
		vector<vector<char>>  output(this->scr_width, vector<char>(this->scr_height, '\0'));
		f32  psi = 0.0;
		f32  theta = 0.0;

		f32 wid_offset = (this->scr_width / 2);
		f32 hei_offset = (this->scr_height / 2);

		while (1) {
			psi += 0.05;
			f32 sin_p = sin(psi);
			f32 cos_p = cos(psi);
			auto z = (this->r2 * sin_p);
			auto z_apo = this->viewer_distance / (this->object_distance - z);

			while (1) {
				theta += 0.05;

				f32 sin_t = sin(theta);
				f32 cos_t = cos(theta);

				auto x = this->r2 * cos_t * cos_p + this->r1 * cos_t;
				auto y = -1.0 * this->r2 * sin_t * cos_p - this->r1 * sin_t;
				auto xp = (x * z_apo + wid_offset);
				auto yp = (y * z_apo + hei_offset);

				if (z > zbuf[xp][yp]) {
					zbuf[xp][yp] = z;
					output[xp][yp] = '*';
				}

				if (theta >= TAU) {
					break;
				}
			}
			theta = 0.0;
			if (psi >= TAU) {
				break;
			}
		}
		return output;
	}

	// torus rotate along with y-axis counter-clockwise
	// [-r2*sin(delta)*sin(the) + r2*cos(delta)*cos(psi)*cos(the) + r1*cos(delta)*cos(psi), -r2*sin(psi)*cos(the) - r1*sin(psi), r2*sin(delta)*cos(psi)*cos(the) + r1*sin(delta)*cos(psi) + r2*sin(the)*cos(delta)]
//#[allow(dead_code)]
	vector<vector<char>> next_frame() {
		vector<vector<i32>>  zbuf(this->scr_width, vector<i32>(this->scr_height, -123));
		vector<vector<char>>  output(this->scr_width, vector<char>(this->scr_height, '\0'));
		f32  psi = 0.0;
		f32  theta = 0.0;

		f32 wid_offset = (this->scr_width / 2);
		f32 hei_offset = (this->scr_height / 2);

		this->delta += RESO;
		f32 sin_d = sin(this->delta);
		f32 cos_d = cos(this->delta);

		while (1) {
			psi += RESO;
			while (1) {
				theta += RESO;
				f32 sin_t = sin(theta);
				f32 cos_t = cos(theta);

				f32 sin_p = sin(psi);
				f32 cos_p = cos(psi);
				i32 z = (this->r2 * sin_d * cos_p * cos_t + this->r1 * sin_d * cos_p + this->r2 * sin_t * cos_d);
				auto z_apo = this->viewer_distance / (this->object_distance - z);

				auto x = -1.0 * this->r2 * sin_d * sin_t + this->r2 * cos_t * cos_p * cos_d + this->r1 * cos_d * cos_p;
				auto y = -1.0 * this->r2 * sin_p * cos_t - this->r1 * sin_p;
				auto xp = (x * z_apo + wid_offset);
				auto yp = (y * z_apo + hei_offset);

				if (z > zbuf[xp][yp]) {
					zbuf[xp][yp] = z;
					output[xp][yp] = '*';
				}

				if (theta >= TAU) {
					break;
				}
			}
			theta = 0.0;
			if (psi >= TAU) {
				break;
			}
		}
		return output;
	}

	// x = (4*cos(the) + 10)*cos(delta)*cos(psi) - 4*sin(delta)*sin(the)
	// y = ((4*cos(the) + 10)*sin(delta)*cos(psi) + 4*sin(the)*cos(delta))*sin(a) - (4*cos(the) + 10)*sin(psi)*cos(a)
	// z = ((4*cos(the) + 10)*sin(delta)*cos(psi) + 4*sin(the)*cos(delta))*cos(a) + (4*cos(the) + 10)*sin(a)*sin(psi)
	//

	// torus normal is
	// -sin(delta)*sin(the) + cos(delta)*cos(psi)*cos(the),
	// (sin(delta)*cos(psi)*cos(the) + sin(the)*cos(delta))*sin(a) - sin(psi)*cos(a)*cos(the)
	// (sin(delta)*cos(psi)*cos(the) + sin(the)*cos(delta))*cos(a) + sin(a)*sin(psi)*cos(the)
	vector<vector<char>> next_frame_with_xy_rotate(bool light) {
		vector<vector<i32>>  zbuf(this->scr_width, vector<i32>(this->scr_height, -123));
		vector<vector<char>>  output(this->scr_width, vector<char>(this->scr_height, '\0'));
		f32  psi = 0.0;
		f32  theta = 0.0;

		auto wid_offset = (this->scr_width / 2);
		auto hei_offset = (this->scr_height / 2);

		this->delta += RESO;
		this->a_radian += RESO;
		f32 sin_d = sin(this->delta);
		f32 cos_d = cos(this->delta);

		f32 sin_a = sin(this->a_radian);
		f32 cos_a = cos(this->a_radian);

		while (1) {
			psi += RESO;
			while (1) {
				theta += RESO;
				f32 sin_t = sin(theta);
				f32 cos_t = cos(theta);

				f32 sin_p = sin(psi);
				f32 cos_p = cos(psi);
				auto z = ((this->r2 * cos_t + this->r1) * sin_d * cos_p + this->r2 * sin_t * cos_d) * cos_a +
					(this->r2 * cos_t + this->r1) * sin_a * sin_p;
				auto z_apo = this->viewer_distance / (this->object_distance - z);

				auto x = (this->r2 * cos_t + this->r1) * cos_d * cos_p - this->r2 * sin_d * sin_t;
				auto y = ((this->r2 * cos_t + this->r1) * sin_d * cos_p + this->r2 * sin_t * cos_d) * sin_a -
					(this->r2 * cos_t + this->r1) * sin_p * cos_a;

				auto xp = (x * z_apo + wid_offset);
				auto yp = (y * z_apo + hei_offset);

				if ((i32)z > zbuf[xp][yp]) {
					zbuf[xp][yp] = (i32)z;
					if (!light) {
						output[xp][yp] = '*';
					}
					else {
						f32 normal[] = { -1.0 * sin_d * sin_t + cos_d * cos_p * cos_t,
							(sin_d * cos_p * cos_t + sin_t * cos_d) * sin_a - sin_p * cos_a * cos_t,
							(sin_d * cos_p * cos_t + sin_t * cos_d) * cos_a + sin_a * sin_p * cos_t };

						f32 lumi = Donut::dot_product_3d(normal, this->light_source);

						if (lumi < 0.0) {
							output[xp][yp] = LUMINANCE_CHARS[0];
						}
						else
						{
							usize lumi_index = (usize)(lumi * 6.5);
							output[xp][yp] = LUMINANCE_CHARS[lumi_index];
						}
					}
				}

				if (theta >= TAU) {
					break;
				}
			}
			theta = 0.0;
			if (psi >= TAU) {
				break;
			}
		}
		return output;
	}

	f32 static dot_product_3d(f32 a[3], f32 b[3]) {
		return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
	}
};