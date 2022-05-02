#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include <direct.h>
using namespace std;
using namespace cv;
//James Hoffman
string vpath;
// 
//Calculates how many frames per second we need.
//outputs how many fps we need, .1 means we need a frame every 10 seconds.
double FPS(double gsd, double kph, int photosPerFrameSize) {
    double speed, hFH;
    //get kph -> mps
    speed = kph / 3.6;
    //we want to to take a photo every n frame height.
    hFH = gsd / photosPerFrameSize;
    return 1/(hFH / speed); // output of fps needed
}

// all values excluding elevation should be in mm
//elevation should be in meters , lowest elevation once scanning has started to be safe.
//SH is the height of the sensor used. 
//pix is directional pixel count.
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
// 1-n
//1 exited properly
//0 could not create folder
//-1 no video detected
//-2 failed to save photo
int slicer(int elevation, double SH, double FL, double kph, string path, int photosPerFrameSize) {
    int index = 0, loopcount = 1;
    double fps;
    //video capture obj
    fps = FPS(frameGSD(elevation, SH, FL), kph, photosPerFrameSize);
    VideoCapture video(path);
    //cv:VideoCapture video(0);
    cv::Mat frame;

    if (!video.isOpened()) {
        return -1;
    }
    else {
        path.append("-slicer-out");
        const char* fname = path.c_str();
        if (_mkdir(fname) != 0) {
            video.release();
            return 1;
        }
    }
    double vfps = video.get(CAP_PROP_FPS);
    fps = vfps / fps;
    //always start at first frame
    video >> frame;
    imwrite(path + "//" + (std::to_string(loopcount) + ".png"), frame);
    loopcount++;
    index = fps;
    while (video.grab()){
        video.set(CAP_PROP_POS_FRAMES, index);
        video.read(frame);
        if (frame.empty()) {//if we are at the end of the video we are done save the last frame
            video.set(CAP_PROP_POS_FRAMES, CAP_PROP_FRAME_COUNT);
            video.read(frame);
            imwrite(path + "//" + (std::to_string(CAP_PROP_FRAME_COUNT) + ".jpg"), frame);
            break;
        }
        if (imwrite(path + "//" + (std::to_string(loopcount) + ".jpg"), frame)) {
            loopcount++;
            //saved properly
        }
        else {
            return -2;
        }
        index += fps;
    }
    video.release();
    //destroyAllWindows();
    return 0;
}

//1 exited properly
//0 could not create folder
//-1 no video detected
//-2 failed to save photo
int main(int argc, char* argv[])
{
    if (argc != 7) {
        //return -3;
    }
    string path = argv[1];
    //string path = "movie.MOV";
    //int elevation = 1, sensorHeight = 1, focalLength = 1, speed = 1, photosPerFramesize = 1;
    int elevation = atoi(argv[2]), sensorHeight = atoi(argv[3]), focalLength = atoi(argv[4]), speed = atoi(argv[5]), photosPerFramesize = atoi(argv[6]);
    return slicer(elevation, sensorHeight, focalLength, speed, path, photosPerFramesize);
}
