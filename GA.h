#ifndef GA_H_INCLUDED
#define GA_H_INCLUDED

#include <vector>
#include "Picture.h"
#include "Solution.h"
#include "CVImage.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class GA
{
    CVImage cvpic;
    Picture origin, pic;
    std::vector<Solution> soluSet;
    std::vector<Solution> mating;
    std::vector<Solution> child;
    int divide_width=10, divide_height=10;
    int parent=10;
    int select_num=6;

public:
    bool initial(char fileName[])
    {
        if( !cvpic.load(fileName) ) return false;
        origin.memAllocate(cvpic.getw(), cvpic.geth());
        pic.memAllocate(cvpic.getw(), cvpic.geth());

        cvpic.save2picture(origin);
        cvpic.show("Original Picture");

// test 用的 =======================
//    cvpic.save2picture(pic);
//    Circle test;
//    test.R = 0; test.G = 0; test.B = 255; test.A = 100;
//    test.x = 50; test.y = 50; test.radius = 100;
//    Solution tt;
//    tt.DrawCircle( test, pic );
//    cvpic.loadFrompicture(pic);
//    cvpic.show("new window8");
//    cvWaitKey(0);
// test 用的 =======================
        return true;
    }


    void generateInitSoluction()
    {
        Solution test3030(3, 3, origin);
        test3030.DrawAll(pic);
        cvpic.loadFrompicture(pic);
        cvpic.show("test 30 * 30");

        for(int p=0; p<parent; p+=1) {
            Solution tS(divide_height, divide_width, origin);
            cout << "  p = " << p << endl;
            soluSet.push_back(tS);
        }

//        test3030.AddCircle(origin, 3, 3);
//        test3030.DrawAll(pic);
//        cvpic.show("second 30", pic);


//        soluSet[0].Crossover(test3030, 3, 3);
//        test3030.DrawAll(pic);
//        cvpic.show("third 30", pic);
//        cout << origin.CalcDifference(pic) << endl;


        for(int i=0;i<10;i++)
        {
            test3030.AddCircle(origin, 3, 3);
            test3030.DrawAll(pic);
            cvpic.show("second 30", pic);

            cvWaitKey();
        }

        char str[100]="";
        str[0]='1';
        for(int i=0; i<10; i+=1){
            if(i > 0) break;
            soluSet[i].DrawAll(pic);
            cvpic.loadFrompicture(pic);
            cvpic.show(str);
            str[i+1]='1';
        }
        cout << origin.CalcDifference(pic) << endl;


        Solution test5050(50, 50, origin);
        test5050.DrawAll(pic);
        cvpic.loadFrompicture(pic);
        cvpic.show("test 50 * 50");
        cout << origin.CalcDifference(pic) << endl;





    }

    // 選出 select_num 個 solution 來當成 mating
    void Roulette_Wheel_Seletion();


};

#endif // GA_H_INCLUDED
