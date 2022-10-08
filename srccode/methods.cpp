#include "method.h"
#include "iostream"

#include "math.h"

using namespace std;


// some (unnecessary) function
double fungsi_x(double x){
  return pow(x,2) - exp(x) + 9;
}


// method function creation
void metode_tabel(Parameters param, output_callback output){
  // parameter initiation
  double a = param.next<double>();
  double b = param.next<double>();
  int64_t banyak_pecahan = param.next<int64_t>();


  // mencari step dari pecahan
  double step_pecahan = (a-b)/banyak_pecahan;
  
  // menghitung satu persatu sesuai dengan banyak pecahan dari a ke b
  double x = a;
  for(int i = 0; i <= banyak_pecahan; i++){

    // pemanggilan persamaan fungsi untuk dihitung
    double fx = fungsi_x(x);

    // jangan lupa untuk memanggil output untuk program memproses selanjutnya dan menuliskan di excel
    output(i, x, fx);

    // kemudian x dikurangi dengan step
    x -= step_pecahan;
  }
}

// registrating method of 'metode_tabel'
ADD_METHOD(metode_tabel) new method_data{
  .callback = metode_tabel,
  .method_name = "Metode Tabel",
  .datatype = {
    {"x", data_type::dt_double},
    {"f(x)", data_type::dt_double}
  },
  
  .input_parameter = {
    {"a", data_type::dt_double},
    {"b", data_type::dt_double},
    {"banyak pecahan", data_type::dt_int64}
  }
};