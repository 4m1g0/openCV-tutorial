#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv )
{
    if ( argc != 3 )
    {
        printf("usage: Correlaciones <Image_Path> <pattern>\n");
        return -1;
    }

    Mat src, dst, pattern;
    src = imread( argv[1], 1 );
    pattern = imread( argv[2], 1 );

    if ( !src.data || !pattern.data )
    {
        printf("No image data \n");
        return -1;
    }
    
    namedWindow("Original", WINDOW_AUTOSIZE );
    imshow("Original", src);
    
    int iwidth = src.cols - pattern.cols + 1;
    int iheith = src.rows - pattern.rows + 1;
    
    int match_method = CV_TM_CCOEFF_NORMED;
    
    matchTemplate(src, pattern, dst, match_method);
    normalize(dst, dst, 0, 1, NORM_MINMAX, -1, Mat());
    
    double minVal, maxVal;
    Point minLoc, maxLoc;
    Point matchLoc;
    
    minMaxLoc(dst, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
    
    cout << "Min: " << minVal << " Max: " << maxVal << endl;
    
    if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
        matchLoc = minLoc;
    else
        matchLoc = maxLoc;
    
    // dibujamos el rectangulo en matchLoc
    rectangle(src, matchLoc, Point(matchLoc.x + pattern.cols, matchLoc.y + pattern.rows), Scalar(255, 0, 0), 4, 8, 0);
    rectangle(dst, matchLoc, Point(matchLoc.x + pattern.cols, matchLoc.y + pattern.rows), Scalar(255, 0, 0), 4, 8, 0);
    
    
    
    imwrite(strcat(argv[2], "-result.jpg"), src);
    imshow("pattern", pattern);
    imshow("src", src);
    //imshow("dst", dst);
    
    waitKey(0);

    return 0;
}
