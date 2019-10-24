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
        int N, type;
        My_Cluster* clusters;
    public:
        My_Poisk();
        ~My_Poisk();
        void get_type(int);
        int ret_type();

        void addCluster(int, My_Point2D** );                   //dobavlenie clustera

        void printCluster(int);                                 //pechat' v komadnu'u stroku
        void printClasterFILE(int, const char* );               //pechat' v fajl
        void PrintAllClasterFile(const char* );                 //dopysyvanie v fajl (kogda mnogo clasterov)
        void PrintAllClasterFile(int, const char* );                 //dopysyvanie v fajl (kogda mnogo clasterov)
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