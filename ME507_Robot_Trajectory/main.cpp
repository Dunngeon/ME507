//main file for testing


#include <stdlib.h>                         // These are standard C/C++ libraries
#include <string.h>
#include <stdint.h>
#include <iostream>

// This namespace is needed to use I/O streams on a PC but not on a microcontroller
using namespace std;

#include "Spline.h"                          // Include header file for this project



int main (void)
{
	Spline Spl;

	double P0[3]; //[x,y,theta]
	double P1[3];
	P0[0] = 0.0;
	P0[1] = 0.0;
	P0[2] = 0.0;
	P1[0] = 25.0;
	P1[1] = 5.0;
	P1[2] = (15.0 / 180.0 * 3.14159265);
	cout << P1[2] << endl;
	int type = 1;
	bool success = false;
	success = Spl.reticulateSplines(P0,P1,type);
	
	cout << "Success? " << success << endl;
	cout << Spl.y_offset_ << endl << Spl.x_offset_ << endl << Spl.knot_distance_ << endl;
	cout << 'A' << Spl.a_ << endl << "b" << Spl.b_ << endl << "c " << Spl.c_ << endl << "d " << Spl.d_ << endl << "e " << Spl.e_ << endl;
	
}