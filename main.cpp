#include <cv.h>
#include <highgui.h>
#include <ctime>
#include <iostream>
#include <cstdio>
#include <vector>
#include "CVImage.h"
#include "GA.h"
using namespace std;

int main()
{
    srand(time(NULL));
//    freopen("image/log.txt", "w", stdout);
    GA mona;
    if( !mona.initial("monalisa.jpg") ) return 1;
    mona.Start();
//    mona.start2_4();
    //mona.generateInitSoluction();


    cvWaitKey(0);

    return 0;
}

