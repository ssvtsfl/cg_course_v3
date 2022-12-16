#pragma once
#include "stdio.h"
#include "math.h"

#define X 0
#define Y 1
#define Z 2
#define W 3

#define MIN 0
#define MAXX 1000
#define MAXY 600


class point
{
	double* multiply(double _m[4][4])
	{
		double x_ = x;
		double y_ = y;
		double z_ = z;
		double w_ = w;
		double cpy[4] = { x_, y_, z_, w_ };
		double res[4] = { 0,0,0,0 };

		res[X] = cpy[0] * _m[0][0] + cpy[1] * _m[1][0] + cpy[2] * _m[2][0] + cpy[3] * _m[3][0];
		res[Y] = cpy[0] * _m[0][1] + cpy[1] * _m[1][1] + cpy[2] * _m[2][1] + cpy[3] * _m[3][1];
		res[Z] = cpy[0] * _m[0][2] + cpy[1] * _m[1][2] + cpy[2] * _m[2][2] + cpy[3] * _m[3][2];
		res[W] = cpy[0] * _m[0][3] + cpy[1] * _m[1][3] + cpy[2] * _m[2][3] + cpy[3] * _m[3][3];

		x = res[X];
		y = res[Y];
		z = res[Z];
		w = res[W];
		return res;
	}

	void rotateX(double _phi) {
		_phi = _phi * 3.1415 / 180;

		double matrix[4][4] = {
			1, 0, 0, 0,
			0, cos(_phi), -sin(_phi), 0,
			0, sin(_phi), cos(_phi),
			0, 0, 0, 0, 1 };
		multiply(matrix);
	}

	void rotateY(double _phi) {
		_phi = _phi * 3.1415 / 180;

		double matrix[4][4] = {
			cos(_phi), 0, -sin(_phi), 0,
			0, 1, 0, 0,
			sin(_phi), 0, cos(_phi), 0,
			0, 0, 0, 1 };
		multiply(matrix);
	}

	void rotateZ(double _phi) {
		_phi = _phi * 3.1415 / 180;

		double matrix[4][4] = {
			cos(_phi), -sin(_phi), 0, 0,
			sin(_phi), cos(_phi), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 };
		multiply(matrix);
	}

public:

	double x;
	double y;
	double z;
	double w;



	point()
	{

	}
	point(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
	{
		w = 1;
	}

	void print()
	{
		printf("%f %f %f %f\n", x, y, z, w);
	}

	void move(double _x, double _y, double _z)
	{
		double matrix[4][4] = {
			1,  0,  0,  0,
			0,  1,  0,  0,
			0,  0,  1,  0,
			_x, _y, _z, 1 };

		multiply(matrix);
	}

	void scale(double _x, double _y, double _z) {
		double matrix[4][4] = {
			_x, 0, 0, 0,
			0, _y, 0, 0,
			0, 0, _z, 0,
			0, 0, 0, 1 };

		multiply(matrix);
	}

	void rotate(double _phi, int _axis) {
		if (_axis == X)
			rotateX(_phi);
		if (_axis == Y)
			rotateY(_phi);
		if (_axis == Z)
			rotateZ(_phi);
	}


};