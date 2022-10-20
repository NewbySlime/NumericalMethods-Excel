#include "method.h"
#include "editing.h"
#include "iostream"

#include "math.h"

using namespace std;


// some (unnecessary) function
double f_x(double x){
  return pow(x,2) - exp(x) + 9;
}

double f_x1(double x){
  return pow(exp(x)-9, 0.5);
}

double f_x2(double x){
  return (exp(x)+9)/x;
}

double f_x_(double x){
  return 2*x - exp(x);
}

double f_x__(double x){
  return 2 - exp(x);
}



// actual methods
void metode_iterasi_sederhana(Parameters param, output_callback output){
  float x_awal = param.next<float>();
  float tol_err = param.next<float>();
  int maks_iter = param.next<int>();

  add_text(0, 0, "Name: Your Name");

  int _coliter = 2;
  vector<double(*)(double)> _func = {
    f_x1,
    f_x2
  };

  for(int _if = 0; _if < _func.size(); _if++){
    _coliter += 2;

    string _fname = "Fungsi ke-" + to_string(_if+1);
    add_text(_coliter++, 0, _fname.c_str());
    init_table(_coliter++);

    float x0 = x_awal;
    float _err = INFINITY;
    for(int i = 0; i < maks_iter && _err > tol_err; i++){
      _err = abs(f_x(x0));
      float x = _func[_if](x0);

      output(_coliter++, i+1, x0, x, _err);
      x0 = x;
    }
  }
}


// registrating method of 'metode_iterasi_sederhana'
ADD_METHOD(metode_iterasi_sederhana) new method_data{
  .callback = metode_iterasi_sederhana,
  .method_name = "Metode Iterasi Sederhana",
  .datatype = {
    {"Iterasi", data_type::dt_int},
    {"x", data_type::dt_float},
    {"g(x)", data_type::dt_float},
    {"Ea/f(x)", data_type::dt_float}
  },
  
  .input_parameter = {
    {"X awal", data_type::dt_float},
    {"Toleransi Error", data_type::dt_float},
    {"Maks Iterasi", data_type::dt_int}
  }
};