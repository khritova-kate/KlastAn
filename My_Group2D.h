#include "My_Point2D.h"

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