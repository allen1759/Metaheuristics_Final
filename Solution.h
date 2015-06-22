#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED

#include <vector>
#include <algorithm>
using namespace std;

struct Circle
{
    int R, G, B, A;
    int x, y, radius;
};

class Solution
{
public:
    std::vector< std::vector< std::vector<Circle> > > sol;

public:
    Solution() {}
    Solution(int h, int w)
    {
        sol.resize(h);
        for(int i=0; i<h; i+=1)
            sol[i].resize(w);
    }
    void DrawCircle(Circle & circ, Picture & pic)
    {
        int left = max(circ.x - circ.radius, 0);
        int right = min(circ.x + circ.radius, (int)pic.width);
        int up = max(circ.y - circ.radius, 0);
        int down = min(circ.y + circ.radius, (int)pic.height);
        for(int i=up; i<down; i+=1) {
            for(int j=left; j<right; j+=1) {
                if( (i-circ.y)*(i-circ.y) + (j-circ.x)*(j-circ.x) < circ.radius*circ.radius ) {
                    pic.B[i*pic.width+j] = (pic.B[i*pic.width+j]*(255-circ.A) + circ.B*circ.A)/255;
                    pic.G[i*pic.width+j] = (pic.G[i*pic.width+j]*(255-circ.A) + circ.G*circ.A)/255;
                    pic.R[i*pic.width+j] = (pic.R[i*pic.width+j]*(255-circ.A) + circ.R*circ.A)/255;
                }
            }
        }
    }

    void DrawAll(Picture & pic)
    {
        pic.setWhite();
        for(int i=0; i<sol.size(); i+=1) {
            for(int j=0; j<sol[i].size(); j+=1) {
                for(int k=0; k<sol[i][j].size(); k+=1) {
                    DrawCircle(sol[i][j][k], pic);
                }
            }
        }
    }


};


#endif // SOLUTION_H_INCLUDED
