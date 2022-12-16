#pragma once
#include "stdio.h"
#include "side4.h"
#include "shadow_side4.h"

#define FLAG 0
#define BR 1
#define DR 2
#define VS 3

#define SIDE_NUM 6

class parallelepiped
{
	int n;

	side4* T[6];
	shadow_side4* S[6];
	point* v[8];
	point* mid;
	point* cam;
	point* light;

	int clr[4][SIDE_NUM];

	void rotate_each(double _phi, int axis)
	{
		for (int i = 0; i < 8; i++)
			v[i]->rotate(_phi, axis);
	}

	void scale_each(double _x, double _y, double _z)
	{
		for (int i = 0; i < 8; i++)
			v[i]->scale(_x, _y, _z);
	}

	void upd_shadow()
	{
		point* ref = light;
		double y = 600;

		double t = (y - v[0]->y) / (ref->y - v[0]->y);
		double x = (ref->x - v[0]->x) * t + v[0]->x;
		double z = (ref->z - v[0]->z) * t + v[0]->z;

		point* A1 = new point(x, y, z);

		t = (y - v[1]->y) / (ref->y - v[1]->y);
		x = (ref->x - v[1]->x) * t + v[1]->x;
		z = (ref->z - v[1]->z) * t + v[1]->z;
		point* B1 = new point(x, y, z);

		t = (y - v[2]->y) / (ref->y - v[2]->y);
		x = (ref->x - v[2]->x) * t + v[2]->x;
		z = (ref->z - v[2]->z) * t + v[2]->z;
		point* C1 = new point(x, y, z);

		t = (y - v[3]->y) / (ref->y - v[3]->y);
		x = (ref->x - v[3]->x) * t + v[3]->x;
		z = (ref->z - v[3]->z) * t + v[3]->z;
		point* D1 = new point(x, y, z);

		t = (y - v[4]->y) / (ref->y - v[4]->y);
		x = (ref->x - v[4]->x) * t + v[4]->x;
		z = (ref->z - v[4]->z) * t + v[4]->z;
		point* A2 = new point(x, y, z);

		t = (y - v[5]->y) / (ref->y - v[5]->y);
		x = (ref->x - v[5]->x) * t + v[5]->x;
		z = (ref->z - v[5]->z) * t + v[5]->z;
		point* B2 = new point(x, y, z);

		t = (y - v[6]->y) / (ref->y - v[6]->y);
		x = (ref->x - v[6]->x) * t + v[6]->x;
		z = (ref->z - v[6]->z) * t + v[6]->z;
		point* C2 = new point(x, y, z);

		t = (y - v[7]->y) / (ref->y - v[7]->y);
		x = (ref->x - v[7]->x) * t + v[7]->x;
		z = (ref->z - v[7]->z) * t + v[7]->z;
		point* D2 = new point(x, y, z);


		A1->rotate(30, X);
		B1->rotate(30, X);
		C1->rotate(30, X);
		D1->rotate(30, X);
		A2->rotate(30, X);
		B2->rotate(30, X);
		C2->rotate(30, X);
		D2->rotate(30, X);

		S[0]->reset(A1, B1, C1, D1);
		S[1]->reset(A1, B1, B2, A2);
		S[2]->reset(B1, C1, C2, B2);
		S[3]->reset(C1, D1, D2, C2);
		S[4]->reset(D1, A1, A2, D2);
		S[5]->reset(A2, B2, C2, D2);


	}

	void project()
	{
		rotate_each(30, X);

	}

	void unproject()
	{

		rotate_each(-30, X);
	}

	void upd_mid()
	{
		mid->x = 0;
		for (int i = 0; i < 8; i++)
			mid->x += v[i]->x;

		mid->x /= (float)8;

		mid->y = 0;
		for (int i = 0; i < 8; i++)
			mid->y += v[i]->y;

		mid->y /= (float)8;

		mid->z = 0;
		for (int i = 0; i < 8; i++)
			mid->z += v[i]->z;

		mid->z /= (float)8;
		mid->w = 1;
	}



public:

