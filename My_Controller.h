#include "My_Field.h"

class My_Controller
{
private:
    My_Field F;
public:
    My_Controller();                                            //consructor
    ~My_Controller();                                           //destructor
    //My_Field* RetFIELD();                                       //vernut' pole
    void createCLOUD  (double, double, double, double, int);    //sozdat' oblako
    void createSTARSKY(double, double, double, double, int);    //ravnomerno zapolnennyj kvadrat
    void moveCLOUD    (int, double, double);                    //sdvig oblaka
    void stretchCLOUD (int, double, double);                    //rast'agenie
    void turnCLOUD    (int, double);                            //povorot
    void save_CLOUD_in_file (int, const char*);                 //pechat' oblaka v fajl
    void save_all_clouds    (const char*);                      //pechat' vsekh oblakov v fajl
    void Print_CLOUD(int) ;                                     //pechat' v komandnu'u stroku
};