#include <sstream>
#include <cstring>
#include <fstream>
//#include <iostream>

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

My_Interface::My_Interface() {limit = 0;}
void My_Interface::help_()
{
    ifstream fin("help.txt");
    if (!fin) //cout<<"error - (HELP) :: can't open file help.txt\n";
    {
        cout<<"CREATE   (double cx, double cy, double DSPx,  ||  create Group with centre ('cx','cy'), dispertion('DSPx','DSPy'), number of points 'N'\n";
        cout<<"                          double DSPy, int N)     ~ add 1 group to FIELD\n";
        cout<<"STARSKY  (double xmin, double xmax,           ||  create a Group consisting of 'n' points evenly distributed on a rectangle\n";
        cout<<"           double ymin, double ymax, int n)       ['xmin';'xmax']x['ymin';'ymax']\n";
        cout<<"                                                  ~ add 1 group to FIELD\n";
        cout<<"MOGR     (int number, double px, double py)   ||  move Group with number 'number' to the point ('px','py')\n";
        cout<<"STGR     (int number, double dx, double dy)   ||  stretch CLOUD with number 'number' on coefficient ('dx','dy')\n";
        cout<<"TUGR     (int number, double fi)              ||  turn Group with number 'number' angle 'fi'\n";
        cout<<"\n";
        cout<<"SHOW     (int num)                            ||  print Group with number 'number'\n";
        cout<<"SAVE     (int number, string file_name)       ||  save Group with number 'number' in file 'file_name'\n";
        cout<<"SAVE-ALL (string file_name)                   ||  save all Groups in file 'file_name'\n";
        cout<<"\n";
        cout<<"EXIT                                          ||  stop command input (exit)\n";
    }
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
    if(comma == "") {cout<<"empty input"<<endl; return "EMPTY INPUT";}
    string FileName1;
    ofstream f;
    double D1,D2,D3,D4;
    int INT1;
	if(parse(comma).str_("HELP").success()) { this->help_(); return "help"; }
    if(parse(comma).str_("CREATE").double_(D1).double_(D2).double_(D3).double_(D4).int_(INT1).success())
    {
        limit++;
        C.createCLOUD(D1,D2,D3,D4,INT1);
        return "OK";
    }
    if(parse(comma).str_("STARSKY").double_(D1).double_(D2).double_(D3).double_(D4).int_(INT1).success())
    {
        limit++;
        C.createSTARSKY(D1,D2,D3,D4,INT1);
        return "OK";
    }
    if(parse(comma).str_("TUGR").int_(INT1).double_(D1).success())
    {
        C.turnCLOUD(INT1,D1);
        return "OK";
    }
    if(parse(comma).str_("MOGR").int_(INT1).double_(D1).double_(D2).success())
    {
        C.moveCLOUD(INT1,D1,D2);
        return "OK";
    }
    if(parse(comma).str_("STGR").int_(INT1).double_(D1).double_(D1).success())
    {
        C.stretchCLOUD(INT1,D1,D2);
        return "OK";
    }
    if(parse(comma).str_("SHOW").int_(INT1).success())             //!!!
    {
        if (INT1 > limit || INT1 < 1) return "error (SHOW num) :: no proper group ";
        C.Print_CLOUD(INT1);
        return "OK";
    }
    if(parse(comma).str_("SAVE").int_(INT1).qrstr_(FileName1).success())
    {
        int i=0;
        while ( !( FileName1[i] == '.' && FileName1[i+1] == 't' && FileName1[i+2] == 'x' && FileName1[i+3] == 't' ) ) 
        {
            i++;
            if(i+4 > FileName1.length() ) return "error (SAVE-ALL name) :: can't open file " + FileName1;
        }
        FileName1.erase(i+4);
        f.open(FileName1.c_str()); f.close();
        C.save_CLOUD_in_file(INT1,FileName1.c_str());
        return "OK";
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
        f.open(FileName1.c_str()); f.close();
        C.save_all_clouds(FileName1.c_str());
        return "OK";
	}
    if(parse(comma).str_("EXIT").success())
    {
        return "END";
    }
    return "NOT SATED COMMAND";
}
void My_Interface::do_it()
{
    cout<<"SELECT HOW TO ENTER COMMANDS >> 1 to read commands from file" << endl << "\t\t\t\t2 to enter commands manually" << endl;
    int method;
    cout<<"> "; cin>>method;
    switch (method)
    {
    case 1:
    {
        string comma = "", res;
        cout<<"file name > ";
        string name; cin>>name;
        ifstream f( name.c_str() );
        if(!f) { cout<<"error: Can't open file "<<name<<endl; break; }
            
        char buf[50];   
        ofstream err("error.txt");
        do
        {
            f.getline(buf,50); comma = buf;
            res = this->ReadCommand(comma);
            err<<res<<"\n";
            cout<<res<<endl;
        } 
        while(! parse(comma).str_("EXIT").success() );

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