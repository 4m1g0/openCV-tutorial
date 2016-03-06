#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int contraste(Mat img);
int enfoque(Mat img);

int main(int argc, char** argv )
{
    if ( argc != 4 )
    {
        printf("usage: CalidadImagen <Image1> <Image2> <Image3>\n");
        return -1;
    }

    Mat img1, img2, img3;
    img1 = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
    img2 = imread( argv[2], CV_LOAD_IMAGE_GRAYSCALE );
    img3 = imread( argv[3], CV_LOAD_IMAGE_GRAYSCALE );

    if ( !img1.data || !img2.data || !img3.data )
    {
        printf("No image data \n");
        return -1;
    }
    
    namedWindow("img1", WINDOW_AUTOSIZE );
    imshow("img1", img1);
    namedWindow("img2", WINDOW_AUTOSIZE );
    imshow("img2", img2);
    namedWindow("img3", WINDOW_AUTOSIZE );
    imshow("img3", img3);
    
    
    cout << "Contraste imagen1: " << contraste(img1) << '%' << endl;
    cout << "Contraste imagen2: " << contraste(img2) << '%' << endl;
    cout << "Contraste imagen3: " << contraste(img3) << '%' << endl;
    
    cout << endl;
    
    cout << "Enfoque imagen1: " << enfoque(img1) << '%' << endl;
    cout << "Enfoque imagen2: " << enfoque(img2) << '%' << endl;
    cout << "Enfoque imagen3: " << enfoque(img3) << '%' << endl;
    
    waitKey(0);

    return 0;
}

int contraste(Mat img)
{
    Mat equaliz_img, diff;
    
    equalizeHist(img, equaliz_img);
    
    subtract(img, equaliz_img, diff, noArray(), -1);
    return 100 - sum(diff)[0] / (float)(diff.rows * diff.cols) * 0.3921f;
}

int enfoque(Mat img)
{
    Mat grad_x, grad_y, abs_grad_x, abs_grad_y, grad, diff;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    
    // Gradiente x
    Sobel(img, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);
    
    // Gradiente Y
    Sobel(img, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);
    
    // Suma ponderada de gradientes
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
    diff = grad / 255;
    return sum(grad)[0] / (float)(diff.rows * diff.cols) * 0.3921f;
}
