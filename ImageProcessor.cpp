#include"opencv_test.h"
#include <cstdio>
#include<graphics.h>
#include<vector>

bool photoroot::image_loader(Mat& src)
{
	//wchar_t file[30];
	//InputBox(file, 10, L"type in the filename...");
	std::string filename;
	std::cin >> filename;
	src = imread(filename);
	return !src.empty();
}
bool photoroot::image_judger(Mat& image)
{
	justice = false;
	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
			int b = image.at<cv::Vec3b>(row, col)[0];
			int g = image.at<cv::Vec3b>(row, col)[1];
			int r = image.at<cv::Vec3b>(row, col)[2];
			if (image.at<cv::Vec3b>(row, col) == Vec3b(255, 255, 255))
			{
				justice = true;
			}
		}
	}
	return justice;
}
bool photoroot::image_saver(Mat& src)
{
	//wchar_t file[30];
	//InputBox(file, 10, L"type in the filename...");
	std::string filename;
	std::cin >> filename;
	return imwrite(filename, src);
}
bool videoroot::video_player(void)
{
	std::string filename;
	std::cin >> filename;
	VideoCapture capture(filename);
	return capture.isOpened();
}
Mat photoroot::rgb_detect(const Mat& image)
{
	Mat temp = Mat(image.rows, image.cols, CV_8UC3, Scalar(0));
	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
			int b = image.at<cv::Vec3b>(row, col)[0];
			int g = image.at<cv::Vec3b>(row, col)[1];
			int r = image.at<cv::Vec3b>(row, col)[2];
			if ((r > 95) && (g > 40) && (b > 20) && (max(max(r, g), b) - min(min(r, g), b) > 15) && (abs(r - g) > 15 && r > g && r > b))
			{
				temp.at<cv::Vec3b>(row, col) = Vec3b(255, 255, 255);
			}
		}
	}
	return temp;
}
Mat photoroot::hsv_detect(const Mat& image)
{
	Mat temp = Mat(image.rows, image.cols, CV_8UC3, Scalar(0));
	Mat* h = new(Mat);
	Mat tempchannel[3];
	cvtColor(image, temp, COLOR_BGR2HSV);
	split(temp, tempchannel);
	*h = tempchannel[0];
	inRange(*h, Scalar(2), Scalar(13), temp);
	delete h;
	return temp;
}
Mat photoroot::YCbCr_detect(const Mat& image)
{
	Mat temp = Mat(image.rows, image.cols, CV_8UC3, Scalar(0));
	cvtColor(image, temp, COLOR_BGR2YCrCb);
	inRange(temp, Scalar(0, 138, 77), Scalar(255, 243, 127), temp);
	return temp;
}
Mat photoroot::YCbCr_ellipse_detect(const Mat& image)
{
	Mat temp = Mat(image.rows, image.cols, CV_8UC3, Scalar(0));
	Mat temp_result = Mat(image.rows, image.cols, CV_8UC3, Scalar(0));
	Mat skinCrCbHist = Mat::zeros(Size(256, 256), CV_8UC1);
	ellipse(skinCrCbHist, Point(113, 155.6), Size(23.4, 23.2), 43.0, 0.0, 360.0, Scalar(255, 255, 255), -1);
	cvtColor(image, temp, COLOR_BGR2YCrCb);
	for (int row = 0; row < image.rows; row++)
	{
		for (int col = 0; col < image.cols; col++)
		{
			int y, cr, cb;
			y = temp.at<cv::Vec3b>(row, col)[0];
			cr = temp.at<cv::Vec3b>(row, col)[1];
			cb = temp.at<cv::Vec3b>(row, col)[2];
			if (skinCrCbHist.at<uchar>(cr, cb) > 0)
			{
				temp_result.at<cv::Vec3b>(row, col) = Vec3b(255, 255, 255);
			}
		}
	}
	return temp_result;
}
Mat photoroot::YCbCr_ostu_detect(const Mat& image)
{
	Mat temp = Mat(image.rows, image.cols, CV_8UC3, Scalar(0));
	Mat temp_result = Mat(image.rows, image.cols, CV_8UC3, Scalar(0));
	cvtColor(image, temp, COLOR_BGR2YCrCb);
	Mat detect;
	Mat channels[3];
	split(temp, channels);
	temp_result = channels[1];
	threshold(temp_result, temp_result, 0, 255, THRESH_BINARY | THRESH_OTSU);
	return temp_result;
}
int Opponent::Judge(hand_gesture& gseture)
{
	switch (gseture)
	{
	case rock:
		if (response == rock)
		{
			sum++;
			return 0;
		}
		else if (response == scissors)
		{
			sum++;
			win++;
			return -1;
		}
		else if (response == paper)
		{
			sum++;
			lose++;
			return 1;
		}
		break;
	case scissors:
		if (response == rock)
		{
			sum++;
			lose++;
			return 1;
		}
		else if (response == scissors)
		{
			sum++;
			return 0;
		}
		else if (response == paper)
		{
			sum++;
			win++;
			return -1;
		}
		break;
	case paper:
		if (response == rock)
		{
			sum++;
			win++;
			return -1;
		}
		else if (response == scissors)
		{
			sum++;
			lose++;
			return 1;
		}
		else if (response == paper)
		{
			sum++;
			return 0;
		}
		break;
	}
}
void Opponent::Spawn(void)
{
	int spawner = rand() % 3;
	switch (spawner)
	{
	case 1:
		this->response = rock;
		break;
	case 2:
		this->response = scissors;
		break;
	case 0:
		this->response = paper;
		break;
	}
}
void Opponent::Set(hand_gesture& gesture)
{
	this->response = gesture;
}
hand_gesture Opponent::GetResponse(void)
{
	return response;
}
