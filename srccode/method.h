#ifndef METHOD_HEADER
#define METHOD_HEADER

#include "string"
#include "vector"

#include "var_data.h"

#define Parameters VariadicData_linkedlist&

#define ADD_METHOD(f_name)\
  _m_adr ___m_dmpvar##f_name =

typedef void (*output_callback)(int Iteration, ...);
typedef void (*method_callback)(Parameters, output_callback);

enum data_type{
  dt_int64,
  dt_int,
  dt_double,
  dt_float,
  dt_string
};

struct method_data{
  public:
    method_callback callback;
    std::string method_name;
    std::vector<std::pair<std::string, data_type>> datatype;
    std::vector<std::pair<std::string, data_type>> input_parameter;
};

// don't care about returned values
int add_method(method_data *data);

class _m_adr{
  public:
    _m_adr(method_data *md){
      add_method(md);
    }
};

#endif