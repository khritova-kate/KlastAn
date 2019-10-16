#include "My_Cluster.h"

class My_Poisk
{
private:
    int N, type;
    My_Cluster* clusters;
public:
    My_Poisk();
    ~My_Poisk();
    void get_type(int);

    void addCluster(int, My_Point2D** );                   //dobavlenie clustera

    void printCluster(int);                                 //pechat' v komadnu'u stroku
    void printClasterFILE(int, const char* );               //pechat' v fajl
    void PrintAllClasterFile(const char* );                 //dopysyvanie v fajl (kogda mnogo clasterov)
};