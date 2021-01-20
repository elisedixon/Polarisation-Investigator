//
//  thetaChoice.h
//  Polarisation Shifter
//
//  Created by Elise Dixon on 17/01/2021.
//

#ifndef thetaChoice_h
#define thetaChoice_h
class thetaChoice{
private:
    
public:
    thetaChoice();
    ~thetaChoice();
    int menuOption();
    int dimensionChoice();
    double constantTheta();
    double circularTheta(double xval,double yval);
    double radialTheta(double xval, double yval);
    double jonesMatrixCalculate(double fastAxisTheta);
    void convToRadians(double* pDegreeAngle);
};



#endif /* thetaChoice_h */
