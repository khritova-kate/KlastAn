#include <iostream>
#include <fstream>

#include "My_Classes.h"

using namespace std;

My_Cluster::My_Cluster(int N): n(N)
{
    PointList = new My_Point2D* [n];
}
My_Cluster::My_Cluster()  { n=0; }
My_Cluster::~My_Cluster()
{
    delete [] PointList;
}                                     
int My_Cluster::ReturnN()    { return n;    }                                          
void My_Cluster::printCluster()
{
    for(int i=0;i<n;i++) cout << PointList[i]->ReturnX() << "   " << PointList[i]->ReturnY() << endl;
}                                    
void My_Cluster::printClasterFILE(const char* FileName)
{
    ofstream fout(FileName);
    for (int k=0;k<n;k++) fout << PointList[k]->ReturnX() << "   " << PointList[k]->ReturnY() << "\n";
	fout << "\n";
	fout.close();
}                    
void My_Cluster::PrintAllClasterFile(int num, const char* FileName)
{
    ofstream fout(FileName, ios::app);
	for (int k=0;k<n;k++) fout << PointList[k]->ReturnX() << "  " << PointList[k]->ReturnY() << "  " << num << "\n";
	fout.close();
}
void My_Cluster::AddPointList (int N, My_Point2D** points)
{
    n=N;
    if (!PointList) PointList = new My_Point2D* [n];
    else 
    {
        delete [] PointList;
        PointList = new My_Point2D* [n];
    }
    for (int i=0;i<n;i++) PointList[i] = points[i];
}