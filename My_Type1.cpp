#include "My_Type1.h"
#include "My_Group2D.h"
#include "My_Poisk.h"

My_Type1::My_Type1(int NOP, double D): nop(NOP), dist(D)
{
    points = new My_Point2D* [nop];
    distances = new double* [nop*nop];
    distances01 = new int [nop*nop];
    point_mark = new int [nop];
}
My_Type1::~My_Type1()
{
    delete [] points;
    delete [] distances;
    delete [] distances01;
    delete [] point_mark;
}
My_Type1& My_Type1::pnt_(int nogr, My_Group2D**gr)
{
    int i,j,k=0, n;
    for (i=0; i<nogr; i++)
    {
        n = gr[i]->RetN();
        for (j=0; j < n; j++) points[k+j] = gr[i]->RetPOINT(j);
        k += gr[i]->RetN();
    }
    return *this;
}
My_Type1& My_Type1::dst_()
{
    int i,j;
    for (i=0; i<nop; i++)
    {
        distances[i*nop + i] = 0;
        for (j=i+1; j<nop; j++)
        {
            distances[i*nop + j] = points[i]->Dist(points[j]); 
            distances[j][i] = distances[i][j];
        }
    }
    return *this;
}
My_Type1& My_Type1::dst01_()
{
    int i,j;
    for (i=0; i<nop; i++)
    {
        distances_01[i*nop + i] = 1;
        for (j=i+1; j<nop; j++)
        {
            if (distances[i*nop + j] < dist) {distances_01[i*nop + j] = 1; distances_01[j*nop + i] = 1;}
            else {distances_01[i*nop + j] = 0; distances_01[j*nop + i] = 0;}
        }
    }
    return *this;
}
void My_Type1::save_(My_Poisk Poisk)
{
    int p_num = 0, i,j,t, add_marker, qual;
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
                    if(distances_01[i*nop + j] == 1 && point_mark[j] == 0)    // pokryvaushee derevo
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
        Poisk.addCluster(qual, clust_pnt);

        qual = p_num; p_num = -1;
        for (i = qual; i<nop; i++) if(point_mark[i] == 0) p_num = i;
    } 
    delete [] clust_pnt;  
}