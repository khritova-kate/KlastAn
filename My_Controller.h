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
    void createARCup  (double, double, double, int);
    void createARCdown(double, double, double, int);
    void createARC    (double, double, double, int);

    void moveCLOUD    (int, double, double);                    //sdvig oblaka
    void stretchCLOUD (int, double, double);                    //rast'agenie
    void turnCLOUD    (int, double);                            //povorot

    void save_CLOUD_in_file (int, const char*);                 //pechat' oblaka v fajl
    void save_all_clouds    (const char*);                      //pechat' vsekh oblakov v fajl
    void Print_CLOUD(int) ;                                     //pechat' v komandnu'u stroku

    int ConnCLOUD(double , bool);
    int SpanningTree (int, bool);
    void k_means (int , bool);
    void k_means_core (int, int, bool);
    int forel(double, bool);
    
    void print_Clust (int, int);
    void save_Clust_in_file (int, int, const char*);
    void save_all_Clust (int, const char*);
    void save_all_Clust_type (int, const char*);
    void save_Tree (const char*);

    bool save_barchart (int, const char*);
    bool save_k_means_centres (int, const char*);
    bool save_forel_circles (int, const char* );
};