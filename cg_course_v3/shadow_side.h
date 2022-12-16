#pragma once
#include "../libwinbgi/src/graphics.h"
#include <stdio.h>
#include "point.h"

#define X 0
#define Y 1
#define Z 2


class shadow_side
{
	point* v[3];
	point* mid;
	int bc;
	int fc;

	void fill_bkg(int x_isx, int y_isx)
	{
		if (x_isx <= MIN || y_isx <= MIN || x_isx >= MAXX || y_isx >= MAXY)
			return;
		if (x_isx == 0 || y_isx == 0)
			return;

		if (getpixel(x_isx, y_isx) != bc)
		{
			putpixel(x_isx, y_isx, bc);
			fill_bkg(x_isx + 1, y_isx);
			fill_bkg(x_isx, y_isx + 1);
			fill_bkg(x_isx - 1, y_isx);
			fill_bkg(x_isx, y_isx - 1);
		}
	}

	void fill_clr(int x_isx, int y_isx)
	{
		if (x_isx <= MIN || y_isx <= MIN || x_isx >= MAXX || y_isx >= MAXY)
			return;
		if (x_isx == 0 || y_isx == 0)
			return;
		if (getpixel(x_isx, y_isx) != 0 && getpixel(x_isx, y_isx) == bc)
		{
			putpixel(x_isx, y_isx, fc);
			fill_clr(x_isx + 1, y_isx);
			fill_clr(x_isx, y_isx + 1);
			fill_clr(x_isx - 1, y_isx);
			fill_clr(x_isx, y_isx - 1);
		}
	}

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
	
	shadow_side()
	{
		for (int i = 0; i < 3; i++)
			v[i] = new point;
		mid = new point;
		bc = 9;
		fc = 1;
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

	void color()
	{
		upd_mid();
		setcolor(bc);
		setlinestyle(0, 1, 3);
		line(v[0]->x, v[0]->y, v[1]->x, v[1]->y);
		line(v[0]->x, v[0]->y, v[2]->x, v[2]->y);
		line(v[2]->x, v[2]->y, v[1]->x, v[1]->y);

		fill_bkg(mid->x, mid->y);
		fill_clr(mid->x, mid->y);
	}



};