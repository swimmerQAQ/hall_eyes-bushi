#include <opencv2/opencv.hpp>
using namespace cv;
#include <iostream>
using namespace std;
#include <math.h>
#include "../mylib/mymath.hpp"
#include "../displace/displace.hpp"
Mat imgHSV; //frame transfer imghsv
Mat mask;	//for inrang after imghsv
Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
Mat medium;

int hmin = 0;
int hmax = 255;
int smin = 71;
int smax = 255;
int vmin = 186;
int vmax = 255;
vector<Point> kval(5); // store the K value
float distance(Point A, Point B)
{
	float bulf[2];
	bulf[0] = powf((A.x - B.x), 2);
	bulf[1] = powf((A.y - B.y), 2);
	return sqrtf(bulf[0] + bulf[1]);
}
void detect(Mat in_img, Mat origin)
{
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(in_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<vector<Point>> conPoly(contours.size()); //画点
	
	int radius[contours.size()] = {0};

	for (int i = 0; i < contours.size(); i++)
	{
		conPoly[i] = contours[i];

		for (int j = 0; j < contours[i].size(); j++)
		{
			if (conPoly[i][0].y >= contours[i][j].y) //min_up
			{
				conPoly[i][0].y = contours[i][j].y;
				conPoly[i][0].x = contours[i][j].x;
			}
			if (conPoly[i][1].y < contours[i][j].y) //max_down
			{
				conPoly[i][1].y = contours[i][j].y;
				conPoly[i][1].x = contours[i][j].x;
			}
		}
		cout << " the y_max is " << conPoly[i][0].y << " the y_min is " << conPoly[i][1].y << endl;
		//rectangle(img, conPoly[i][0], conPoly[i][1], Scalar(100, 255, 50),1);
		line(origin, conPoly[i][0], conPoly[i][1], Scalar(255, 255, 255), 2);
		//中点
		radius[i] = (conPoly[i][1].y - conPoly[i][0].y) / 2;
		conPoly[i][2].y = (conPoly[i][0].y + conPoly[i][1].y) / 2;
		conPoly[i][2].x = (conPoly[i][0].x + conPoly[i][1].x) / 2;
		cout << "radius = " << radius[i] << endl;
		line(origin, conPoly[i][0], conPoly[i][1], Scalar(255, 255, 255), 2);
		cout << " the y_max is " << conPoly[i][0].y << " the y_min is " << conPoly[i][1].y << endl;
	}
	///////////////////
	cout << " num obj " << contours.size() << endl;
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		for (int j = 0; j < contours.size(); j++)
		{
			if (j != i)
			{

				//第一个向量{k0x,k0y}_面向i的物体外沿
				//第二个向量{k1x,k1y}_面向两个物体一边的向量
				kval[0].x = conPoly[i][1].x - conPoly[i][0].x; //i1点——>i0点
				kval[0].y = conPoly[i][1].y - conPoly[i][0].y;
				kval[1].x = conPoly[i][0].x - conPoly[j][0].y; //i0点——>j0点
				kval[1].y = conPoly[i][0].y - conPoly[j][0].y;

				//kval[5].x = kval[0].x*kval[1].x + kval[0].y*kval[1].y ;
				//算出向量内积
				if (fabs(radius[j] - radius[i]) < 10)
				{

					/*
 						putText(origin,"ksc",conPoly[i][2], FONT_HERSHEY_SCRIPT_COMPLEX,1.5,Scalar(255,20,150),1);
 						putText(origin,"ksc",conPoly[j][2], FONT_HERSHEY_SCRIPT_COMPLEX,1.5,Scalar(255,255,0),1);
 						*/
					if (area > 500)
					{
						//cout <<"kval_5 = "<< fabs(kval[5].x) << endl;
						//cout << "sqrt = " << sqrt(kval[1].x*kval[1].x+ kval[1].y*kval[1].y) << endl;
						//line(origin, conPoly[i][0], conPoly[j][0], Scalar(20, 255, 255),2);
						//line(origin, conPoly[i][1], conPoly[j][1], Scalar(20, 255, 255),2);
						circle(origin, conPoly[j][2], radius[j], Scalar(255, 150, 100), 2);
						circle(origin, conPoly[i][2], radius[i], Scalar(255, 150, 255), 2);
						line(origin, conPoly[i][0], conPoly[j][1], Scalar(240, 32, 160), 2);
						line(origin, conPoly[i][1], conPoly[j][0], Scalar(240, 32, 160), 2);
						kval[2].x = (conPoly[i][2].x + conPoly[j][2].x) / 2;
						kval[2].y = (conPoly[i][2].y + conPoly[j][2].y) / 2;
						circle(origin, kval[2], 5, Scalar(0, 0, 255), FILLED);
						circle(origin, kval[2], 10, Scalar(0, 0, 255), 2);
						cout << j << "  &&&___j__&__i___&&&&&& " << i << endl;
					}
				}
			}
		}
	}

	//////////////////
}
int main()
{
	VideoCapture capture;
	Mat frame;
	string path = "../src/b1.avi";
	frame = capture.open(path);
	if (!capture.isOpened())
	{
		cout << " cannot open the vedio..." << endl;
		return -1;
	}
	namedWindow("Trackbars", 1);
	createTrackbar("Hue min ", "Trackbars", &hmin, 255);
	createTrackbar("Hue max ", "Trackbars", &hmax, 255);
	createTrackbar("sue min ", "Trackbars", &smin, 255);
	createTrackbar("sue max ", "Trackbars", &smax, 255);
	createTrackbar("vue min ", "Trackbars", &vmin, 255);
	createTrackbar("vue max ", "Trackbars", &vmax, 255);
	while (capture.read(frame))
	{
		cvtColor(frame, imgHSV, COLOR_BGR2HSV);
		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);

		imshow("window_1", mask);
		cout << "hmin=" << hmin << endl;
		cout << "hmax=" << hmax << endl;
		cout << "smin=" << smin << endl;
		cout << "smax=" << smax << endl;
		cout << "vmin=" << vmin << endl;
		cout << "vmax=" << vmax << endl;

		GaussianBlur(mask, imgBlur, Size(3, 3), 3, 0);
		Canny(imgBlur, imgCanny, 25, 75);
		//imshow("imgcanny",imgCanny);
		Mat kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
		dilate(imgBlur, imgDil, kernal);
		erode(imgDil, imgErode, kernal);

		imshow("imgerode", imgErode);
		//blur(imgErode, medium, Size(5,5), {-1,-1});
		//imshow("medium", medium);
		//erode(medium, medium, kernal);
		detect(imgErode, frame);
		imshow("detect", frame);
		if (waitKey(30) == 32)
		{
			if (waitKey(0) == 32)
			{
				break;
			}
		};
	}
	capture.release();
	return 0;
}
