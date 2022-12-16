#include "../libwinbgi/src/graphics.h"
#include <stdio.h>

#include "side.h"
#include "point.h"
#include "piramid.h"
#include "parallelepiped.h"
#include "point.h"


int main()
{
	initwindow(MAXX, MAXY);

	point* A = new point(0, 150, 0);
	point* B = new point(150, 0, 200);
	point* C = new point(250, 150, 200);
	point* D = new point(150, 50, 0);

	side* ABC = new side(A, B, C);
	side* ADC = new side(A, D, C);
	side* DBC = new side(D, B, C);
	side* ADB = new side(A, D, B);

	point* A1 = new point(100, 300, 300);
	point* B1 = new point(300, 300, 300);
	point* C1 = new point(300, 300, 100);
	point* D1 = new point(100, 300, 100);

	point* A2 = new point(200, 100, 300);
	point* B2 = new point(400, 100, 300);
	point* C2 = new point(400, 100, 100);
	point* D2 = new point(200, 100, 100);

	side4* A1B1C1D1 = new side4(A1, B1, C1, D1);
	side4* A1B1B2A2 = new side4(A1, B1, B2, A2);
	side4* B1C1C2B2 = new side4(B1, C1, C2, B2);
	side4* C1D1D2C2 = new side4(C1, D1, D2, C2);
	side4* D1A1A2D2 = new side4(D1, A1, A2, D2);
	side4* A2B2C2D2 = new side4(A2, B2, C2, D2);


	piramid* p = new piramid(ABC, ADC, DBC, ADB);
	parallelepiped* p2 = new parallelepiped(A1B1C1D1, A1B1B2A2, B1C1C2B2, C1D1D2C2, D1A1A2D2, A2B2C2D2);

	p->set_v(A, B, C, D);
	p->move(100, 200, -400);
	p->scale(0.5, 0.5, 0.5);

	p2->set_v(A1, B1, C1, D1, A2, B2, C2, D2);
	p2->move(250, 200, -400);
	p2->scale(0.5, 0.5, 0.5);

	p2->paint();
	p->paint();


	char c;
	char fig = 0;
	bool exit_flag = false;
	while (true)
	{
		fig = getch();
		switch (fig)
		{
		case '1':
		{
			printf("piramida: ");
			c = getch();
			switch (c)
			{
			case 'z':
				printf("smaller\n");
				p->scale(0.5, 0.5, 0.5);
				break;
			case 'x':
				printf("bigger\n");
				p->scale(2, 2, 2);
				break;

			case 'w':
				printf("up\n");
				p->move(0, -50, 0);
				break;
			case 's':
				printf("down\n");
				p->move(0, 50, 0);
				break;
			case 'a':
				printf("left\n");
				p->move(-50, 0, 0);
				break;
			case 'd':
				printf("right\n");
				p->move(50, 0, 0);
				break;
			case 'q':
				printf("to back\n");
				p->move(0, 0, -50);
				break;
			case 'e':
				printf("to front\n");
				p->move(0, 0, 50);
				break;

			case 'r':
				printf("ratate x +30\n");
				p->rotate(30, X);
				break;
			case 'f':
				printf("ratate x -30\n");
				p->rotate(-30, X);
				break;
			case 't':
				printf("ratate y +30\n");
				p->rotate(30, Y);
				break;
			case 'g':
				printf("ratate y -30\n");
				p->rotate(-30, Y);
				break;
			case 'y':
				printf("ratate z +30\n");
				p->rotate(30, Z);
				break;
			case 'h':
				printf("ratate z -30\n");
				p->rotate(-30, Z);
				break;
			case '0':
				break;
			default:
				printf("unknown command\n");
			}
		}
		break;

		case '2':
		{
			printf("parallelepiped: ");
			c = getch();
			switch (c)
			{
			case 'z':
				printf("smaller\n");
				p2->scale(0.5, 0.5, 0.5);
				break;
			case 'x':
				printf("bigger\n");
				p2->scale(2, 2, 2);
				break;
			case 'w':
				printf("up\n");
				p2->move(0, -50, 0);
				break;
			case 's':
				printf("down\n");
				p2->move(0, 50, 0);
				break;
			case 'a':
				printf("left\n");
				p2->move(-50, 0, 0);
				break;
			case 'd':
				printf("right\n");
				p2->move(50, 0, 0);
				break;
			case 'q':
				printf("to back\n");
				p2->move(0, 0, -50);
				break;
			case 'e':
				printf("to front\n");
				p2->move(0, 0, 50);
				break;

			case 'r':
				printf("ratate x +30\n");
				p2->rotate(30, X);
				break;
			case 'f':
				printf("ratate x -30\n");
				p2->rotate(-30, X);
				break;
			case 't':
				printf("ratate y +30\n");
				p2->rotate(30, Y);
				break;
			case 'g':
				printf("ratate y -30\n");
				p2->rotate(-30, Y);
				break;
			case 'y':
				printf("ratate z +30\n");
				p2->rotate(30, Z);
				break;
			case 'h':
				printf("ratate z -30\n");
				p2->rotate(-30, Z);
				break;
			case '0':
				return 0;
			default:
				printf("unknown command\n");
			}
		}
		break;

		case '0':
			exit_flag = true;
			break;
		}

		if (!exit_flag)
		{
			clearviewport();
			p2->paint();
			p->paint();
			p2->print_mid();
			p->print_mid();
		}
		else
			break;
	}

	closegraph();
	return 0;
}