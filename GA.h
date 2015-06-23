#ifndef GA_H_INCLUDED
#define GA_H_INCLUDED

#include <vector>
#include "Picture.h"
#include "Solution.h"
#include "CVImage.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm>
using namespace std;

class GA
{
    CVImage cvpic;
    Picture origin, pic;
    std::vector<Solution> soluSet;
    std::vector<Solution> child;
    int divide_width=10, divide_height=10;
    int parent=30;
    int select_num=6;
    int generation=0;
    void Sort(vector<Solution> & arr)
    {
        for(int i=0; i<arr.size(); i+=1) {
            arr[i].DrawAll(pic);
            arr[i].score = origin.CalcDifference(pic);
        }
//        vector<int> test;
        sort(arr.begin(), arr.end());
//        sort(test.begin(), test.end());
    }

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


        for(int p=0; p<parent; p+=1) {
            Solution tS(divide_height, divide_width, origin);
            soluSet.push_back(tS);

        }

//        test3030.AddCircle(origin, 3, 3);
//        test3030.DrawAll(pic);
//        cvpic.show("second 30", pic);


//        soluSet[0].Crossover(test3030, 3, 3);
//        test3030.DrawAll(pic);
//        cvpic.show("third 30", pic);
//        cout << origin.CalcDifference(pic) << endl;


//        for(int i=0;i<10;i++)
//        {
//            test3030.AddCircle(origin, 10, 10);
//            test3030.DrawAll(pic);
//            cvpic.show("second 30", pic);
//
//            cvWaitKey();
//        }
//        cout << "pause\n";
//
//        soluSet[0].DrawAll(pic);
        //cvpic.loadFrompicture(pic);
        //cvpic.show("11second 30", pic);

//        char str[100]="";
//        str[0]='1';
//        for(int i=0; i<10; i+=1){
//            //if(i > 0) break;
//            soluSet[i].DrawAll(pic);
//            cvpic.loadFrompicture(pic);
//            cout << "size:" << soluSet.size() << endl;
//
//
//
//            cvpic.show(str);
//            str[i+1]='1';
//        }
//        cout << origin.CalcDifference(pic) << endl;

//
//        Solution test5050(50, 50, origin);
//        test5050.DrawAll(pic);
//        cvpic.loadFrompicture(pic);
//        cvpic.show("test 50 * 50");
//        cout << origin.CalcDifference(pic) << endl;
    }

    // 選出 select_num 個 solution 來當成 mating
    void Roulette_Wheel_Seletion();
    void Start()
    {
        generateInitSoluction();
        bool tag = true;
        int row=2, col=4, r=0, c=0;
        cvpic.show("new 30-2", pic);
        while(generation<100000)
        {

            Roulette_Wheel_Seletion();
            for(int i=0;i<child.size();i+=2){
                child[i].Crossover(child[i+1],divide_height,divide_width);
                soluSet.push_back(child[i]);
                soluSet.push_back(child[i+1]);
            }
            Sort(soluSet);
            while(soluSet.size()>parent){
                soluSet.pop_back();
            }

            for(int i=0;i<soluSet.size();i++)
            {   if((rand()%100)>70)
                    soluSet[i].AddCircle(origin,divide_height,divide_width);
            }
            soluSet[0].DrawAll(pic);

//            if(tag) cvpic.show("new 30-1", pic), cvpic.destoyWindow("new 30-2");
//            else cvpic.show("new 30-2", pic), cvpic.destoyWindow("new 30-1");
//            tag = !tag;



            stringstream ss;
            ss << r << "-" << c;
            string wind;
            ss >> wind;
            wind = "Generation " + wind;
            cvpic.show(wind.c_str(), pic);
            cvpic.moveWindow(wind.c_str(), 20+origin.width*c, 50+origin.height*r);

            c += 1; c %= col;
            if( c==0 ) {
                r += 1; r %= row;
            }

//            if(genZeration%100==0)
                cvWaitKey();

            generation++;
            cout << generation << endl;
            //mutation
        }
    }

};

#endif // GA_H_INCLUDED
