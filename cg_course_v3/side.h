#pragma once
#include "../libwinbgi/src/graphics.h"
#include <stdio.h>
#include "point.h"

#define X 0
#define Y 1
#define Z 2


class side
{
	float A, B, C, D;
	point* v[3];
	point* mid;


	void colour_dot(int x_isx, int y_isx, int ref_color, int fill_color)
	{
		if (x_isx <= MIN || y_isx <= MIN || x_isx >= MAXX || y_isx >= MAXY)
			return;

		if (getpixel(x_isx, y_isx) != ref_color && getpixel(x_isx, y_isx) != fill_color)
		{
			putpixel(x_isx, y_isx, fill_color);
			colour_dot(x_isx + 1, y_isx, ref_color, fill_color);
			colour_dot(x_isx, y_isx + 1, ref_color, fill_color);
			colour_dot(x_isx - 1, y_isx, ref_color, fill_color);
			colour_dot(x_isx, y_isx - 1, ref_color, fill_color);
		}
		return;
	}

public:
	side()
	{
		for (int i = 0; i < 3; i++)
			v[i] = new point;
		mid = new point;
	}

	side(point* a, point* b, point* c)
	{
		v[0] = a;
		v[1] = b;
		v[2] = c;
		mid = new point;
	}
	
	void upd_mid()
	{
		mid->x = 0;
		for (int i = 0; i < 3; i++)
			mid->x += v[i]->x;

		mid->x /= 3.0;

		mid->y = 0;
		for (int i = 0; i < 3; i++)
			mid->y += v[i]->y;

		mid->y /= 3.0;

		mid->z = 0;
		for (int i = 0; i < 3; i++)
			mid->z += v[i]->z;

		mid->z /= 3.0;
		mid->w = 1;
	}

	void reset(point* a, point* b, point* c)
	{
		v[0] = a;
		v[1] = b;
		v[2] = c;
	}
	void reset(point a, point b, point c)
	{
		v[0] = &a;
		v[1] = &b;
		v[2] = &c;
	}

	void rotate()
	{
		upd_mid();
		for (int i = 0; i < 3; i++)
			v[i]->move(mid->x, mid->y, mid->z);
		for (int i = 0; i < 3; i++)
			v[i]->rotate(30, X);
		for (int i = 0; i < 3; i++)
			v[i]->move(-mid->x, -mid->y, -mid->z);
	}

	void color(int c)
	{
		upd_mid();
		int b_c = 7;
		setcolor(b_c);
		setlinestyle(0, 1, 3);
		line(v[0]->x, v[0]->y, v[1]->x, v[1]->y);
		line(v[0]->x, v[0]->y, v[2]->x, v[2]->y);
		line(v[2]->x, v[2]->y, v[1]->x, v[1]->y);

		colour_dot(mid->x, mid->y, b_c, c);
		
	}

	void calc_coefs(int i)
	{
		float M[3] = { v[i]->x, v[i]->y, v[i]->z };
		int ai = i - 1;
		if (ai < 0)
			ai = 2;
		int bi = i + 1;
		if (bi > 2)
			bi = 0;
		float a[3] = { v[ai]->x - v[i]->x, v[ai]->y - v[i]->y, v[ai]->z - v[i]->z };
		float b[3] = { v[bi]->x - v[i]->x, v[bi]->y - v[i]->y, v[bi]->z - v[i]->z };

		A = a[Y] * b[Z] - a[Z] * b[Y];
		B = a[X] * b[Z] - a[Z] * b[X];
		B = -B;
		C = a[X] * b[Y] - a[Y] * b[X];

		D = M[X] * A + M[Y] * B + M[Z] * C;
		D = -D;
		
	}

	void print()
	{
		printf("%f*x + %f*y + %f*z + %f = 0\n", A, B, C, D);
	}

	int sign(point* p)
	{
		float val = A * p->x + B * p->y + C * p->z + D;
		return (val <= 0);
	}

	void swap_sign()
	{
		A = -A;
		B = -B;
		C = -C;
		D = -D;
	}

	int isSeen(point* p)
	{
		float val = A * p->x + B * p->y + C * p->z;
		return (val <= 0);
	}
};