#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: %s <Image_Path>\n", argv[0]);
        return -1;
    }

    Mat RGB, HSV;
    RGB = imread( argv[1], 1 );

    if ( !RGB.data )
    {
        printf("No image data \n");
        return -1;
    }
    
    vector<Mat> bgr_planes;
    split(RGB, bgr_planes);
    
    cvtColor(RGB, HSV, CV_BGR2HSV);
    vector<Mat> hsv_planes;
    split(HSV, hsv_planes);
    
    namedWindow("RGB", WINDOW_AUTOSIZE );
    imshow("RGB", RGB);
    imwrite("RGB.png", RGB);
    
    namedWindow("HSV", WINDOW_AUTOSIZE );
    imshow("HSV", HSV);
    imwrite("HSV.png", HSV);
    
    namedWindow("B", WINDOW_AUTOSIZE );
    imshow("B", bgr_planes[0]);
    imwrite("B.png", bgr_planes[0]);
    
    namedWindow("G", WINDOW_AUTOSIZE );
    imshow("G", bgr_planes[1]);
    imwrite("G.png", bgr_planes[1]);
    
    namedWindow("R", WINDOW_AUTOSIZE );
    imshow("R", bgr_planes[2]);
    imwrite("R.png", bgr_planes[2]);
    
    namedWindow("H", WINDOW_AUTOSIZE );
    imshow("H", hsv_planes[0]);
    imwrite("H.png", hsv_planes[0]);
    
    namedWindow("S", WINDOW_AUTOSIZE );
    imshow("S", hsv_planes[1]);
    imwrite("S.png", hsv_planes[1]);
    
    namedWindow("V", WINDOW_AUTOSIZE );
    imshow("V", hsv_planes[2]);
    imwrite("V.png", hsv_planes[2]);

    waitKey(0);

    return 0;
}
