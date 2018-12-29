//main file for testing


#include <stdlib.h>                         // These are standard C/C++ libraries
#include <string.h>
#include <stdint.h>
#include <iostream>

// This namespace is needed to use I/O streams on a PC but not on a microcontroller
using namespace std;

#include "Spline.h"                          // Include header file for this project
#define DELAYINTERVAL_MS 5    //This defines the interval that the task will run on.
#define WHEELBASE_TICKS	531		//This defines the wheelbase of the robot in ticks
#define LeftShiftAmount 0 		//This defines the amount of leftshifting to use
int main (void)
{
	//declare variables needed for the state space estimator
	
	//Encoder value storage variables -> Current and previous state
	int16_t M_Enc1_Val;
	int16_t M_Enc2_Val;
	int16_t M_Enc1_Val_Prev;
	int16_t M_Enc2_Val_Prev;
	
	int16_t M_1_DistTick;
	int16_t M_2_DistTick;
	int16_t M_DifferTick;
	
	int16_t M_1_v1; 
	int16_t M_2_v2; 
	int16_t R_V_Bar; 
	int16_t R_Omega;
	int16_t R_POS_Y_delta; //robot only moves in Y direction in the local coordinate system
	int16_t R_THETA_Delta;		
	int16_t R_THETA_PREV; //previous angular positon of the robot.
	
	int16_t R_INERT_Theta;	
	int16_t R_I_POS_X_delta; 
	int16_t R_I_POS_Y_delta;
	int16_t R_I_POS_X;
	int16_t R_I_POS_Y;
	int16_t Robot_Pos_X_INERT;			// Contains current position of robot in X_INERTIAL
	int16_t Robot_Pos_Y_INERT;			// Contains current position of robot in Y_INERTIAL
	int16_t Robot_Angle_Theta_INERT;	// Contains current angle of the robot in THETA_INERTIAL
	
	//float test variables
	float M_1_v1_F; 
	float M_2_v2_F; 
	float R_V_Bar_F; 
	float R_Omega_F;
	float R_POS_Y_delta_F; //robot only moves in Y direction in the local coordinate system
	float R_THETA_Delta_F;		
	
	//setup variables to required inital values
	
		M_Enc1_Val_Prev = 0; //read value of encoders for starting value
		M_Enc2_Val_Prev = 0;
		
		R_THETA_Delta = 0; //zero out the angular position of the robot upon startup.
		R_I_POS_X = 0;
		R_I_POS_Y = 0;
		Robot_Pos_X_INERT = 0;			
		Robot_Pos_Y_INERT = 0;			
		Robot_Angle_Theta_INERT = 0;	
	
	//run state estimator code!
	//get current encoder values
		M_Enc1_Val = -0; //multiply by -1 so that positive encoder count is forwards on both sides.
		M_Enc2_Val = 100;
				
		//calculate ticks elapsed since last iteration, we'll left shift by LeftShiftAmount bits to increase data resolution (at max speed, we run the risk of losing MSB data, should quantify this risk)
		M_1_DistTick = ((M_Enc1_Val-M_Enc1_Val_Prev) << LeftShiftAmount);
		M_2_DistTick = ((M_Enc2_Val-M_Enc2_Val_Prev) << LeftShiftAmount);
		//calculate differential ticks between the motors.
		//Positive M_DifferTick = CCW Rotation (right faster than left)
		//Negative M_DifferTick = CW Rotation (left side faster than right)
		M_DifferTick = (M_2_DistTick - M_1_DistTick); //left shifted by two from earlier
		cout << "Differential Encoder Values " << (M_1_DistTick>>LeftShiftAmount) << " " << (M_2_DistTick>>LeftShiftAmount) << " Differtick " << (M_DifferTick>>LeftShiftAmount) << endl;
		
		//remain in tick units (leftshifted two) to maintain maximal resolution
		//calculate v1 & v2 (ticks/timetasktakestorun)
		M_1_v1 = M_1_DistTick / (DELAYINTERVAL_MS << LeftShiftAmount);			//calculate linear velocity of left wheel (ticks/ms)
		M_2_v2 = M_2_DistTick / (DELAYINTERVAL_MS << LeftShiftAmount);			//calculate linear velocity of right wheel (ticks/ms)
			//compute numbers with floats to determine error percentage
			M_1_v1_F = float(M_1_DistTick) / (float(DELAYINTERVAL_MS));			//calculate linear velocity of left wheel (ticks/ms)
			M_2_v2_F = float(M_2_DistTick) / (float(DELAYINTERVAL_MS));
		
		cout << "M_vel_1 " << (M_1_v1>>LeftShiftAmount) << " M_vel_2 " << (M_2_v2>>LeftShiftAmount) << endl;
		cout << "M_vel_1_F " << (M_1_v1_F) << " M_vel_2_F " << (M_2_v2_F) << endl;
		
		//calculate vbar and angular position of the drivebase in robot coordinates.
		R_V_Bar = (M_2_v2 + M_1_v1) / (2<<LeftShiftAmount);					//calculate Vbar for the robot (ticks/ms)
		R_POS_Y_delta = ((M_2_v2 + M_1_v1) / (2<<LeftShiftAmount)) * (DELAYINTERVAL_MS << LeftShiftAmount); //delta y position in local frame
		R_Omega = (M_2_v2 - M_1_v1) / (WHEELBASE_TICKS << LeftShiftAmount);	//angular velocity (rad/ms) -> only calculated for debugging. Angular position is calculated directly.
		R_THETA_Delta = ((M_2_v2 - M_1_v1) * (DELAYINTERVAL_MS << LeftShiftAmount)) / (WHEELBASE_TICKS<<LeftShiftAmount);		//calculate angular position change for the robot (we calculate directly to avoid losing resolution (rad))
		
		//compute numbers with floats for error approximation
		R_V_Bar_F = (M_2_v2_F + M_1_v1_F) / (2.0);					//calculate Vbar for the robot (ticks/ms)
		R_POS_Y_delta_F = ((M_2_v2_F + M_1_v1_F) / (2.0)) * (DELAYINTERVAL_MS << LeftShiftAmount); //delta y position in local frame
		R_Omega_F = (M_2_v2_F - M_1_v1_F) / (float(WHEELBASE_TICKS));	//angular velocity (rad/ms) -> only calculated for debugging. Angular position is calculated directly.
		R_THETA_Delta_F = ((M_2_v2_F - M_1_v1_F) * (float(DELAYINTERVAL_MS))) / (float(WHEELBASE_TICKS));		//calculate angular position change for the robot (we calculate directly to avoid losing resolution (rad))
		
		cout << "R_V_Bar " << (R_V_Bar>>LeftShiftAmount) << " RPOSYDELTA " << (R_POS_Y_delta>>LeftShiftAmount) << " ROMEGA " << (R_Omega>>LeftShiftAmount) << " R_THETA_DELTA " << (R_THETA_Delta>>LeftShiftAmount) << endl;
		cout << "Now print floats" << endl;
		cout << "R_V_BaF " << (R_V_Bar_F) << " RPOSYDELTA " << (R_POS_Y_delta_F) << " ROMEGA " << (R_Omega_F) << " R_THETA_DELTA " << (R_THETA_Delta_F) << endl;
		
		
		
		R_INERT_Theta = R_INERT_Theta + (R_THETA_Delta>>LeftShiftAmount); //update the angular position of the robot with the new estimate (right shift two for compatibility).
		//now translate R_POS_Y_delta back to inertial frame
		
		R_I_POS_X_delta = R_POS_Y_delta * cos(R_INERT_Theta);	//calculate vbar component in x inertial frame
		R_I_POS_Y_delta = R_POS_Y_delta * sin(R_INERT_Theta);	//calculate vbar component in y intertial frame
		R_I_POS_X = R_I_POS_X + (R_I_POS_X_delta>>LeftShiftAmount);				//compute new robot position in X inertial
		R_I_POS_Y = R_I_POS_Y + (R_I_POS_Y_delta>>LeftShiftAmount);				//compute new robot position in Y inertial
		
	
	
	
}