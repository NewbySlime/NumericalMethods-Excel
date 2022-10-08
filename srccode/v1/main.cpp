#include "iostream"
#include "string"
#include "sstream"
#include "math.h"

#include "../../Libraries/libxlsxw/include/xlsxwriter.h"
#include "fungsi.h"


using namespace std;


const string _extname = ".xlsx";

long long _lastiter = 0;
long long _smallestiter = 0;
double _smallestd = 0.0f;

lxw_workbook *currwb;
lxw_worksheet *currws;

double _var_a, _var_b, _var_te;
long long _var_bp, _var_mt;

void output_tabel(long long iterasi, double x, double fx){
  worksheet_write_number(currws, iterasi, 0, iterasi, NULL);
  worksheet_write_number(currws, iterasi, 1, x, NULL);
  worksheet_write_number(currws, iterasi, 2, fx, NULL);

  if(abs(fx) < _smallestd){
    _smallestiter = iterasi;
    _smallestd = abs(fx);
  }
}

void output_biseksi(long long iterasi, double a, double b, double x, double fx, double fa, std::string ket){
  worksheet_write_number(currws, iterasi, 0, iterasi, NULL);
  worksheet_write_number(currws, iterasi, 1, a, NULL);
  worksheet_write_number(currws, iterasi, 2, b, NULL);
  worksheet_write_number(currws, iterasi, 3, x, NULL);
  worksheet_write_number(currws, iterasi, 4, fx, NULL);
  worksheet_write_number(currws, iterasi, 5, fa, NULL);
  worksheet_write_string(currws, iterasi, 6, ket.c_str(), NULL);

  if(_lastiter < iterasi)
    _lastiter = iterasi;
}

void output_regula_falsi(long long iterasi, double a, double b, double fa, double fb, double fc, double c){
  worksheet_write_number(currws, iterasi, 0, iterasi, NULL);
  worksheet_write_number(currws, iterasi, 1, a, NULL);
  worksheet_write_number(currws, iterasi, 2, b, NULL);
  worksheet_write_number(currws, iterasi, 3, fa, NULL);
  worksheet_write_number(currws, iterasi, 4, fb, NULL);
  worksheet_write_number(currws, iterasi, 5, fc, NULL);
  worksheet_write_number(currws, iterasi, 6, c, NULL);

  if(_lastiter < iterasi)
    _lastiter = iterasi;
}

void m_tabel(){
  cout << "Proses metode tabel...\nMasukkan banyak pecahan:   "; cin >> _var_bp; fflush(stdin);

  currws = workbook_add_worksheet(currwb, "Tabel");
  worksheet_write_string(currws, 0, 0, "Iterasi", NULL);
  worksheet_write_string(currws, 0, 1, "x", NULL);
  worksheet_write_string(currws, 0, 2, "f(x)", NULL);

  _smallestiter = 0;
  _smallestd = INFINITY;
  metode_tabel(_var_a, _var_b, _var_bp);

  lxw_format *newf = workbook_add_format(currwb);
  newf->bg_color = _smallestd < _var_te? LXW_COLOR_GREEN: LXW_COLOR_YELLOW;

  worksheet_set_row(currws, _smallestiter, LXW_DEF_ROW_HEIGHT, newf);
}

void m_biseksi(){
  cout << "Proses metode biseksi..." << endl;
  
  currws = workbook_add_worksheet(currwb, "Biseksi");
  worksheet_write_string(currws, 0, 0, "Iterasi", NULL);
  worksheet_write_string(currws, 0, 1, "a", NULL);
  worksheet_write_string(currws, 0, 2, "b", NULL);
  worksheet_write_string(currws, 0, 3, "x", NULL);
  worksheet_write_string(currws, 0, 4, "f(x)", NULL);
  worksheet_write_string(currws, 0, 5, "f(a)", NULL);
  worksheet_write_string(currws, 0, 6, "Ket", NULL);

  worksheet_set_column(currws, 6, 6, 16.0f, NULL);

  _lastiter = 0;
  metode_biseksi(_var_a, _var_b, _var_te, _var_mt);

  lxw_format *newf = workbook_add_format(currwb);
  newf->bg_color = LXW_COLOR_GREEN;

  worksheet_set_row(currws, _lastiter, LXW_DEF_ROW_HEIGHT, newf);
}

void m_regula_falsi(){
  cout << "Proses metode regula falsi..." << endl;

  currws = workbook_add_worksheet(currwb, "Regula Falsi");
  worksheet_write_string(currws, 0, 0, "Iterasi", NULL);
  worksheet_write_string(currws, 0, 1, "a", NULL);
  worksheet_write_string(currws, 0, 2, "b", NULL);
  worksheet_write_string(currws, 0, 3, "f(a)", NULL);
  worksheet_write_string(currws, 0, 4, "f(b)", NULL);
  worksheet_write_string(currws, 0, 5, "f(c)", NULL);
  worksheet_write_string(currws, 0, 6, "c", NULL);

  _lastiter = 0;
  metode_regula_falsi(_var_a, _var_b, _var_te, _var_mt);

  lxw_format *newf = workbook_add_format(currwb);
  newf->bg_color = LXW_COLOR_GREEN;

  worksheet_set_row(currws, _lastiter, LXW_DEF_ROW_HEIGHT, newf);
}


int main(){
  string filename;
  cout << "Nama file yang akan dibuat: "; cin >> filename;

  if(filename.length() <= 0){
    cout << "Nama file kosong." << endl;
    return 1;
  }

  if(filename.length() <= _extname.length() || filename.substr(filename.length()-_extname.length()-1) != _extname)
    filename += _extname;

  currwb = workbook_new(filename.c_str());

  // testing for file name
  lxw_error lerr = workbook_close(currwb);
  if(lerr != lxw_error::LXW_NO_ERROR){
    cout << "File tidak bisa dibuat. Kode error: " << (int)lerr << endl;
    return (int)lerr;
  }

  currwb = workbook_new(filename.c_str());
  cout << "Masukkan batas atas:       "; cin >> _var_a; fflush(stdin);
  cout << "Masukkan batas bawah:      "; cin >> _var_b; fflush(stdin);
  cout << "Masukkan maks iterasi:     "; cin >> _var_mt; fflush(stdin);
  cout << "Masukkan toleransi error:  ";{
    cin >> _var_te;
    int c = cin.peek();
    if(c == '^'){
      char _c; cin >> _c;
      double e; cin >> e;
      _var_te = pow(_var_te, e);
    }
  }fflush(stdin);

  cout << endl;

  if(_var_a < _var_b){
    auto _tmp = _var_a;
    _var_a = _var_b;
    _var_b = _tmp;
  }
  

  m_tabel();
  m_biseksi();
  m_regula_falsi();

  workbook_close(currwb);

  cout << "Program selesai!" << endl;
}