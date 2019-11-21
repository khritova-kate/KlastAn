#define N_OF_ALG_TYPES 1
#include "My_Interface.h"

using namespace std;

//============================================================== functions ==============================================================

bool move_ptr(int&ptr,const string& str)
{
    if (ptr < int(str.size()) - 1) {ptr++; return true;}
    ptr = str.size();
    return false;
}
bool test_ptr(int&ptr,const string& str,char c)
{
    if(ptr<int(str.size())) return str[ptr]==c;
    return false;
}
bool match_int(const string& str, int& val, string& tail)
{
    int ptr = 0;
    if (test_ptr(ptr, str, '+') || test_ptr(ptr, str, '-')) move_ptr(ptr, str);
    if (!isdigit(str[ptr])) return false;
    while (isdigit(str[ptr]) && move_ptr(ptr, str));

    string slice = str.substr(0, ptr); 
    char* slice_ch;
    slice_ch = new char [slice.length() + 1 ];
    strcpy( slice_ch , slice.c_str() );
    val = atoi(slice_ch);
    tail = str.substr(ptr);
    delete [] slice_ch;
    return true;
}
bool match_float(const string& str, double& val, string& tail)
{
    int ptr = 0;
    if (test_ptr(ptr, str, '+') || test_ptr(ptr, str, '-')) move_ptr(ptr, str);
    if (!isdigit(str[ptr])) return false;
    while (isdigit(str[ptr]) && move_ptr(ptr, str));
    if (str[ptr] == '.') move_ptr(ptr, str);
    while (isdigit(str[ptr]) && move_ptr(ptr, str));

    string slice = str.substr(0, ptr); 
    char* slice_ch;
    slice_ch = new char [slice.length() + 1 ];
    strcpy( slice_ch , slice.c_str() );
    val = atof(slice_ch);
    tail = str.substr(ptr); 
    delete [] slice_ch;
    return true;
}
bool skip_str(const string& str, const string& val, string& tail)
{
    if (str.find(val) == 0) 
    {
        string slice = str.substr(val.size());
        tail = slice;
        return true;
    }
    return false;
}
bool match_str(const string& str, string& val, string& tail) 
{
    int ptr = 0;
    while ((move_ptr(ptr, str))&&( !test_ptr(ptr, str, ' ') && ( !test_ptr(ptr, str, '\n') ) ));
    string slice = str.substr(0, ptr);
    val = slice;
    tail = str.substr(ptr);
    return true;
}
string skip_spaces(const string& str) 
{
    unsigned ptr = 0;
    while ((ptr < str.size())&&(str[ptr] == ' ' || str[ptr] == '\n' || str[ptr] == '\t')) ptr++; 
    return str.substr(ptr);
}

// ============================================================== classes ============================================================== 

void parse::handle_err(bool match, const string& type)
{
    if (!match)
    {
        err = true;
        string s = (tail.size() < 7) ? tail : tail.substr(0, 7) + "...";
        err_info = string("can't parse '") + s + "' as " + type;
    }
}
parse::parse(const string& tail_): tail(tail_) { err = false; }
parse& parse::double_(double& val)                  
{
    if (err) return *this; 
    handle_err(match_float(tail, val, tail), "double");
    tail = skip_spaces(tail);
    return *this;
}
parse& parse::double_(double& val, double def_val)
{
    if (err) return *this;
    if (tail == "") val = def_val;
    else handle_err(match_float(tail, val, tail), "double");
    tail = skip_spaces(tail);
    return *this;
}
parse& parse::int_(int& val)  
{
    if (err) return *this;
    handle_err(match_int(tail, val, tail), "int");
    tail = skip_spaces(tail);
    return *this;
}
parse& parse::int_(int& val, int def_val)   
{
    if (err) return *this;
    if (tail == "") val = def_val;
    else handle_err(match_int(tail, val, tail), "int");
    tail = skip_spaces(tail);
    return *this;
}
parse& parse::str_(const string& str)
{
    if (err) return *this;
    handle_err(skip_str(tail, str, tail), "string");
    tail = skip_spaces(tail);
    return *this;
}
parse& parse::qrstr_(string& val)
{
    if (err) return *this;
    handle_err(match_str(tail, val, tail), "string");
    tail = skip_spaces(tail);
    return *this;
}
bool parse::success() { return !err; }
string parse::get_err_info() { return err_info; }

