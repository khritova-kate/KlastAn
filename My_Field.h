#include "My_Classes.h"

class My_Field
{
   private:
      int N, N_P, n_of_points;                  //chislo grupp, poiskov, tochek polja                                 
      My_Group2D *clouds_basic, **clouds;       //grupy i ssylki na gruppy
      My_Poisk *Poisk;                          //poiski
      double *distances;                        //rasstoyanie meshdu tochksmi
      My_Point2D **points;                      //ssylki na tochki polja
      edge* Tree;                               //tree of distances
   public:

      // ============================================= creation and simple operations =============================================
      
      My_Field (int);
      My_Field ();
      ~My_Field();
      int        ReturnN   ();                   //N
      My_Point2D* RetPoint      (int ,int );     //vosvrashaet tochku pol'a
      int        RetCLOUDpower (int );           //chislo toche v gruppe

      void PrintCLOUD(int );                     //pechat' oblaka v komandnu'u stroku                
      void PrintCLinFile(int , const char* );    //pchat' v fajl
      void PrintAllCLinFile_bas  (const char*);  //pechat' vsekh oblakov v fajl
      
      void   MoveCL        (int , My_Point2D*);       //sdvig oblaka
      void   RotateCLOUD   (int , double);       //povorot
      void   StretchCLOUD  (int , My_Point2D*);       //rast'agenie

      //void AddPointList(int, int, My_Point2D* );                //dobavlenie tochek v oblako
      void AddCLOUD(double, double, double, double, int );      //dobavlenie oblaka
      void star_sky(double, double, double, double, int );      //ravnomerno zapolnennyj tochkami kvadrat
      void arc_up  (double, double, double, int, double);
      void arc_down(double, double, double, int, double);
      void arc     (double, double, double, int, double);

      // ============================================= clust_an :: type 1 =============================================

      void pnt_();
      void dst_();
      int Type1(double, bool);
      void PrintClust(int, int );
      void PrintClustFILE(int, int , const char*);
      void PrintAllClustFILE(int, const char*);
      void PrintAllClustTypeFILE(int, const char*);

     // ============================================= clust_an :: type 1 =============================================
   
      int Type2(int, bool);
      void save_Tree(const char*);
      bool save_barch(int, const char*);

     // ============================================= clust_an :: type 3 ============================================= 

      void find_far_away_points (My_Point2D**, int ) ;   //k>1 !!
      void k_means(int , bool);
      bool save_centers (int , const char* );

     // ============================================= clust_an :: type 4 ============================================= 

      void k_means_core(int, int, bool);

     // ============================================= clust_an :: type 5 ============================================= 

      int forel(double, bool);
      bool save_circles(int, const char*);
};