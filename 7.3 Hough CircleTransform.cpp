
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>
using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("1.jpg");
	Mat midImage, dstImage;
	cvtColor(srcImage, midImage, CV_BGR2GRAY);
	GaussianBlur(midImage, dstImage, Size(9, 9), 2, 2);

	vector<Vec3f> circles;
	HoughCircles(dstImage, circles, HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		circle(dstImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		circle(dstImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);

	}
	imshow("<1>", dstImage);
	waitKey(0);
	return 0;
}