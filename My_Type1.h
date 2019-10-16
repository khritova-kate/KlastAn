#include "My_Point2D.h"
#include "My_Poisk.h"

class My_Type1
{
    public:
        int nop, distances01, point_mark;  // chislo tochek
        double dist, distances;            // rasstojanie meshdu tochkami
        My_Point2D** points;               // massiv ssylok na tochki
    private:
        My_Type1(int , double );
        ~My_Type1();
        My_Type1& pnt_(int, My_Group2D**);
        My_Type1& dst_();
        My_Type1& dst01_();
        void save_(My_Poisk );
};