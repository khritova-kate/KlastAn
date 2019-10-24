#include <iostream>
#include <fstream>
#include <math.h>

#include "My_Classes.h"

#define pi 3.1415926535897932

using namespace std;

My_Group2D::My_Group2D()
{ x=0; y=0; DSPx = 1; DSPy = 1; n = 0; }
My_Group2D::My_Group2D(double xx, double yy, double DSPxx, double DSPyy, int N):
        x(xx), y(yy), DSPx(DSPxx), DSPy(DSPyy), n(N)
{
    double sumx = 0, sumy = 0, Cx = 0, Cy = 0;
    int i;
    numb = 0;
    if(n!=0)
    {
        PointList = new My_Point2D[n];
        srand(time(NULL));
        for (i=0;i<n;i++)
        {
            for (int j=0;j<1001;j++)
            { 
                sumx += (rand() %10001 - 5000)*0.0001; 
                sumy += (rand() %10001 - 5000)*0.0001; 
            }
            PointList[i] = My_Point2D(x + DSPx*sumx/1001, y + DSPy*sumy/1001);
            PointList[i].AssignNumb();
            sumx = sumy = 0;
            Cx+=PointList[i].ReturnX();
            Cy+=PointList[i].ReturnY();
        }
        Cx = Cx/n; Cy = Cy/n;
        My_Point2D inaccuracy(x-Cx,y-Cy);
        for (i=0;i<n;i++) PointList[i] += inaccuracy;
    }
}
My_Group2D::~My_Group2D() {delete [] PointList;}
My_Group2D::My_Group2D (const My_Group2D& cl)
{
    x = cl.x; y = cl.y;
    DSPx = cl.DSPx; DSPy = cl.DSPy;
    n = cl.n; numb = cl.numb;
}
void My_Group2D::operator = (const My_Group2D&CLL)
{
    x = CLL.x; y = CLL.y; DSPx = CLL.DSPx; DSPy = CLL.DSPy; n = CLL.n; numb = CLL.numb;
    PointList = new My_Point2D[n];
    for (int i=0;i<n;i++) PointList[i] = CLL.PointList[i];
}
void My_Group2D::printCLOUD()
{
    for (int k=0;k<n;k++) cout << PointList[k].ReturnX() << "   " << PointList[k].ReturnY() << endl;
} 
void My_Group2D::printCLOUDinFILE(const char* FileName)
{
    ofstream fout(FileName);
    for (int k=0;k<n;k++) fout << PointList[k].ReturnX() << "   " << PointList[k].ReturnY() << "\n";
	fout << "\n";
	fout.close();
}
void My_Group2D::PrintAllCLinFile(int num, const char* FileName)
{
    ofstream fout(FileName, ios::app);
	for (int k=0;k<n;k++) fout << PointList[k].ReturnX() << "  " << PointList[k].ReturnY() << "  " << num << "\n";
	fout.close();
}
void My_Group2D::AssignNumb() 
{ 
    static int NUMBER = 0; 
    NUMBER++; 
    numb = NUMBER;
}
//void My_Group2D::ChangeNumb(int num) {numb = num;}
//void My_Group2D::ChangeN   (int nn ) {n=nn;} 
//void My_Group2D::ChangePOINT(My_Point2D *p, int i) {PointList[i] = *p;}
void My_Group2D::AddPointList(int N, My_Point2D*points)
{
    n=N;
    if (!PointList) PointList = new My_Point2D[n];
    else 
    {
        delete [] PointList;
        PointList = new My_Point2D[n];
    }
    for (int i=0;i<n;i++) {PointList[i] = points[i];}
}
//int My_Group2D::RetNumb() {return numb;}
int My_Group2D::RetN   () {return n;}
//double My_Group2D::RetCentre_x() {return x;}
//double My_Group2D::RetCentre_y() {return y;}
My_Point2D* My_Group2D::RetPOINT (int i)   {return &PointList[i];}
void My_Group2D::MoveCLOUD(My_Point2D *p)
{ 
    for(int i=0;i<n;i++) PointList[i] += *p; 
    x += p->ReturnX(); 
    y += p->ReturnY();
} 
void My_Group2D::StretchCLOUD(const double& Ax, const double& Ay)
{
    for (int i=0;i<n;i++)
    {
        PointList[i] += My_Point2D(-x,-y);
        PointList[i] *= My_Point2D(Ax,Ay);
        PointList[i] += My_Point2D(x,y);
    }
}
void My_Group2D::RotateCLOUDcm (double b)
{
    double Cx=0, Cy=0; int i;
    for (i=0;i<n;i++) { Cx += PointList[i].ReturnX(); Cy += PointList[i].ReturnY();}
    Cx = Cx/n; Cy = Cy/n;
    for (i=0;i<n;i++)
    {
        double katy = PointList[i].ReturnY()-Cy;
        double katx=PointList[i].ReturnX()-Cx;
        double gip = sqrt(katx*katx + katy*katy);
        double a = asin(katy/gip);
        if ((katx/gip)<0) a = pi-a;
        PointList[i] = My_Point2D(Cx + gip*cos(a+b), Cy + gip*sin(a+b));
    }
}