//
//  thetaChoice.cpp
//  Polarisation Shifter
//
//  Created by Elise Dixon on 17/01/2021.
//

#include <stdio.h>
#include <iostream>
#include "thetaChoice.h"
using namespace std;

//Constructor
thetaChoice::thetaChoice(){

}

//Destructor
thetaChoice::~thetaChoice(){
}

//Takes the menu option from the user, checks it is an integer and is in range of the menu.
int thetaChoice::menuOption(){
    double option=0;
    while (option!=1 && option!=2 && option!=3){
        cout << "Please choose from the following options:" << endl;
        cout << "1. Constant theta." << endl;
        cout << "2. Radial theta." << endl;
        cout << "3. Circular theta." << endl;
        cin>> option;
        if(cin.fail()||((int)option!=option)||(option!=1 && option!=2 && option!=3)){
            cout << "Selection invalid, please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            option=0;
        }
    }
    return (int)option;
}


//Allows the user to select the dimensions for the arrays. Checks it is a valid integer and then returns.
int thetaChoice::dimensionChoice(){
    double dimensions;
    do {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please pick integer dimensions for the x and y axes arrays: " << endl;
        cin>> dimensions;
    } while (!cin || (int)dimensions!=dimensions);
    return (int)dimensions;
}


//Allows the user to pick an angle between 0 and 180, checks it's valid, converts it to radians, and then returns.
double thetaChoice::constantTheta(){
    double constThetaChoice;
    do {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Choose a constant angle in degrees between fast axis and the positive x axis (between 0 and 180): "<<flush;
        cin >> constThetaChoice;
    } while (!cin || constThetaChoice<0 || constThetaChoice>180);
    thetaChoice::convToRadians(&constThetaChoice);
    return constThetaChoice;
}



//Calculates the angle of a radial line from the origin, and corrects for when atan throws out an angle in the wrong quadrant.
double thetaChoice::radialTheta(double xval,double yval){
    double thetaValue=atan(yval/xval);
    if (xval<0){
        thetaValue=thetaValue+M_PI;
    }
    return thetaValue;
}


//Calculates the angle of a tangent to a circle surrounding the origin, and corrects for when atan throws out an angle in the wrong quadrant.
double thetaChoice::circularTheta(double xval, double yval){
    double circleRadius=sqrt(yval*yval+xval*xval);
    double circleGradient=(-xval)/sqrt((circleRadius*circleRadius-xval*xval));
    if (yval<0){
        circleGradient=-circleGradient;
    }
    cout << circleGradient<<'\t';
    double thetaValue=atan(circleGradient);
    if (yval<0){
        thetaValue=thetaValue+M_PI;
    }
    return thetaValue;
}

//Calculates the angle of polarisation for the output wave using a Jones matrix calculation.
double thetaChoice::jonesMatrixCalculate(double fastAxisTheta){
    double outputWaveX=(cos(fastAxisTheta)*cos(fastAxisTheta))-(sin(fastAxisTheta)*sin(fastAxisTheta));
    double outputWaveY=2*cos(fastAxisTheta)*sin(fastAxisTheta);
    double polarisationAngle=atan(outputWaveY/outputWaveX);
    return polarisationAngle;
};


//Converts a degree value to radians.
void thetaChoice::convToRadians(double* pDegreeAngle){
    cout << "Converting your selection to radians..." << endl;
    double radiansAngle =*pDegreeAngle*M_PI/180;
    *pDegreeAngle = radiansAngle;
    cout << "Angle in radians: " << *pDegreeAngle/M_PI << "pi" <<endl;
}


