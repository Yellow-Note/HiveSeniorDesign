#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;
//James Hoffman
//Calculates how many frames per second we need, FH is frame height and should be calculated with the included function.
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

//video and output should be in "projectfolder\projectfolder"
void slicer(double elevation, double SH, double FL, double kph) {
    string vname;
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
    double vfps = video.get(CAP_PROP_FPS);
    fps = vfps / fps;
    cout << vfps << endl << fps << endl;
    //always start at first frame
    video >> frame;
    imwrite((std::to_string(index) + ".jpg"), frame);
    while (video.read(frame)){
        //display the frame
        //video >> frame;

        //if (waitKey(1) == 25) {
        //    break;
        //}
        if (frame.empty()) {//if we are at the end of the video we are done
            cout << "frame is empty at " + std::to_string(index) + "fraems" << endl;
            break;
        }
        //imshow("video",frame);
        //write the frame to memory

        namedWindow("image", WINDOW_AUTOSIZE);
        imshow("image", frame);
        waitKey(30);
        if (loopcount == (int)fps) {
            cout << "loopcount == fps" << endl;
            if (imwrite((std::to_string(index) + ".jpg"), frame)) {
                cout << "saved image" << endl;
            }else{
                    cout << "failed to save image" << endl;
            }
            loopcount = 0;
        }
        index++;
        loopcount++;
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
        if (test == "exit") {
            return 0;
        }
    }
    return 0;
}
