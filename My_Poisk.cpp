#include "My_Classes.h"

using namespace std;

My_Poisk::My_Poisk()
{
    clusters = new My_Cluster [N_OF_CLUSTER];           // !!!
    k_means_centers = NULL;
    k_means_P = 1;
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
}
void My_Poisk::get_k_p (int k, int p)   {k_means_K = k; k_means_P = p; }
void My_Poisk::PrintCentersFile (const char* FileName)
{
    ofstream fout (FileName);
    for (int i=0; i<k_means_K; i++)
        for (int j=0; j<k_means_P; j++)
            fout<<k_means_centers[i*k_means_P + j].ReturnX()<<"  "<<k_means_centers[i*k_means_P + j].ReturnY()<<"  "<<i<<"\n";
    fout.close();
}
void My_Poisk::get_r (double R) {r = R;} 
void My_Poisk::PrintCircles (const char* FileName)
{
    ofstream fout (FileName);
    for (int i=0; i<k_means_K; i++)
        fout<<k_means_centers[i].ReturnX()<<"  "<<k_means_centers[i].ReturnY()<<"  "<<r<<"\n";
    fout.close();
}