#include "My_Classes.h"

My_Type4::My_Type4(int n_of_points, int k_means_K, int n_of_cores, My_Point2D** fircen): nop(n_of_points), k(k_means_K), p(n_of_cores)
{
    point_mark = new int [nop];
    cores = new My_Point2D [p*k];
    for(int i=0; i<k; i++ ) cores[i] = *fircen[i];
}
My_Type4::~My_Type4()
{
    delete [] cores;
    delete [] point_mark;
}
void My_Type4::centres_group(My_Point2D** pnt)
{
    double mindist, dist;
    int got_mark;

    for(int i=0; i<nop; i++)
    {
        mindist = cores[0].Dist(pnt[i]);
        got_mark = 0;
        for (int j=1; j<k; j++)
        {
            dist = cores[j].Dist(pnt[i]);
            if (dist < mindist)
            {
                mindist = dist;
                got_mark = j;
            }
        }
        point_mark[i] = got_mark;
    } 
}
bool My_Type4::core_group(My_Point2D**pnt)
{
    double mindist=0, dist;
    int got_mark;
    bool marker_changed = false, not_counted;

    for(int i=0; i<nop; i++)
    {
        not_counted = true;
        got_mark = 0;
        for(int M=0; M<k; M++)
            for(int j=0; j<p; j++)
            {
                dist = cores[M*p + j].Dist( pnt[i] );
                if(dist<mindist || not_counted)
                {
                    mindist = dist;
                    got_mark = M;
                    not_counted = false;
                }
            }
        if (got_mark != point_mark[i])
        {
            marker_changed = true;
            point_mark[i] = got_mark;
        }
    }
    return marker_changed;
}
void My_Type4::neighbors(double *distances, My_Point2D** points, My_Point2D** first_centers)
{
    int* fircen_num = new int [k];
    fircen_num[0] = 0; fircen_num [1] = 1;
    double mindist = distances [1], *dist;
    for(int i=0; i<nop; i++)
    {
        dist = distances + i*nop;
        for(int j=i+1; j<nop; j++)
            if( dist[j] < mindist )
            {
                mindist = dist[j];
                fircen_num[0] = i;
                fircen_num[1] = j;
            }
    }
    int t = 2;
    bool not_counted, not_met;
    double sum;
    while (t < k)
    {
        not_counted = true; not_met = true;
        for(int i=0; i<nop; i++)
        {
            dist = distances + i*nop;
            for(int p=0; p<t; p++)
                if (i == fircen_num[p]) not_met = false;
            if (not_met)
                for(int j=i+1; j<nop; j++)
                {
                    not_met = true;
                    for(int p=0; p<t; p++)
                        if (j == fircen_num[p]) not_met = false;
                    sum = 0;
                    if( not_met ) 
                    {
                        for(int p=0; p<t; p++) sum += distances[ fircen_num[p]*nop + j ];
                    }
                    if( ( not_met && sum < mindist ) || not_counted )
                    {
                        mindist = sum;
                        fircen_num[t] = j;
                        not_counted = false;
                    }
                }
        }
        t++;
    }
    for(int i=0; i<k; i++)
       first_centers[i] = points[ fircen_num[i] ];

    delete [] fircen_num;
}
void My_Type4::group_core(My_Point2D**pnt, double *distances)
{
    My_Point2D **pnt_group, **pnt_group_fircen, *cores_group;
    int nop_group, delta;
    pnt_group = new My_Point2D* [nop];
    pnt_group_fircen = new My_Point2D* [p];

    for(int M=0; M<k; M++)
    {
        nop_group = 0;
        cores_group = cores + M*p;
        for(int i=0; i<nop; i++)
            if(point_mark[i] == M) pnt_group[nop_group++] = pnt[i];
        //this->neighbors(distances, pnt, pnt_group_fircen);
        delta = int(nop_group/p);
        for(int i=0; i<p; i++)                                                      //nachal'nye tochki k-means
            pnt_group_fircen[i] = pnt_group[(i+1)*delta - 1];
        My_Type3(nop_group,p,pnt_group_fircen).k_means_centers_(cores_group, pnt_group);
    }

    delete [] pnt_group;
    delete [] pnt_group_fircen;
}

void My_Type4::save_(My_Poisk *Poisk, My_Point2D** pnt, double *distances)
{
    this->centres_group(pnt);
    this->group_core(pnt, distances);
    int iter_count = 0;
    while( this->core_group(pnt) ) 
    {
        this->group_core(pnt, distances);
        if(++iter_count > ITERATIONS)
        {
            printf("forced stop after %d iterations\n", ITERATIONS);
            return;
        }
    }
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
    Poisk->addCenters(cores,k*p);
    Poisk->get_k_p(k, p);
}