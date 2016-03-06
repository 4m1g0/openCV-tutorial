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
    
    Mat src_gray;
    Mat grad;
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;
    
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    
    GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
    imshow("blur", src);
    
    // Gradiente x
    Sobel(src, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    imshow("x", abs_grad_x);
    
    // Gradiente Y
    Sobel(src, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);
    imshow("y", abs_grad_y);
    
    // Suma ponderada de gradientes
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    
    imshow("Sobel", grad);
    imwrite(strcat(argv[1], "-border.png"), grad);
    
    
    waitKey(0);

    return 0;
}
