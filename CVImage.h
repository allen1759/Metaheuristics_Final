#ifndef CVIMAGE_H_INCLUDED
#define CVIMAGE_H_INCLUDED

#include <cv.h>
#include <highgui.h>
#include <cmath>

#include <algorithm>
using namespace std;

class CVImage
{
    IplImage *p2image;
    size_t height, width;

    const double PI = 3.1415926535;
    double Gaussian(double sigma, double miu, double x)
    {
        return 1.0/(sqrt(2*PI)*sigma) * exp(-1*(x-miu)*(x-miu)/(2*sigma*sigma));
    }

public:
    ~CVImage() { if(NULL) release(); }
    double getB(int i, int j) { return cvGet2D(p2image, i , j ).val[0]; }
    double getG(int i, int j) { return cvGet2D(p2image, i , j ).val[1]; }
    double getR(int i, int j) { return cvGet2D(p2image, i , j ).val[2]; }
    double getA(int i, int j) { return cvGet2D(p2image, i , j ).val[3]; }
    CvScalar getData(int i, int j) { return cvGet2D(p2image, i, j); }
    void setData(int i, int j, const CvScalar & rhs) { cvSet2D(p2image, i, j, rhs); }
    const CVImage & operator = (const CVImage & rhs)
    {
        height = rhs.height;
        width = rhs.width;
        p2image =  cvCloneImage(rhs.p2image);
        return *this;
    }
    bool load(char filename[], int state=1)
    {
        p2image = cvLoadImage(filename, state);
        if(p2image)  height = p2image->height, width = p2image->width;
        return p2image!=NULL;
    }
    void save(char filename[])
    {
        cvSaveImage(filename, p2image);
    }
    void show(char window[])
    {
        cvShowImage(window, p2image);
    }
    void destoyWindow(char window[])
    {
        cvDestroyWindow(window);
    }
    void release()
    {
        cvReleaseImage(&p2image);
        p2image = NULL;
    }
    void createImage(int w, int h)
    {
        p2image = cvCreateImage(cvSize(h, w), IPL_DEPTH_8U, 3);
        height = p2image->height;
        width = p2image->width;
    }
    void setColor(int color)
    {
        for(int i=0; i<height; i+=1)
            for(int j=0; j<width; j+=1)
                setData( i, j, cvScalarAll(color) );
    }

    void gray();
    void GaussianNoise(double sigma, double miu);
    void DrawCircle(int x, int y, int radius, int R, int G, int B, int alpha)
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
};

#endif // CVIMAGE_H_INCLUDED
