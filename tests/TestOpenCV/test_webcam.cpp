#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;


VideoCapture * webCam_;

int main(int, char**)
{
    webCam_=new VideoCapture(0); // open the default camera
    int width=webCam_->get(CV_CAP_PROP_FRAME_WIDTH);
    int height=webCam_->get(CV_CAP_PROP_FRAME_HEIGHT);
    if(!webCam_->isOpened())  // check if we succeeded
    {
        cerr<<"Error openning the default camera"<<endl;
        return -1;
    }
    else
    {
        cout<<endl<<"Video ok, image is "<<width<<"x"<<height<<endl;
    }

    Mat frame;
    namedWindow("WebCam",1);
    cout<<endl<<"Window created"<<endl;
    for(;;)
    {
        if (webCam_->read(frame)) // get a new frame from camera
        {
            imshow("WebCam", frame);
            if(waitKey(30) >= 0) break;
        }
        else
        {
            cout<<"Error capturing the frame"<<endl;
        }
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
