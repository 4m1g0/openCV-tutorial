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

    Mat image;
    image = imread( argv[1], 1 );

    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    
    for (int i = image.rows / 4; i < 3 * image.rows / 4; i++)
        for (int j = image.cols / 4; j < 3 * image.cols / 4; j++)
            image.at<Vec3b>(Point(i, j)) = Vec3b(0, 0, 0);
    
    
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    
    imwrite("resultado.png", image);

    waitKey(0);

    return 0;
}
