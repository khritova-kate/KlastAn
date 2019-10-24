#include "My_Controller.h"

//#include <iostream>
//using namespace std;

My_Controller::My_Controller () {}
My_Controller::~My_Controller() {}
//My_Field* My_Controller::RetFIELD() { return &F; }
void My_Controller::createCLOUD(double cx, double cy, double DSPx, double DSPy, int n)
{
    F.AddCLOUD(cx,cy,DSPx,DSPy,n);
}
void My_Controller::createSTARSKY(double minx,double maxx,double miny,double maxy, int n) 
{
    F.star_sky(minx,maxx,miny,maxy,n);
}
void My_Controller::moveCLOUD(int cloud_number, double px, double py)
{
    My_Point2D p(px,py);
    F.MoveCL(cloud_number,&p);
}
void My_Controller::stretchCLOUD(int cloud_number, double px, double py)
{
    My_Point2D p(px,py);
    F.StretchCLOUD(cloud_number,&p);
}
void My_Controller::turnCLOUD(int cloud_number, double angle)
{
    F.RotateCLOUD(cloud_number,angle);
}
void My_Controller::save_CLOUD_in_file(int cloud_number,const char*FileName)
{
    F.PrintCLinFile(cloud_number,FileName);
}
void My_Controller::save_all_clouds (const char* FileName)
{
    //printf("\ngot '%s'\n",FileName);
    F.PrintAllCLinFile_bas(FileName);
}
void My_Controller::Print_CLOUD(int num)
{
    F.PrintCLOUD(num);
}
int My_Controller::ConnCLOUD(double dis, bool need_to_find_dist)
{
    return F.Type1(dis, need_to_find_dist);
}
void My_Controller::print_Clust (int num_p, int num_c)
{
    F.PrintClust(--num_p, --num_c);
}
void My_Controller::save_Clust_in_file (int num_p, int num_c, const char* FileName)
{
    F.PrintClustFILE(--num_p,--num_c,FileName);
}
void My_Controller::save_all_Clust (int num_p, const char* FileName)
{
    F.PrintAllClustFILE(--num_p,FileName);
}
void My_Controller::save_all_Clust_type (int type, const char* FileName)
{
    F.PrintAllClustTypeFILE(type,FileName);
}