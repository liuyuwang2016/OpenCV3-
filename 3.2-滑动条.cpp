#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

#define WINDOW_NAME "[���Ի��ʾ��]"

const int g_nMaxAlphaValue = 100;
int g_nAlphaValueSlider;
double g_dAlphaValue;
double g_dBetaValue;

Mat g_srcImage1;
Mat g_srcImage2;
Mat g_dstImage;

void on_Trackbar(int, void*)
{
	g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;
	g_dBetaValue = (1.0 - g_dAlphaValue);

	addWeighted(g_srcImage1, g_dAlphaValue, g_srcImage2, g_dBetaValue, 0.0, g_dstImage);
	imshow(WINDOW_NAME, g_dstImage);
}

int main(int argc, char** argv)
{
	g_srcImage1 = imread("1.jpg");
	g_srcImage2 = imread("2.jpg");
	if (!g_srcImage1.data)
	{
		printf("��ȡ��һ��ͼƬ������ȷ���Ƿ���ͼƬ����~��\n");
		return -1;
	}
	g_nAlphaValueSlider = 70;
	namedWindow(WINDOW_NAME, 1);

	char TrackbarName[50];
	sprintf(TrackbarName, "͸��ֵ%d", g_nMaxAlphaValue);

	createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);
	on_Trackbar(g_nAlphaValueSlider, 0);
	waitKey(0);
	return 0;
}