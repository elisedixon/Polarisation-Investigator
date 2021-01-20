//
//  main.cpp
//  Polarisation Shifter
//
//  Created by Elise Dixon on 17/01/2021.
//


//This code allows the user to decide on the profile of fast axis across an optical component. It will then calculate the potentially non uniform polarisation angle profile of the output wave using jones calculus and the assumption that the incident wave is uniformly linearly polarised in the X direction.

#include <iostream>
#include <cmath>
#include <fstream>
#include "thetaChoice.h"
using namespace std;


int main() {
    //Creates an object of the thetaChoice class, to call the methods included in thetaChoice.
    thetaChoice thetaProfile;
    
    //Takes the user's option from the menu of possible polarisation profiles.
    int option= thetaProfile.menuOption();
    string thetaProfileType;
    
    
    
    //Fills in the x and y axis values to fit symmetrically around the array dimensions.
    //int ArrayDimensions=5;
    int ArrayDimensions=thetaProfile.dimensionChoice();
    int xAxis[ArrayDimensions];
    int yAxis[ArrayDimensions];
    for(int i=0; i<ArrayDimensions; i++){
        xAxis[i]=-(ArrayDimensions/2)+i;
        yAxis[i]=-(ArrayDimensions/2)+i;
    }
    double thetaArray[ArrayDimensions][ArrayDimensions];
    
    
    //Fills the fast axis theta array with the same value, which is input by the user as part of the constantTheta method of the thetaChoice class.
    if(option==1){
        thetaProfileType ="ConstantTheta";
        double constThetaChoice=thetaProfile.constantTheta();
        for(int i=0; i<ArrayDimensions; i++){
            for(int j=0; j<ArrayDimensions; j++){
                thetaArray[i][j]=constThetaChoice;
            };
        };
    };
    
    //Uses the radialTheta method of the thetaChoice class to fill out the fast axis array with radial angles.
    if(option==2){
        thetaProfileType ="RadialTheta";
        for(int i=0; i<ArrayDimensions; i++){
            for(int j=0; j<ArrayDimensions; j++){
                thetaArray[i][j]=thetaProfile.radialTheta(xAxis[j],yAxis[i]);
            };
        };
    };
    
    //Uses the circularTheta method of the thetaChoice class to fill the fast axis array with circular fast axes angles
    if(option==3){
        thetaProfileType ="CircularTheta";
        for(int i=0; i<ArrayDimensions; i++){
            for(int j=0; j<ArrayDimensions; j++){
                thetaArray[i][j]=thetaProfile.circularTheta(xAxis[j],yAxis[i]);
            };
        };
    };

    
    //Writes a text file containing the array of angles of the fast axis profile. couts are commented out but can be returned if user wants to check.
    ofstream fastAxisProfile;
    fastAxisProfile.open ("fastAxisProfile.txt");
    cout << "===================================" << endl;
    cout << "Fast axis theta array" << endl;
    for(int i=0; i<ArrayDimensions; i++){
        for(int j=0; j<ArrayDimensions; j++){
            //cout << thetaArray[i][j]/M_PI << '\t';
            fastAxisProfile << thetaArray [i][j] <<";";
        }
        fastAxisProfile<< endl;
        //cout << endl;
    }
    
    
    //This section calculates and then writes the polarisation angle of the output wave to the text file.
    //Opens a polarisationAngle file and uses a Jones matrix formula to create an array of the output wave x components and y components, with their corresponding angles.
    cout << "===================================" << endl;
    cout << "Polarisation Angle Profile"<< endl;
    ofstream polarisationAngleFile;
    polarisationAngleFile.open ("polarisationAngle.txt");
    double polarisationAngle[ArrayDimensions][ArrayDimensions];
    for(int i=0; i<ArrayDimensions; i++){
        for(int j=0; j<ArrayDimensions; j++){
            polarisationAngle[i][j]=thetaProfile.jonesMatrixCalculate(thetaArray[i][j]);
            //cout << polarisationAngle[i][j] << '\t';
            polarisationAngleFile << polarisationAngle[i][j] << ';';
        };
        //cout << endl;
        polarisationAngleFile << endl;
    };
    
    polarisationAngleFile.close();
    fastAxisProfile.close();
    return 0;
}
