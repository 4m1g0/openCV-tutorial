#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: Convoluciones <Image_Path>\n");
        return -1;
    }

    Mat src, dst;
    src = imread( argv[1], 1 );

    if ( !src.data )
    {
        printf("No image data \n");
        return -1;
    }
    
    namedWindow("Original", WINDOW_AUTOSIZE );
    imshow("Original", src);
    
    Mat kernel;
    int kernelSize = 3;
    kernel = Mat::ones(kernelSize, kernelSize, CV_32F) / (float)(kernelSize * kernelSize);
    cout << "kernel: \n" << kernel << endl;
    
    filter2D(src, dst, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
    
    namedWindow("dst3", WINDOW_AUTOSIZE );
    imshow("dst3", dst);
    
    kernelSize = 9;
    kernel = Mat::ones(kernelSize, kernelSize, CV_32F) / (float)(kernelSize * kernelSize);
    cout << "kernel: \n" << kernel << endl;
    
    filter2D(src, dst, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
    
    namedWindow("dst9", WINDOW_AUTOSIZE );
    imshow("dst9", dst);
    
    kernelSize = 15;
    kernel = Mat::ones(kernelSize, kernelSize, CV_32F) / (float)(kernelSize * kernelSize);
    cout << "kernel: \n" << kernel << endl;
    
    filter2D(src, dst, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
    
    namedWindow("dst15", WINDOW_AUTOSIZE );
    imshow("dst15", dst);
    
    waitKey(0);

    return 0;
}
