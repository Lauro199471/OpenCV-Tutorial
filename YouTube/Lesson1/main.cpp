// Device ID: xinput list
// Video Stream: ls -ltrh /dev/video*

#include <opencv2/opencv.hpp>
#include <iostream>


#define usbCam 0
#define running 1

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
  // Make 2 frames for orginal and grayScale
  Mat OG_frame;
  Mat GR_frame;
  
  //Open the default video camera
  VideoCapture cap(usbCam);

  // if not success, exit program
  if (cap.isOpened() == false)  
  {
    cout << "Cannot open the video camera" << endl;
    cin.get(); //wait for any key press
    return -1;
  } 
  
  while (running)
  {
    bool bSuccess = cap.read(OG_frame); // read a new frame from video 

    //Breaking the while loop if the frames cannot be captured
    if (bSuccess == false) 
    {
     cout << "Video camera is disconnected" << endl;
     cin.get(); //Wait for any key press
     break;
    }
    
    //Convert OG Frame to grayscale
    cvtColor(OG_frame,GR_frame,COLOR_BGR2GRAY);//RGB->Gray
    
    //show the frame in the created window
    imshow("Gray Frame", GR_frame);
    imshow("RGB Frame", OG_frame);
    
    //wait for for 10 ms until any key is pressed.  
    //If the 'Esc' key is pressed, break the while loop.
    //If the any other key is pressed, continue the loop 
    //If any key is not pressed withing 10 ms, continue the loop 
    if (waitKey(10) == 27)
    {
     cout << "Esc key is pressed by user. Stoppig the video" << endl;
     break;
    }
  }
  
  cap.release();
  destroyAllWindows();

  return 0;

}