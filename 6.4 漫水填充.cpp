
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


int main()
{
	Mat src = imread("1.jpg");
	imshow("��ԭʼͼ��", src);
	Rect comp;
	floodFill(src, Point(50, 300), Scalar(155, 255, 55), &comp, Scalar(20, 20, 20), Scalar(20, 20, 20));
	imshow("��Ч��ͼ��", src);
	waitKey(0);
	return 0;
}