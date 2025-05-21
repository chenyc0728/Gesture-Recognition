#pragma once
#include <opencv2\opencv.hpp>
#include<iostream>
#include <windows.h>
#include <string>
#define R 5
using namespace cv;

//void Wchar_tToString(std::string& szDst, wchar_t* wchar)
//{
//	wchar_t* wText = wchar;
//	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);
//	char* psText;  
//	psText = new char[dwNum];
//	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);
//	szDst = psText;
//	delete[]psText;
//}

enum hand_gesture { rock = -3, paper = -2, scissors = -1, null = -4 };

class photoroot {
private:
	bool justice;
public:
	bool image_loader(Mat& src);
	bool image_saver(Mat& src);
	bool image_judger(Mat& image);
	bool GetJustice(void) { return justice; }
	Mat rgb_detect(const Mat& image);
	Mat hsv_detect(const Mat& image);
	Mat YCbCr_detect(const Mat& image);
	Mat YCbCr_ellipse_detect(const Mat& image);
	Mat YCbCr_ostu_detect(const Mat& image);
};

class videoroot {
public:
	bool video_player(void);
};

class Opponent {
private:
	hand_gesture response;
	int sum = 0;
	int win = 0;
	int lose = 0;
public:
	int Judge(hand_gesture& gesture);
	void Spawn(void);
	void Set(hand_gesture& gesture);
	void Reset(void) { sum = 0; win = 0; lose = 0; }
	int GetCount(void) { return sum; }
	int GetWin(void) { return win; }
	int GetLose(void) { return lose; }
	float Percent(void) { return sum / win; }
	hand_gesture GetResponse(void);
};