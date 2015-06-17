#include <cv.h>
#include <highgui.h>
#include <ctime>
#include <cmath>
#include "CVImage.h"
using namespace std;

int main()
{
    srand(time(NULL));
    CVImage gray, gauss1, gauss2;

    if( !gray.load("ml.jpg")) return 1;


//    gray.createImage(300, 300);
//    gray.setColor(100);
    gray.show("Original Picture");

    gray.DrawCircle(50, 50, 100, 0, 0, 255, 100);
    gray.show("new windows");
    gray.DrawCircle(50, 50, 100, 0, 0, 255, 200);
    gray.show("new windows 2");
//    gray.save("Origin.jpg");

//    gauss1 = gray;
//    gauss1.GaussianNoise(sqrt(15), 0);
//    gauss1.show("Gaussian Noise Variance=15");
//    gauss1.save("Gaussian Noise Variance=15.jpg");
//
//    gauss2 = gray;
//    gauss2.GaussianNoise(15, 0);
//    gauss2.show("Gaussian Noise Variance=225");
//    gauss2.save("Gaussian Noise Variance=225.jpg");
//
//    cvWaitKey(0);
//    gauss1.destoyWindow("Gaussian Noise Variance=15");
//    gauss2.destoyWindow("Gaussian Noise Variance=225");

    cvWaitKey(0);

    return 0;
}

