
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <iostream>

//using namespace std;
using namespace cv;

int main()
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;
	Mat src = imread("1.jpg");
	cvtColor(src, src, CV_BGR2GRAY);
	imshow("【原始图】", src);
	Sobel(src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("【x方向sobel】", abs_grad_x);
	Sobel(src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("【y方向sobel】", abs_grad_y);

	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("【效果图】", dst);
	waitKey(0);
	return 0;
}