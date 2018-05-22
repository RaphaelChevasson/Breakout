#include "detectmotion.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QImage>
#include <iostream>
#include <QDebug>

using namespace std;


QLabel *DetectMotion::pCameraDisplay = nullptr;
QImage *DetectMotion::pImageToDisplay = nullptr;

DetectMotion::DetectMotion()
{
    qDebug()<<"1"<<endl;

    workingRect = Rect((frameWidth-subImageWidth)/2,
                     frameHeight/2+(frameHeight/2-subImageHeight)/2,
                     subImageWidth,subImageHeight);
    templateRect = Rect((workingRect.width-templateWidth)/2,
                      (workingRect.height-templateHeight)/2,
                      templateWidth,templateHeight);
    workingCenter = Point(workingRect.x+subImageWidth/2,
                        workingRect.y+subImageHeight/2);
    qDebug()<<"2"<<endl;

    // /--------------------------------------------------------------------------
    //   First image ; goal = Create the matchTemplate image result
    try
    {
        webCam_=new VideoCapture(0); // open the default camera
    }
    catch (Exception e) {}
    while(!webCam_->isOpened())
    {
        cerr<<"Error openning the default camera"<<endl;
        try
        {
            webCam_=new VideoCapture(0); // open the default camera
        }
        catch (Exception e) {}
    }

    qDebug()<<"3"<<endl;
    int width=webCam_->get(CV_CAP_PROP_FRAME_WIDTH);
    int height=webCam_->get(CV_CAP_PROP_FRAME_HEIGHT);
    qDebug()<<endl<<"Video ok, image is "<<width<<"x"<<height<<endl;

    //webCam_->set(CV_CAP_PROP_FRAME_WIDTH,frameWidth);
    //webCam_->set(CV_CAP_PROP_FRAME_HEIGHT,frameHeight);
    qDebug()<<"4"<<endl;

    // Widget size and position setup
    pCameraDisplay->setFixedSize(frameWidth, frameHeight);
    qDebug()<<endl<<"Window created"<<endl;

    // Get frame1
    for(;;)
    {
        if (webCam_->read(frame1)) {
            qDebug()<<"First frame captured !"<<endl;
            updateImage(frame1);
            break;
        }
        else {
            cerr<<"Error capturing the first frame"<<endl;
            cerr<<"retrying..."<<endl;
            if(waitKey(30) >= 0) break;
        }
    }
    // Mirror effect
    cv::flip(frame1,frame1,1);
    // Extract rect1 and convert to gray
    cv::cvtColor(Mat(frame1,workingRect),frameRect1,COLOR_BGR2GRAY);
    //Mat(frame1,rect).copyTo(frameRect1);

    // Create the matchTemplate image result
    int result_cols = frame1.cols-templateWidth  + 1;
    int result_rows = frame1.rows-templateHeight + 1;
    resultImage.create( result_cols, result_rows, CV_32FC1 );

}

void DetectMotion::init(QLabel *pCameraLabel)
{
    pCameraDisplay = pCameraLabel;
}

void DetectMotion::computeDetection()
{
    // /--------------------------------------------------------------------------
    //   Other images ; goal = display and process images

   while (waitKey(1000)<0)
    {
        // Get frame2
        *webCam_ >> frame2;
        // Mirror effect
        cv::flip(frame2,frame2,1);
        // Extract working rect in frame2 and convert to gray
        cv::cvtColor(Mat(frame2,workingRect),frameRect2,COLOR_BGR2GRAY);

        // Extract template image in frame1
        Mat templateImage(frameRect1,templateRect);
        // Do the Matching between the working rect in frame2 and the templateImage in frame1
        matchTemplate( frameRect2, templateImage, resultImage, TM_CCORR_NORMED );
        // Localize the best match with minMaxLoc
        double minVal; double maxVal; Point minLoc; Point maxLoc;
        minMaxLoc( resultImage, &minVal, &maxVal, &minLoc, &maxLoc);
        // Compute the translation vector between the origin and the matching rect
        Point vect(maxLoc.x-templateRect.x,maxLoc.y-templateRect.y);

        // Draw green rectangle and the translation vector
        rectangle(frame2,workingRect,Scalar( 0, 255, 0),2);
        Point p(workingCenter.x+vect.x,workingCenter.y+vect.y);
        arrowedLine(frame2,workingCenter,p,Scalar(255,255,255),2);

        // Update image to display with frame2
        updateImage(frame2);

        // Swap matrixes
        swap(frameRect1,frameRect2);
    }

    // \--------------------------------------------------------------------------

    // the camera will be deinitialized automatically in VideoCapture destructor

}

void DetectMotion::updateImage(Mat img)
{
    cv::cvtColor(img,img,CV_BGR2RGB); //Qt reads in RGB whereas CV in BGR

    // Converts the CV image into Qt standard format
    pImageToDisplay = new QImage((uchar*)img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
}

void DetectMotion::displayImage()
{
    if (pCameraDisplay == nullptr || pImageToDisplay == nullptr)
    {
        return;
    }

    // Display the image in label that is created earlier
    try
    {
        pCameraDisplay->setPixmap(QPixmap::fromImage(*pImageToDisplay));
    }
    catch(Exception e) {qDebug() << "Error caught :" << e.what();}
}
