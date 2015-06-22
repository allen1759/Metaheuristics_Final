#ifndef PICTURE_H_INCLUDED
#define PICTURE_H_INCLUDED

class Picture
{
public:
    int width, height;
    int *R, *G, *B;
    ~Picture()
    {
        delete [] R;
        delete [] G;
        delete [] B;
    }

    void memAllocate(int w, int h)
    {
        width = w;
        height = h;
        R = new int[w*h];
        G = new int[w*h];
        B = new int[w*h];
    }

    void setWhite()
    {
        for(int i=0; i<height*width; i+=1) {
            R[i] = G[i] = B[i] = 255;
        }
    }

    // fitness function
    int CalcDifference(Picture & rhs)
    {
        int diff = 0, tmp;
        for(int i=0; i<height; i+=1) {
            for(int j=0; j<width; j+=1) {
                tmp = R[i*width+j] - rhs.R[i*width+j];
                diff += tmp*tmp;
                tmp = G[i*width+j] - rhs.G[i*width+j];
                diff += tmp*tmp;
                tmp = B[i*width+j] - rhs.B[i*width+j];
                diff += tmp*tmp;
            }
        }
        return diff;
    }
};

#endif // PICTURE_H_INCLUDED
