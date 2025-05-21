#pragma comment(lib, "opencv_world470.lib")
#define _CRT_SECURE_NO_WARNINGS
#include <opencv2\opencv.hpp>
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <cstdlib>
#include <string>
#include <Windows.h>
#include <cmath>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#include "opencv_test.h"
using namespace cv;
using namespace std;

void title(int left, int right, int top, int bottom, int r, const wchar_t* ch, COLORREF text_color, COLORREF shape_color, LPCTSTR fontstyle)
{
    settextstyle((top - bottom) * 2 / 3, 0, fontstyle);
    settextcolor(text_color);
    outtextxy((left + right - textwidth(ch)) / 2, (top + bottom - textheight(ch)) / 2, ch);
}
void textout(int left, int right, int top, int bottom, int r, const TCHAR* ch, COLORREF text_color, COLORREF shape_color, LPCTSTR fontstyle)
{
    settextstyle((top - bottom) * 2 / 3, 0, fontstyle);
    settextcolor(text_color);
    outtextxy((left + right - textwidth(ch)) / 2, (top + bottom - textheight(ch)) / 2, ch);
}
void botton(int left, int right, int top, int bottom, int r, const wchar_t* ch, COLORREF text_color, COLORREF shape_color, LPCTSTR fontstyle)
{
    setfillcolor(shape_color);
    solidroundrect(left, top, right, bottom, r, r);
    settextstyle((top - bottom) * 2 / 3, 0, fontstyle);
    settextcolor(text_color);
    outtextxy((left + right - textwidth(ch)) / 2, (top + bottom - textheight(ch)) / 2, ch);
    setfillcolor(NULL), settextcolor(NULL);
}
void buttonspawner0(void)
{
    title(210, 410, 15, 120, R, L"石头 剪刀 布", WHITE, NULL, _T("华文中宋"));
    title(210, 410, 120, 175, R, L"                         —— 手势识别", WHITE, NULL, _T("华文中宋"));
    botton(215, 425, 210, 255, R, L"开始", BLACK, LIGHTGRAY, _T("等线"));
    botton(215, 425, 300, 345, R, L"设置", BLACK, LIGHTGRAY, _T("等线"));
    botton(215, 425, 390, 435, R, L"退出", BLACK, LIGHTGRAY, _T("等线"));
}
void buttonspawner1(void)
{
    title(210, 410, 35, 140, R, L"选择颜色模型", WHITE, NULL, _T("华文中宋"));
    botton(70, 280, 210, 255, R, L"BGR", BLACK, LIGHTGRAY, _T("等线"));
    botton(360, 570, 210, 255, R, L"HSV", BLACK, LIGHTGRAY, _T("等线"));
    botton(215, 425, 300, 345, R, L"YCbCr_ostu", BLACK, LIGHTGRAY, _T("等线"));
    botton(70, 280, 390, 435, R, L"YCbCr", BLACK, LIGHTGRAY, _T("等线"));
    botton(360, 570, 390, 435, R, L"YCbCr_Ellipse", BLACK, LIGHTGRAY, _T("等线"));
}


