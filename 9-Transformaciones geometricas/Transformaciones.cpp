#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: Transformaciones <Image_Path>\n");
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
    
    // Scale
    resize(src, dst, Size(0,0), 0.5, 0.5, INTER_LINEAR);
    imshow("scale", dst);
    imwrite("scale.png", dst);
    
    //translation
    dst = Mat::zeros(src.size(), src.type());
    src(Rect(100, 100, src.cols - 100, src.rows - 100)).copyTo(dst(Rect(0, 0, src.cols - 100, src.rows - 100)));
    imshow("translate", dst);
    imwrite("translate.png", dst);
    
    // rotate
    int len = max(src.cols, src.rows);
    double angle = 60;
    Point2f pt(len / 2.0, len / 2.0);
    Mat r = getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(src, dst, r, Size(len, len));
    imshow("rotate", dst);
    imwrite("rotate.png", dst);
    
    flip(src, dst, 1);
    imshow("reflection", dst);
    imwrite("reflection.png", dst);
    
    waitKey(0);

    return 0;
}
