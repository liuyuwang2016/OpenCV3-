#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

bool MultiChannelBlending();

int main()
{
	system("color 9f");
	if (MultiChannelBlending())
	{
		cout << endl << "\n���гɹ����ó�������Ҫ��ͼ��~��";
	}
	waitKey(0);
	return 0;
}

bool MultiChannelBlending()
{
	Mat srcImage;
	Mat logoImage;
	vector<Mat> channels;
	Mat imageBlueChannel;


	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");
	if (!logoImage.data)
	{
		printf("��ȡlogoImage����~��\n");
		return false;
	}
	if (!srcImage.data)
	{
		printf("��ȡsrcImage����~��\n");
		return false;
	}
	split(srcImage, channels);
	imageBlueChannel = channels.at(0);
	addWeighted(imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0, imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));
	merge(channels, srcImage);
	namedWindow("<1>��Ϸԭ��+��ɫͨ��");
	imshow("<1>��Ϸԭ��+��ͨ��", srcImage);
	Mat imageGreenChannel;

	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");
	if (!logoImage.data)
	{
		printf("��ȡlogoImage����~��\n");
		return false;
	}
	if (!srcImage.data)
	{
		printf("��ȡsrcImage����~��\n");
		return false;
	}

	split(srcImage, channels);

	imageGreenChannel = channels.at(1);
	addWeighted(imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0, imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));
	merge(channels, srcImage);
	namedWindow("<2>��Ϸԭ��+��ɫͨ��");
	imshow("<2>��Ϸԭ��+ɫͨ��", srcImage);

	Mat imageRedChannel;
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");
	if (!logoImage.data)
	{
		printf("��ȡlogoImage����~��\n");
		return false;
	}
	if (!srcImage.data)
	{
		printf("��ȡsrcImage����~��\n");
		return false;
	}

	split(srcImage, channels);
	imageRedChannel = channels.at(2);
	addWeighted(imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0, imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));
	merge(channels, srcImage);
	namedWindow("<3>��Ϸԭ��+��ɫͨ��");
	imshow("<3>��Ϸԭ��+ɫͨ��", srcImage);

	return true;
}

