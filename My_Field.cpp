#include "My_Field.h"

static bool have_tree = false;
static bool have_pnt = false;
static bool have_dst = false;

// ============================================= creation and simple operations =============================================
      
My_Field::My_Field (int n=0): N(n), N_P(0), n_of_points(0)
{
    clouds_basic = new My_Group2D[N_OF_CLOUDS];
    clouds = new My_Group2D* [N_OF_CLOUDS];
    Poisk = new My_Poisk [N_OF_POISK]; 
}
My_Field::My_Field (): N(0), N_P(0), n_of_points(0)
{
    clouds_basic = new My_Group2D[N_OF_CLOUDS];
    clouds = new My_Group2D* [N_OF_CLOUDS]; 
    Poisk = new My_Poisk [N_OF_POISK];
}
My_Field::~My_Field()
{
    delete [] clouds_basic;
    delete [] clouds;
    delete [] Poisk;
    if (have_dst ) delete [] distances;
    if (have_pnt ) delete [] points;
    if (have_tree) delete [] Tree;
} 
int    My_Field::ReturnN   ()                                         {return N;}
My_Point2D* My_Field::RetPoint      (int num_of_cloud,int num_of_pnt) {return clouds_basic[num_of_cloud-1].RetPOINT(num_of_pnt);}
int    My_Field::RetCLOUDpower (int num)                              {return clouds_basic[num-1].RetN();}

void My_Field::PrintCLOUD(int num)                         { clouds_basic[num-1].printCLOUD(); }
void My_Field::PrintCLinFile(int num, const char* Fname)   { clouds_basic[num-1].printCLOUDinFILE(Fname); }
void My_Field::PrintAllCLinFile_bas  (const char* Fname)   { for(int i=0;i<N;i++) clouds_basic[i].PrintAllCLinFile(i,Fname); }

void My_Field::MoveCL       (int num, My_Point2D *p)       {clouds_basic[num-1].MoveCLOUD(p);}
void My_Field::RotateCLOUD  (int num, double ang)          {clouds_basic[num-1].RotateCLOUDcm(ang);}
void My_Field::StretchCLOUD (int num, My_Point2D *p)       {clouds_basic[num-1].StretchCLOUD(p->ReturnX(),p->ReturnY());}
      
//void My_Field::AddPointList(int numb_of_cloud,int n_of_points,My_Point2D*pnt)
//      { clouds_basic[numb_of_cloud-1].AddPointList(n_of_points,pnt); }
void My_Field::AddCLOUD(double x,double y,double DSPx,double DSPy,int nop)
{
    clouds_basic[N] = My_Group2D(x,y,DSPx,DSPy,nop);
    clouds_basic[N].AssignNumb();
    clouds[N] = &clouds_basic[N];
    N++; n_of_points += nop;
}
void My_Field::star_sky(double minx,double maxx,double miny,double maxy, int n)
{
    My_Point2D*pnt; pnt = new My_Point2D [n];
    double x,y,dx=maxx-minx,dy=maxy-miny;
    srand(time(NULL));
    for(int i=0;i<n;i++)
    {
        x=minx + (rand()%int(dx*10000))*0.0001;
        y=miny + (rand()%int(dy*10000))*0.0001;
        pnt[i] = My_Point2D(x,y);
    }
    clouds_basic[N].AddPointList(n,pnt);
    clouds_basic[N].AssignNumb();
    clouds[N] = &clouds_basic[N];
    N++; n_of_points += n;
    delete [] pnt;
}
void My_Field::arc_up(double x_cen, double y_cen, double rad, int n, double width)
{
    My_Point2D *pnt; pnt = new My_Point2D [n];
    double delta = pi/(n-1), x, y;
    srand(time(NULL));
    for(int i = 0; i < n; i++)
    {
        x = x_cen + rad*cos(delta*i) + rad*width*(rand() %1000 - 1000)*0.0001;
        y = y_cen + rad*sin(delta*i) + rad*width*(rand() %1000 - 1000)*0.0001;
        pnt[i] = My_Point2D(x,y);
    }
    clouds_basic[N].AddPointList(n,pnt);
    clouds_basic[N].AssignNumb();
    clouds[N] = &clouds_basic[N];
    N++; n_of_points += n;
    delete [] pnt;
}
void My_Field::arc_down(double x_cen, double y_cen, double rad, int n, double width)
{
    My_Point2D *pnt; pnt = new My_Point2D [n];
    double delta = pi/(n-1), x, y;
    srand(time(NULL));
    for(int i = 0; i < n; i++)
    {
        x = x_cen + rad*cos(- delta*i) + rad*width*(rand() %1000 - 1000)*0.0001;
        y = y_cen + rad*sin(- delta*i) + rad*width*(rand() %1000 - 1000)*0.0001;
        pnt[i] = My_Point2D(x,y);
    }
    clouds_basic[N].AddPointList(n,pnt);
    clouds_basic[N].AssignNumb();
    clouds[N] = &clouds_basic[N];
    N++; n_of_points += n;
    delete [] pnt;
}
void My_Field::arc(double x_cen, double y_cen, double rad, int n, double width)
{
    My_Point2D *pnt; pnt = new My_Point2D [n];
    double delta = 2*pi/(n-1), x, y;
    srand(time(NULL));
    for(int i = 0; i < n; i++)
    {
        x = x_cen + rad*cos(delta*i) + rad*width*(rand() %1000 - 1000)*0.0001;
        y = y_cen + rad*sin(delta*i) + rad*width*(rand() %1000 - 1000)*0.0001;
        pnt[i] = My_Point2D(x,y);
    }
    clouds_basic[N].AddPointList(n,pnt);
    clouds_basic[N].AssignNumb();
    clouds[N] = &clouds_basic[N];
    N++; n_of_points += n;
    delete [] pnt;
}

