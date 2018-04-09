#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  // Read the image file
  cv::Mat image = cv::imread("Lion.jpg");
  cout << "image = \n" << image << "\n\n";
  
  // Check for failure
  if (image.empty()) 
  {
  cout << "Could not open or find the image" << endl;
  cin.get(); //wait for any key press
  return -1;
  }

  string windowName = "The Lion"; //Name of the window

  cv::namedWindow(windowName); // Create a window

  cv::imshow(windowName, image); // Show our image inside the created window.

  cv::waitKey(0); // Wait for any keystroke in the window

  cv::destroyWindow(windowName); //destroy the created window

  return 0;
}