	parallelepiped(side4* s1, side4* s2, side4* s3, side4* s4, side4* s5, side4* s6)
	{
		n = 6;
		T[0] = s1;
		T[1] = s2;
		T[2] = s3;
		T[3] = s4;
		T[4] = s5;
		T[5] = s6;

		for (int i = 0; i < n; i++)
			S[i] = new shadow_side4;

		mid = new point;
		cam = new point(0, -500, 1000);
		light = new point(500, -500, 0);

		for (int i = 0; i < n; i++)
			clr[FLAG][i] = 0;


		clr[BR][0] = 13; // желтый
		clr[BR][1] = 11; // голубой
		clr[BR][2] = 10; // зеленый
		clr[BR][3] = 12; // красный
		clr[BR][4] = 9; //  синий
		clr[BR][5] = 15; // белый

		clr[DR][0] = 6;
		clr[DR][1] = 3;
		clr[DR][2] = 2;
		clr[DR][3] = 4;
		clr[DR][4] = 1;
		clr[DR][5] = 8;

		for (int i = 0; i < n; i++)
			clr[VS][i] = 1;
	}


	void set_v(point* p1, point* p2, point* p3, point* p4, point* p5, point* p6, point* p7, point* p8)
	{
		v[0] = p1;
		v[1] = p2;
		v[2] = p3;
		v[3] = p4;
		v[4] = p5;
		v[5] = p6;
		v[6] = p7;
		v[7] = p8;

	}
	void print_mid()
	{
		printf("parallelepiped: %f %f %f\n", mid->x, mid->y, mid->z);
	}

	void upd_sides()
	{
		for (int i = 0; i < n; i++)
		{
			T[i]->calc_coefs(0);
		}
	}

	void check_signs()
	{
		for (int i = 0; i < n; i++)
		{
			if (T[i]->sign(mid) == 1)
				T[i]->swap_sign();
		}
	}

	void check_colors()
	{
		point* ref = new point(light->x - mid->x, light->y - mid->y, light->z - mid->z);
		for (int i = 0; i < n; i++)
		{
			if (T[i]->isSeen(ref) == 1)
				clr[FLAG][i] = BR;
			else
				clr[FLAG][i] = DR;
		}
	}

	void check_visibility()
	{
		point* ref = cam;
		for (int i = 0; i < n; i++)
		{
			if (T[i]->isSeen(ref) == 1)
				clr[VS][i] = 1;
			else
				clr[VS][i] = 0;
		}
	}

	void draw_fig()
	{
		for (int i = 0; i < n; i++)
		{
			if (clr[VS][i] == 1)
			{
				int l = clr[FLAG][i];
				T[i]->color(clr[l][i]);
			}
		}
	}

	void draw_shadow()
	{
		for (int i = 0; i < n; i++)
		{
			S[i]->color();
		}
	}

	void move(double _x, double _y, double _z)
	{
		for (int i = 0; i < 8; i++)
			v[i]->move(_x, _y, _z);
	}

	void scale(double _x, double _y, double _z)
	{
		upd_mid();
		move(-mid->x, -mid->y, -mid->z);
		scale_each(_x, _y, _z);
		move(mid->x, mid->y, mid->z);
	}

	void rotate(double _phi, int axis)
	{
		upd_mid();
		move(-mid->x, -mid->y, -mid->z);
		rotate_each(_phi, axis);
		move(mid->x, mid->y, mid->z);
	}

	void move_light(double _x, double _y, double _z)
	{
		light->move(_x, _y, _z);
	}

	void paint()
	{
		upd_mid();
		upd_sides();

		upd_shadow();
		draw_shadow();

		check_signs();
		check_colors();
		check_visibility();

		project();
		draw_fig();
		unproject();
	}

};