// ============================================= clust_an :: type 1 =============================================

void My_Field::pnt_()
{
    int i,j,k=0, n;

    if(!have_pnt) points = new My_Point2D* [n_of_points];
    else
    {
        delete [] points;
        points = new My_Point2D* [n_of_points];
    }
    for (i=0; i<N; i++)
    {
        n = clouds[i]->RetN();
        for (j=0; j < n; j++) points[k+j] = clouds[i]->RetPOINT(j);
        k += clouds[i]->RetN();
    }

    have_pnt = true;
}
void My_Field::dst_()
{
    int i,j;

    if(!have_dst) distances = new double [n_of_points*n_of_points];
    else
    {
        delete [] distances;
        distances = new double [n_of_points*n_of_points];
    }
    for (i=0; i<n_of_points; i++)
    {
        distances[i*n_of_points + i] = 0;
        for (j=i+1; j<n_of_points; j++)
        {
            distances[i*n_of_points + j] = points[i]->Dist(points[j]); 
            distances[j*n_of_points + i] = distances[i*n_of_points + j];
        }
    }

    have_dst = true;
}
int My_Field::Type1(double dis, bool need_to_find_dist)
{
    Poisk[N_P].get_type(1);
    if(need_to_find_dist)
    {
        this->pnt_();
        this->dst_();
    }
    int nocl = My_Type1(n_of_points,dis).dst01_(distances).save_(&Poisk[N_P], points);
    N_P++;
    return nocl;
}
void My_Field::PrintClust(int num_p, int num_cl)
{
    Poisk[num_p].printCluster(num_cl);
}
void My_Field::PrintClustFILE(int num_p, int num_cl, const char* FileName)
{
    Poisk[num_p].printClasterFILE(num_cl,FileName);
}
void My_Field::PrintAllClustFILE(int num_p, const char* FileName)
{
    Poisk[num_p].PrintAllClasterFile(FileName);
}
void My_Field::PrintAllClustTypeFILE(int type, const char* FileName)
{
    int i, qual = 0;
    for (i=0;i < N_P; i++)
        if(Poisk[i].ret_type() == type) Poisk[i].PrintAllClasterFile(qual++, FileName);
}
// ============================================= clust_an :: type 2 =============================================

int My_Field::Type2(int n_of_barch_col, bool need_pnt_dis)
{
    Poisk[N_P].get_type(2);
    if(need_pnt_dis)
    {
        this->pnt_();
        this->dst_();
    }

    int nocl;

    if(need_pnt_dis) 
    {
        if(!have_tree) 
        {
            Tree = new edge [n_of_points];
            have_tree = true;
        }
        else
        {
            delete [] Tree;
            Tree = new edge [n_of_points];
        }
        nocl = My_Type2(n_of_points, n_of_barch_col, &Tree).tree_(distances).barch_(&Poisk[N_P]).save_(&Poisk[N_P], points);
    }
    else nocl = My_Type2(n_of_points, n_of_barch_col, &Tree).barch_(&Poisk[N_P]).save_(&Poisk[N_P], points);
    //printf("nocl = %d\n",nocl);

    N_P++;
    return nocl;
}
void My_Field::save_Tree(const char* FileName)
{
    if (!have_tree)
    {
        std::cout<<"Cant save Tree of Distances\n";
        return;
    }
    std::ofstream fout(FileName);
    int i = 0;
    while (i < n_of_points - 1)
    {
        fout<<points[ Tree[i].begin ]->ReturnX()<<"  "<<points[ Tree[i].begin ]->ReturnY()<<"\n";
        fout<<points[ Tree[i].end   ]->ReturnX()<<"  "<<points[ Tree[i].end   ]->ReturnY()<<"\n\n";
        i++;
    }
    fout.close();
}
bool My_Field::save_barch(int p_num, const char* FileName)
{
    if(Poisk[p_num].ret_type() != 2) return false;
    Poisk[p_num].PrintBarch(FileName);
    return true;
}
// ============================================= clust_an :: type 3 =============================================

