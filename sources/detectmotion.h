#ifndef DETECTMOTION_H
#define DETECTMOTION_H

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <QLabel>
#include <QImage>

using namespace cv;


// description blabla
// @autor RaphaelChevasson
// using detection code from Simon Mure
class DetectMotion
{
public:
    float dX = 0, dY = 0;
    DetectMotion();
    void computeDetection();

    static void init(QLabel *pCameraLabel);
    static void displayImage();

private:
    int frameWidth=320;
    int frameHeight=240;
    int subImageWidth=100;
    int subImageHeight=100;
    int templateWidth=25;
    int templateHeight=25;

    VideoCapture * webCam_;
    Rect workingRect;
    Rect templateRect;
    Point workingCenter;
    Mat frame1,frame2,frameRect1,frameRect2;
    Mat resultImage;    // to store the matchTemplate result

    static QLabel *pCameraDisplay;
    static QImage *pImageToDisplay;

    void updateImage(Mat img);
};


#endif // DETECTMOTION_H
