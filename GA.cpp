#include "GA.h"

void GA::Roulette_Wheel_Seletion()
{
    vector<double> CDF(soluSet.size(), 0);
    soluSet[0].DrawAll(pic);
    CDF[0] = origin.CalcDifference(pic)+1;
    for(int i=1; i<CDF.size(); i+=1) {
        soluSet[i].DrawAll(pic);
        CDF[i] = CDF[i-1] + origin.CalcDifference(pic)+1;
    }

    child.clear();
    // select_num 是要選出的個數
    for(int i=0; i<select_num; i+=1) {
        int random = rand()%(long long int)CDF.back();
        int ind = lower_bound(CDF.begin(), CDF.end(), random) - CDF.begin();
        child.push_back(soluSet[ind]);
    }
}
