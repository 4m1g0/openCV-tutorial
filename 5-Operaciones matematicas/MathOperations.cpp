#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 3 )
    {
        printf("usage: MathOperations.out <Image_Path> <Image_Path>\n");
        return -1;
    }

    Mat image1, image2;
    image1 = imread( argv[1], 1 );
    image2 = imread( argv[2], 1 );

    if ( !image1.data || !image2.data )
    {
        printf("No image data \n");
        return -1;
    }
    
    namedWindow("iamge1", WINDOW_AUTOSIZE );
    imshow("iamge1", image1);
    
    namedWindow("iamge2", WINDOW_AUTOSIZE );
    imshow("iamge2", image2);
    
    Mat dst;
    add(image1, image2, dst, noArray(), -1);
    namedWindow("suma", WINDOW_AUTOSIZE );
    imshow("suma", dst);
    imwrite("suma.png", dst);
    
    subtract(image1, image2, dst, noArray(), -1);
    namedWindow("resta", WINDOW_AUTOSIZE );
    imshow("resta", dst);
    imwrite("resta.png", dst);
    
    multiply(image1, image2, dst, 1.0f, -1);
    namedWindow("multiplicacion", WINDOW_AUTOSIZE );
    imshow("multiplicacion", dst);
    imwrite("multiplicacion.png", dst);
    
    divide(image1, image2, dst, 1.0f, -1);
    namedWindow("division", WINDOW_AUTOSIZE );
    imshow("division", dst);
    imwrite("division.png", dst);

    waitKey(0);

    return 0;
}
