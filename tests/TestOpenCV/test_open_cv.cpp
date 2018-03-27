#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main()
{
    Mat image=imread("../TestOpenCV/lena.jpg");
    namedWindow("My Image");
    imshow("My Image",image);
    waitKey(0);


    return 0;
}
