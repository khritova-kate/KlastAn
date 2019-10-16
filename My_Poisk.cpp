#include "My_Classes.h"

My_Poisk::My_Poisk()
{
    clusters = new My_Cluster [70];
}
My_Poisk::~My_Poisk()
{
    delete [] clusters;
}
void My_Poisk::get_type(int TYPE)                              { type = TYPE; }
void My_Poisk::addCluster(int nop, My_Point2D** clust_pnt)
{
    clusters[++N].AddPointList(nop, clust_pnt);
}
void My_Poisk::printCluster(int num)                           { clusters[num].printCluster(); }
void My_Poisk::printClasterFILE(int num, const char* FileName) { clusters[num].printClasterFILE(FileName); }
void My_Poisk::PrintAllClasterFile(const char* FileName)       { for(int i=0;i<N;i++) clusters[i].PrintAllClasterFile(i,FileName); }