#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED

#include <vector>
#include <iostream>
#include <algorithm>
#include <cstring>
#include "picture.h"
#include <cstdio>
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
    int score;

    Solution() {}
    Solution(int divide_height, int divide_width, Picture &origin)
    {
        sol.resize(divide_height);
        for(int i=0; i<divide_height; i+=1)
            sol[i].resize(divide_width);

        int tR[divide_height][divide_width], tG[divide_height][divide_width], tB[divide_height][divide_width], area[divide_height][divide_width];
        memset(tR, 0, sizeof(tR));
        memset(tG, 0, sizeof(tG));
        memset(tB, 0, sizeof(tB));
        memset(area, 0, sizeof(area));
        int newWidth=(origin.width/divide_width) + 1;
        int newHeight=(origin.height/divide_height) + 1;

        for(int i=0; i<origin.height; i+=1){
            for(int j=0; j<origin.width; j+=1){
                tR[ i/newHeight ][ j/newWidth ] += origin.R[i*origin.width + j];
                tG[ i/newHeight ][ j/newWidth ] += origin.G[i*origin.width + j];
                tB[ i/newHeight ][ j/newWidth ] += origin.B[i*origin.width + j];
                area[ i/newHeight ][ j/newWidth ] += 1;
            }
        }


        for(int i=0; i<divide_height; i+=1){
            for(int j=0; j<divide_width; j+=1){
                if( area[i][j] == 0 ) continue;
                Circle tC;
                tC.A=100+rand()%100;
                tC.radius=newHeight/2 + rand()%(newHeight/2);
                tC.R=tR[i][j]/area[i][j]-25+rand()%50;
                tC.G=tG[i][j]/area[i][j]-25+rand()%50;
                tC.B=tB[i][j]/area[i][j]-25+rand()%50;
                tC.x=min( j*newWidth+rand()%newWidth, origin.width );
                tC.y=min( i*newHeight+rand()%newHeight, origin.height );
                sol[i][j].push_back(tC);
            }
        }
    }
    bool operator < (const Solution & rhs) const
    {
        return score < rhs.score;
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

    void Crossover(Solution &rs, int divide_height, int divide_width)
    {

        int x_part = rand()%divide_width;
        int y_part = rand()%divide_height;
        sol[y_part][x_part].swap(rs.sol[y_part][x_part]);
    }

    void Mutation(int divide_height, int divide_width)
    {



    }

    void AddCircle(Picture &origin, int divide_height, int divide_width)
    {
        Circle add;
        add.A=100+rand()%100;
        add.radius=rand()%(origin.height/3);

        add.x=rand()%origin.width;
        add.y=rand()%origin.height;

        add.R = origin.R[ add.y*origin.width+add.x ];
        add.G = origin.G[ add.y*origin.width+add.x ];
        add.B = origin.B[ add.y*origin.width+add.x ];

        int newHeight = origin.height/divide_height + 1;
        int newWidth = origin.width/divide_width + 1;

//        printf("x:%d  y:%d\n", add.x, add.y);

        sol[ add.y/newHeight ][ add.x/newWidth ].push_back(add);
//        printf("i:%d  j:%d\n", add.x/newWidth, add.y/newHeight);

    }

};


#endif // SOLUTION_H_INCLUDED
