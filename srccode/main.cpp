#include "string"
#include "iostream"
#include "math.h"

#include "../Libraries/libxlsxw/include/xlsxwriter.h"
#include "method.h"
#include "editing.h"

#define _iter_attr_name "Iteration"


using namespace std;

const string _extname = ".xlsx";

long long _smallestiter = 0;
double _smallestd = 0.0f;

lxw_workbook *currwb;
lxw_worksheet *currws;

static vector<method_data*> *_m_datas = NULL;
method_data *currmd;

lxw_format *_def_tableheadfmt;


// editing.h functions
void init_table(int row){
  for(int o = 0; o < currmd->datatype.size(); o++)
    worksheet_write_string(currws, row, o, currmd->datatype[o].first.c_str(), _def_tableheadfmt);
}

void add_text(int row, int col, const char *str){
  worksheet_write_string(currws, row, col, str, NULL);
}


double get_double(){
  double res;
  cin >> res;
  int c = cin.peek();
  if(c == '^'){
    char _c; cin >> _c;
    double e; cin >> e;
    res = pow(res, e);
  }

  return res;
}

void output_method(int i, ...){
  va_list _arg;
  va_start(_arg, i);

  for(int _i = 0; _i < currmd->datatype.size(); _i++){
    switch(currmd->datatype[_i].second){
      break; case data_type::dt_float:
        case data_type::dt_double:{
        double _r = va_arg(_arg, double);
        worksheet_write_number(currws, i, _i, _r, NULL);
      }

      break; case data_type::dt_int64:{
        int64_t _r = va_arg(_arg, int64_t);
        worksheet_write_number(currws, i, _i, _r, NULL);
      }
      
      break; case data_type::dt_int:{
        int32_t _r = va_arg(_arg, int32_t);
        worksheet_write_number(currws, i, _i, _r, NULL);
      }

      break; case data_type::dt_string:{
        const char *_r = va_arg(_arg, const char*);
        worksheet_write_string(currws, i, _i, _r, NULL);
      }
    }
  }

  va_end(_arg);
}

void call_all_method(){
  if(_m_datas->size() > 0 && _m_datas){
    for(int i = 0; i < _m_datas->size(); i++){
      auto _data = _m_datas->operator[](i);

      cout << endl << "Processing " << _data->method_name << "..." << endl;
      currws = workbook_add_worksheet(currwb, _data->method_name.c_str());
      
      _smallestd = INFINITY;
      _smallestiter = 0;

      VariadicData_linkedlist vdll;
      for(int o = 0; o < _data->input_parameter.size(); o++){
        auto *_idata = &_data->input_parameter[o];

        cout << "Input " << _idata->first << ": ";
        switch(_idata->second){
          break; case data_type::dt_double:{
            double _r; _r = get_double();
            vdll.add_tovar(_r);
          }

          break; case data_type::dt_float:{
            float _r; _r = get_double();
            vdll.add_tovar(_r);
          }

          break; case data_type::dt_int64:{
            int64_t _r; cin >> _r;
            vdll.add_tovar(_r);
          }

          break; case data_type::dt_int:{
            int32_t _r; cin >> _r;
            vdll.add_tovar(_r);
          }

          //break; case data_type::dt_string:
        }

        fflush(stdin);
      }

      vdll.init_var();
      currmd = _data;
      _data->callback(vdll, output_method);
    }
  }
  else
    cout << "[ERROR]: No method supplied." << endl; 
}

int add_method(method_data *data){
  if(!_m_datas)
    _m_datas = new vector<method_data*>();

  _m_datas->push_back(data);
}

int main(){
  string filename;
  cout << "Name of the file (extension can be omitted): "; cin >> filename;

  if(filename.length() <= _extname.length() || filename.substr(filename.length()-_extname.length()-1) != _extname)
    filename += _extname;

  currwb = workbook_new(filename.c_str());

  // testing for file name
  lxw_error lerr = workbook_close(currwb);
  if(lerr != lxw_error::LXW_NO_ERROR){
    cout << "[ERROR]: File cannot be created. Error code: " << (int)lerr << endl;
    return (int)lerr;
  }

  currwb = workbook_new(filename.c_str());


  // setting up default variables
  _def_tableheadfmt = workbook_add_format(currwb);
  format_set_bg_color(_def_tableheadfmt, LXW_COLOR_CYAN);
  format_set_border(_def_tableheadfmt, LXW_BORDER_THIN);


  call_all_method();
  workbook_close(currwb);
  cout << "Done calculating!" << endl;
}