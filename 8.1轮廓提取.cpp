#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
	Mat srcImage = imread("1.jpg", 0);
	imshow("ԭʼͼ", srcImage);
	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);
	srcImage = srcImage > 119;
	imshow("ȥ��ֵ֮���ԭʼͼ", srcImage);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(srcImage, contours, hierarchy, RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	int index = 0;
	for (; index >= 0; index = hierarchy[index][0])
	{
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);
	}
	imshow("����ͼ", dstImage);
	waitKey(0);
	return 0;
}