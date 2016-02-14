#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    Mat img1 = Mat::zeros(Size(400, 200), CV_8UC1);
    Mat img2 = Mat::zeros(Size(400, 200), CV_8UC1);
    
    img1(Range(0, img1.rows), Range(0, img1.cols / 2)) = 255;
    imshow("img1", img1);
    imwrite("img1.png", img1);
    img2(Range(100, 150), Range(150, 350)) = 255;
    imshow("img2", img2);
    imwrite("img2.png", img2);
    
    Mat dst;
    bitwise_and(img1, img2, dst);
    imshow("and", dst);
    imwrite("and.png", dst);
    
    bitwise_or(img1, img2, dst);
    imshow("or", dst);
    imwrite("or.png", dst);
    
    bitwise_xor(img1, img2, dst);
    imshow("xor", dst);
    imwrite("xor.png", dst);
    
    bitwise_not(img1, dst);
    imshow("not", dst);
    imwrite("not.png", dst);

    waitKey(0);

    return 0;
}
