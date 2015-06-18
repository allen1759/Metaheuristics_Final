#include "CVImage.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

void CVImage::DrawCircle(int x, int y, int radius, int R, int G, int B, int alpha)
{
    int left = max(x - radius, 0);
    int right = min(x + radius, (int)width);
    int up = max(y - radius, 0);
    int down = min(y + radius, (int)height);
    for(int i=up; i<down; i+=1) {
        for(int j=left; j<right; j+=1) {
            if( (i-y)*(i-y) + (j-x)*(j-x) < radius*radius ) {
//                    setData( i, j, cvScalar( (getB(i, j)*getA(i, j) + B*alpha)/255,
//                                             (getG(i, j)*getA(i, j) + G*alpha)/255,
//                                             (getR(i, j)*getA(i, j) + R*alpha)/255,
//                                             (getA(i, j) + alpha) ) );
                setData( i, j, cvScalar( (getB(i, j)*(255-alpha) + B*alpha)/255,
                                         (getG(i, j)*(255-alpha) + G*alpha)/255,
                                         (getR(i, j)*(255-alpha) + R*alpha)/255) );
            }
        }
    }
}
