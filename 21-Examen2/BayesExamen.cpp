#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define NCLASES 3

static Ptr<ml::TrainData> prepare_train_data(const Mat& data, const Mat& responses, int ntrain_samples)
{
	Mat sample_idx = Mat::zeros(1, ntrain_samples, CV_8U);

	int nvars = data.cols;
	Mat var_type(nvars + 1, 1, CV_8U);
	var_type.setTo(Scalar::all(ml::VAR_ORDERED));
	var_type.at<uchar>(nvars) = ml::VAR_CATEGORICAL;

	return ml::TrainData::create(data, ml::ROW_SAMPLE, responses,
		noArray(), sample_idx, noArray(), var_type);
}

Mat prepare_image(Mat image)
{
    Mat image_bin = Mat(image.size(), CV_8UC1, 1);
	cvtColor(image, image, CV_BGR2GRAY);
	threshold(image, image_bin, 78, 255, CV_THRESH_BINARY);
	bitwise_not(image_bin, image_bin);
	
	morphologyEx(image_bin, image_bin, CV_MOP_OPEN, Mat(), Point(-1, -1), 2);
    morphologyEx(image_bin, image_bin, CV_MOP_CLOSE, Mat(), Point(-1, -1), 2);
    return image_bin;
}

bool isExternalContour(Vec4i hierarchy)
{
    return hierarchy[3] == -1;
}

int findRelation(int relation[], int value, int count)
{
    for (int i = 0; i < count; i++)
        if (relation[i] == value)
            return i;
    
    return -1;
}

int main(int argc, char* argv[])
{
    Ptr<ml::NormalBayesClassifier> bayes = ml::NormalBayesClassifier::create();
    const char *nombre_clases[3] = { "Tornillo", "Tuerca", "Arandela" };
    
    if ( argc != 5 )
    {
        printf("usage: BayesExamen <train_tornillo> <train_tuerca> <train_arandela> <clasif_image>\n");
        return -1;
    }
    
    vector<vector<Point> > contours[NCLASES];
    vector<Vec4i> hierarchy[NCLASES];
    
    for (int clase = 0; clase < NCLASES; clase++)
    {
        Mat image = imread(argv[clase+1]);
		if (!image.data) {
			cout << "Error al cargar la imagen" << endl;
			return 1;
		}
		
		Mat image_bin = prepare_image(image);
		
		imshow("ventana", image_bin);
        waitKey(0);
        
        findContours(image_bin, contours[clase], hierarchy[clase], RETR_CCOMP, CV_CHAIN_APPROX_NONE);
        
        for (int i = 0; i < contours[clase].size(); i++)
		{
			Scalar color1(0, 0, 255);
			drawContours(image, contours[clase], i, color1, 2, 8, hierarchy[clase], 0, Point());
		}
		
		imshow("ventana", image);
        waitKey(0);
    }
    
    int count = 0, before = 0;
    for (int clase = 0; clase < NCLASES; clase++)
    {
        for (int i = 0; i < hierarchy[clase].size(); i++)
        {
            count += isExternalContour(hierarchy[clase][i]);
        }
        
        cout << "El numero de " << nombre_clases[clase] << "s es: " << count - before << endl;
        before = count;
    }
    
    cout << "El numero de objetos es: " << count << endl << endl;
    
    // Generate train data based on arc and area
    double perimetro, area;
    Mat train_data(count, 2, CV_32FC1);
    Mat response_data(count, 1, CV_32FC1);
    int k = 0;
    for (int clase = 0; clase < NCLASES; clase++)
    {
        int relation[contours[clase].size()]; // store relation between contour index and k
        for (int i = 0; i < contours[clase].size(); i++)
		{
		    if (isExternalContour(hierarchy[clase][i]))
		    {
		        area = contourArea(contours[clase][i], false);
			    perimetro = arcLength(contours[clase][i], 1);
			    
			    train_data.at<float>(k, 0) = perimetro;
			    train_data.at<float>(k, 1) = area;
			    response_data.at<float>(k) = clase;
			    
			    relation[i] = k;
			    k++;
		    }
		    else // es un perimetro interior, restamos este área
		    {
		        area = contourArea(contours[clase][i], false);
		        int parent = hierarchy[clase][i][3];
		        train_data.at<float>(relation[parent], 1) -= area;
		    }
		}
    }
    
    Ptr<ml::TrainData> tdata = prepare_train_data(train_data, response_data, count);
    bayes->train(tdata);
    
    // End of train phase
    // Load image to detect object
    Mat image = imread(argv[4], 1);
	if (!image.data) {
		cout << "Error al cargar la imagen" << endl;
		return 1;
    }
    
	Mat image_bin = prepare_image(image);
	
	vector<vector<Point> > contours2;
    vector<Vec4i> hierarchy2;
	findContours(image_bin, contours2, hierarchy2, RETR_CCOMP, CV_CHAIN_APPROX_NONE);
	
	count = 0;
	for (int i = 0; i < hierarchy2.size(); i++)
    {
        count += isExternalContour(hierarchy2[i]);
    }
    
    cout << "El numero de objetos detectados es: " << count << endl;
    
    Mat test_data(count, 2, CV_32FC1);
    int relation[count]; // store relation between contour index and k
    for (int i = 0; i < count; i++) relation[i] = -1; // initialize relation to avoid memory warning.
    k = 0;
    for (int i = 0; i < contours2.size(); i++)
    {
        if (isExternalContour(hierarchy2[i]))
	    {
	        area = contourArea(contours2[i], false);
		    perimetro = arcLength(contours2[i], 1);
		    
		    test_data.at<float>(k, 0) = perimetro;
		    test_data.at<float>(k, 1) = area;
		    
		    relation[k] = i;
		    k++;
	    }
	    else // es un perimetro interior, restamos este área
	    {
	        area = contourArea(contours2[i], false);
	        int parent = hierarchy2[i][3];
	        test_data.at<float>(findRelation(relation, parent, count), 1) -= area;
	    }
    }
    
    Mat clasif(count, 1, CV_32FC1);
    Mat result(1, 2, CV_32FC1);
    Mat imagen_color;
    int cantidad[NCLASES] = {0,0,0};
    for (int i = 0; i < count; i++)
    {
        result.at<float>(0, 0) = test_data.at<float>(i, 0);
		result.at<float>(0, 1) = test_data.at<float>(i, 1);

		clasif.at<float>(i) = bayes->predict(result);
		
		imagen_color = image.clone();
		Scalar color(0, 0, 255);
		drawContours(imagen_color, contours2, relation[i], color, 2);
		imshow("ventana", imagen_color);
		cout << "La pieza resaltada es un " << nombre_clases[(int)clasif.at<float>(i)] << endl;
		
		cantidad[(int)clasif.at<float>(i)]++;
		waitKey(0);
    }
    
    cout << endl << endl;
	
	for (int i = 0; i < 3; i++)
	    cout << nombre_clases[i] << "s: " << cantidad[i] << endl;
    
    return 0;
}

