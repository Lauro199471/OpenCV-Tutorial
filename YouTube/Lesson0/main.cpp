#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  // Read the image file
  // Read as in Gray Scale
  cv::Mat image = cv::imread("../Lion.jpg",cv::IMREAD_GRAYSCALE); 

  cout << "image = \n" << image << "\n\n";
  
  // Check for failure
  if (image.empty()) 
  {
    cout << "Could not open or find the image" << endl;
    cin.get(); //wait for any key press
    return -1;
  }
  // Save image as gray
  cv::imwrite("../GrayLion.jpg",image);
  
  cv::imshow("The Lion", image); // Show our image inside the created window.
  cv::waitKey(0); // Wait for any keystroke in the window
  return 0;
}
