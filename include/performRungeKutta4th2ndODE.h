#ifndef PERFORMRUNGEKUTTA4TH2NDODE_H

#define PERFORMRUNGEKUTTA4TH2NDODE_H

int writeHeaderForResults();

int writeResults(const double t, const double x, const double v);

int calculateCoeff1(const double t, const double x, const double v, const double dt,
                    int function(const double t_temp, const double x_temp, const double v_temp, double *result_temp),
                    double *result);

int calculateCoeff2(const double t, const double x, const double v, const double dt,
                    int function(const double t_temp, const double x_temp, const double v_temp, double *result_temp),
                    const double coeffPrev,
                    double *result);

int calculateCoeff3(const double t, const double x, const double v, const double dt,
                    int function(const double t_temp, const double x_temp, const double v_temp, double *result_temp),
                    const double coeffPrev1, const double coeffPrev2,
                    double *result);

int calculateCoeff4(const double t, const double x, const double v, const double dt,
                    int function(const double t_temp, const double x_temp, const double v_temp, double *result_temp),
                    const double coeffPrev2, const double coeffPrev3,
                    double *result);

int calculateNext(const double t, const double x, const double v, const double dt,
                  int function(const double t_temp, const double x_temp, const double v_temp, double *result_temp),
                  double *x_next, double *v_next);

int performRungeKutta4th2ndODE(const double init_t, const double init_x, const double init_v,
                               const double final_t, const int numberStep,
                               int function(const double t_temp, const double x_temp, const double v_temp, double *result_temp));

#endif // PERFORMRUNGEKUTTA4TH2NDODE_H