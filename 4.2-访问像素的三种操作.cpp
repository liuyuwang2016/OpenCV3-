#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void colorReduce(Mat& inputImage, Mat& outputImage, int div);

int main()
{
	Mat srcImage = imread("1.jpg");
	imshow("源图像", srcImage);

	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());

	double time0 = static_cast<double>(getTickCount());
	colorReduce(srcImage, dstImage, 32);
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "此方法运行时间为：" << time0 << "秒" << endl;
	imshow("效果图", dstImage);
	waitKey();
}

//1：指针访问
//void colorReduce(Mat& inputImage, Mat& outputImage, int div)
//{
//	outputImage = inputImage.clone();
//	int rowNumber = outputImage.rows;
//	int colNumber = outputImage.cols* outputImage.channels();
//	for (int i = 0; i < rowNumber; i++)
//	{
//		uchar* data = outputImage.ptr<uchar>(i);
//		for (int j = 0; j < colNumber; j++){
//			data[j] = data[j] / div*div /*+ div / 2*/;
//		}
//	}
//}

////2：迭代器操作
//void colorReduce(Mat& inputImage, Mat& outputImage, int div)
//{
//	outputImage = inputImage.clone();
//	Mat_<Vec3b>::iterator it = outputImage.begin<Vec3b>();
//	Mat_<Vec3b>::iterator itend = outputImage.end<Vec3b>();
//	for (; it != itend; ++it)
//	{
//		(*it)[0] = (*it)[0] / div*div + div / 2;
//		(*it)[1] = (*it)[1] / div*div + div / 2;
//		(*it)[2] = (*it)[2] / div*div + div / 2;
//	}
//}

//动态地址计算
void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	outputImage = inputImage.clone();
	int rowNumber = outputImage.rows;
	int colNumber = outputImage.cols;
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < colNumber; j++)
		{
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div*div + div / 2;
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div*div + div / 2;
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div*div + div / 2;
		}
	}
}