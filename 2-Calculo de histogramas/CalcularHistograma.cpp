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

    Mat src, dst;
    src = imread( argv[1], 1 );

    if ( !src.data )
    {
        printf("No image data \n");
        return -1;
    }
    
    vector<Mat> bgr_planes;
    split(src, bgr_planes);
    
    int histSize = 256;
    float range[] = {0, 256};
    const float* histRange = {range};
    
    bool uniform = true, accumulate = false;
    Mat b_hist, g_hist, r_hist;
    
    // Calculamos histogramas
    // imagen, nimages, channels, mask, hist, dims, size, ranges...
    calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);
    
    int hist_w = 512;
    int hist_h = 400;
    Mat histImg(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));
    
    // normalizar
    normalize(b_hist, b_hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());
    normalize(g_hist, g_hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());
    normalize(r_hist, r_hist, 0, histImg.rows, NORM_MINMAX, -1, Mat());
    
    int step = cvRound((double)hist_w / histSize);
    
    for (int i = 1; i < histSize; i++)
    {
        line(histImg, Point(step * (i -1), hist_h - cvRound(b_hist.at<float>(i - 1))),
                    Point(step * i, hist_h - cvRound(b_hist.at<float>(i))),
                    Scalar(255, 0, 0), 2, 8, 0);
        line(histImg, Point(step * (i -1), hist_h - cvRound(g_hist.at<float>(i - 1))),
                    Point(step * i, hist_h - cvRound(g_hist.at<float>(i))),
                    Scalar(0, 255, 0), 2, 8, 0);
        line(histImg, Point(step * (i -1), hist_h - cvRound(r_hist.at<float>(i - 1))),
                    Point(step * i, hist_h - cvRound(r_hist.at<float>(i))),
                    Scalar(0, 0, 255), 2, 8, 0);
    }

    namedWindow("Original", WINDOW_AUTOSIZE );
    imshow("Original", src);
    
    namedWindow("Histograma", WINDOW_AUTOSIZE );
    imshow("Histograma", histImg);
    
    imwrite("histograma.png", histImg);

    waitKey(0);

    return 0;
}
