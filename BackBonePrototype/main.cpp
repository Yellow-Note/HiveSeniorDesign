#include <cstdio>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <semaphore.h>
#include <mutex>
#include <vector>
#include <Windows.h>
#include "queue_array.h"
using namespace std;

unsigned int totalthreadnum = std::thread::hardware_concurrency();
vector<array<array<array<char,3>,1080>,1920>> frame; //just fill this with random crap, this is the stand in for our video file, or rather a section of it
mutex multex, start;
array<array<array<char,3>,1080>,1920> fillme; //this is a stupid kludge, declaring this in fillvector created a stackdump

void fillvector(int number);
void worker(queue<int> myQueue, int id);
int rxDPlaceholder(short redImg, short blueImg, short greenImg, short redSamImg, short blueSamImg, short greenSamImg);
int analysisPlaceholder();

int main(int argc, char *argv[]) {
    if (argc == 1) return 1;
    int frameno = atoi(argv[1]); //number of frames
    //this will be replaced by us grabbing a set of frames
    fillvector(frameno);
    //cout << frame[0][16][9][0];
    //so by now we have our frames to work with, courtesy of the slicer. We replace the proceeding code with the results from the slicer.

    //create queue of frame numbers
    totalthreadnum -= 1;
    int workamount = frameno / totalthreadnum;
    QueueArray<int> workerQueues(totalthreadnum);

    int totaladded = 0;
    for (int i = 0; i < totalthreadnum - 1; i++) {
        int limit = totaladded + workamount;
        while (totaladded < limit)
        {
            workerQueues.Enqueue(totaladded,i);
            totaladded++;
            //cout << i << ": " << totaladded << endl;
        }
    }
    //add remaining frames to queues, this is for having a number of frames not evenly divisible by thread count
    for (int i = totaladded; i < frame.size(); i++)
    {
        //cout << totalthreadnum - 1 << ": " << totaladded << endl;
        workerQueues.Enqueue(i,totalthreadnum - 1);
        totaladded++;
    }
    //lets review
    cout << "We are gonna have " << totalthreadnum << " threads.\n"
        << "We have queued up work for " << workerQueues.Asize() << " threads.\n"
        << "Each thread gets about " << workamount << " frames to process.\n";

    thread workers[totalthreadnum];
    /*
    for (int j = 0; j < totalthreadnum; j++)
    {

        thread[j] = thread(worker(workerQueues.returnQueue(i),i)); //will figure this out later
    }*/

    return 0;
}
void fillvector(int number) //create our "images"
{
    for (int i = 0; i < number; i++) {
        srand(time(NULL));
        for (int j = 0; j < 1920; j++) {
            for (int k = 0; k < 1080; k++) {
                fillme[j][k][0] = rand() % 256;
                fillme[j][k][1] = rand() % 256;
                fillme[j][k][2] = rand() % 256;
            }
        }

        frame.push_back(fillme);
    }
}
void worker(queue<int> myQueue, int id)
{
    printf ("Worker %d has started.\n",id);
    while(myQueue.size() != 0)
    {
        int currentFrame = myQueue.front();
        myQueue.pop();
        //pretend we have a frame now to send to rxD
        int m = rxDPlaceholder(0,0,0,0,0,0);
        //commit modified frame back
        multex.lock();
        for (int j = 0; j < 1920; j++) {
            for (int k = 0; k < 1080; k++) {
                frame[currentFrame][j][k][0] = rand() % 256;
                frame[currentFrame][j][k][1] = rand() % 256;
                frame[currentFrame][j][k][2] = rand() % 256;
            }
        }
        multex.unlock();


    }
}
int rxDPlaceholder(short redImg, short blueImg, short greenImg, short redSamImg, short blueSamImg, short greenSamImg)
{
    this_thread::sleep_for(chrono::milliseconds(400) );
    srand(time(NULL));
    return (rand()% 10000);
}