int main(int argc, char** argv) {
    Mat tempframe;
    Mat frametoshow;
    Mat framework;
    photoroot photogragh;
    char TimeRec[50];
    TCHAR ThisCount[10];
    TCHAR ThatCount[10];
    TCHAR TotalCount[10];
    int choice = 5;
    bool judge;
    bool judge2;
    int mode;
    int select = 0;
    int random = 0;
    int count = 0;
    int win, lose, tie;
    int screenshot = 0;
    double area_k;
    double arc_k;
    double convex_s;
    double cont_s;
    bool EndOrNot = true;
    bool EndDetectingOrNot = true;
    bool TestOrNot = true;
    bool FoutOrNot = false;
    bool RivalonOrNot = false;
    bool TimerChoice = true;
    wchar_t name[30] = L"花园宝宝";
    time_t t;
    clock_t start, end;
    clock_t timer1, timer2;
    struct tm* now;
    IMAGE img, img2;
    IMAGE This, That;
    Opponent rival;
    hand_gesture gesture = null;
    hand_gesture gesture2 = null;
    string data;
    Mat morp, binary;
    vector<vector<Point>> contours, contour;
    vector<double> area;
    Mat RIVAL;



    srand(time(NULL));
    loadimage(&img, _T("bg.bmp"));
    loadimage(&This, _T("This.bmp"));
    loadimage(&That, _T("Rival.bmp"));


    mciSendString(_T("open Maroon.mp3 alias music"), 0, 0, 0);
    mciSendString(_T("play music repeat"), 0, 0, 0);

    fstream text;
    text.open("Output.txt", ios::app);

    t = time(nullptr);
    now = localtime(&t);
    strftime(TimeRec, sizeof(TimeRec), "%Y年%m月%d日 %H:%M:%S", now);
    text << "\n" << TimeRec << endl;


    do {
        initgraph(640, 480);
        setbkmode(TRANSPARENT);
        do {
            BeginBatchDraw();
            cleardevice();
            putimage(0, 0, &img);
            buttonspawner0();
            EndBatchDraw();
            do {
                judge = false;
                if (MouseHit())
                {
                    MOUSEMSG msg = GetMouseMsg();
                    if (msg.uMsg == WM_LBUTTONDOWN)
                    {
                        if (msg.x >= 210 && msg.x <= 425 && msg.y >= 210 && msg.y <= 255)
                        {
                            mode = 1;
                            judge = true;
                        }
                        if (msg.x >= 210 && msg.x <= 425 && msg.y >= 300 && msg.y <= 345)
                        {
                            mode = 2;
                            judge = true;
                        }
                        if (msg.x >= 210 && msg.x <= 425 && msg.y >= 390 && msg.y <= 435)
                        {
                            mode = 3;
                            judge = true;
                        }
                    }
                }
            } while (!judge);
            if (mode == 2)
            {

                do {
                    BeginBatchDraw();
                    cleardevice();
                    putimage(0, 0, &img);
                    title(210, 410, 0, 100, R, L"设 置", WHITE, NULL, _T("华文中宋"));
                    botton(215, 425, 165, 120, R, (RivalonOrNot ? L"机器对手：开" : L"机器对手：关"), BLACK, LIGHTGRAY, _T("等线"));
                    botton(215, 425, 210, 255, R, (TestOrNot ? L"测试视图：开" : L"测试视图：关"), BLACK, LIGHTGRAY, _T("等线"));
                    botton(215, 425, 300, 345, R, L"模型选择", BLACK, LIGHTGRAY, _T("等线"));
                    botton(215, 425, 390, 435, R, (FoutOrNot ? L"导出：开" : L"导出：关"), BLACK, LIGHTGRAY, _T("等线"));
                    botton(500, 570, 390, 435, R, L"返回", BLACK, LIGHTGRAY, _T("等线"));
                    EndBatchDraw();

                    judge = false;
                    while (1)
                    {
                        if (MouseHit())
                        {
                            MOUSEMSG msg = GetMouseMsg();
                            if (msg.uMsg == WM_LBUTTONDOWN)
                            {
                                if (msg.x >= 500 && msg.x < 570 && msg.y >= 390 && msg.y <= 435)
                                {
                                    judge = true;
                                    /*random = -1;*/
                                    break;
                                }
                                if (msg.x >= 215 && msg.x <= 425 && msg.y >= 300 && msg.y <= 345)
                                {
                                    select = 1;
                                    break;
                                }
                                if (msg.x >= 215 && msg.x <= 425 && msg.y >= 390 && msg.y <= 425)
                                {
                                    select = 2;
                                    break;
                                }
                                if (msg.x >= 215 && msg.x <= 425 && msg.y >= 210 && msg.y <= 255)
                                {
                                    select = 3;
                                    break;
                                }
                                if (msg.x >= 215 && msg.x <= 425 && msg.y >= 120 && msg.y <= 165)
                                {
                                    select = 4;
                                    break;
                                }
                            }
                        }
                    }
                    switch (select)
                    {
                    case 1:
                        BeginBatchDraw();
                        cleardevice();
                        putimage(0, 0, &img);
                        buttonspawner1();
                        botton(580, 620, 440, 460, R, L"返回", BLACK, LIGHTGRAY, _T("等线"));
                        EndBatchDraw();
                        do {
                            judge2 = false;
                            if (MouseHit())
                            {
                                MOUSEMSG msg = GetMouseMsg();
                                if (msg.uMsg == WM_LBUTTONDOWN)
                                {
                                    if (msg.x >= 70 && msg.x <= 280 && msg.y >= 210 && msg.y <= 255)
                                    {
                                        choice = 1;
                                        judge2 = true;
                                    }
                                    if (msg.x >= 360 && msg.x <= 570 && msg.y >= 210 && msg.y <= 255)
                                    {
                                        choice = 2;
                                        judge2 = true;
                                    }
                                    if (msg.x >= 215 && msg.x <= 425 && msg.y >= 300 && msg.y <= 345)
                                    {
                                        choice = 3;
                                        judge2 = true;
                                    }
                                    if (msg.x >= 70 && msg.x <= 280 && msg.y >= 390 && msg.y <= 435)
                                    {
                                        choice = 4;
                                        judge2 = true;
                                    }
                                    if (msg.x >= 360 && msg.x < 570 && msg.y >= 390 && msg.y <= 435)
                                    {
                                        choice = 5;
                                        judge2 = true;
                                    }
                                    if (msg.x >= 580 && msg.x < 620 && msg.y >= 440 && msg.y <= 460)
                                    {
                                        judge2 = true;
                                    }
                                }
                            }
                        } while (!judge2);
                        cout << "模型已被设置为 " << choice << endl;
                        cleardevice();
                        putimage(0, 0, &img);
                        break;
                    case 2:
                        FoutOrNot = !FoutOrNot;
                        cout << "导出 已被设置为 " << FoutOrNot << endl;
                        BeginBatchDraw();
                        botton(215, 425, 390, 435, R, (FoutOrNot ? L"导出：开" : L"导出：关"), BLACK, LIGHTGRAY, _T("等线"));
                        EndBatchDraw();
                        break;
                    case 3:
                        TestOrNot = !TestOrNot;
                        cout << "测试视图 已被设置为 " << TestOrNot << endl;
                        BeginBatchDraw();
                        botton(215, 425, 210, 255, R, (TestOrNot ? L"测试视图：开" : L"测试视图：关"), BLACK, LIGHTGRAY, _T("等线"));
                        EndBatchDraw();
                        break;
                    case 4:
                        RivalonOrNot = !RivalonOrNot;
                        cout << "机器对手 已被设置为 " << RivalonOrNot << endl;
                        BeginBatchDraw();
                        botton(215, 425, 165, 120, R, (RivalonOrNot ? L"机器对手：开" : L"机器对手：关"), BLACK, LIGHTGRAY, _T("等线"));
                        EndBatchDraw();
                        break;
                    }
                    select = 0;
                } while (!judge);
            }
            else if (mode == 3)
            {
                EndOrNot = false;
                return 0;
            }
        } while (mode == 2);

        closegraph();
        mciSendString(_T("close music"), 0, 0, 0);

        VideoCapture capture(0);
        initgraph((RivalonOrNot ? 900 : 450), 300, EX_NOCLOSE);
        BeginBatchDraw();
        cleardevice();
        select = 0;
        mciSendString(_T("open Youreonyourownkid.mp3 alias music2"), 0, 0, 0);
        mciSendString(_T("play music2 repeat"), 0, 0, 0);

        if (RivalonOrNot)
        {
            RIVAL = imread("bg2.bmp", 1);
            loadimage(&img2, _T("rivalbg.bmp"));
            putimage(0, 0, &img2);
            putimage(25, 25, &This);
            putimage(825, 25, &That);
            title(25, 75, 100, 130, R, name, WHITE, NULL, _T("华文中宋"));
            title(825, 875, 100, 130, R, L"小A", WHITE, NULL, _T("华文中宋"));
            botton(30, 180, 240, 270, R, L"截屏", BLACK, LIGHTGRAY, _T("等线"));
            botton(270, 420, 240, 270, R, L"退出", BLACK, LIGHTGRAY, _T("等线"));
            botton(480, 630, 240, 270, R, L"清零", BLACK, LIGHTGRAY, _T("等线"));
            botton(720, 870, 240, 270, R, L"改名", BLACK, LIGHTGRAY, _T("等线"));
        }
        else
        {
            loadimage(&img2, _T("rivallessbg.bmp"));
            putimage(0, 0, &img2);
            title(125, 325, 30, 80, R, L"手势识别", WHITE, NULL, _T("华文中宋"));
            botton(30, 180, 240, 270, R, L"截屏", BLACK, LIGHTGRAY, _T("等线"));
            botton(270, 420, 240, 270, R, L"退出", BLACK, LIGHTGRAY, _T("等线"));
            botton(100, 350, 110, 150, R, L"识别结果：    ", WHITE, NULL, _T("华文中宋"));
        }
        EndBatchDraw();

        setbkmode(TRANSPARENT);
        start = clock();

        while (EndDetectingOrNot) {

            capture.read(tempframe);
            flip(tempframe, tempframe, 1);
            if (tempframe.empty())
                break;

            select = 0;
            judge = false;
            if (MouseHit())
            {
                MOUSEMSG msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN)
                {
                    if (msg.x >= 30 && msg.x <= 180 && msg.y >= 240 && msg.y <= 270)
                    {
                        select = 1;
                        judge = true;
                    }
                    if (msg.x >= 270 && msg.x <= 420 && msg.y >= 240 && msg.y <= 270)
                    {
                        select = 2;
                        judge = true;
                    }
                    if (msg.x >= 480 && msg.x <= 630 && msg.y >= 240 && msg.y <= 270 && RivalonOrNot)
                    {
                        select = 3;
                        judge = true;
                    }
                    if (msg.x >= 720 && msg.x <= 870 && msg.y >= 240 && msg.y <= 270 && RivalonOrNot)
                    {
                        select = 4;
                        judge = true;
                    }
                }
            }

            frametoshow = tempframe;
            GaussianBlur(tempframe, tempframe, Size(39, 33), 3, 3);

            switch (choice)
            {
            case 1:
                framework = photogragh.rgb_detect(tempframe);
                break;
            case 2:
                framework = photogragh.hsv_detect(tempframe);
                break;
            case 3:
                framework = photogragh.YCbCr_ostu_detect(tempframe);
                break;
            case 4:
                framework = photogragh.YCbCr_detect(tempframe);
                break;
            case 5:
                framework = photogragh.YCbCr_ellipse_detect(tempframe);
                break;
            }
            if (choice == 1 || choice == 5)
            {
                if (photogragh.image_judger(framework) == false)
                    continue;
            }
            //framework.set(CV_CAP_PROP_EXPOSURE, -4.7);
            GaussianBlur(framework, framework, Size(5, 5), 0, 0);
            Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));

            morphologyEx(framework, morp, MORPH_OPEN, kernel);

            Canny(morp, binary, 50, 200);

            vector<Vec4i> hierachy;

            findContours(binary, contours, hierachy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);// 提取最外层轮廓
            area.clear();

            for (int i = 0; i < contours.size(); ++i) {
                area.push_back(contourArea(contours[i]));
            }

            int maxPosition = max_element(area.begin(), area.end()) - area.begin();//求面积最大的轮廓所在位置

            vector<vector<Point>> convex(1);


            convexHull(contours[maxPosition], convex[0], true);//求手势的凸包轮廓

            drawContours(framework, convex, 0, Scalar::all(255));

            Rect rects = boundingRect(contours[maxPosition]);//获得包围手势轮廓的矩形

            RNG rngs = { 12345 };
            Scalar colors = Scalar(rngs.uniform(0, 255), rngs.uniform(0, 255), rngs.uniform(0, 255));
            rectangle((TestOrNot ? framework : frametoshow), rects, colors, 2);//画出包围手势轮廓的矩形

            cont_s = rects.height * rects.width;
            if (cont_s /*手势轮廓面积*/ >= 20000) {

                convexHull(contours[maxPosition], convex[0], true);//求手势的凸包轮廓

                drawContours(framework, convex, 0, Scalar::all(255));

                convex_s = contourArea(convex[0]);

                area_k = convex_s / cont_s;//计算面积比
                arc_k = arcLength(contours[maxPosition], true) / arcLength(convex[0], true);//计算周长比

                Rect rects = boundingRect(contours[maxPosition]);//获得包围手势轮廓的矩形

                RNG rngs = { 12345 };
                Scalar colors = Scalar(rngs.uniform(0, 255), rngs.uniform(0, 255), rngs.uniform(0, 255));
                rectangle((TestOrNot ? framework : frametoshow), rects, colors, 2);//画出包围手势轮廓的矩形

                if (arc_k < 1.95 && arc_k > 1.2/* && area_k > 0.7 && area_k < 0.85*/)
                {
                    (TimerChoice ? timer1 : timer2) = clock();
                    TimerChoice = !TimerChoice;
                    end = clock();
                    putText((TestOrNot ? framework : frametoshow), "Rock", Point(rects.x, rects.y), FONT_HERSHEY_TRIPLEX, 0.8, Scalar(255, 200, 200), 2, (30, 144, 255));
                    gesture = rock;
                    cout << count + 1 << " 石头 面积比 周长比：" << area_k << "    " << arc_k << endl;
                }
                else if (arc_k > 2.1 && arc_k < 2.9/* && area_k > 0.65 && area_k < 0.85*/)
                {
                    (TimerChoice ? timer1 : timer2) = clock();
                    TimerChoice = !TimerChoice;
                    end = clock();
                    putText((TestOrNot ? framework : frametoshow), "Scissors", Point(rects.x, rects.y), FONT_HERSHEY_TRIPLEX, 0.8, Scalar(255, 200, 200), 2, (30, 144, 255));
                    gesture = scissors;
                    cout << count + 1 << " 剪刀 面积比 周长比：" << area_k << "    " << arc_k << endl;
                }
                else if (arc_k > 3.1 && arc_k < 3.9/* && area_k> 0.65 && area_k < 0.8*/)
                {
                    (TimerChoice ? timer1 : timer2) = clock();
                    TimerChoice = !TimerChoice;
                    end = clock();
                    putText((TestOrNot ? framework : frametoshow), "Paper", Point(rects.x, rects.y), FONT_HERSHEY_TRIPLEX, 0.8, Scalar(255, 200, 200), 2, (30, 144, 255));
                    gesture = paper;
                    cout << count + 1 << " 布 面积比 周长比：" << area_k << "    " << arc_k << endl;
                }
                else
                    gesture = null;
            }
            imshow("VideoCapture", (TestOrNot ? framework : frametoshow));


            BeginBatchDraw();
            switch (gesture)
            {
            case rock:
                BeginBatchDraw();
                if (RivalonOrNot)
                {
                    if (abs(timer1 - timer2) >= 3000 || gesture != gesture2)
                    {
                        cleardevice();
                        putimage(0, 0, &img2);
                        rival.Spawn();
                        rival.Judge(gesture);
                        _stprintf(ThisCount, _T("%d"), rival.GetLose());
                        _stprintf(ThatCount, _T("%d"), rival.GetWin());
                        _stprintf(TotalCount, _T("%d"), rival.GetCount());
                        putimage(25, 25, &This);
                        putimage(825, 25, &That);
                        title(25, 75, 100, 130, R, name, WHITE, NULL, _T("华文中宋"));
                        title(825, 875, 100, 130, R, L"小A", WHITE, NULL, _T("华文中宋"));
                        textout(375, 425, 125, 175, R, ThisCount, WHITE, NULL, _T("华文中宋"));
                        textout(475, 525, 125, 175, R, ThatCount, WHITE, NULL, _T("华文中宋"));
                        title(175, 300, 125, 175, R, L"石头", WHITE, NULL, _T("华文中宋"));
                        title(445, 455, 125, 175, R, L"：", WHITE, NULL, _T("华文中宋"));
                        if (rival.GetResponse() == rock)
                            title(525, 750, 125, 175, R, L"石头", WHITE, NULL, _T("华文中宋"));
                        else if (rival.GetResponse() == scissors)
                            title(525, 750, 125, 175, R, L"剪刀", WHITE, NULL, _T("华文中宋"));
                        else if (rival.GetResponse() == paper)
                            title(525, 750, 125, 175, R, L"布", WHITE, NULL, _T("华文中宋"));
                        botton(30, 180, 240, 270, R, L"截屏", BLACK, LIGHTGRAY, _T("等线"));
                        botton(270, 420, 240, 270, R, L"退出", BLACK, LIGHTGRAY, _T("等线"));
                        botton(480, 630, 240, 270, R, L"清零", BLACK, LIGHTGRAY, _T("等线"));
                        botton(720, 870, 240, 270, R, L"改名", BLACK, LIGHTGRAY, _T("等线"));
                        gesture2 = rock;
                    }
                    else
                        putText((TestOrNot ? framework : frametoshow), "Waiting for 3s...", Point(0,0), FONT_HERSHEY_TRIPLEX, 0.8, Scalar(255, 200, 200), 2, (30, 144, 255));
                }
                else
                {
                    cleardevice();
                    putimage(0, 0, &img2);
                    title(125, 325, 30, 80, R, L"手势识别", WHITE, NULL, _T("华文中宋"));
                    botton(30, 180, 240, 270, R, L"截屏", BLACK, LIGHTGRAY, _T("等线"));
                    botton(270, 420, 240, 270, R, L"退出", BLACK, LIGHTGRAY, _T("等线"));
                    title(100, 350, 110, 150, R, L"识别结果：    ", WHITE, NULL, _T("华文中宋"));
                    title(300, 350, 110, 150, R, L"石头", WHITE, NULL, _T("华文中宋"));
                }
                EndBatchDraw();
                count++;
                data += "" + count;
                data += ": 石头\n";
                if (FoutOrNot)
                {
                    if (RivalonOrNot)
                    {
                        text << count << "\t" << end - start << "ms\t" << "Player：" << "：石头\t" << "Rival：";
                        if (rival.GetResponse() == rock)
                            text << "石头\t" << rival.Judge(gesture) << endl;
                        else if (rival.GetResponse() == scissors)
                            text << "剪刀\t" << rival.Judge(gesture) << endl;
                        else if (rival.GetResponse() == paper)
                            text << " 布 \t" << rival.Judge(gesture) << endl;
                    }
                    else
                        text << count << "\t" << end - start << "\t石头" << endl;
                }
                if (1) gesture = null;
                break;
            case scissors:
                BeginBatchDraw();
                if (RivalonOrNot)
                {
                    if (abs(timer1 - timer2) >= 3000 || gesture != gesture2)
                    {
                        cleardevice();
                        putimage(0, 0, &img2);
                        rival.Spawn();
                        rival.Judge(gesture);
                        _stprintf(ThisCount, _T("%d"), rival.GetLose());
                        _stprintf(ThatCount, _T("%d"), rival.GetWin());
                        _stprintf(TotalCount, _T("%d"), rival.GetCount());
                        putimage(25, 25, &This);
                        putimage(825, 25, &That);
                        title(25, 75, 100, 130, R, name, WHITE, NULL, _T("华文中宋"));
                        title(825, 875, 100, 130, R, L"小A", WHITE, NULL, _T("华文中宋"));
                        textout(375, 425, 125, 175, R, ThisCount, WHITE, NULL, _T("华文中宋"));
                        textout(475, 525, 125, 175, R, ThatCount, WHITE, NULL, _T("华文中宋"));
                        title(175, 300, 125, 175, R, L"剪刀", WHITE, NULL, _T("华文中宋"));
                        title(445, 455, 125, 175, R, L"：", WHITE, NULL, _T("华文中宋"));
                        if (rival.GetResponse() == rock)
                            title(525, 750, 125, 175, R, L"石头", WHITE, NULL, _T("华文中宋"));
                        else if (rival.GetResponse() == scissors)
                            title(525, 750, 125, 175, R, L"剪刀", WHITE, NULL, _T("华文中宋"));
                        else if (rival.GetResponse() == paper)
                            title(525, 750, 125, 175, R, L"布", WHITE, NULL, _T("华文中宋"));
                        botton(30, 180, 240, 270, R, L"截屏", BLACK, LIGHTGRAY, _T("等线"));
                        botton(270, 420, 240, 270, R, L"退出", BLACK, LIGHTGRAY, _T("等线"));
                        botton(480, 630, 240, 270, R, L"清零", BLACK, LIGHTGRAY, _T("等线"));
                        botton(720, 870, 240, 270, R, L"改名", BLACK, LIGHTGRAY, _T("等线"));
                        gesture2 = scissors;
                    }
                    else
                        putText((TestOrNot ? framework : frametoshow), "Waiting for 3s...", Point(0, 0), FONT_HERSHEY_TRIPLEX, 0.8, Scalar(255, 200, 200), 2, (30, 144, 255));
                }
                else
                {
                    cleardevice();
                    putimage(0, 0, &img2);
                    title(125, 325, 30, 80, R, L"手势识别", WHITE, NULL, _T("华文中宋"));
                    botton(30, 180, 240, 270, R, L"截屏", BLACK, LIGHTGRAY, _T("等线"));
                    botton(270, 420, 240, 270, R, L"退出", BLACK, LIGHTGRAY, _T("等线"));
                    title(100, 350, 110, 150, R, L"识别结果：    ", WHITE, NULL, _T("华文中宋"));
                    title(300, 350, 110, 150, R, L"剪刀", WHITE, NULL, _T("华文中宋"));
                }
                EndBatchDraw();
                count++;
                data += "" + count;
                data += ": 剪刀\n";
                if (FoutOrNot)
                {
                    if (RivalonOrNot)
                    {
                        text << count << "\t" << end - start << "ms\t" << "Player：" << "：剪刀\t" << "Rival：";
                        if (rival.GetResponse() == rock)
                            text << "石头\t" << rival.Judge(gesture) << endl;
                        else if (rival.GetResponse() == scissors)
                            text << "剪刀\t" << rival.Judge(gesture) << endl;
                        else if (rival.GetResponse() == paper)
                            text << " 布 \t" << rival.Judge(gesture) << endl;
                    }
                    else
                        text << count << "\t" << end - start << "\t石头" << endl;
                }
                if (1) gesture = null;
                break;
            case paper:
                BeginBatchDraw();
                if (RivalonOrNot)
                {
                    if (abs(timer1 - timer2) >= 3000 || gesture!=gesture2)
                    {
                        cleardevice();
                        putimage(0, 0, &img2);
                        rival.Spawn();
                        rival.Judge(gesture);
                        _stprintf(ThisCount, _T("%d"), rival.GetLose());
                        _stprintf(ThatCount, _T("%d"), rival.GetWin());
                        _stprintf(TotalCount, _T("%d"), rival.GetCount());
                        putimage(25, 25, &This);
                        putimage(825, 25, &That);
                        title(25, 75, 100, 130, R, name, WHITE, NULL, _T("华文中宋"));
                        title(825, 875, 100, 130, R, L"小A", WHITE, NULL, _T("华文中宋"));
                        textout(375, 425, 125, 175, R, ThisCount, WHITE, NULL, _T("华文中宋"));
                        textout(475, 525, 125, 175, R, ThatCount, WHITE, NULL, _T("华文中宋"));
                        title(175, 300, 125, 175, R, L"布", WHITE, NULL, _T("华文中宋"));
                        title(445, 455, 125, 175, R, L"：", WHITE, NULL, _T("华文中宋"));
                        if (rival.GetResponse() == rock)
                            title(525, 750, 125, 175, R, L"石头", WHITE, NULL, _T("华文中宋"));
                        else if (rival.GetResponse() == scissors)
                            title(525, 750, 125, 175, R, L"剪刀", WHITE, NULL, _T("华文中宋"));
                        else if (rival.GetResponse() == paper)
                            title(525, 750, 125, 175, R, L"布", WHITE, NULL, _T("华文中宋"));
                        botton(30, 180, 240, 270, R, L"截屏", BLACK, LIGHTGRAY, _T("等线"));
                        botton(270, 420, 240, 270, R, L"退出", BLACK, LIGHTGRAY, _T("等线"));
                        botton(480, 630, 240, 270, R, L"清零", BLACK, LIGHTGRAY, _T("等线"));
                        botton(720, 870, 240, 270, R, L"改名", BLACK, LIGHTGRAY, _T("等线"));
                        gesture2 = paper;
                    }
                    else
                        putText((TestOrNot ? framework : frametoshow), "Waiting for 3s...", Point(0, 0), FONT_HERSHEY_TRIPLEX, 0.8, Scalar(255, 200, 200), 2, (30, 144, 255));
                }
                else
                {
                    cleardevice();
                    putimage(0, 0, &img2);
                    title(125, 325, 30, 80, R, L"手势识别", WHITE, NULL, _T("华文中宋"));
                    botton(30, 180, 240, 270, R, L"截屏", BLACK, LIGHTGRAY, _T("等线"));
                    botton(270, 420, 240, 270, R, L"退出", BLACK, LIGHTGRAY, _T("等线"));
                    title(100, 350, 110, 150, R, L"识别结果：    ", WHITE, NULL, _T("华文中宋"));
                    title(300, 350, 110, 150, R, L"布 ", WHITE, NULL, _T("华文中宋"));
                }
                EndBatchDraw();
                count++;
                data += "" + count;
                data += ": 布\n";
                if (FoutOrNot)
                {
                    if (RivalonOrNot)
                    {
                        text << count << "\t" << end - start << "ms\t" << "Player：" << "：剪刀\t" << "Rival：";
                        if (rival.GetResponse() == rock)
                            text << "石头\t" << rival.Judge(gesture) << endl;
                        else if (rival.GetResponse() == scissors)
                            text << "剪刀\t" << rival.Judge(gesture) << endl;
                        else if (rival.GetResponse() == paper)
                            text << " 布 \t" << rival.Judge(gesture) << endl;
                    }
                    else
                        text << count << "\t" << end - start << "\t石头" << endl;
                }
                if (1) gesture = null;
                break;
                //default:
                //    BeginBatchDraw();
                //    if (RivalonOrNot)
                //    {
                //        cleardevice();
                //        putimage(0, 0, &img2);
                //        _stprintf(ThisCount, _T("%d"), rival.GetLose());
                //        _stprintf(ThatCount, _T("%d"), rival.GetWin());
                //        _stprintf(TotalCount, _T("%d"), rival.GetCount());
                //        putimage(25, 25, &This);
                //        putimage(825, 25, &That);
                //        title(25, 75, 100, 130, R, name, WHITE, NULL, _T("华文中宋"));
                //        title(825, 875, 100, 130, R, L"小A", WHITE, NULL, _T("华文中宋"));
                //        textout(375, 425, 125, 175, R, ThisCount, WHITE, NULL, _T("华文中宋"));
                //        textout(475, 525, 125, 175, R, ThatCount, WHITE, NULL, _T("华文中宋"));
                //        title(175, 300, 125, 175, R, L"未识别", WHITE, NULL, _T("华文中宋"));
                //        title(445, 455, 125, 175, R, L"：", WHITE, NULL, _T("华文中宋"));
                //        title(525, 750, 125, 175, R, L"等待中", WHITE, NULL, _T("华文中宋"));
                //        botton(30, 180, 240, 270, R, L"截屏", BLACK, LIGHTGRAY, _T("等线"));
                //        botton(270, 420, 240, 270, R, L"退出", BLACK, LIGHTGRAY, _T("等线"));
                //        botton(480, 630, 240, 270, R, L"清零", BLACK, LIGHTGRAY, _T("等线"));
                //        botton(720, 870, 240, 270, R, L"改名", BLACK, LIGHTGRAY, _T("等线"));
                //    }
                //    else
                //    {
                //        cleardevice();
                //        title(125, 325, 30, 80, R, L"手势识别", WHITE, NULL, _T("华文中宋"));
                //        botton(30, 180, 240, 270, R, L"截屏", BLACK, LIGHTGRAY, _T("等线"));
                //        botton(270, 420, 240, 270, R, L"退出", BLACK, LIGHTGRAY, _T("等线"));
                //        botton(100, 350, 110, 150, R, L"识别结果：    ", WHITE, NULL, _T("华文中宋"));
                //        botton(300, 350, 110, 150, R, L"未识别...", WHITE, NULL, _T("华文中宋"));
                //    }
                //    EndBatchDraw();
                //    break;
            }
            EndBatchDraw();


            if (judge)
            {
                switch (select)
                {
                case 1:
                    switch (screenshot % 10)
                    {
                    case 0:
                        imwrite("save01.png", (TestOrNot ? framework : frametoshow));
                        break;
                    case 1:
                        imwrite("save02.png", (TestOrNot ? framework : frametoshow));
                        break;
                    case 2:
                        imwrite("save03.png", (TestOrNot ? framework : frametoshow));
                        break;
                    case 3:
                        imwrite("save04.png", (TestOrNot ? framework : frametoshow));
                        break;
                    case 4:
                        imwrite("save05.png", (TestOrNot ? framework : frametoshow));
                        break;
                    case 5:
                        imwrite("save06.png", (TestOrNot ? framework : frametoshow));
                        break;
                    case 6:
                        imwrite("save07.png", (TestOrNot ? framework : frametoshow));
                        break;
                    case 7:
                        imwrite("save08.png", (TestOrNot ? framework : frametoshow));
                        break;
                    case 8:
                        imwrite("save09.png", (TestOrNot ? framework : frametoshow));
                        break;
                    case 9:
                        imwrite("save10.png", (TestOrNot ? framework : frametoshow));
                        break;
                    }
                    screenshot++;
                    select = 0;
                    break;
                case 2:
                    EndDetectingOrNot = false;
                    select = 0;
                    break;
                case 3:
                    if (FoutOrNot)
                    {
                        text << "WIN:" << rival.GetLose() << "\t" << "LOSE:" << rival.GetWin() << "\tTOTAL:" << rival.GetCount() << endl;
                        text << "WIN PERCENT" << (float)rival.GetLose() / rival.GetCount() << endl;
                    }
                    rival.Reset();
                    botton(375, 425, 125, 175, R, L"0", WHITE, NULL, _T("华文中宋"));
                    botton(475, 525, 125, 175, R, L"0", WHITE, NULL, _T("华文中宋"));
                    select = 0;
                    break;
                case 4:
                    InputBox(name, 30, L"起个好名字:)", L"输入用户名");
                    botton(25, 75, 100, 130, R, name, WHITE, NULL, _T("华文中宋"));
                    select = 0;
                    break;
                }
            }

            int key = waitKey(1);
            if (key == 27 || (judge && select == 2))
                EndDetectingOrNot = false;
        }
        closegraph;
        if (RivalonOrNot && FoutOrNot)
            text << "WIN:" << rival.GetLose() << "\t" << "LOSE:" << rival.GetWin() << "\tTOTAL:" << rival.GetCount() << endl;
        rival.Reset();
        destroyAllWindows();
    } while (select == -1);
    mciSendString(_T("close music2"), 0, 0, 0);
    text << endl;
    text.close();
    return 0;
}
//处理对象是名为framework的Mat类
//识别结果放入变量gesture中
//点击"开始"开始，“设置”选择模型
//背景颜色不能和皮肤颜色过于接近