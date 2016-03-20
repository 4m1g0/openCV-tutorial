#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/opencv_modules.hpp>

using namespace std;
using namespace cv;

int main() {

	Mat image = imread("screw.jpg");
	
	if (!image.data) {
		cout << "Error!!\n";
		return 1;
	}
	imshow("Input Image", image);
	
	//Prepare the image for findContours
	cvtColor(image, image, CV_BGR2GRAY);
	threshold(image, image, 108, 255, CV_THRESH_BINARY);
	
	morphologyEx(image, image, CV_MOP_OPEN, Mat(), Point(-1, -1), 2);
	morphologyEx(image, image, CV_MOP_CLOSE, Mat(), Point(-1, -1), 2);

	//Find the contours
	vector<vector<Point> > contours;
	Mat contourOutput = image.clone();
	findContours(contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	//Draw the contours
	Mat contourImage(image.size(), CV_8UC3, Scalar(0, 0, 0));
	Scalar colors[3];
	colors[0] = Scalar(255, 0, 0);
	colors[1] = Scalar(0, 255, 0);
	colors[2] = Scalar(0, 0, 255);
	
	for (size_t idx = 0; idx < contours.size(); idx++)
			drawContours(contourImage, contours, idx, colors[idx % 3]);	
		
	imshow("Contours", contourImage);	
	
	waitKey(0);
	return 0;
}


