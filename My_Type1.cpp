#include "My_Classes.h"

//#include <iostream>
//using namespace std;

My_Type1::My_Type1(int NOP, double D): nop(NOP), dist(D)
{
    distances01 = new int [nop*nop];
    point_mark = new int [nop];
}
My_Type1::~My_Type1()
{
    delete [] distances01;
    delete [] point_mark;
}
My_Type1& My_Type1::dst01_(double *distances)
{
    int i,j;
    for (i=0; i<nop; i++)
    {
        distances01[i*nop + i] = 1;
        for (j=i+1; j<nop; j++)
        {
            if (distances[i*nop + j] < dist) {distances01[i*nop + j] = 1; distances01[j*nop + i] = 1;}
            else {distances01[i*nop + j] = 0; distances01[j*nop + i] = 0;}
        }
    }
    return *this;
}
int My_Type1::save_(My_Poisk* Poisk, My_Point2D** points)
{
    int p_num = 0, i,j,t, add_marker, qual, nocl = 0;
    for (i=0; i<nop; i++) point_mark[i] = 0;
    My_Point2D** clust_pnt; clust_pnt = new My_Point2D* [nop];

    while (p_num != -1)
    {
        t = 1; add_marker = 1; qual = 0; point_mark[p_num] = 1;
        while (add_marker != 0)
        {
            add_marker = 0;
            for(i=0; i<nop; i++) if(point_mark[i] == t)
                for(j=0; j<nop; j++) 
                    if(distances01[i*nop + j] == 1 && point_mark[j] == 0)    // pokryvaushee derevo
                    { 
                        point_mark[j] = t+1;
                        add_marker = 1; 
                    }
            t++;
        }

        t=0;           
        for (i=0; i<nop; i++) if(point_mark[i] > 0)
        {
            clust_pnt[t] = points[i];                                         //dobavlenie v poisk
            point_mark[i]= -1;
            t++; qual++;
        }
        Poisk->addCluster(qual, clust_pnt); nocl++;

        qual = p_num; p_num = -1;
        for (i = qual; i<nop; i++) if(point_mark[i] == 0) { p_num = i; break; }
    } 
    delete [] clust_pnt; 
    return nocl;
}