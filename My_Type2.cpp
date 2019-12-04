#include "My_Classes.h"

My_Type2::My_Type2 (int n_of_pnt, int n_of_col, edge**Tree): nop(n_of_pnt), noc(n_of_col)
{
    T = *Tree;
    pnt_mark = new int [nop];   for(int i=0;i<nop;i++) pnt_mark[i] = 0;
}
My_Type2::~My_Type2()
{
    delete [] pnt_mark;
}
int My_Type2::min_edge_(int S, int *i0, int *j0, double *min_dist, double *distances, int counter)
{
    // S - start point number, *i0 and *j0 - number of first and last tree point, added to tree, *min_dist - length of edge
    // distances - array of distances, conter - buff (mindist is (not) defined)

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
    T[0].begin = i0; T[0].end = j0; T[0].len = min_dist;
    pnt_mark[i0] = 1; pnt_mark[j0] = 1;
    
    int counter;
    while(t < nop-1 )
    {
        counter = 0;
        counter = this -> min_edge_(T[0].begin, &i0, &j0, &min_dist, distances, counter);
        for(i=0; i<t; i++) counter = this -> min_edge_(T[i].end, &i0, &j0, &min_dist, distances, counter);    //ostsl'nye rebra
        T[t].begin = i0; T[t].end = j0; T[t].len = min_dist;
        pnt_mark[j0] = 1;
        t++;
    }
    return *this;
}
My_Type2& My_Type2::barch_(My_Poisk* Poisk)
{
    int i, step_1, step_2;
    int* barch = new int [noc];
    for (i=0;i<noc;i++) barch[i] = 0;

    double max_dist = 0, delta;
    for(i=0; i<nop-1; i++)
        if(T[i].len > max_dist) max_dist = T[i].len;
    delta = max_dist/(noc - 1);
    
    for(i=0; i<nop-1; i++) barch[int( T[i].len / delta )]++;

    Poisk -> get_barch(noc, barch);                                      //gistogramma sohranjaets'a v poiske
    
    i = 0;
    while (barch[i]  > 0 && i < noc) {i++;} step_1 = i;
    while (barch[i] == 0 && i < noc) {i++;} step_2 = (i >= step_1 ? i : noc - 1 + step_1);
    porog = (step_1 == step_2 ? max_dist+delta : (step_2 - step_1)*delta);
    printf("  porog = %.3lf\n", porog);

    delete [] barch;
    return *this;
}
int My_Type2::find_clust(int i_start, int *i_end, My_Point2D** pnt, My_Point2D** pnt_clust)
{
    int nop_cl = 0, i;

    //printf("\tstart_i = %d ... (%d)\n\t", i_start, nop-3);

    if(i_start == 0)
    {
        pnt_clust[0] = pnt[ T[0].begin ]; nop_cl++;
        i = 0;
        while( T[i].len < porog && i < nop-1 )
        {
            //printf("%d ", i);
            pnt_clust[nop_cl++] = pnt[ T[i].end ];
            i++; 
        }
        if (i == 0) i++;
        //printf("\n\t... end_i = %d\n", i);
        if (i == nop-1) { *i_end = -1; return nop_cl; }
        *i_end = i; return nop_cl;
    }
    i = i_start + 1;
    pnt_clust[0] = pnt [ T[i_start].end ]; nop_cl++;
    if (i_start > nop-3)              { /*printf("\t... end_i = %d\n", i);*/ *i_end = -1; return nop_cl;}
    if (T[i_start].end != T[i].begin) { /*printf("\t... end_i = %d\n", i);*/ *i_end =  i; return nop_cl;}
    if (T[i].len > porog )            { /*printf("\t... end_i = %d\n", i);*/ *i_end =  i; return nop_cl;}
    while( T[i].len < porog && i < nop-1)
    {
        //printf("%d ", i);
        pnt_clust[nop_cl++] = pnt[ T[i].end ];
        i++; 
    }
    //printf("\n\t... end_i = %d", i);
    if (i == nop-1) {*i_end = -1; return nop_cl;}
    *i_end = i; return nop_cl;
}
int My_Type2::save_(My_Poisk* Poisk, My_Point2D** pnt)
{
    int i = 0, nop_cl = 0, n_clust = 0;
    My_Point2D** pnt_clust = new My_Point2D* [nop];
    
    int nopp = 0;
    while(i != -1)
    {
        nop_cl = this->find_clust(i,&i,pnt,pnt_clust);
        nopp += nop_cl;
       // printf("iter -- %d (%d)\n",n_clust+1, nop_cl);
        Poisk -> addCluster(nop_cl, pnt_clust); 
        n_clust++;
        //printf("\n\nnop_cl = %d\n", nop_cl);
        //Poisk->printCluster(n_clust - 1);
    }
   // printf("sum :: %d\n", nopp);

    delete [] pnt_clust;
    return n_clust;
}