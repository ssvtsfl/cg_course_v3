#pragma once
#include "../libwinbgi/src/graphics.h"
#include <stdio.h>
#include "point.h"

#define X 0
#define Y 1
#define Z 2


class shadow_side4
{
	int v_num;
	point* v[4];
	point* mid;
	int bc;
	int fc;

	void fill_bkg(int x_isx, int y_isx)
	{
		if (x_isx <= MIN || y_isx <= MIN || x_isx >= MAXX || y_isx >= MAXY)
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

		if (getpixel(x_isx, y_isx) != 0 && getpixel(x_isx, y_isx) == bc)
		{
			putpixel(x_isx, y_isx, fc);
			fill_clr(x_isx + 1, y_isx);
			fill_clr(x_isx, y_isx + 1);
			fill_clr(x_isx - 1, y_isx);
			fill_clr(x_isx, y_isx - 1);
		}
	}

	void fill_bkg2(int x_isx, int y_isx)
	{
		if (x_isx <= MIN || y_isx <= MIN || x_isx >= MAXX || y_isx >= MAXY)
			return;
		if (x_isx == 0 || y_isx == 0)
			return;

		if (getpixel(x_isx, y_isx) != bc)
		{
			putpixel(x_isx, y_isx, bc);
			fill_bkg2(x_isx + 1, y_isx);
			fill_bkg2(x_isx, y_isx + 1);
			fill_bkg2(x_isx - 1, y_isx);
			fill_bkg2(x_isx, y_isx - 1);
		}
	}

	void fill_clr2(int x_isx, int y_isx)
	{
		if (x_isx <= MIN || y_isx <= MIN || x_isx >= MAXX || y_isx >= MAXY)
			return;
		if (x_isx == 0 || y_isx == 0)
			return;
		if (getpixel(x_isx, y_isx) != 0 && getpixel(x_isx, y_isx) == bc)
		{
			putpixel(x_isx, y_isx, fc);
			fill_clr2(x_isx + 1, y_isx);
			fill_clr2(x_isx, y_isx + 1);
			fill_clr2(x_isx - 1, y_isx);
			fill_clr2(x_isx, y_isx - 1);
		}
	}


public:

	shadow_side4()
	{
		v_num = 4;
		for (int i = 0; i < v_num; i++)
			v[i] = new point;
		mid = new point;
		bc = 9;
		fc = 1;
		
	}

	void upd_mid()
	{
		mid->x = 0;
		for (int i = 0; i < v_num; i++)
			mid->x += v[i]->x;

		mid->x /= (float)v_num;

		mid->y = 0;
		for (int i = 0; i < v_num; i++)
			mid->y += v[i]->y;

		mid->y /= (float)v_num;

		mid->z = 0;
		for (int i = 0; i < v_num; i++)
			mid->z += v[i]->z;

		mid->z /= (float)v_num;
		mid->w = 1;
	}

	void reset(point* a, point* b, point* c, point* d)
	{
		v[0] = a;
		v[1] = b;
		v[2] = c;
		v[3] = d;
	}

	void color()
	{
		setlinestyle(SOLID_LINE, 0, 3);
		setcolor(bc);
		
		line(v[0]->x, v[0]->y, v[1]->x, v[1]->y);
		line(v[1]->x, v[1]->y, v[2]->x, v[2]->y);
		line(v[2]->x, v[2]->y, v[3]->x, v[3]->y);
		line(v[3]->x, v[3]->y, v[0]->x, v[0]->y); 
		upd_mid();
		fill_bkg(mid->x, mid->y);
		fill_clr(mid->x, mid->y);
	}



};