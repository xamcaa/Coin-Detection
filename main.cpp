#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace  cv;

static const char* keys =
{
    "{ |  image   |         |  Source image }"
    "{ |  method  |  Hough  |  A method to work with }"
};

Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);
int counter = 0;

void thresh_callback(int, void* );

/** @function main */
int main(int argc, char** argv)
{
    cv::CommandLineParser parser( argc, argv, keys );
    // Parse and validate input parameters
    std::string image_file = parser.get<std::string>( "image" );
    std::string method = parser.get<std::string>( "method" );

//    Mat src, src_gray;
    
    /// Read the image
    std::cout << image_file << std::endl;
    src = imread( image_file );
    CV_Assert(!src.empty());
  
  /// Convert it to gray
  cvtColor( src, src_gray, CV_BGR2GRAY );

  //imshow( " ", src_gray );

  /// Reduce the noise so we avoid false circle detection
  GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2);


  Mat kernel;
  kernel = Mat::ones( 6, 6, CV_8UC1);
  kernel = kernel * 255;
  morphologyEx(src_gray, src_gray, MORPH_OPEN, kernel);
  
  thresh_callback( 0, 0 );

  std::cout<< "number of coins:\t" << counter << std::endl;
  
  /// Show your results
  imshow( "Hough Circle Transform Demo", src );
  imshow( "Gray scale", src_gray ); 

  waitKey(0);
  return 0;
}


void thresh_callback(int, void* )
{
  Mat threshold_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using Threshold
  threshold( src_gray, threshold_output, thresh, 255, THRESH_OTSU);

  /// Filling empty spots with Morph 

  imshow("tre", threshold_output);

  /// Find contours
  findContours( threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Find the rotated rectangles and ellipses for each contour
  vector<RotatedRect> minRect( contours.size() );
  vector<RotatedRect> minEllipse( contours.size() );
  int sizeofimage = src.size().height;
  for( int i = 0; i < contours.size(); i++ )
     {
         
         minRect[i] = minAreaRect( Mat(contours[i]));
         if ( contours[i].size() > 5 )
         { 
             double area = cv::contourArea( contours[i]);
             if ( ( area < sizeofimage * sizeofimage / 4 ) && ( area > 300 ) )
             {
                 minEllipse[i] = fitEllipse( Mat(contours[i]) );
                 counter++ ;
             }
         }
     }

  /// Draw contours + rotated rects + ellipses
  Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       // contour
       drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
       // ellipse
       ellipse( drawing, minEllipse[i], color, 2, 8 );
     }
  src_gray = drawing;
}