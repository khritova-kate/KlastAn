#include <time.h>
#include <stdlib.h>

#include "My_Field.h"

//#include <iostream>
//using namespace std;

// ============================================= creation and simple operations =============================================
      
My_Field::My_Field (int n=0): N(n), N_P(0), n_of_points(0)
{
    clouds_basic = new My_Group2D[30];
    clouds = new My_Group2D* [30];
    Poisk = new My_Poisk [20]; 
}
My_Field::My_Field (): N(0), N_P(0), n_of_points(0)
{
    clouds_basic = new My_Group2D[100];
    clouds = new My_Group2D* [100]; 
    Poisk = new My_Poisk [50];
    distances = NULL;
    points = NULL;
}
My_Field::~My_Field()
{
    delete [] clouds_basic;
    delete [] clouds;
    delete [] Poisk;
    if (distances != NULL) delete [] distances;
    if (points != NULL)    delete [] points;
} 
int    My_Field::ReturnN   ()                                         {return N;}
My_Point2D* My_Field::RetPoint      (int num_of_cloud,int num_of_pnt) {return clouds_basic[num_of_cloud-1].RetPOINT(num_of_pnt);}
int    My_Field::RetCLOUDpower (int num)                              {return clouds_basic[num-1].RetN();}

void My_Field::PrintCLOUD(int num)                         { clouds_basic[num-1].printCLOUD(); }
void My_Field::PrintCLinFile(int num, const char* Fname)   { clouds_basic[num-1].printCLOUDinFILE(Fname); }
void My_Field::PrintAllCLinFile_bas  (const char* Fname)   { for(int i=0;i<N;i++) clouds_basic[i].PrintAllCLinFile(i,Fname); }

void My_Field::MoveCL       (int num, My_Point2D *p)       {clouds_basic[num-1].MoveCLOUD(p);}
void My_Field::RotateCLOUD  (int num, double ang)          {clouds_basic[num-1].RotateCLOUDcm(ang);}
void My_Field::StretchCLOUD (int num, My_Point2D *p)       {clouds_basic[num-1].StretchCLOUD(p->ReturnX(),p->ReturnY());}
      
//void My_Field::AddPointList(int numb_of_cloud,int n_of_points,My_Point2D*pnt)
//      { clouds_basic[numb_of_cloud-1].AddPointList(n_of_points,pnt); }
void My_Field::AddCLOUD(double x,double y,double DSPx,double DSPy,int nop)
{
    clouds_basic[N] = My_Group2D(x,y,DSPx,DSPy,nop);
    clouds_basic[N].AssignNumb();
    clouds[N] = &clouds_basic[N];
    N++; n_of_points += nop;
}
void My_Field::star_sky(double minx,double maxx,double miny,double maxy, int n)
{
    My_Point2D*pnt; pnt = new My_Point2D [n];
    double x,y,dx=maxx-minx,dy=maxy-miny;
    srand(time(NULL));
    for(int i=0;i<n;i++)
    {
        x=minx + (rand()%int(dx*10000))*0.0001;
        y=miny + (rand()%int(dy*10000))*0.0001;
        pnt[i] = My_Point2D(x,y);
    }
    clouds_basic[N].AddPointList(n,pnt);
    clouds_basic[N].AssignNumb();
    clouds[N] = &clouds_basic[N];
    N++; n_of_points += n;
    delete [] pnt;
}

// ============================================= clust_an :: type 1 =============================================

void My_Field::pnt_()
{
    int i,j,k=0, n;

    if(points == NULL) points = new My_Point2D* [n_of_points];
    else
    {
        delete [] points;
        points = new My_Point2D* [n_of_points];
    }
    for (i=0; i<N; i++)
    {
        n = clouds[i]->RetN();
        for (j=0; j < n; j++) points[k+j] = clouds[i]->RetPOINT(j);
        k += clouds[i]->RetN();
    }
}
void My_Field::dst_()
{
    int i,j;
    if(distances == NULL) distances = new double [n_of_points*n_of_points];
    else
    {
        delete [] distances;
        distances = new double [n_of_points*n_of_points];
    }
    for (i=0; i<n_of_points; i++)
    {
        distances[i*n_of_points + i] = 0;
        for (j=i+1; j<n_of_points; j++)
        {
            distances[i*n_of_points + j] = points[i]->Dist(points[j]); 
            distances[j*n_of_points + i] = distances[i*n_of_points + j];
        }
    }
}
int My_Field::Type1(double dis, bool need_to_find_dist)
{
    Poisk[N_P].get_type(1);
    if(need_to_find_dist)
    {
        this->pnt_();
        this->dst_();
    }
    int nocl = My_Type1(n_of_points,dis).dst01_(distances).save_(&Poisk[N_P], points);
    N_P++;
    return nocl;
}
void My_Field::PrintClust(int num_p, int num_cl)
{
    Poisk[num_p].printCluster(num_cl);
}
void My_Field::PrintClustFILE(int num_p, int num_cl, const char* FileName)
{
    Poisk[num_p].printClasterFILE(num_cl,FileName);
}
void My_Field::PrintAllClustFILE(int num_p, const char* FileName)
{
    Poisk[num_p].PrintAllClasterFile(FileName);
}
void My_Field::PrintAllClustTypeFILE(int type, const char* FileName)
{
    int i, qual = 0;
    for (i=0;i < N_P; i++)
        if(Poisk[i].ret_type() == type) Poisk[i].PrintAllClasterFile(qual++, FileName);
}