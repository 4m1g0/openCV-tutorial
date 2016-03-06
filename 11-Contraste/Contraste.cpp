#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	//Nombre de la imagen que se va a cargar
	char NombreImagen[] = "ivvi_low_contrast.jpg";
	Mat original_img, equaliz_img;

	//Cargamos la imagen y se comprueba que lo ha hecho correctamente
	original_img = cv::imread(NombreImagen, CV_LOAD_IMAGE_GRAYSCALE);
	if (!original_img.data) {
		cout << "Error al cargar la imagen: " << NombreImagen << endl;
		exit(1);
	}

	//Variables para el histograma
	int histSize = 256;
	/// el rango del nivel del gris 0-255
	float range[] = { 0, 256 };
	const float* histRange = { range };

	/// imagen del histograma
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	Mat equalizedHistImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	//calcular el histograma
	Mat original_hist, normalized_hist, equalized_hist, equalized_normalized_hist;
	calcHist(&original_img, 1, 0, Mat(), original_hist, 1, &histSize, &histRange, true, false);

	// Mostrar los valores del histograma de la imagen original

	cout << "Original histogram" << endl;
	for (int h = 0; h < histSize; h++)
	{
		float binVal = original_hist.at<float>(h);
		cout << " " << binVal;
	}
	cout << endl;

	/// Normalizar el resultado a [ 0, histImage.rows ]
	normalize(original_hist, normalized_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	// Mostrar los valores
	cout << "Normalized histogram" << endl;
	for (int h = 0; h < histSize; h++)
	{
		float binVal = normalized_hist.at<float>(h);
		cout << " " << binVal;
	}
	cout << endl;

	// Equalize histogram from a grayscale image	
	equalizeHist(original_img, equaliz_img);
	calcHist(&equaliz_img, 1, 0, Mat(), equalized_hist, 1, &histSize, &histRange, true, false);

	// Mostrar los valores
	cout << "Equalized histogram" << endl;
	for (int h = 0; h < histSize; h++)
	{
		float binVal = equalized_hist.at<float>(h);
		cout << " " << binVal;
	}
	cout << endl;

	// Normalizar el histograma ecualizado
	normalize(equalized_hist, equalized_normalized_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	// Mostrar los valores
	cout << "Equalized normalized histogram" << endl;
	for (int h = 0; h < histSize; h++)
	{
		float binVal = equalized_normalized_hist.at<float>(h);
		cout << " " << binVal;
	}
	cout << endl;

	/// dibujar los histogramas
	for (int i = 1; i < histSize; i++)
	{
		//	Line of width 2 (bin_w = 512 width / 256 gray scale values) filled
		line(histImage,
			Point(bin_w*(i), hist_w),
			Point(bin_w*(i), hist_h - cvRound(normalized_hist.at<float>(i))),
			Scalar(255, 0, 0), bin_w, 8, 0);

		line(equalizedHistImage,
			Point(bin_w*(i), hist_w),
			Point(bin_w*(i), hist_h - cvRound(equalized_normalized_hist.at<float>(i))),
			Scalar(0, 255, 0), bin_w, 8, 0);
	}

	//Mostrar las imagens
	namedWindow("Original picture", CV_WINDOW_AUTOSIZE);
	namedWindow("Equalized picture", CV_WINDOW_AUTOSIZE);
	namedWindow("Original histogram", CV_WINDOW_AUTOSIZE);
	namedWindow("Equalized histogram", CV_WINDOW_AUTOSIZE);

	imshow("Original picture", original_img);
	imshow("Equalized picture", equaliz_img);
	imshow("Original histogram", histImage);
	imshow("Equalized histogram", equalizedHistImage);

	waitKey(0);
	return 0;
}
