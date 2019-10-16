#include "My_Interface.h"

int main()
{
    //My_Interface I;
    //I.do_it();
    My_Field F;
    F.AddCLOUD(0,0,10,10,1000);
    F.AddCLOUD(0,2,10,10,1000);
    int nop = F.NumberOfPOINT();
    F.Type1(nop,1);
    return 0;
}