#include "GA.h"

void GA::Roulette_Wheel_Seletion()
{
    vector<int> CDF(soluSet.size(), 0);
    soluSet[0].DrawAll(pic);
    CDF[0] = origin.CalcDifference(pic);
    for(int i=1; i<CDF.size(); i+=1) {
        soluSet[i].DrawAll(pic);
        CDF[i] = CDF[i-1] + origin.CalcDifference(pic);
    }

    mating.clear();
    // select_num 是要選出的個數
    for(int i=0; i<select_num; i+=1) {
        int random = rand()%CDF.back();
        int ind = lower_bound(CDF.begin(), CDF.end(), random) - CDF.begin();
        mating.push_back(soluSet[ind]);
    }
}
