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
    std::vector<Circle> arr;
    std::vector<Solution> soluSet;




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
    cvpic.show("new windows");
// test 用的 =======================
        return true;
    }
    void generateInitSoluction()
    {
        //
    }

};

#endif // GA_H_INCLUDED
