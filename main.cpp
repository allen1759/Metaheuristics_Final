#include <cv.h>
#include <highgui.h>
#include <ctime>
#include <iostream>
#include <vector>
#include "CVImage.h"
#include "GA.h"
using namespace std;

int main()
{
    srand(time(NULL));
    GA mona;
    if( !mona.initial("monalisa.jpg") ) return 1;
    mona.Start();
    //mona.generateInitSoluction();


    cvWaitKey(0);

    return 0;
}

