

using namespace std;
#include "Spline.h"


Spline::Spline(void)
{
	//do nothing
}
double Spline::getDifferenceInAngleRadians(double from, double to)
{
	return boundAngleNegPiToPiRadians(to - from);
}
double Spline::boundAngleNegPiToPiRadians(double angle)
{
	cout << "Given Angle " << angle << endl;
	if(angle >= PI) {
		angle -= 2.0 * PI;
	}
	else if(angle < -PI){
		angle += 2.0 * PI;
	}
	else
		
	if(_debugPrint == true) {
	cout << "returning angle " << angle << endl;
	}
	return angle;
}
bool Spline::almostEqual(double val1, double val2)
{
	if(abs((val1-val2)) < 1e-6){
		cout << "abs val " << abs(val1-val2) << endl;
		return true;
	}
	cout << "returning false!" << endl;
	return false;
}
bool Spline::reticulateSplines(double *P0, double *P1, int type = 1)
{
	/*
	P0 = [x0,y0,theta0]
	P1 = [x1,y1,theta1]
	type - 1=cubic, 2= quartic, currently only cubic is implemented.
	*/
	if(_debugPrint == true) {
		cout << "data" << endl;
	}
	double x0 = *P0++;
	double y0 = *P0++;
	double theta0 = *P0++;
	double x1 = *P1++;
	double y1 = *P1++;
	double theta1 = *P1++;
	
	if(_debugPrint == true) {
		cout << "x0 " << x0 << " y0 " << y0 << " theta0 " << theta0 << endl;
		cout << "x1 " << x1 << " y1 " << y1 << " theta1 " << theta1 << endl;
	}
	//transform x & y to orgin
	x_offset_ = x0;
	y_offset_ = y0;
	if(_debugPrint == true) {
		cout << "calculating x1_hat" << endl;
	}
	//create minimum distance vector from x0,y0 to x1,y1.
	double x1_hat = sqrt((x1-x0) * (x1-x0) + (y1-y0)*(y1-y0));
	if(x1_hat == 0) {
		return false; //ensure that the same two points weren't fed in.
	}
	if(_debugPrint == true) {
		cout << "x1_hat success " << x1_hat << endl;
	}
	knot_distance_ = x1_hat;
	theta_offset_ = atan2((y1-y0),(x1-x0));
	if(_debugPrint == true) {
		cout << "theta_offset_ " << theta_offset_ << endl;
	}
	double theta0_hat = getDifferenceInAngleRadians(theta_offset_, theta0);
	double theta1_hat = getDifferenceInAngleRadians(theta_offset_, theta1);
	if(_debugPrint == true) {
		cout << "theta0_hat: " << theta0_hat << " theta1_hat " << theta1_hat << endl;
	}
	 //This static solution for the cubic cannot handle vertical slopes in the rotated, translated basis. 
	 //prevent user from requesting a 90 deg or greater rotation between P0 and P1.
	 
	if(almostEqual(abs(theta0_hat),PI/2) || almostEqual(abs(theta1_hat),PI/2)) {
		if(_debugPrint == true) {
			cout << "this was true" << endl;
		}
		return false;
	}
	if(abs(getDifferenceInAngleRadians(theta0_hat,theta1_hat)) >= (PI/2)){
		if(_debugPrint == true) {
			cout << "this was true1" << endl;
		}
		return false;
	}
	//turn angles into derivatives(slopes)
	double yp0_hat = tan(theta0_hat);
	double yp1_hat = tan(theta1_hat);
	
	if(type = 1) {
		a_ = 0.0;
		b_ = 0.0;
		c_ = (yp1_hat + yp0_hat) / (x1_hat * x1_hat);
		d_ = -(2.0 * yp0_hat + yp1_hat) / x1_hat;
		e_ = yp0_hat;
	}
	else if(type != 1){
		return false; //quartic not implemented, so return false.
	}
	return true;
}