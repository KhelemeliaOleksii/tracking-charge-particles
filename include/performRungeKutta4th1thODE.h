#ifndef PERFORMRUNGEKUTTA4TH1THODE_H
#define PERFORMRUNGEKUTTA4TH1THODE_H

// int calculateCoeff1(const double x, const double t, const double dt,
//                     int function(const double x_temp, const double t_temp, double *result_temp),
//                     double *result);

// int calculateCoeff2(const double x, const double t, const double dt,
//                     int function(const double x_temp, const double t_temp, double *result_temp),
//                     const double coeffPrev,
//                     double *result);

// int calculateCoeff3(const double x, const double t, const double dt,
//                     int function(const double x_temp, const double t_temp, double *result_temp),
//                     const double coeffPrev,
//                     double *result);

// int calculateCoeff4(const double x, const double t, const double dt,
//                     int function(const double x_temp, const double t_temp, double *result_temp),
//                     const double coeffPrev,
//                     double *result);

// int calculateNext(const double xn, const double t, const double dt,
//                   int function(const double x_temp, const double t_temp, double *result_temp),
//                   double *xn1);

// int writeResults(const double x, const double t);

// int writeHeaderForResults();

int performRungeKutta4th1thODE(const double initArgue, const double initFuncValue,
                               const double finalArgue, const int numberStep,
                               int function(const double argu, const double funcValue,

                                            double *result_temp));

#endif // PERFORMRUNGEKUTTA4TH1THODE_H