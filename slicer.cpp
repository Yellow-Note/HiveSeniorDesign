#include <iostream>
using namespace std;
//James Hoffman
//Calculates how many frames per second we need, FH is frame height and should be calculated with the included function. 
int FPS(double FH, double kph){
    double speed,hFH;
    //get kph -> kps
    speed = kph / 60 / 60;
    //get kps -> mps*
    speed = speed * 1000;
    //we want to to take a photo every half frame height.
    hFH = FH/2;
    return hFH/speed;
}

// all values excluding elevation should be in mm
//elevation should be in meters , lowest elevation once scanning has started to be safe.
//SH is the height of the sensor used. 
//SW is the width of the sensor used. 
//xpix is directional pixel count.
//FL is the focal length of the lense you are using
double hGSD(int Hpix, double elevation,double SH, double FL){
    double hGSD, temp;
    //calculate vertical GSD
    //elevation * 1000 to convert m -> mm
    hGSD = (elevation *1000) * SH;
    temp = FL * Hpix;
    hGSD = hGSD/temp;
    //output is in CM
    return hGSD/10;
}

double wGSD(int Wpix, double elevation, double SW, double FL){
    double wGSD, temp;
    //calculate horizontal GSD
    wGSD = (elevation *1000) * SW;
    temp = FL * Wpix;
    wGSD = wGSD/temp;
    //output is in CM
    return wGSD/10;
}

double frameHeight(double elevation,double SH, double FL){
    double FH, temp;
    //calculate vertical GSD
    //elevation * 1000 to convert m -> mm
    FH = (elevation *1000) * SH;
    FH = FH/FL;
    //output is in M
    return FH/1000;
}

double frameWidth(double elevation,double SW, double FL){
    double FW, temp;
    //calculate vertical GSD
    //elevation * 1000 to convert m -> mm
    FW = (elevation *1000) * SW;
    FW = FW/FL;
    //output is in M
    return FW/1000;
}

int main(){
    cout << "Start: " << endl;
    cout << "hGSD: "<< hGSD(3078, 80,8.0,8.8) << endl;
    cout << "wGSD: "<< wGSD(5472 , 80,13.2,8.8) << endl;
    cout << "Frame Height: " << frameHeight(80, 13.2, 8.8) << endl;
    cout << "Fps: " << FPS(frameHeight(80, 13.2, 8.8),1);
    return 0;
}