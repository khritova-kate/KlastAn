#include "My_Classes.h"
using namespace std;

My_Type5::My_Type5(int n_of_pnt, double R, My_Point2D**pnt): nop(n_of_pnt), r(R)
{
    point_mark = new int [3*nop];

    double end_x = pnt[0]->ReturnX(), end_y = pnt[0]->ReturnY();
    double x,y;
    start_x = end_x; start_y = end_y;
    for(int i=0; i<nop; i++)
    {
        x = pnt[i]->ReturnX(); y = pnt[i]->ReturnY();
        if(x < start_x) start_x = x;
        if(x >  end_x ) end_x = x; 
        if(y < start_y) start_y = y;
        if(y >  end_y ) end_y = y;
    }
    n_cl = max( int( (end_x - start_x) / (2*r) ), int( (end_y - start_y) / (2*r) ) );
    if(n_cl < 2) n_cl = 2;

    col_le =  (end_x - start_x)/n_cl;
    line_le = (end_y - start_y)/n_cl;

    int mark;
    for(int i=0; i<nop; i++)
    {
        mark = int ( (pnt[i]->ReturnX() - start_x) / col_le );
        point_mark[3*i] = (mark < n_cl ? mark : n_cl-1);
        mark = int ( (pnt[i]->ReturnY() - start_y) / line_le );
        point_mark[3*i + 1] = (mark < n_cl ? mark : n_cl-1); 
        point_mark[3*i + 2] = -1;    
    }

    nof = int ( (n_cl*n_cl*line_le*col_le) / (r*r) ) + 1;
    nof = (nof > nop ? nop : nof);
    forel = new My_Point2D [nof];
}
My_Type5::~My_Type5()
{
    delete [] point_mark;
    delete [] forel;
}
int My_Type5::add_to_neigh (int t, int pnc, int pnl, int cen_num, My_Point2D **neigh, int *numpp, My_Point2D **pnt)
{
    for (int i=0; i<nop; i++ )
        if( point_mark[3*i] == pnc && point_mark[3*i + 1] == pnl && point_mark[3*i + 2] == -1 &&
            forel[cen_num].Dist(pnt[i]) < r )
        {
            numpp[t] = i;
            neigh[t++] = pnt[i];
        }
    return t;
}
int My_Type5::neigh(int cen_num, My_Point2D **neigh, My_Point2D **pnt, int *numpp)
{
    int pnc,pnl,t=0;
    pnc = int( ( forel[cen_num].ReturnX() - start_x) / col_le );
    pnc = (pnc < n_cl ? pnc : n_cl-1);
    pnc = (pnc < 0 ? 0 : pnc);
    pnl = int( ( forel[cen_num].ReturnY() - start_y) / line_le );
    pnl = (pnl < n_cl ? pnl : n_cl-1);
    pnl = (pnl < 0 ? 0 : pnl);
    
    t=this->add_to_neigh(t,pnc,pnl,cen_num,neigh,numpp,pnt);
    int t1=0,t2=0,t3=0,t4=0;
    if( pnc>0 && forel[cen_num].ReturnX() - pnc*col_le - start_x < r )
    {
        t1 = 1; 
        t  = this->add_to_neigh(t,pnc-1,pnl,cen_num,neigh,numpp,pnt);
    }
    if( pnc<n_cl-1 && start_x + (pnc+1)*col_le - forel[cen_num].ReturnX() < r )
    {
        t2 = 1; 
        t  = this->add_to_neigh(t,pnc+1,pnl,cen_num,neigh,numpp,pnt);
    }
    if( pnl>0 && forel[cen_num].ReturnY() - pnl*line_le - start_y < r )
    {
        t3 = 1; 
        t  = this->add_to_neigh(t,pnc,pnl-1,cen_num,neigh,numpp,pnt);
    }
    if( pnl<n_cl-1 && start_y + (pnl+1)*line_le - forel[cen_num].ReturnY() < r )
    {
        t4 = 1; 
        t  = this->add_to_neigh(t,pnc,pnl+1,cen_num,neigh,numpp,pnt);
    }
    
    if(t1 && t3)  t=this->add_to_neigh(t,pnc-1,pnl-1,cen_num,neigh,numpp,pnt);
    if(t2 && t3)  t=this->add_to_neigh(t,pnc+1,pnl-1,cen_num,neigh,numpp,pnt);
    if(t1 && t4)  t=this->add_to_neigh(t,pnc-1,pnl+1,cen_num,neigh,numpp,pnt);
    if(t2 && t4)  t=this->add_to_neigh(t,pnc+1,pnl+1,cen_num,neigh,numpp,pnt);
    
    return t;  
}
int My_Type5::static_neigh (int cen_num, My_Point2D**neigh, My_Point2D**pnt)
{
    bool centre_moved = true;
    double sumx,sumy;
    int nop_neigh, *numpp_neigh;
    numpp_neigh = new int [nop];

    while(centre_moved)
    {
	    sumx = sumy = 0;
        centre_moved = false;
        
        nop_neigh = this->neigh(cen_num, neigh, pnt, numpp_neigh);
        for(int i=0; i<nop_neigh; i++) 
        {
            sumx += neigh[i]->ReturnX(); 
            sumy += neigh[i]->ReturnY();
        }
        sumx = sumx/nop_neigh; sumy = sumy/nop_neigh;
        if( fabs(forel[cen_num].ReturnX() - sumx) > eps || 
            fabs(forel[cen_num].ReturnY() - sumy) > eps ) centre_moved = true;
        forel[cen_num] = My_Point2D(sumx, sumy);
    }
    for(int i=0; i<nop_neigh; i++) point_mark[ 3*numpp_neigh[i] + 2 ] = cen_num;

    delete [] numpp_neigh;
    return nop_neigh;
}
int My_Type5::forel_(My_Poisk *P, My_Point2D** pnt)
{
    My_Point2D **neigh = new My_Point2D* [nop];
    int nop_neigh, nocl = 0, markered = 0, t;

    while(markered < nop)
    {
        t = 0;
        while (point_mark[3*t + 2] != -1) t++;
        forel[nocl] = *pnt[t];
        nop_neigh = this->static_neigh(nocl++, neigh, pnt);
        P->addCluster(nop_neigh,neigh);
        markered += nop_neigh;
    }
    P->addCenters(forel,nocl);
    P->get_r(r);

	delete [] neigh;
    return nocl;
}