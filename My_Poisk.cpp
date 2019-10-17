#include "My_Classes.h"

//#include <iostream>
//using namespace std;

My_Poisk::My_Poisk()
{
    clusters = new My_Cluster [150];           // !!!
}
My_Poisk::~My_Poisk()
{
    delete [] clusters;
}
void My_Poisk::get_type(int TYPE)                              { type = TYPE; }
int  My_Poisk::ret_type()                                      { return type; }
void My_Poisk::addCluster(int nop, My_Point2D** clust_pnt)
{
    clusters[N].AddPointList(nop, clust_pnt);
    N++;
}
void My_Poisk::printCluster(int num)                           { clusters[num].printCluster(); }
void My_Poisk::printClasterFILE(int num, const char* FileName) { clusters[num].printClasterFILE(FileName); }
void My_Poisk::PrintAllClasterFile(const char* FileName)       { for(int i=0;i<N;i++) clusters[i].PrintAllClasterFile(i,FileName); }
void My_Poisk::PrintAllClasterFile(int n, const char* FileName){ for(int i=0;i<N;i++) clusters[i].PrintAllClasterFile(n+i,FileName); }