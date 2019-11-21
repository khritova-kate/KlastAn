#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <math.h>

#define eps 1e-15
#define pi 3.1415926535897932

#define N_OF_POISK 20
#define N_OF_CLOUDS 30
#define ITERATIONS 10000
#define OK "  OK"

struct edge
{
    int begin = 0, end = 0;
    double len = 0;
};

class My_Point2D
{
   private:
       double x, y;                             
       int numb;                                    
   public:
       My_Point2D(double, double);             //inizialisazia
       My_Point2D();                           //inizialisazia
       ~ My_Point2D();                         //destructor
       My_Point2D (const My_Point2D& );        //constructor copirovania
       double ReturnX();                       // X
       double ReturnY();                       // Y
       void operator =  (const  My_Point2D& );
       void operator += (const  My_Point2D& ); 
       void operator *= (const  My_Point2D& );
       void AssignNumb();                      // tocke prisvaivaets'a por'adkovy' nomer
       double Dist (const My_Point2D* );       //rasstoyanie ot dannoy tochki do argumenta
};

class My_Group2D
{
   private:
       double x, y, DSPx, DSPy;                             //coordinaty i dispersi'a
       int n, numb;                                         //nomer i chaslo tochek
       My_Point2D *PointList;                               //tochki
    public:
        My_Group2D();                                       //inizialisazia
        My_Group2D(double, double, double, double, int );   //inizialisazia
        ~My_Group2D();                                      //destructor
        My_Group2D (const My_Group2D& );                    //constructor copirovania
        void operator = (const My_Group2D& );
        void printCLOUD();                                  //pechat' v komadnu'u stroku
        void printCLOUDinFILE(const char* );                //pechat' v fajl
        void PrintAllCLinFile(int , const char* );           //dopysyvanie v fajl (kogda mnogo oblakov)
        void AssignNumb();                                  //gruppe prisvaivaets'a por'adkovy' nomer
        //void ChangeNumb( int );                             //perenumerovka
        //void ChangeN( int );                                //ismenenie chisla tochek
        //void ChangePOINT(My_Point2D*, int );                //ismenenie odnoj tochki v gruppe
        void AddPointList(int , My_Point2D*);               //dobavlenie massiva tochek
        //int RetNumb();                                      //nomer
        int RetN();                                         //chislo tochek
        //double RetCentre_x();                               //zentr oblaka
        //double RetCentre_y(); 
        My_Point2D* RetPOINT (int );                        //kaka'a-to tocha oblaka
        void MoveCLOUD(My_Point2D*);                        //sdvig oblaka
        void StretchCLOUD(const double&,const double&);     //rast'agenie oblaka
        void RotateCLOUDcm (double );                       //povorot otnositelno centra mass
};

class My_Cluster
{
    private:
        int n ;                       //chislo tochek
        My_Point2D **PointList;       //massiv ssylok na tochki
    public:
        My_Cluster(int);                                        //constructor
        My_Cluster();                                           //constructor
        ~My_Cluster();                                          //destructor
        int ReturnN();                                          //chislo tochek
        void printCluster();                                    //pechat' v komadnu'u stroku
        void printClasterFILE(const char* );                    //pechat' v fajl
        void PrintAllClasterFile(int num, const char* );        //dopysyvanie v fajl (kogda mnogo clasterov)
        void AddPointList (int, My_Point2D** );                 //zapolnenie massiva PointList pri uslovii, chto pam'at' usge vydelena
};

class My_Poisk
{
    private:
        int N, type, n_of_col, *barchart, k_means_K, k_means_P;
        My_Cluster* clusters;
        My_Point2D* k_means_centers;
        double r;
    public:
        My_Poisk();
        ~My_Poisk();
        void get_type(int);
        int ret_type();

        void addCluster(int, My_Point2D** );                   //dobavlenie clustera

        void printCluster(int);                                 //pechat' v komadnu'u stroku
        void printClasterFILE(int, const char* );               //pechat' v fajl
        void PrintAllClasterFile(const char* );                 //dopysyvanie v fajl (kogda mnogo clasterov)
        void PrintAllClasterFile(int, const char* );            //dopysyvanie v fajl (kogda mnogo clasterov)

        void get_barch(int, int*);
        void PrintBarch(const char*);

        void addCenters (My_Point2D* , int);                    //dobavlenie centrov k-mens v fajl
        void get_k_p (int, int );
        void PrintCentersFile (const char*);                    //vypisyvanie centrov k-mens v fajl

        void get_r (double );
        void PrintCircles (const char*);
};

class My_Type1
{
    private:
        int nop, *distances01, *point_mark;  // chislo tochek
        double dist;                         // rasstojanie meshdu tochkami
    public:
        My_Type1(int , double );
        ~My_Type1();
        My_Type1& dst01_(double *dst);
        int save_(My_Poisk* , My_Point2D**);
};

class My_Type2
{
    private:
        edge *T;
        int nop, noc, *pnt_mark;
        double porog;
    public:
        My_Type2(int, int, edge**);
        ~My_Type2();
        int min_edge_(int, int*, int*, double*, double*,int);
        My_Type2& tree_(double *);
        My_Type2& barch_(My_Poisk*);
        int find_clust(int , int *, My_Point2D**, My_Point2D** );
        int save_(My_Poisk* , My_Point2D**);
};

class My_Type3
{
    private:
        int nop, *point_mark, k;
        My_Point2D* centres;
    public:
        My_Type3(int,int,My_Point2D**);
        ~My_Type3();
        bool centres_group(My_Point2D**);                   //po cenram - gruppu, vosvrashaet true, esli marker tochki ismenils'a, i false inache
        void group_centres(My_Point2D**);                   //po gruppe centry
        void save_(My_Poisk*, My_Point2D**);
        void k_means_centers_(My_Point2D*, My_Point2D**);   //zagrugaet centry v massiv (pnt - massiv tochek gruppy) Achtung pri objavlenii Type3 v Type4
};

class My_Type4
{
    private:
        int nop, *point_mark, k, p;
        My_Point2D* cores;
    public:
        My_Type4(int,int,int,My_Point2D**);
        ~My_Type4();
        bool core_group(My_Point2D**);
        void group_core(My_Point2D**,double*);
        void neighbors(double*, My_Point2D**, My_Point2D**);
        void centres_group(My_Point2D**);
        void save_(My_Poisk*, My_Point2D**, double*);
};

class My_Type5
{
    private:
        int nop, nop_cell, *point_mark, n_cl, nof;
        double r, start_x, start_y, col_le, line_le;
        My_Point2D* forel;
    public:
        My_Type5(int, double , My_Point2D**);                                 //razbivaem pole na kletki
        ~My_Type5();                                      
        int add_to_neigh(int, int, int, int, My_Point2D**, int*, My_Point2D**);
        int neigh(int, My_Point2D**, My_Point2D**, int*);
        int static_neigh (int, My_Point2D**, My_Point2D**);
        int forel_(My_Poisk*, My_Point2D**);
};