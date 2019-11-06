#include "My_Classes.h"

using namespace std;

My_Poisk::My_Poisk()
{
    clusters = new My_Cluster [150];           // !!!
    k_means_centers = NULL;
}
My_Poisk::~My_Poisk()
{
    delete [] clusters;
    if (k_means_centers != NULL) delete [] k_means_centers;
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

void My_Poisk::addCenters (My_Point2D *centers , int k)
{
    k_means_K = k;
    k_means_centers = new My_Point2D [k];
    for(int i=0; i<k; i++) k_means_centers[i] = centers[i];
    cout<<"in add Centers (K = "<<k_means_K<<"):\n";
    for(int i=0;i<k_means_K;i++) cout<<k_means_centers[i].ReturnX()<<"  "<<k_means_centers[i].ReturnY()<<"  "<<i<<"\n";
}
void My_Poisk::PrintCentersFile (const char* FileName)
{
    ofstream fout (FileName);

    cout<<"in Print Centers (K = "<<k_means_K<<"):\n";
    for(int i=0;i<k_means_K;i++) cout<<k_means_centers[i].ReturnX()<<"  "<<k_means_centers[i].ReturnY()<<"  "<<i<<"\n";

    for (int i=0; i<k_means_K; i++)
        fout<<k_means_centers[i].ReturnX()<<"  "<<k_means_centers[i].ReturnY()<<"  "<<i<<"\n";
    fout.close();
}