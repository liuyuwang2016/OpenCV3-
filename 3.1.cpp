#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main()
{
	Mat girl = imread("girl.jpg");
	namedWindow("����ͼ");
	imshow("����ͼ", girl);
	Mat image = imread("dota.jpg");
	Mat logo = imread("dota_logo.jpg");
	namedWindow("ԭͼ");
	imshow("ԭͼ", image);
	namedWindow("logoͼ");
	imshow("logoͼ", logo);

	Mat imageROI;
	imageROI = image(Rect(800, 350, logo.cols, logo.rows));

	addWeighted(imageROI, 0.5, logo, 0.3, 0., imageROI);
	namedWindow("ԭ��ͼ+logo");
	imshow("����", image);


	waitKey();
	return 0;
}