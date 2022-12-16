#pragma once
#include "stdio.h"
#include "side.h"
#include "shadow_side.h"

#define FLAG 0
#define BR 1
#define DR 2
#define VS 3

#define SIDE_NUM 4

class piramid
{
	int n;
	
	side* T[4];
	shadow_side* S[4];
	point* v[4];
	point* mid;
	point* cam;
	point* light;

	int clr[4][SIDE_NUM];

	void rotate_each(double _phi, int axis)
	{
		for (int i = 0; i < n; i++)
			v[i]->rotate(_phi, axis);
	}

	void scale_each(double _x, double _y, double _z)
	{
		for (int i = 0; i < n; i++)
			v[i]->scale(_x, _y, _z);
	}

	void upd_shadow()
	{
		point* ref = light;
		double y = 600;

		double t = (y - v[0]->y) / (ref->y - v[0]->y);
		double x = (ref->x - v[0]->x) * t + v[0]->x;
		double z = (ref->z - v[0]->z) * t + v[0]->z;

		point* A = new point(x, y, z);

		t = (y - v[1]->y) / (ref->y - v[1]->y);
		x = (ref->x - v[1]->x) * t + v[1]->x;
		z = (ref->z - v[1]->z) * t + v[1]->z;
		point* B = new point(x, y, z);

		t = (y - v[2]->y) / (ref->y - v[2]->y);
		x = (ref->x - v[2]->x) * t + v[2]->x;
		z = (ref->z - v[2]->z) * t + v[2]->z;
		point* C = new point(x, y, z);

		t = (y - v[3]->y) / (ref->y - v[3]->y);
		x = (ref->x - v[3]->x) * t + v[3]->x;
		z = (ref->z - v[3]->z) * t + v[3]->z;
		point* D = new point(x, y, z);

		A->rotate(30, X);
		B->rotate(30, X);
		C->rotate(30, X);
		D->rotate(30, X);

		S[0]->reset(A, B, C);
		S[1]->reset(A, D, C);
		S[2]->reset(D, B, C);
		S[3]->reset(A, D, B);

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
		for (int i = 0; i < 4; i++)
			mid->x += v[i]->x;

		mid->x /= 4.0;

		mid->y = 0;
		for (int i = 0; i < 4; i++)
			mid->y += v[i]->y;

		mid->y /= 4.0;

		mid->z = 0;
		for (int i = 0; i < 4; i++)
			mid->z += v[i]->z;

		mid->z /= 4.0;
		mid->w = 1;
	}



public:

	piramid(side* s1, side* s2, side* s3, side* s4)
	{
		n = 4;
		T[0] = s1;
		T[1] = s2;
		T[2] = s3;
		T[3] = s4;
		for (int i = 0; i < 4; i++)
			S[i] = new shadow_side;

		mid = new point;
		cam = new point(0, -500, 1000);
		light = new point(500, -500, 0);

		for (int i = 0; i < 4; i++)
			clr[FLAG][i] = 0;
		

		clr[BR][0] = 13; // желтый
		clr[BR][1] = 11; // голубой
		clr[BR][2] = 10; // зеленый
		clr[BR][3] = 12; // красный
			
		clr[DR][0] = 6;
		clr[DR][1] = 3;
		clr[DR][2] = 2;
		clr[DR][3] = 4;

		for (int i = 0; i < 4; i++)
			clr[VS][i] = 1;
	}

	
	void set_v(point* p1, point* p2, point* p3, point* p4)
	{
		v[0] = p1;
		v[1] = p2;
		v[2] = p3;
		v[3] = p4;
	}

	void upd_sides()
	{
		for (int i = 0; i < 4; i++)
		{
			T[i]->calc_coefs(0);
		}
	}

	void check_signs()
	{
		for (int i = 0; i < 4; i++)
		{
			if (T[i]->sign(mid) == 1)
				T[i]->swap_sign();		
		}
	}

	void print_mid()
	{
		printf("piramida: %f %f %f\n", mid->x, mid->y, mid->z);
	}
	void check_colors()
	{
		point* ref = new point(light->x - mid->x, light->y - mid->y, light->z - mid->z);
		for (int i = 0; i < 4; i++)
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
		for (int i = 0; i < 4; i++)
		{
			if (T[i]->isSeen(ref) == 1)
				clr[VS][i] = 1;
			else
				clr[VS][i] = 0;
		}
	}

	void draw_fig()
	{
		for (int i = 0; i < 4; i++)
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
		for (int i = 0; i < 4; i++)
			S[i]->color();
	}

	void move(double _x, double _y, double _z)
	{
		for (int i = 0; i < n; i++)
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