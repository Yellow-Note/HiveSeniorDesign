#define _GNU_SOURCE
#include <cstdio>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <semaphore.h>
#include <mutex>
#include <vector>
#include <sched.h>
#include "queue_array.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

unsigned int totalthreadnum = std::thread::hardware_concurrency();
vector<array<array<array<char,3>,1080>,1920>> frame; //just fill this with random crap, this is the stand in for our video file, or rather a section of it
mutex multex, start;
array<array<array<char,3>,1080>,1920> fillme; //this is a stupid kludge, declaring this in fillvector created a stackdump
int idnumber = 1;
float progress = 0.0;
float progslice = 0;


void fillvector(int number);
void worker(queue<int> myQueue, int id);
int rxDPlaceholder(short redImg, short blueImg, short greenImg, short redSamImg, short blueSamImg, short greenSamImg);
int analysisPlaceholder();
void launchworker(QueueArray<int> overall, int i);
void displayprogress();


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

    progslice = 100.0 / (float)frameno;
    cout << progslice << endl;

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
    for (int i = 0; i < totalthreadnum; i++)
    {
        //queue<int>* y = workerQueues.returnQueue(i);
        //workers[i] = thread(fillvector,i);
        //worker( workerQueues.returnQueue(i),i);



        workers[i] = thread(launchworker,workerQueues,i);

        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(i, &cpuset);
        int rc = pthread_setaffinity_np(workers[i].native_handle(),
                                        sizeof(cpu_set_t), &cpuset);
        if (rc != 0) {
            std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
        }

    }
    thread monitor;
    monitor = thread(displayprogress);
    for (int i = 0; i < totalthreadnum; i++)
    {
        workers[i].join();
    }
    monitor.join();

    return 0;
}
void launchworker(QueueArray<int> overall, int i) { //dumb kludge
    worker( overall.returnQueue(i),i);
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
    int i = 0;
    while(myQueue.size() != 0)
    {
        int currentFrame = myQueue.front();
        myQueue.pop();
        //printf ("Worker %d is now processing frame %d from it's queue\n",id,i);
        //pretend we have a frame now to send to rxD
        int m = rxDPlaceholder(0,0,0,0,0,0);
        //this_thread::sleep_for(chrono::milliseconds(400) );
        //commit modified frame back
        //multex.lock();
        for (int j = 0; j < 1920; j++) {
            for (int k = 0; k < 1080; k++) {
                //printf ("RGB values before: %d, %d, &d", frame[currentFrame][j][k][0], frame[currentFrame][j][k][1], frame[currentFrame][j][k][2]);
                frame[currentFrame][j][k][0] = rand() % 256;
                frame[currentFrame][j][k][1] = rand() % 256;
                frame[currentFrame][j][k][2] = rand() % 256;
                //printf ("RGB values after: %d, %d, &d", frame[currentFrame][j][k][0], frame[currentFrame][j][k][1], frame[currentFrame][j][k][2]);
            }
        }
        i++;
        //multex.unlock();
        progress+=progslice;


    }
}
int rxDPlaceholder(short redImg, short blueImg, short greenImg, short redSamImg, short blueSamImg, short greenSamImg)
{
    this_thread::sleep_for(chrono::milliseconds(400) );
    srand(time(NULL));
    return (rand()% 10000);
}
void displayprogress()
{
    while(progress < 99)
    {
        this_thread::sleep_for(chrono::milliseconds(200) );
        cout << "\x1B[2J\x1B[H";
        cout.precision(4);
        cout << "Processing frames " << progress << "% complete.\n";
    }
}

