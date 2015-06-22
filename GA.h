#ifndef GA_H_INCLUDED
#define GA_H_INCLUDED

#include <vector>
#include "Picture.h"
#include "Solution.h"
#include "CVImage.h"
#include <iostream>
using namespace std;



class GA
{
    CVImage cvpic;
    Picture origin, pic;
    //std::vector<Circle> arr;
    std::vector<Solution> soluSet;
    int divide_width=3, divide_height=3;

public:
    bool initial(char fileName[])
    {
        if( !cvpic.load(fileName) ) return false;
        origin.memAllocate(cvpic.getw(), cvpic.geth());
        pic.memAllocate(cvpic.getw(), cvpic.geth());

        cvpic.save2picture(origin);
        cvpic.show("Original Picture");

// test 用的 =======================
    cvpic.save2picture(pic);
    Circle test;
    test.R = 0; test.G = 0; test.B = 255; test.A = 100;
    test.x = 50; test.y = 50; test.radius = 100;
    Solution tt;
    tt.DrawCircle( test, pic );
    cvpic.loadFrompicture(pic);
    cvpic.show("new window8");
// test 用的 =======================
        return true;
    }


    void generateInitSoluction()
    {
        int tR[divide_height][divide_width], tG[divide_height][divide_width], tB[divide_height][divide_width];
        memset(tR, 0, sizeof(tR));
        memset(tG, 0, sizeof(tG));
        memset(tB, 0, sizeof(tB));
        int newWidth=(origin.width/divide_width);
        int newHeight=(origin.height/divide_height);
        int newArea=newHeight*newWidth;

        for(int i=0; i<origin.height; i+=1){
            for(int j=0; j<origin.width; j+=1){
                tR[ i/newHeight ][ j/newWidth ] += origin.R[i*origin.width + j];
                tG[ i/newHeight ][ j/newWidth ] += origin.G[i*origin.width + j];
                tB[ i/newHeight ][ j/newWidth ] += origin.B[i*origin.width + j];
            }
        }

        Solution tS(divide_height, divide_width);
        Circle tC;
        tC.A=150;
        tC.radius=newHeight/2;
        for(int i=0; i<divide_height; i+=1){
            for(int j=0; j<divide_width; j+=1){
                tC.R=tR[i][j]/newArea;
                tC.G=tG[i][j]/newArea;
                tC.B=tB[i][j]/newArea;
                tC.x=i*newWidth+newWidth/2;
                tC.y=j*newHeight+newHeight/2;
                tS.sol[i][j].push_back(tC);
            }
        }

        tS.DrawAll(pic);
        cvpic.loadFrompicture(pic);
        cvpic.show("tesstettttttttttttttttt");



    }

};

#endif // GA_H_INCLUDED
