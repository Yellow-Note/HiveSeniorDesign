#include <fstream>
#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <chrono>
#include <queue>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "Support.h"
#include "RXD.h"


namespace fs = std::filesystem;
namespace ch = std::chrono;
namespace th = std::this_thread;
using namespace std;

const int threadNum = thread::hardware_concurrency();

void create_file(const fs::path& p) { ofstream o{ p }; }
string get_stem(const fs::path& p,bool analysis){ 
	if (analysis) {
		return(p.stem().string() + "A" + p.extension().string());
	}
	else {
		return (p.filename().string());
	}
}

void worker(fs::directory_entry fileName, fs::path dirTo, int threshold) {

	//cout << "File: " << dirTo<<"/"<<get_stem(fileName.path()) << endl;
	//create_file(dirTo / get_stem(fileName.path()));
	bool goodWrite = false;
	string oFile = dirTo.string() + "/" + get_stem(fileName,false);
	string aFile = dirTo.string() + "/" + get_stem(fileName,true);
	Mat image = cv::imread(fileName.path().string());
	//cout << "Writing file:" << oFile << endl;

	goodWrite = imwrite(oFile, image);

	MatrixXi bMatrix = convertImgtoMatrix(image, 0);
	MatrixXi gMatrix = convertImgtoMatrix(image, 1);
	MatrixXi rMatrix = convertImgtoMatrix(image, 2);

	MatrixXi RXDKfilterMat = RXDK(rMatrix, gMatrix, bMatrix, threshold);
	Mat RXDKfilterImg = convertMatrixtoImg(RXDKfilterMat);
	//cout << "Writing file:" << aFile << endl;


	if (goodWrite && imwrite(aFile, RXDKfilterImg)) {
		if (!fs::remove(fileName)) {
			cout << "Failed to remove file:" << fileName << endl;
		}
	}
}


int main(int argc,char **argv) {//give threshold then video name
	const int NUM_THREADS = 8;
	thread *workers = new thread[threadNum];
	bool listFlag = true;
	string videoName;
	int threshold;
	
	//TODO:sanitize input

	if (argc < 2) {
		cout << "No threshold given" << endl;
		return 0;
	}
	else if (argc > 4) {
		cout << "Too many arguments given" << endl;
		return 0;
	}
	else {
		threshold = atoi(argv[1]);
		videoName = argv[2];
	}

	/*threshold = 30;
	cout << "Video Name:" << endl;
	cin >> videoName;
	cout << endl;*/


	fs::path dirFrom,dirTo;
	dirFrom = videoName+"-slicer-out";
	dirTo = videoName+"_Complete";

	if (!fs::exists(dirTo)) {
		fs::create_directory(dirTo);
	}

	while (listFlag) {
		int dirCount = 0;
		bool newFile = true;
		deque<fs::directory_entry> fileList;
		deque<fs::directory_entry>::iterator it;

		for (auto const& dir_entry : fs::directory_iterator(dirFrom))
		{
			if (fileList.empty()) {
				fileList.push_back(dir_entry);
			}
			for (int i = 0; i < fileList.size(); i++) {
				if (dir_entry == fileList.at(i)) {
					newFile = false;
				}
			}
			if (newFile) {
				fileList.push_back(dir_entry);
			}
			newFile = true;
		}

		dirCount = fileList.size();

		for (int i = 0; i < NUM_THREADS; i++) {
			if (!fileList.empty()) {
				workers[i] = thread(worker, fileList.front(),dirTo,threshold);
				fileList.pop_front();
			}
		}
		
		for (int i = 0; i < NUM_THREADS; i++) {
			if (workers[i].joinable()) {
				workers[i].join();
			}
		}

		if (fileList.empty()) {
			listFlag = false;
		}
	}


	return 0;
}