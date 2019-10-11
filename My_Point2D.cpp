#include "My_Point2D.h"
 
My_Point2D:: My_Point2D(double xx=0, double yy=0)
{
    x = xx; y = yy;
} 
My_Point2D::My_Point2D(){ x=0; y=0; }
My_Point2D::~My_Point2D(){}
My_Point2D::My_Point2D (const My_Point2D& p)            
{
    x = p.x; y = p.y;
}
double My_Point2D::ReturnX()    {return x;}
double My_Point2D::ReturnY()    {return y;}

void My_Point2D::operator = (const My_Point2D& p)
{
    x = p.x; y = p.y;
}
void My_Point2D::operator += (const My_Point2D& p)    {x += p.x;  y += p.y; } 
void My_Point2D::operator *= (const My_Point2D& p)    {x *= p.x; y *= p.y;} 
void My_Point2D::AssignNumb() 
{
    static int NUMBER = -1; 
    NUMBER++; 
    numb = NUMBER;
} 
