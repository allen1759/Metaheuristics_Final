#include "CVImage.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

void CVImage::gray()
{
    for(int i=0; i<height; i+=1) {
        for(int j=0; j<width; j+=1) {
            double tmp = getB(i,j) + getG(i,j) + getR(i,j);
            tmp /= 3;
            setData( i, j, cvScalarAll(tmp) );
        }
    }
}

void CVImage::GaussianNoise(double sigma, double miu)
{
    vector<double> CDF(100);
    CDF[0] = 0;
    for(int i=1; i<CDF.size(); i+=1)
        CDF[i] = CDF[i-1] + Gaussian(sigma, miu, i-50);
    double shift = (1-CDF.back()) / 2;
    for(int i=0; i<CDF.size(); i+=1)
        CDF[i] += shift;

    vector<int> counting(256, 0);
    for(int i=0; i<height; i+=1) {
        for(int j=0; j<width; j+=1) {
            double random = (double)rand() / RAND_MAX;
            int ind = lower_bound(CDF.begin(), CDF.end(), random) - CDF.begin();
            setData(i, j, cvScalarAll(100 + ind-50));
            counting[ getB(i, j) ] += 1;
        }
    }
//    for(int i=0; i<counting.size(); i+=1)
//        cout << i << '\t' << counting[i] << endl;
}
