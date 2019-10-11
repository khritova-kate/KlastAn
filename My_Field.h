#include "My_Group2D.h"

class My_Field
{
   private:
      int N;                                            
      My_Group2D *clouds_basic; // **clouds; CLOUD** clouds_buff;             
   public:

      // ============================================= creation and simple operations =============================================
      
      My_Field (int);
      My_Field ();
      ~My_Field();
      int        ReturnN   ();                    //N
      //My_Point2D* RetPoint      (int ,int );      //vosvrashaet tochku pol'a
      //int        RetCLOUDpower (int );           //chislo toche v gruppe
      //int        NumberOfPOINT ();               //chislo tochek v pole

      void PrintCLOUD(int );                     //pechat' oblaka v komandnu'u stroku                
      void PrintCLinFile(int , const char* );    //pchat' v fajl
      void PrintAllCLinFile_bas  (const char*);  //pechat' vsekh oblakov v fajl
      
      void   MoveCL        (int , My_Point2D*);       //sdvig oblaka
      void   RotateCLOUD   (int , double);       //povorot
      void   StretchCLOUD  (int , My_Point2D*);       //rast'agenie

      //void AddPointList(int, int, My_Point2D* );                //dobavlenie tochek v oblako
      void AddCLOUD(double, double, double, double, int );      //dobavlenie oblaka
      void star_sky(double, double, double, double, int );      //ravnomerno zapolnennyj tochkami kvadrat
};