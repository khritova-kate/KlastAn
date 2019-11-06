#include "My_Classes.h"

My_Type3::My_Type3(int n_of_points, int k_means_K, My_Point2D** cnt): nop(n_of_points), k(k_means_K) 
{
    centres = new My_Point2D [k];
    point_mark = new int [nop];
    for(int i=0; i<k; i++) centres[i] = *cnt[i];
}
My_Type3::~My_Type3()
{
    delete [] centres;
    delete [] point_mark;
}
bool My_Type3::centres_group(My_Point2D** pnt)
{
    double mindist, dist;
    int got_mark;
    bool marker_changed = false;

    for(int i=0; i<nop; i++)
    {
        mindist = centres[0].Dist(pnt[i]);
        got_mark = 0;
        for (int j=1; j<k; j++)
        {
            dist = centres[j].Dist(pnt[i]);
            if (dist < mindist)
            {
                mindist = dist;
                got_mark = j;
            }
        }
        if ( got_mark != point_mark[i] )
        {
            marker_changed = true;
            point_mark[i] = got_mark;
        }
    } 
    return marker_changed;
}
void My_Type3::group_centres(My_Point2D** pnt)
{
    double x,y;
    int nop_in_group;
    for(int t=0; t<k; t++)
    {
        x = 0; y = 0; nop_in_group = 0;
        for (int i=0; i<nop; i++)
            if(point_mark[i] == t)
            {
                x += pnt[i]->ReturnX();
                y += pnt[i]->ReturnY();
                nop_in_group ++;
            }
        centres[t] = My_Point2D (x/nop_in_group, y/nop_in_group);
    }
}
void My_Type3::save_(My_Poisk *Poisk,My_Point2D** pnt)
{
    while( this->centres_group(pnt) ) this->group_centres(pnt);
    My_Point2D** clust_pnt; clust_pnt = new My_Point2D* [nop];
    int nop_cl;

    for(int t=0; t<k; t++)
    {
        nop_cl = 0;
        for(int i=0; i<nop; i++)
            if(point_mark[i] == t) clust_pnt[nop_cl++] = pnt[i];
        Poisk->addCluster(nop_cl, clust_pnt);
    }
    delete [] clust_pnt;
    Poisk->addCenters(centres,k);
}
void My_Type3::k_means_centers_(My_Point2D* cen, My_Point2D** pnt)      //zagrugaet centry v massiv (pnt - massiv tochek gruppy) Achtung pri objavlenii Type3 v Type4
{
    while( this->centres_group(pnt) ) this->group_centres(pnt);
    for(int i=0; i<k; i++) cen[i] = centres[i];
}