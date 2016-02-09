#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }

    Mat src;
    src = imread( argv[1], 1 );

    if ( !src.data )
    {
        printf("No image data \n");
        return -1;
    }
    
    Mat inverseLut(1, 256, CV_8U);
    Mat sqrtLut(1, 256, CV_8U);
    Mat cubicLut(1, 256, CV_8U);
    
    for (int i = 0; i < 256; i++)
    {
        inverseLut.at<uchar>(i) = 255 - i;
        sqrtLut.at<uchar>(i) = pow((float)i * 255, (float)(1/2.0f));
        cubicLut.at<uchar>(i) = pow((float)i , 3.0f) / (255 * 255);
    }
    
    namedWindow("original", WINDOW_AUTOSIZE );
    imshow("original", src);
    
    Mat inverse;
    LUT(src, inverseLut, inverse);
    namedWindow("inversa", WINDOW_AUTOSIZE );
    imshow("inversa", inverse);
    imwrite("inversa.png", inverse);
    
    Mat sqrtImg;
    LUT(src, sqrtLut, sqrtImg);
    namedWindow("raiz cuadrada", WINDOW_AUTOSIZE );
    imshow("raiz cuadrada", sqrtImg);
    imwrite("sqrt.png", sqrtImg);
    
    Mat cubicImg;
    LUT(src, cubicLut, cubicImg);
    namedWindow("cubica", WINDOW_AUTOSIZE );
    imshow("cubica", cubicImg);
    imwrite("cubic.png", cubicImg);

    waitKey(0);

    return 0;
}
