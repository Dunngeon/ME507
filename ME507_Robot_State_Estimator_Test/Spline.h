/*

This is a library that will take two points, with angular orientations,
and fit a cubic spline between the two points.

It also includes other useful functions to compute first and second order
derivatives of the cubic spline at various percentages of path completion.

Created with inspiration from FRC Team 254's 2017 robot code on github.

Creation - Ryan G. Dunn - 12/3/2018

TODO:
-Everything
*/
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cmath>

#define PI 3.14159265 //for use in math.

class Spline
{
protected:
	//variables and function calls to be protected
	
//private:
public:
	//variables and funcion calls to be private
	bool _debugPrint = true;
	double a_;
	double b_;
	double c_;
	double d_;
	double e_;
	// f is always zero for the spline formulation supported here.
	double y_offset_;
	double x_offset_;
	double knot_distance_;
	double theta_offset_;
	double arc_length_;
	double getDifferenceInAngleRadians(double from, double to);
	double boundAngleNegPiToPiRadians(double angle);
	bool almostEqual(double val1, double val2);
//public:
	Spline(void); //Default constructor
	
	bool reticulateSplines(double *P0, double *P1, int type);
	
};
		