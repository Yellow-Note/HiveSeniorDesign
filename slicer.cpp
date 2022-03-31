#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include <direct.h>
using namespace std;
using namespace cv;
//James Hoffman
int vfps, vwidth, vheight;
int elevation, sensorHeight, focalLength, speed;
string vpath;
// 
//Calculates how many frames per second we need.
//outputs how many fps we need, .1 means we need a frame every 10 seconds.
double FPS(double Hgsd, double kph) {
    double speed, hFH;
    //get kph -> mps
    speed = kph / 3.6;
    cout << speed << endl;
    //we want to to take a photo every half frame height.
    hFH = Hgsd / 2;
    cout << hFH << endl;
    return 1/(hFH / speed); // output of fps needed
}

// all values excluding elevation should be in mm
//elevation should be in meters , lowesst elevation once scanning has started to be safe.
//SH is the height of the sensor used. 
//SW is the width of the sensor used. 
//xpix is directional pixel count.
//FL is the focal length of the lense you are using
//GSD will have to be calculated twice, once for height once width
double GSD(int pix, double elevation, double SH, double FL) {
    double GSD, temp;
    //calculate vertical GSD
    //elevation * 1000 to convert m -> mm
    GSD = (elevation * 1000) * SH;
    temp = FL * pix;
    GSD = GSD / temp;
    //output is in CM
    return GSD / 10;
}
//frameGSD will have to be calculated twice once for height once for width
double frameGSD(double elevation, double SH, double FL) {
    double FH, temp;
    //calculate vertical GSD
    //elevation * 1000 to convert m -> mm
    FH = (elevation * 1000) * SH;
    FH = FH / FL;
    //output is in M
    return FH / 1000;
}
//for the sets use .get(prop_ID)
void setwidth() {
    VideoCapture video("movie.mov");
    cout << "frame width: " << video.get(CAP_PROP_FRAME_WIDTH);
    video.release();
    //CAP_PROP_FRAME_WIDTH
}

void setHeight() {
    VideoCapture video("movie.mov");
    cout << "frame width: " << video.get(CAP_PROP_FRAME_HEIGHT);
    video.release();
    //CAP_PROP_FRAME_HEIGHT
}

void setFPS() {
    VideoCapture video("movie.mov");
    cout << "frame width: " << video.get(CAP_PROP_FPS);
    //CAP_PROP_FPS
    video.release();
}

//video and output should be in "projectfolder\projectfolder\videoname.xxx"Output""
//Todo: change from void to int, use the return value as exit codes
//1 exited properly
//0 could not create folder
//-1 no video detected
void slicer(double elevation, double SH, double FL, double kph) {
    string  vname;
    int index = 0, loopcount = 0;
    double fps;
    //video capture obj
    cout << "what is the path of the video?" << endl;
    cin >> vname;
    fps = FPS(frameGSD(elevation, SH, FL), kph);
    cout << "FPS : " << fps << "-----------------------" << endl;
    VideoCapture video(vname);
    //cv:VideoCapture video(0);
    cv::Mat frame;

    if (!video.isOpened()) {
        cout << "no video stream detected" << endl << endl <<endl;
        return;
    }
    else {
        vname.append("Output");
        const char* fname = vname.c_str();
        cout << fname << endl;
        if (_mkdir(fname) != 0) {
            cout << "failed to open folder ------" << endl;
            video.release();
            return;
        }
    }
    double vfps = video.get(CAP_PROP_FPS);
    fps = vfps / fps;
    cout << vfps << endl << fps << endl;
    //always start at first frame
    video >> frame;
    imwrite(vname + "//" + (std::to_string(index) + ".jpg"), frame);
    index = fps;
    while (video.grab()){
        video.set(CAP_PROP_POS_FRAMES, index);
        video.read(frame);
        if (frame.empty()) {//if we are at the end of the video we are done
            video.set(CAP_PROP_POS_FRAMES, CAP_PROP_FRAME_COUNT);
            video.read(frame);
            imwrite(vname + "//" + (std::to_string(CAP_PROP_FRAME_COUNT) + ".jpg"), frame);
            cout << "frame is empty at " + std::to_string(index) + "fraems" << endl;
            break;
        }
        if (imwrite(vname + "//" + (std::to_string(index) + ".jpg"), frame)) {
            //saved properly
        }
        else {
            cout << "failed to save image" << endl;
        }
        index += fps;
    }
    video.release();
    //destroyAllWindows();

}
int main()
{
    string test;
    for (true; true;true) {
        cout << "what would you like to test" << endl;
        cin >> test;
        if (test == "slicer") {
            slicer(80, 8, 8.8, 15);
        }
        if (test == "fps") {
            //int FPS(double FH, double kph)
            double elevation, SH, FL, kph;
            cin >> elevation;
            cin >> SH;
            cin >> FL;
            cin >> kph;
            //this frameGSD is for height of frame
            cout << FPS(frameGSD(elevation, SH, FL), kph) << endl;
            //fps();
        }
        if (test == "frameGSD") {
            //double frameWidth(double elevation, double SW, double FL) {
            double elevation, SH, FL;
            cin >> elevation;
            cin >> SH;
            cin >> FL;
            cout << frameGSD(elevation, SH, FL) << endl;;
        }
        if (test == "GSD") {
            int hpix;
            double elevation, SH, FL;
            cin >> hpix;
            cin >> elevation;
            cin >> SH;
            cin >> FL;
            //double hGSD(int Hpix, double elevation, double SH, double FL) {
            cout << GSD(hpix, elevation, SH, FL) << endl;
        }
        if (test == "setfps") {
            setFPS();
        }
        if (test == "exit") {
            return 0;
        }
    }
    return 0;
}
