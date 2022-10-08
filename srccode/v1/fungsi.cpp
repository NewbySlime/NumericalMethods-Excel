#include "fungsi.h"
#include "math.h"

/*      DIBACA      */
/**
 * Jadi ini adalah lembar pengerjaan fungsi-fungsi yang diperlukan agar program berjalan.
 * 
 * Diisi sesuai dengan tempatnya masing-masing.
 * Setiap diatas codingan fungsi yang tersedia disini akan dikasih comment untuk memberi tahu fungsi nya untuk apa.
 */



// ini adalah fungsi untuk menyelesaikan persamaan fungsi f(x)
double fungsi_x(double x){
  return pow(x,2) - exp(x) + 9;
}



// program akan menjalankan fungsi ini apabila program akan mengisi file excel dengan metode tabel.
//
// program juga memerlukan output dari metode ini dengan fungsi ini memanggil fungsi tertentu yang disediakan.
//
// untuk memanggil fungsi output metode ini: 
//    output_tabel(long long iterasi, double x, double fx);
//
void metode_tabel(double a, double b, long long banyak_pecahan){
  // mencari step dari pecahan
  double step_pecahan = (a-b)/banyak_pecahan;
  
  // menghitung satu persatu sesuai dengan banyak pecahan dari a ke b
  double x = a;
  for(int i = 0; i <= banyak_pecahan; i++){

    // pemanggilan persamaan fungsi untuk dihitung
    double fx = fungsi_x(x);

    // jangan lupa untuk memanggil output untuk program memproses selanjutnya dan menuliskan di excel
    output_tabel(i+1, x, fx);

    // kemudian x ditambahkan dengan step
    x -= step_pecahan;
  }
}



// program akan menjalankan fungsi ini apabila program akan mengisi file excel dengan metode biseksi.
//
// program juga memerlukan output dari metode ini dengan fungsi ini memanggil fungsi tertentu yang disediakan.
//
// untuk memanggil fungsi output metode ini: 
//    output_biseksi(long long iterasi, double a, double b, double x, double fx, double fa, std::string ket);
//
void metode_biseksi(double a, double b, double tol_error, long long maks_toleransi){
  double fa = fungsi_x(a);
  double fb = fungsi_x(b);
  double x = (a+b)/2;

  // nggak ada akar
  if((fa*fb) > 0){
    output_biseksi(1, a, b, x, fungsi_x(x), fa, "Tidak ada akar");
    return;
  }

  double fx = fungsi_x(x);
  for(int i = 0; i < maks_toleransi; i++){
    bool b1 = (fx*fa) < 0;
    output_biseksi(i+1, a, b, x, fx, fa, b1? "Tanda kebalik": "");

    if(abs(fx) < tol_error)
      break;

    if(b1)
      b = x;
    else
      a = x;

    x = (a+b)/2;
    fx = fungsi_x(x);
    fa = fungsi_x(a);
  }
}


// program akan menjalankan fungsi ini apabila program akan mengisi file excel dengan metode biseksi.
//
// program juga memerlukan output dari metode ini dengan fungsi ini memanggil fungsi tertentu yang disediakan.
//
// untuk memanggil fungsi output metode ini: 
//    output_regula_falsi(long long iterasi, double a, double b, double fa, double fb, double fc, double c);
//
void metode_regula_falsi(double a, double b, double tol_error, long long maks_toleransi){
  for(int i = 0; i < maks_toleransi; i++){
    double fa = fungsi_x(a);
    double fb = fungsi_x(b);
    double x = (fb*a-fa*b)/(fb-fa);
    double fx = fungsi_x(x);

    output_regula_falsi(i+1, a, b, fa, fb, fx, x);

    // tidak ada akar
    if(i == 0 && (fa*fb) > 0)
      break;

    if(abs(fx) < tol_error)
      break;

    if((fx*fa) < 0)
      b = x;
    else
      a = x;
  }
}