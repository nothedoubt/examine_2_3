#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("O:\\board.jpg"), dst, temp;
	namedWindow("原图");
	imshow("原图", img);

	//预处理
	cvtColor(img, img, COLOR_BGR2GRAY);			//转换颜色空间
	GaussianBlur(img, img, Size(5, 5), 0, 0);	//5*5内核高斯滤波模糊
	Canny(img, temp, 122, 255);					//Canny边缘检测
	cvtColor(temp, dst, COLOR_GRAY2BGR);		//还原图像色彩

	//霍夫变换
	vector<Vec4f> plines;				//存放直线点
	Scalar color = Scalar(0, 0, 255);	// 定义画线颜色
	HoughLinesP(temp, plines, 1, CV_PI / 180.0, 10, 0, 0);  //识别直线并储存直线点

	//将得到的直线点在原图上画出
	for (size_t i = 0; i < plines.size(); i++) 
	{
		Vec4f hline = plines[i];
		line(dst, Point(hline[0], hline[1]), Point(hline[2], hline[3]), color, 2, LINE_AA);
	}
	namedWindow("棋盘", WINDOW_AUTOSIZE);
	imshow("棋盘", dst);

	waitKey(0);
	return 0;
}
