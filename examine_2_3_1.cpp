#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("O:\\board.jpg"), dst, temp;
	namedWindow("ԭͼ");
	imshow("ԭͼ", img);

	//Ԥ����
	cvtColor(img, img, COLOR_BGR2GRAY);			//ת����ɫ�ռ�
	GaussianBlur(img, img, Size(5, 5), 0, 0);	//5*5�ں˸�˹�˲�ģ��
	Canny(img, temp, 122, 255);					//Canny��Ե���
	cvtColor(temp, dst, COLOR_GRAY2BGR);		//��ԭͼ��ɫ��

	//����任
	vector<Vec4f> plines;				//���ֱ�ߵ�
	Scalar color = Scalar(0, 0, 255);	// ���廭����ɫ
	HoughLinesP(temp, plines, 1, CV_PI / 180.0, 10, 0, 0);  //ʶ��ֱ�߲�����ֱ�ߵ�

	//���õ���ֱ�ߵ���ԭͼ�ϻ���
	for (size_t i = 0; i < plines.size(); i++) 
	{
		Vec4f hline = plines[i];
		line(dst, Point(hline[0], hline[1]), Point(hline[2], hline[3]), color, 2, LINE_AA);
	}
	namedWindow("����", WINDOW_AUTOSIZE);
	imshow("����", dst);

	waitKey(0);
	return 0;
}
