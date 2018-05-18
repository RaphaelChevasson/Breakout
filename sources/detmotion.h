#ifndef DETMOTION_H
#define DETMOTION_H

#include <QMainWindow>
#include <iostream>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;
using namespace std;

class DetMotion : public QMainWindow
{
    Q_OBJECT

public:
    explicit DetMotion(QWidget *parent = 0);
    int frameWidth=320;
    int frameHeight=240;

private:
    VideoCapture cap;
    Mat frame1,frame2,frameRect1,frameRect2;
private slots:

    void afficherImage();

};


#endif // DETMOTION_H