void My_Field::find_far_away_points (My_Point2D** first_centers, int k) //k>1 !!
{
    int* fircen_num = new int [k];
    fircen_num[0] = 0; fircen_num [1] = 1;
    double maxdist = distances [1], *dist;
    for(int i=0; i<n_of_points; i++)
    {
        dist = distances + i*n_of_points;
        for(int j=i+1; j<n_of_points; j++)
            if( dist[j] > maxdist )
            {
                maxdist = dist[j];
                fircen_num[0] = i;
                fircen_num[1] = j;
            }
    }
    int t = 2;
    bool not_counted, not_met;
    double sum;
    while (t < k)
    {
        not_counted = true; not_met = true;
        for(int i=0; i<n_of_points; i++)
        {
            dist = distances + i*n_of_points;
            for(int p=0; p<t; p++)
                if (i == fircen_num[p]) not_met = false;
            if (not_met)
                for(int j=i+1; j<n_of_points; j++)
                {
                    not_met = true;
                    for(int p=0; p<t; p++)
                        if (j == fircen_num[p]) not_met = false;
                    sum = 0;
                    if( not_met ) 
                    {
                        for(int p=0; p<t; p++) sum += distances[ fircen_num[p]*n_of_points + j ];
                    }
                    if( ( not_met && sum > maxdist ) || not_counted )
                    {
                        maxdist = sum;
                        fircen_num[t] = j;
                        not_counted = false;
                    }
                }
        }
        t++;
    }
    for(int i=0; i<k; i++)
       first_centers[i] = points[ fircen_num[i] ];

    delete [] fircen_num;
}
void My_Field::k_means(int k, bool need_to_fill_pnt)
{
    Poisk[N_P].get_type(3);
    if(need_to_fill_pnt)
    {
        this->pnt_();
        this->dst_();
    }
    My_Point2D** first_centers = new My_Point2D* [k];
    if(k>1) this->find_far_away_points(first_centers, k);
    else first_centers[0] = points[0];

    My_Type3(n_of_points, k, first_centers).save_(&Poisk[N_P], points);

    delete [] first_centers;
    N_P++;
}
bool My_Field::save_centers(int p_num, const char* FileName)
{
    if (Poisk[p_num].ret_type() == 3 || Poisk[p_num].ret_type() == 4 || Poisk[p_num].ret_type() == 5)
    {
        Poisk[p_num].PrintCentersFile(FileName);
        return true;
    }
    return false;
}

// ============================================= clust_an :: type 4 =============================================

void My_Field::k_means_core(int k, int p, bool need_to_fill_pnt)
{
    Poisk[N_P].get_type(4);
    if(need_to_fill_pnt)
    {
        this->pnt_();
        this->dst_();
    }
    My_Point2D** first_centers = new My_Point2D* [k];
    if(k>1) this->find_far_away_points(first_centers, k);
    else first_centers[0] = points[0];

    My_Type4(n_of_points,k,p,first_centers).save_(&Poisk[N_P], points, distances);

    delete [] first_centers;
    N_P++;
}
// ============================================= clust_an :: type 5 =============================================

int My_Field::forel(double r, bool need_to_fill_pnt)
{
    Poisk[N_P].get_type(5);
    if(need_to_fill_pnt) this->pnt_();

    int n_of_clust = My_Type5(n_of_points, r, points).forel_(&Poisk[N_P], points);
    
    N_P++;
    return n_of_clust;
}
bool My_Field::save_circles(int num_p, const char* FileName)
{
    if (Poisk[num_p].ret_type() == 5)
    {
        Poisk[num_p].PrintCircles(FileName);
        return true;
    }
    return false;
}
