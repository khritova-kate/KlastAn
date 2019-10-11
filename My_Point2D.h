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
};