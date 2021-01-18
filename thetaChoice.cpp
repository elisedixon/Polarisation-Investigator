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


thetaChoice::thetaChoice(){

}

thetaChoice::~thetaChoice(){
}


double thetaChoice::constantTheta(){
    double constThetaChoice;
    cout << "Choose a constant angle in degrees between fast axis and the positive x axis (between 0 and 180): "<<flush;
    cin >> constThetaChoice;
    thetaChoice::convToRadians(&constThetaChoice);
    return constThetaChoice;
};


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
};


double thetaChoice::jonesMatrixCalculate(double fastAxisTheta){
    double outputWaveX=(cos(fastAxisTheta)*cos(fastAxisTheta))-(sin(fastAxisTheta)*sin(fastAxisTheta));
    double outputWaveY=2*cos(fastAxisTheta)*sin(fastAxisTheta);
    double polarisationAngle=atan(outputWaveY/outputWaveX);
    return polarisationAngle;
};


void thetaChoice::convToRadians(double* pDegreeAngle){
    cout << "Converting your selection to radians..." << endl;
    double radiansAngle =*pDegreeAngle*M_PI/180;
    *pDegreeAngle = radiansAngle;
    cout << "Angle in radians: " << *pDegreeAngle/M_PI << "pi" <<endl;
}


