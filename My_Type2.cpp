#include "My_Classes.h"

My_Type2::My_Type2 (int n_of_pnt, int n_of_col, edge**Tree): nop(n_of_pnt), noc(n_of_col)
{
     T = Tree;
    pnt_mark = new int [nop];   for(int i=0;i<nop;i++) pnt_mark[i] = 0;
}
My_Type2::~My_Type2()
{
    delete [] pnt_mark;
}
int My_Type2::min_edge_(int S, int *i0, int *j0, double *min_dist, double *distances, int counter)
{
    // S - start point number, *i0 and *j0 - number of first and last tree point, added to tree, *min_dist - length of edge
    // distances - array of distances, conter - number of edges in tree

    double *dist;
    int i;
    for(i = 0; i<S; i++)
    {
        dist = distances + S*nop;
        if (pnt_mark[i] == 0)
            if (counter == 0) { *min_dist = dist[i]; counter++; }
            else if(dist[i] < *min_dist)
                 {
                     *j0 = i; *i0 = S; *min_dist = dist[i];
                     counter++;
                 }
    }
    for(i = S+1; i<nop; i++)
    {
        dist = distances + S*nop;
        if (pnt_mark[i] == 0)
            if (counter == 0) { *min_dist = dist[i]; counter++; }
            else if(dist[i] < *min_dist)
                 {
                     *j0 = i; *i0 = S; *min_dist = dist[i];
                     counter++;
                 }
    }
    return counter;  
}
My_Type2& My_Type2::tree_(double *distances)
{
    int i,j,t = 1, i0 = 0, j0 = 1;
    double min_dist = distances[1], *dist;
    for(i = 0; i<nop; i++)
    {
        dist = distances + i*nop;
        for(j = i+1; j<nop; j++)                       //vkl'uchaem v derevo 1 rebro
            if(dist[j] < min_dist)
            {
                i0 = i; j0 = j;
                min_dist = dist[j];
            }
    }
    T[0]->begin = i0; T[0]->end = j0; T[0]->len = min_dist;
    pnt_mark[i0] = 1; pnt_mark[j0] = 1;
    
    int counter;
    while(t != nop)
    {
        counter = 0;
        counter = this -> min_edge_(T[0]->begin, &i0, &j0, &min_dist, distances, counter);
        for(i=0; i<t; i++) counter = this -> min_edge_(T[i]->end, &i0, &j0, &min_dist, distances, counter);    //ostsl'nye rebra
        T[t]->begin = i0; T[t]->end = j0; T[t]->len = min_dist;
        pnt_mark[j0] = 1;
        t++;
    }
    return *this;
}