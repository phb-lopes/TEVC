#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;

int qnt_imagens_chaves = 67;
double criterio = 0.03;
int matchs = 10;

int main( int argc, char** argv ){
	Mat img_matches;
	vector<Mat> images;
	vector<Mat> bd; 
	int i,j,k;
	int inicio = 1070,fim = 500;

	// Leitura das imagens analisadas
  	for (i = inicio; i < (inicio + fim) ; i++){
  		String name = format("imagens/image_0/00%d.png", i);
	    Mat img = imread(name);
	    // Checagem pra ver se ta vazio
	    if ( img.empty ()){      
	        printf("Empty - %d!!\n",i);
	        continue;
	    }
	    images.push_back(img);
  	}

  	// Leitura das placas para realizar os matchs
  	for (i = 0; i < qnt_imagens_chaves ; i++){
  		String name = format("midia/%d.png", i);
	    Mat img1 = imread(name);
	    // Checagem pra ver se ta vazio
	    if ( img1.empty ()){      
	        printf("Empty - %d!!\n",i);
	        continue;
	    }
	    bd.push_back(img1);
  	}

  // 	for (i = 0; i < fim ; i++){
		// imshow("Original",images[i]);
		// waitKey(80);
  // 	}
  // 	for (i = 0; i < 4 ; i++){
		// imshow("Placas",bd[i]);
		// waitKey(1000);
  // 	}


	for (i = 0; i < fim; i++){

		// Construir uma área específica para a análise
				//x,   y, largura, altura
		Rect Rec(700, 0, 300, 300);
   	    rectangle(images[i], Rec, Scalar(255), 1, 8, 0);
 		Mat Roi = images[i](Rec);

		imshow("Video Original",images[i]);
		waitKey(1);

 		//-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
        int minHessian = 400;
        Ptr<SURF> detector = SURF::create();
        detector->setHessianThreshold(minHessian);
        std::vector<KeyPoint> keypoints_1, keypoints_2;
        Mat descriptors_1, descriptors_2;
        detector->detectAndCompute( Roi, Mat(), keypoints_1, descriptors_1 );

        // Este for Analisa o frame do video atual com o banco de imagens
        for(j = 0 ;j < qnt_imagens_chaves; j++){
	        detector->detectAndCompute( bd[j], Mat(), keypoints_2, descriptors_2 );
	        //-- Step 2: Matching descriptor vectors using FLANN matcher
	        FlannBasedMatcher matcher;
	        std::vector< DMatch > matches;
	        matcher.match( descriptors_1, descriptors_2, matches );
	        double max_dist = 0; double min_dist = criterio;
	        // double max_dist = 0; double min_dist = 100;
	        //-- Quick calculation of max and min distances between keypoints
	        for( k = 0; k < descriptors_1.rows; k++ ){ 
	            double dist = matches[k].distance;
	            if( dist < min_dist ) min_dist = dist;
	            if( dist > max_dist ) max_dist = dist;
	        }

	        std::vector< DMatch > good_matches;
	        for(k = 0; k < descriptors_1.rows; k++ ){ 
	            if( matches[k].distance <= max(2*min_dist, 0.05) ){
	            	good_matches.push_back( matches[k]); 
	            }
	        }

	        // Se o numero de matchs for aceitável, ele mostra na tela o match
	        if(good_matches.size() > matchs){
	        	//-- Draw only "good" matches
	        	drawMatches( Roi, keypoints_1, bd[j], keypoints_2,
	            	good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
	            	vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

	        	imshow("Match", img_matches);
	        	
	        	waitKey(5);	
	        }
        }
    }
	return 0;
}
