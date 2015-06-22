#ifndef CVIMAGE_H_INCLUDED
#define CVIMAGE_H_INCLUDED

#include <cv.h>
#include <highgui.h>
#include "Picture.h"

class CVImage
{
    IplImage *p2image;
    size_t height, width;

    const double PI = 3.1415926535;

public:
    ~CVImage() { if(NULL) release(); }
    double getB(int i, int j) { return cvGet2D(p2image, i , j ).val[0]; }
    double getG(int i, int j) { return cvGet2D(p2image, i , j ).val[1]; }
    double getR(int i, int j) { return cvGet2D(p2image, i , j ).val[2]; }
    double getA(int i, int j) { return cvGet2D(p2image, i , j ).val[3]; }
    size_t geth() { return height; }
    size_t getw() { return width; }
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
    void loadFrompicture(Picture & pic);
    void save2picture(Picture & pic);
    void show(char window[])
    {
        cvShowImage(window, p2image);
    }
    void show(char window[], Picture & pic)
    {
        loadFrompicture(pic);
        show(window);
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

    void DrawCircle(int x, int y, int radius, int R, int G, int B, int alpha);
    int CalcDifference(CVImage & rhs);
};

#endif // CVIMAGE_H_INCLUDED
