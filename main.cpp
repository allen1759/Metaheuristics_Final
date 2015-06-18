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
//    gray.DrawCircle(50, 50, 100, 0, 0, 255, 200);
//    gray.show("new windows 2");


    cvWaitKey(0);

    return 0;
}

