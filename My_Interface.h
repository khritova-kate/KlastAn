#include <cstring>
#include <iostream>

#include "My_Controller.h"

using namespace std;

bool move_ptr(int& , const string& );
bool test_ptr(int& , const string& , char );
bool match_int(const string & , int& , string& );
bool match_float(const string & , double& , string& );
bool skip_str(const string & , const string& , string& );
bool match_str(const string& , string& , string& );
string skip_spaces(const string& );

class parse       //klass dl'a chtenia strok
{
private:
    string tail;
    string err_info; 
    bool err;
    void handle_err(bool , const string& );
public:
    parse(const string& );
    parse& double_(double& );
    parse& double_(double& , double );
    parse& int_(int& );
    parse& int_(int& , int );
    parse& str_(const string& str);
    parse& qrstr_(string& );
    bool success();
    string get_err_info();
};

class My_Interface
{
private:
    My_Controller C;                         //controller
    int limit;                               //chislo oblacov
public:
    My_Interface();                          //inizialisazia
    void help_();                            //pro HELP
    string ReadCommand(string comma) ;       //chtenie comandy
    void do_it();                            //obshenie s pol'sovatelem
};