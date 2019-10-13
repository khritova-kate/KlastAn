#include <time.h>
#include <stdlib.h>

#include "My_Field.h"

// ============================================= creation and simple operations =============================================
      
My_Field::My_Field (int n=0): N(n) 
{
    clouds_basic = new My_Group2D[100]; 
}
My_Field::My_Field (): N(0)
{
    clouds_basic = new My_Group2D[100]; 
}
My_Field::~My_Field()
{
    delete [] clouds_basic;
} 
int    My_Field::ReturnN   ()                                         {return N;}
My_Point2D* My_Field::RetPoint      (int num_of_cloud,int num_of_pnt) {return clouds_basic[num_of_cloud-1].RetPOINT(num_of_pnt);}
int    My_Field::RetCLOUDpower (int num)                              {return clouds_basic[num-1].RetN();}
/*int    My_Field::NumberOfPOINT ()
{
    int n_of_points = 0;
    for (int i=0;i<N;i++) n_of_points += clouds_basic[i].RetN();
    return n_of_points;
}*/

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
    clouds_basic[N]=My_Group2D(x,y,DSPx,DSPy,nop);
    clouds_basic[N].AssignNumb();
    N++;
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
    N++;
    delete [] pnt;
}