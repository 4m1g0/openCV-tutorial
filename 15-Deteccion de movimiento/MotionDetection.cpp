#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/opencv_modules.hpp>


using namespace std;
using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: MotionDetection <Video>\n");
        return -1;
    }

    Mat frame, back, fore, dest;
    VideoCapture cap(argv[1]);
    Ptr<BackgroundSubtractorMOG2> bg = createBackgroundSubtractorMOG2(500, 100, true);

	cv::namedWindow("Frame");
	cv::namedWindow("Background");
	cv::namedWindow("Foreground");
	waitKey(0);
    for (;;)
    {
        cap >> frame;
		if (!frame.data)
		{
			cout << "Error al cargar el frame.\n";
			exit(1);
		}

		bg->setNMixtures(5);
		bg->apply(frame, fore);
		bg->getBackgroundImage(back);

		erode(fore, fore, Mat());
		dilate(fore, fore, Mat());
		cvtColor(fore, fore, CV_GRAY2BGR);
		bitwise_and(frame, fore, dest);

		imshow("Frame", frame);
		imshow("Background", back);
		imshow("Foreground", dest);
		if (waitKey(100) >= 0) break;
    }
    waitKey(0);
    return 0;
}
