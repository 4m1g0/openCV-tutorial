
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/opencv_modules.hpp>

//----------------------Clasificaci�n no supervisada

using namespace cv;
using namespace std;

int main()
{
	Mat imagen, imagen_bin, imagen_color;
	vector<vector<Point> > contours;

	int i = 0, clase, k = 0;
	double perimetro, area;

	imagen = imread("Clasif.jpg", 1);

	// creaci�n de imatrices para almacenar la imformaci�n
	Mat	test_data(10, 2, CV_32F);

	imagen_bin = Mat(imagen.size(), 8, 1);
	cvtColor(imagen, imagen, CV_BGR2GRAY);
	threshold(imagen, imagen_bin, 128, 255, CV_THRESH_BINARY);

	imagen_color = Mat(imagen.size(), CV_8UC1, 3);
	cvtColor(imagen, imagen_color, CV_GRAY2BGR);
	imshow("Ventana", imagen_color);

	findContours(imagen_bin, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

	cout << endl << "El numero total de piezas a clasificar es: " << contours.size() << endl;

	int clusterCount = 2;
	Mat labels;
	int attempts = 1;
	Mat centers;

	for (size_t idx = 0; idx < 10; idx++) // 10 primeros contornos para b�squeda autom�tica del centroide de cada clase
	{
		area = contourArea(contours[idx], false);
		perimetro = arcLength(contours[idx], 1);

		test_data.at<float>(idx, 0) = perimetro;
		test_data.at<float>(idx, 1) = area;

		cout << "Perimetro: [" << idx << "] " << perimetro << "   Area: [" << idx << "] " << area << endl;

		cvtColor(imagen, imagen_color, CV_GRAY2BGR);
		Scalar color_verde(0, 255, 0);
		drawContours(imagen_color, contours, idx, color_verde, 2);
		imshow("Ventana", imagen_color);
		waitKey(0);
	}

	kmeans(test_data, clusterCount, labels, TermCriteria(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 10, 1.0), attempts, KMEANS_RANDOM_CENTERS, centers);

	cout << "Cluster [" << labels.at<int>(0, 0) << "] is: Tuerca with center: (" << centers.at< float>(0, 0) << ", " << centers.at< float>(0, 1) << ")" << endl;
	cout << "Cluster [" << labels.at<int>(0, 1) << "] is: Tornillo with center: (" << centers.at< float>(1, 0) << ", " << centers.at< float>(1, 1) << ")" << endl << endl;

	waitKey(0);

	for (size_t idx = 10; idx < contours.size(); idx++) // Clasificaci�n de los 14 contornos restantes de la imagen
	{
		cvtColor(imagen, imagen_color, CV_GRAY2BGR);
		Scalar color_rojo(0, 0, 255);
		drawContours(imagen_color, contours, idx, color_rojo, 2);
		float d0 = 0, d1 = 0;

		d0 = sqrt((pow((arcLength(contours[idx], 1) - centers.at< float>(0, 0)), 2)) + (pow((contourArea(contours[idx], false) - centers.at< float>(0, 1)), 2)));
		d1 = sqrt((pow((arcLength(contours[idx], 1) - centers.at< float>(1, 0)), 2)) + (pow((contourArea(contours[idx], false) - centers.at< float>(1, 1)), 2)));

		cout << "La destancia desde el objeto al cluster[0] es: " << d0 << endl;
		cout << "La destancia desde el objeto al cluster[1] es: " << d1 << endl;

		imshow("Ventana", imagen_color);

		if (d1 < d0)
			cout << "La pieza resaltada es un Tornillo" << endl;
		else
			cout << "La pieza resaltada es un Tuerca" << endl << endl;

		waitKey(0);
	}
	return 0;
}
