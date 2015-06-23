#ifndef GA_H_INCLUDED
#define GA_H_INCLUDED

#include <vector>
#include "Picture.h"
#include "Solution.h"
#include "CVImage.h"
#include <iostream>
#include <string>
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
    int parent=20;
    int select_num=6;
    int generation=0;
    void Sort(vector<Solution> & arr)
    {
        for(int i=0; i<arr.size(); i+=1) {
            arr[i].DrawAll(pic);
            arr[i].score = origin.CalcDifference(pic);
        }
        sort(arr.begin(), arr.end());
    }

public:
    bool initial(char fileName[])
    {
        if( !cvpic.load(fileName) ) return false;
        origin.memAllocate(cvpic.getw(), cvpic.geth());
        pic.memAllocate(cvpic.getw(), cvpic.geth());

        cvpic.save2picture(origin);
        cvpic.show("Original Picture");

        return true;
    }


    void generateInitSoluction()
    {


        for(int p=0; p<parent; p+=1) {
            Solution tS(divide_height, divide_width, origin);
            cout << "  p = " << p << endl;
            soluSet.push_back(tS);

        }
    }

    // 選出 select_num 個 solution 來當成 mating
    void Roulette_Wheel_Seletion();
    void Start()
    {
        generateInitSoluction();
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
            {
                if(rand()%100 > 60)
                    soluSet[i].AddCircle(origin,divide_height,divide_width);
            }

            for(int i=0; i<soluSet.size(); i+=1){
                if(rand()%100 > 85)
                    soluSet[i].Mutation(origin, divide_height, divide_width);
            }

            soluSet[0].DrawAll(pic);

            cvpic.show("third 30", pic);
            if(generation%100==0){
                cout << "Circles:" << soluSet[0].CalCircleNumbers(divide_height, divide_width) << endl;
                cvWaitKey();
            }
            cvpic.destoyWindow("third 30");
            generation++;
            cout << generation << endl;
        }
    }

};

#endif // GA_H_INCLUDED