// ============================================================= interface  =============================================================
string itoa(int n)
{
    ostringstream number; string str;
    number<<n; str = number.str();
    return str;
}

My_Interface::My_Interface() {limit = 0; limit_p = 0;}
void My_Interface::help_()
{
    ifstream fin("help.txt");
    if (!fin) cout<<"error - (HELP) :: can't open file help.txt\n";
    else
    {
        string str;
        char buf [255];
        while(! fin.eof() )
        {
            fin.getline(buf,255);
            str = buf; 
            cout<<str<<endl;
        }
    }
    fin.close();
}
string My_Interface::ReadCommand(string comma)
{
    if(comma == "") return "EMPTY INPUT";
    string FileName1, word;
    ofstream f;
    double D1,D2,D3,D4;
    int INT1, INT2;
    static int n_of_poisk = 0;

  // =========================================== help exit bas operations ===========================================

    if(parse(comma).str_("HELP").success()) { this->help_(); return ""; }
    if(parse(comma).str_("CREATE").double_(D1).double_(D2).double_(D3).double_(D4).int_(INT1).success())
    {
        limit++;
        C.createCLOUD(D1,D2,D3,D4,INT1);
        need_fill_dst = need_fill_pnt = true;
        return "  OK";
    }
    if(parse(comma).str_("STARSKY").double_(D1).double_(D2).double_(D3).double_(D4).int_(INT1).success())
    {
        limit++;
        C.createSTARSKY(D1,D2,D3,D4,INT1);
        need_fill_dst = need_fill_pnt =  true;
        return "  OK";
    }
    if(parse(comma).str_("ARC").success())
    {
        if(parse(comma).str_("ARC-UP").double_(D1).double_(D2).double_(D3).int_(INT1).success())
        {
            if (D3 < 0) return "error (ARC-UP ... ) :: expected red > 0";
            if (INT1 < 1) return "error (ARC-UP ... ) :: expected int > 1";
            limit++;
            C.createARCup(D1,D2,D3,INT1);
            need_fill_dst = need_fill_pnt =  true;
        }
        if(parse(comma).str_("ARC-DOWN").double_(D1).int_(INT1).success()) C.creteARCdown(D1,INT1);
        if(parse(comma).double_(D1).int_(INT1).success()) printf("full\n");
        return OK;
    }
    if(parse(comma).str_("TUGR").int_(INT1).double_(D1).success())
    {
        C.turnCLOUD(INT1,D1);
        need_fill_dst = need_fill_pnt =  true;
        return "  OK";
    }
    if(parse(comma).str_("MOGR").int_(INT1).double_(D1).double_(D2).success())
    {
        C.moveCLOUD(INT1,D1,D2);
        need_fill_dst = need_fill_pnt =  true;
        return "  OK";
    }
    if(parse(comma).str_("STGR").int_(INT1).double_(D1).double_(D1).success())
    {
        C.stretchCLOUD(INT1,D1,D2);
        need_fill_dst = need_fill_pnt =  true;
        return "  OK";
    }
    if(parse(comma).str_("SHOW").int_(INT1).success())             //!!!
    {
        if (INT1 > limit || INT1 < 1) return "error (SHOW num) :: no proper group ";
        C.Print_CLOUD(INT1);
        return "  OK";
    }
    if(parse(comma).str_("SAVE").int_(INT1).qrstr_(FileName1).success())
    {
        if(INT1 > limit || INT1 < 1) return "error (SAVE num name) :: Group with number " + itoa(INT1) + " doesn't exist";
        int i=0;
        while ( !( FileName1[i] == '.' && FileName1[i+1] == 't' && FileName1[i+2] == 'x' && FileName1[i+3] == 't' ) ) 
        {
            i++;
            if(i+4 > FileName1.length() ) return "error (SAVE num name) :: can't open file " + FileName1;
        }
        FileName1.erase(i+4);
        FileName1 = "saves/" + FileName1;
        f.open(FileName1.c_str()); f.close();
        C.save_CLOUD_in_file(INT1,FileName1.c_str());
        return "  OK";
    }
    if(parse(comma).str_("SAVE-ALL").qrstr_(FileName1).success())
	{
        int i=0;
        while ( !( FileName1[i] == '.' && FileName1[i+1] == 't' && FileName1[i+2] == 'x' && FileName1[i+3] == 't' ) ) 
        {
            i++;
            if(i+4 > FileName1.length() ) return "error (SAVE-ALL name) :: can't open file " + FileName1;
        }
        FileName1.erase(i+4);
        FileName1 = "saves/" + FileName1;
        f.open(FileName1.c_str()); f.close();
        C.save_all_clouds(FileName1.c_str());
        return "  OK";
	}
    if(parse(comma).str_("EXIT").success())
    {
        return "  END";
    }

  // ==================================================== type 1 ====================================================

    if(parse(comma).str_("CONGR").double_(D1).success())
    {
        limit_p++;
        if (n_of_poisk > 16) return "error (CONGR dis) :: not enough memory";
        INT1 = C.ConnCLOUD(D1, need_fill_pnt && need_fill_dst);
        need_fill_dst = need_fill_pnt = false;
        return "  OK : " + itoa(INT1) + " clusters found";
    }
     if(parse(comma).str_("CL-SHOW").int_(INT1).int_(INT2).success())             //!!!
    {
        if (INT1 > limit_p || INT1 < 1) return "error (SHOW num) :: no proper Poisk ";
        if(INT2 < 1) return "error (SHOW num) :: no proper cluster";
        C.print_Clust(INT1, INT2);
        return "  OK";
    }
    if(parse(comma).str_("CL-SAVE").int_(INT1).int_(INT2).qrstr_(FileName1).success())
    {
        if(INT1 > limit_p || INT1 < 1) return "error (SAVE num num name) :: Poisk with number " + itoa(INT1) + " doesn't exist";
        if(INT2 < 1) return "error (SAVE num num name) :: no proper cluster";
        int i=0;
        while ( !( FileName1[i] == '.' && FileName1[i+1] == 't' && FileName1[i+2] == 'x' && FileName1[i+3] == 't' ) ) 
        {
            i++;
            if(i+4 > FileName1.length() ) return "error (SAVE num_p num_c name) :: can't open file " + FileName1;
        }
        FileName1.erase(i+4);
        FileName1 = "saves/" + FileName1;
        f.open(FileName1.c_str()); f.close();
        C.save_Clust_in_file(INT1,INT2,FileName1.c_str());
    }
    if(parse(comma).str_("CL-SAVE-ALL").int_(INT1).qrstr_(FileName1).success())
	{
        if(INT1 > limit_p || INT1 < 1) return "error (SAVE num num name) :: Poisk with number " + itoa(INT1) + " doesn't exist";
        int i=0;
        while ( !( FileName1[i] == '.' && FileName1[i+1] == 't' && FileName1[i+2] == 'x' && FileName1[i+3] == 't' ) ) 
        {
            i++;
            if(i+4 > FileName1.length() ) return "error (SAVE-ALL name) :: can't open file " + FileName1;
        }
        FileName1.erase(i+4);
        FileName1 = "saves/" + FileName1;
        f.open(FileName1.c_str()); f.close();
        C.save_all_Clust(INT1,FileName1.c_str());
        return "  OK";
	}
    if(parse(comma).str_("CL-SAVE-TYPE").int_(INT1).qrstr_(FileName1).success())
    {
        if(INT1 < 1 || INT1 > N_OF_ALG_TYPES ) return "error (SAVE-TYPE ... ) : not proper type";
        int i=0;
        while ( !( FileName1[i] == '.' && FileName1[i+1] == 't' && FileName1[i+2] == 'x' && FileName1[i+3] == 't' ) ) 
        {
            i++;
            if(i+4 > FileName1.length() ) return "error (SAVE-ALL name) :: can't open file " + FileName1;
        }
        FileName1.erase(i+4);
        FileName1 = "saves/" + FileName1;
        f.open(FileName1.c_str()); f.close();
        C.save_all_Clust_type (INT1, FileName1.c_str());
        return "  OK";
    }
  // ==================================================== type 2 ====================================================
    if(parse(comma).str_("SPTREE").int_(INT1).success())
    {
        if (INT1 < 2) return "error (SPTREE ...) :: expected int > 1";
        C.SpanningTree(INT1, need_fill_pnt && need_fill_dst);
        limit_p++;
        need_fill_dst = false; need_fill_pnt = false;

        return OK;
    }
    if(parse(comma).str_("TREE-SAVE").qrstr_(FileName1).success())
    {
        int i=0;
        while ( !( FileName1[i] == '.' && FileName1[i+1] == 't' && FileName1[i+2] == 'x' && FileName1[i+3] == 't' ) ) 
        {
            i++;
            if(i+4 > FileName1.length() ) return "error (TREE-SAVE ...) :: can't open file " + FileName1;
        }
        FileName1.erase(i+4);
        FileName1 = "saves/" + FileName1;
        f.open(FileName1.c_str()); f.close();

        C.save_Tree(FileName1.c_str());

        return OK;
    }
    if(parse(comma).str_("BARCH-SAVE").int_(INT1).qrstr_(FileName1).success())
    {
        if (INT1 > limit_p) return "error (BARCH-SAVE ... ) : Poisk with number " + itoa(INT1) + " doesn't exist";
        int i=0;
        while ( !( FileName1[i] == '.' && FileName1[i+1] == 't' && FileName1[i+2] == 'x' && FileName1[i+3] == 't' ) ) 
        {
            i++;
            if(i+4 > FileName1.length() ) return "error (BARCH-SAVE ...) :: can't open file " + FileName1;
        }
        FileName1.erase(i+4);
        FileName1 = "saves/" + FileName1;
        f.open(FileName1.c_str()); f.close();

        if ( C.save_barchart(INT1-1, FileName1.c_str()) ) return OK;
        return "error (BARCH-SAVE ... ) : Poisk with number " + itoa(INT1) + " doesn't have proper type";;
    }
  // ==================================================== type 3 ====================================================
    if(parse(comma).str_("K-MEANS").int_(INT1).success())
    {
        limit_p++;
        if(limit == 0) return "error (K-MEANS ... ) : empty Field";
        if (INT1 < 1) return "error (K-MEANS ... ) : expected int > 0";
        C.k_means(INT1, need_fill_dst && need_fill_pnt);    
        need_fill_dst = need_fill_pnt = false;
        return "  OK";
    }
    if(parse(comma).str_("CEN-SAVE").int_(INT1).qrstr_(FileName1).success())
    {
        if (INT1 > limit_p) return "error (CEN-SAVE ... ) : Poisk with number " + itoa(INT1) + " doesn't exist";
        int i=0;
        while ( !( FileName1[i] == '.' && FileName1[i+1] == 't' && FileName1[i+2] == 'x' && FileName1[i+3] == 't' ) ) 
        {
            i++;
            if(i+4 > FileName1.length() ) return "error (CEN-SAVE ...) :: can't open file " + FileName1;
        }
        FileName1.erase(i+4);
        FileName1 = "saves/" + FileName1;
        f.open(FileName1.c_str()); f.close();

        if ( C.save_k_means_centres(INT1, FileName1.c_str()) ) return "  OK";
        return "error (CEN-SAVE ... ) : Poisk with number " + itoa(INT1) + " doesn't have proper type";
    }
  // ==================================================== type 4 ====================================================
    if (parse(comma).str_("CORE-K-MEANS").int_(INT1).int_(INT2).success())
    {
        limit_p++;
        if(limit == 0) return "error (CORE-K-MEANS ... ) : empty Field";
        if (INT1 < 1) return "error (CORE-K-MEANS ... ) : expected k > 0";
        if (INT2 < 1) return "error (CORE-K-MEANS ... ) : expected p > 0";
        C.k_means_core(INT1,INT2, need_fill_pnt && need_fill_dst);
        need_fill_dst = need_fill_pnt =  false;
        return "  OK";
    }
  // ==================================================== type 5 ====================================================
    if (parse(comma).str_("FOREL").double_(D1).success())
    {
        limit_p++;
        if(limit == 0) return "error (FOREL ... ) : empty Field";
        if(D1<0) return "error (FOREL ... ) : expected double > 0";

        INT1 = C.forel(D1, need_fill_pnt);
        need_fill_pnt = false;

        return "  OK : " + itoa(INT1) + " clusters found";
    }
    if (parse(comma).str_("CIR-SAVE").int_(INT1).qrstr_(FileName1).success())
    {
        if (INT1 > limit_p) return "error (CIR-SAVE ... ) : Poisk with number " + itoa(INT1) + " doesn't exist";
        int i=0;
        while ( !( FileName1[i] == '.' && FileName1[i+1] == 't' && FileName1[i+2] == 'x' && FileName1[i+3] == 't' ) ) 
        {
            i++;
            if(i+4 > FileName1.length() ) return "error (CIR-SAVE ... ) :: can't open file " + FileName1;
        }
        FileName1.erase(i+4);
        FileName1 = "saves/" + FileName1;
        f.open(FileName1.c_str()); f.close();

        if ( C.save_forel_circles(INT1, FileName1.c_str()) ) return "  OK";
        return "error (CIR-SAVE ... ) : Poisk with number " + itoa(INT1) + " doesn't have proper type";
    }
    return "NOT SATED COMMAND";
}
void My_Interface::do_it(char* argv)
{
    int method; bool ne_arg;
    if(argv == NULL)
    {
        cout<<"SELECT HOW TO ENTER COMMANDS >> 1 to read commands from file" << endl << "\t\t\t\t2 to enter commands manually" << endl;
        cout<<"> "; cin>>method;
        ne_arg = true;
    }
    else { method = 1; ne_arg = false; }
    switch (method)
    {
    case 1:
    {
        string comma = "", name, res;
        if(ne_arg) { cout<<"file name > "; cin>>name; }
        else name = argv;
        
        ifstream f( name.c_str() );
        if(!f) { cout<<"error: Can't open file "<<name<<endl; break; }
            
        char buf[50];   
        ofstream err("saves/error.txt");
        f.getline(buf,50);
        do
        {
            comma = buf;
            cout<<"~ "<<comma<<"\n";
            res = this->ReadCommand(comma);
            err<<comma<<" -- "<<res<<"\n";
            cout<<res<<endl;
        } 
        while(!parse(comma).str_("EXIT").success() && f.getline(buf,50) );
        break;
    }
    case 2:
    {
        string comma = "", res;
        char buf[50]; 
        cout<<"> to open command-list enter 'HELP'\n";
        getline(cin, comma);
        do
        {
            cout<<"> "; getline(cin, comma);
            res = this->ReadCommand(comma);
            cout<<res<<endl;
        } while (! parse(comma).str_("EXIT").success());
        
        break;
    }
    default:
        cout<<"error: incorrect input!\n";
        break;
    }
}