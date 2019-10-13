#include "My_Point2D.h"

class My_Cluster
{
private:
    int n ;                       //chislo tochek
    My_Point2D **PointList;       //massiv ssylok na tochki
public:
    My_Cluster(int);                                        //constructor
    ~My_Cluster();                                          //destructor
    int ReturnN();                                          //chislo tochek
    void printCluster();                                    //pechat' v komadnu'u stroku
    void printClasterFILE(const char* );                    //pechat' v fajl
    void PrintAllClasterFile(int num, const char* );        //dopysyvanie v fajl (kogda mnogo clasterov)
    void AddPointList (int, My_Point2D** );                 //zapolnenie massiva PointList pri uslovii, chto pam'at' usge vydelena
};