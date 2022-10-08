#ifndef FUNGSI_HEADER
#define FUNGSI_HEADER

#include "string"

double fungsi_x(double x);

void metode_tabel(double a, double b, long long b_p);
void metode_biseksi(double a, double b, double tol_error, long long maks_toleransi);
void metode_regula_falsi(double a, double b, double tol_error, long long maks_toleransi);

void output_tabel(long long iterasi, double x, double fx);
void output_biseksi(long long iterasi, double a, double b, double x, double fx, double fa, std::string ket);
void output_regula_falsi(long long iterasi, double a, double b, double fa, double fb, double fc, double c);

#endif