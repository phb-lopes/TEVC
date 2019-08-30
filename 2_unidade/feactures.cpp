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
void readme();

int main( int argc, char** argv ){
      int cont = 0, maior, correto = 100;
      VideoCapture vcap;
      Mat img_1, edge, draw;
      Mat img_2 = imread("Livro_1.jpg");
      string info;

      if(!vcap.open("http://192.168.1.10:8080/video?x.mjpeg")) {
            std::cout << "Error opening video stream or file" << std::endl;
            return -1;
      }
      for(;;){
          if(!vcap.read(img_1)) {
                    std::cout << "No frame" << std::endl;
                    cv::waitKey();
          }
          cv::imshow("Output Window", img_1);
          if(cv::waitKey(1) >= 0){
            imwrite( "Prova.jpg", img_1 );  
            break;
          }
      }
      cvtColor(img_1,img_1,COLOR_RGB2GRAY);
      for(int j=0;j<5;j++){

          switch(j){
            case 0:
              img_2 = imread("Livro_1.jpg");
              break;
            case 1:
              img_2 = imread("Livro_2.jpg");
              break;
            case 2:
              img_2 = imread("Livro_3.jpg");
              break;
            case 3:
              img_2 = imread("Livro_4.jpg");
              break;
            case 4:
              img_2 = imread("Livro_5.jpg");
              break;
            default:
              break;
          }
          cvtColor(img_2,img_2,cv::COLOR_RGB2GRAY);
        if( !img_1.data || !img_2.data ){
            std::cout<< " --(!) Error reading images " << std::endl; return -1; 
        }

        //-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
        int minHessian = 400;
        Ptr<SURF> detector = SURF::create();
        detector->setHessianThreshold(minHessian);
        std::vector<KeyPoint> keypoints_1, keypoints_2;
        Mat descriptors_1, descriptors_2;
        detector->detectAndCompute( img_1, Mat(), keypoints_1, descriptors_1 );
        detector->detectAndCompute( img_2, Mat(), keypoints_2, descriptors_2 );
        //-- Step 2: Matching descriptor vectors using FLANN matcher
        FlannBasedMatcher matcher;
        std::vector< DMatch > matches;
        matcher.match( descriptors_1, descriptors_2, matches );
        double max_dist = 0; double min_dist = 100;
        //-- Quick calculation of max and min distances between keypoints
        for( int i = 0; i < descriptors_1.rows; i++ ){ 
            double dist = matches[i].distance;
            if( dist < min_dist ) min_dist = dist;
            if( dist > max_dist ) max_dist = dist;
        }

        std::vector< DMatch > good_matches;
        for( int i = 0; i < descriptors_1.rows; i++ ){ 
            if( matches[i].distance <= max(0.02*min_dist, 0.05) ){
              good_matches.push_back( matches[i]); 
            }

        }

        //-- Draw only "good" matches
        Mat img_matches;
        drawMatches( img_1, keypoints_1, img_2, keypoints_2,
                     good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                     vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
        //-- Show detected matches
        //imshow( "Good Matches", img_matches );

        if(!j){
            correto = j;
            maior = (int)good_matches.size();
        }
        cont = (int)good_matches.size();
        if(cont > maior){
            correto = j;
            maior = cont;
        }
      }
       switch(correto){
          case 0:
            img_2 = imread("Livro_1.jpg");
            printf("Metodologia de pesquisa científica na pratica\n");
            printf("Autor: Jose Guilherme Silva Vieira\n");
            printf("Data da primeira publicação: 2010\n");
            printf("Quantidade de páginas: 152\n");
            break;
          case 1:
            img_2 = imread("Livro_2.jpg");
            printf("Nome: Trabalho da Mulher\n");
            printf("Autor: Georgenor de Sousa Franco Filho\n");
            printf("Data da primeira publicação: 2009\n");
            printf("Quantidade de páginas: 294\n");
            break;
          case 2:
            img_2 = imread("Livro_3.jpg");
            printf("O Poder das suas palavras\n");
            printf("Autor: Billy Joe Daugherty\n");
            printf("Data da primeira publicação: 2004\n");
            printf("Quantidade de páginas: 118\n");
            break;
          case 3:
            printf("Nome: O Principe\n");
            printf("Autor: Nicolau Maquiavel\n");
            printf("Data da primeira publicação: 1532\n");
            printf("Quantidade de páginas: 135\n");
            img_2 = imread("Livro_4.jpg");
            break;
          case 4:
            img_2 = imread("Livro_5.jpg");
            printf("Apocalipse\n");
            printf("Autor: Stanley M. Horton\n");
            printf("Data da primeira publicação: 1991\n");
            printf("Quantidade de páginas: 334\n");
            break;
          default:
            break;
        }
        
        cvtColor(img_2,img_2,cv::COLOR_RGB2GRAY);
        
        if( !img_1.data || !img_2.data ){
            std::cout<< " --(!) Error reading images " << std::endl; return -1; 
        }
        //-- Step 1: Detect the keypoints using SURF Detector, compute the descriptors
        int minHessian = 400;
        Ptr<SURF> detector = SURF::create();
        detector->setHessianThreshold(minHessian);
        std::vector<KeyPoint> keypoints_1, keypoints_2;
        Mat descriptors_1, descriptors_2;
        detector->detectAndCompute( img_1, Mat(), keypoints_1, descriptors_1 );
        detector->detectAndCompute( img_2, Mat(), keypoints_2, descriptors_2 );
        //-- Step 2: Matching descriptor vectors using FLANN matcher
        FlannBasedMatcher matcher;
        std::vector< DMatch > matches;
        matcher.match( descriptors_1, descriptors_2, matches );
        double max_dist = 0; double min_dist = 100;
        //-- Quick calculation of max and min distances between keypoints
        for( int i = 0; i < descriptors_1.rows; i++ ){ 
            double dist = matches[i].distance;
            if( dist < min_dist ) min_dist = dist;
            if( dist > max_dist ) max_dist = dist;
        }
     
        std::vector< DMatch > good_matches;
        for( int i = 0; i < descriptors_1.rows; i++ ){ 
            if( matches[i].distance <= max(0.02*min_dist, 0.05) ){
              good_matches.push_back( matches[i]); 
            }

        }

        //-- Draw only "good" matches
        Mat img_matches;
        drawMatches( img_1, keypoints_1, img_2, keypoints_2,
                     good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                     vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
        //-- Show detected matches
        cont = (int)good_matches.size();
        imshow( "Good Matches", img_matches );
        waitKey(0);

      return 0;
}

void readme(){ 
  std::cout << " Usage: ./SURF_FlannMatcher <img1> <img2>" << std::endl; 
}