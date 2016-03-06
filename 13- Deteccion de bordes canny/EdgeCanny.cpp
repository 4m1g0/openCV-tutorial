#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: EdgeGradient <Image_Path>\n");
        return -1;
    }

    Mat src;
    src = imread( argv[1], 1 );

    if ( !src.data )
    {
        printf("No image data \n");
        return -1;
    }
    
    namedWindow("Original", WINDOW_AUTOSIZE );
    imshow("Original", src);
    
    //GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
    
    Mat img_canny;
    
    Canny(src, img_canny, 25, 50, 3);
    imshow("canny25-50", img_canny);
    
    Canny(src, img_canny, 50, 75, 3);
    imshow("canny50-75", img_canny);
    
    Canny(src, img_canny, 100, 150, 3);
    imshow("canny100-150", img_canny);
    
    Canny(src, img_canny, 200, 250, 3);
    imshow("canny200-250", img_canny);
    
    Canny(src, img_canny, 300, 350, 3);
    imshow("canny300-350", img_canny);
    
    Canny(src, img_canny, 400, 450, 3);
    imshow("canny400-450", img_canny);
    
    waitKey(0);

    return 0;
}
