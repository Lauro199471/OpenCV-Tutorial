// Simple Example of Detecting a Red Object
#include <opencv2/opencv.hpp> //calls the header files for each OpenCV module
#include <iostream>

#define USB_CAM_ID 0
#define running 1
using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
  //open the video file for reading
  VideoCapture cap(USB_CAM_ID);

  // if not success, exit program
  if (cap.isOpened() == false)
  {
    cout << "Cannot open the video file" << endl;
    return -1;
  }

  // create a window called "Control"
  namedWindow("Control", CV_WINDOW_AUTOSIZE);

 // HSV(HUE Saturation Value) max range 
 //Hue (0 - 179)
 //Saturation (0 - 255)
 //Value (0 - 255)
 int LowH = 0;
 int HighH = 179;

 int LowS = 0; 
 int HighS = 255;

 int LowV = 0;
 int HighV = 255;
 
 // Create trackbars(sliders) in "Control" window for HSV
 cvCreateTrackbar("LowH", "Control", &LowH, 179); 
 cvCreateTrackbar("HighH", "Control", &HighH, 179);

 cvCreateTrackbar("LowS", "Control", &LowS, 255); 
 cvCreateTrackbar("HighS", "Control", &HighS, 255);

 cvCreateTrackbar("LowV", "Control", &LowV, 255); 
 cvCreateTrackbar("HighV", "Control", &HighV, 255);

  while (running)
  {
    // Get Frame from USB Camera
    Mat frame_raw;
    bool bSuccess = cap.read(frame_raw); // read a new frame from camera and store it in 'frame_raw' matrix
    if (bSuccess == false)
    {
      cout << "Cannot read a frame from video stream" << endl;
      break;
    }
    
    // Convert 'frame_raw' to a HSV Matrix
    Mat frame_HSV;
    cvtColor(frame_raw,frame_HSV,COLOR_BGR2HSV);
    
    //-- Detect the object based on HSV Range Values
    Mat frameFilter;
    inRange(frame_HSV, 
            Scalar(LowH, LowS, LowV), 
            Scalar(HighH, HighS, HighV), 
            frameFilter);
    
    //morphological opening (remove small objects from the foreground)
    // erode = destory. The erosion makes the object in white smaller.
    // dilate = To resize something. The dilatation makes the object in white bigger.
    erode(frameFilter, frameFilter, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate(frameFilter, frameFilter, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
    
    //morphological closing (fill small holes in the foreground)
    dilate(frameFilter, frameFilter, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
    erode(frameFilter, frameFilter, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    
    //show the thresholded image
    imshow("Thresholded Image", frameFilter);
    
    //show the original image
    imshow("Original", frame_raw); 
    
    
    //wait for for 1 ms until any key is pressed.  
    //If the 'Esc' key is pressed, break the while loop.
    //If the any other key is pressed, continue the loop 
    //If any key is not pressed withing 1 ms, continue the loop
    if (waitKey(1) == 27)
    {
      cout << "Esc key is pressed by user. Stoppig the video" << endl;
      break;
    }
  }

  return 0;

}