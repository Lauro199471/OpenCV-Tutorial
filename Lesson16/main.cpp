#include <iostream>
#include <opencv2/opencv.hpp>

// Purple 160-32-240(R-G-B)
#define purple_r 160
#define purple_g 32
#define purple_b 240

using namespace cv;
using namespace std;
int main( )
{
  Mat image;
  image = imread("../Lion.jpg", 1);  
  
  // Check for failure
  if (image.empty()) 
  {
    cout << "Could not open or find the image" << endl;
    cin.get(); //wait for any key press
    return -1;
  }
  
  namedWindow( "Display window", CV_WINDOW_AUTOSIZE );  
  imshow( "Display window", image );
  Mat gray;
  cvtColor(image, gray, COLOR_RGB2GRAY);//RGB image to gray 
  Canny(gray, gray, 255/3, 255, 3); // detect the edges in an .. image accepts gray scale image
  
  /// Find contours   
  vector< vector<Point> > contours;
  vector<Vec4i> hierarchy;
  //RNG rng(1234);//rng which is a random number generator
  findContours( gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
  
  /// Draw contours
  Mat drawing = Mat::zeros( gray.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
  {
    Scalar color = Scalar( purple_r, purple_g, purple_b );
    drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
  }     

  imshow( "Result window", drawing );
  waitKey(0);                                         
  return 0;
}
