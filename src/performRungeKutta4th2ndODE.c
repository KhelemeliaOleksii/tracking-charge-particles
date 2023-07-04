//////////
// AFTER: https://www.engr.colostate.edu/~thompson/hPage/CourseMat/Tutorials/CompMethods/Rungekutta.pdf
//////////
#include <math.h>
#include <stdio.h>

int writeResults(const double t, const double x, const double v)
{
    fprintf(stdout, "%e\t%e\t%e\n", t, x, v);
    return 0;
};

int writeHeaderForResults()
{
    fprintf(stdout, "t\tx\tv\n");
    return 0;
};

int calculateCoeff1(const double t, const double x, const double v, const double dt,
                    int function(const double t_temp, const double x_temp, const double v_temp, double *result_temp),
                    double *result)
{
    function(t, x, v, result);
    // *result *= dt;

    return 0;
};

int calculateCoeff2(const double t, const double x, const double v, const double dt,
                    int function(const double t_temp, const double x_temp, const double v_temp, double *result_temp),
                    const double coeffPrev,
                    double *result)
{
    function(t + dt / 2., x + v * dt / 2., v + coeffPrev * dt / 2., result);
    // *result *= dt;
    return 0;
};

int calculateCoeff3(const double t, const double x, const double v, const double dt,
                    int function(const double t_temp, const double x_temp, const double v_temp, double *result_temp),
                    const double coeffPrev1, const double coeffPrev2,
                    double *result)
{
    function(t + dt / 2, x + v * dt / 2. + coeffPrev1 * dt * dt / 4., v + coeffPrev2 * dt / 2., result);
    // *result *= dt;
    return 0;
};

int calculateCoeff4(const double t, const double x, const double v, const double dt,
                    int function(const double t_temp, const double x_temp, const double v_temp, double *result_temp),
                    const double coeffPrev2, const double coeffPrev3,
                    double *result)
{
    function(t + dt, x + v * dt + coeffPrev2 * dt / 2, v + coeffPrev3 * dt, result);
    // *result *= dt;
    return 0;
}

int calculateNext(const double t, const double x, const double v, const double dt,
                  int function(const double t_temp, const double x_temp, const double v_temp, double *result_temp),
                  double *x_next, double *v_next)
{
    double coeff1, coeff2, coeff3, coeff4;

    calculateCoeff1(t, x, v, dt, function, &coeff1);
    calculateCoeff2(t, x, v, dt, function, coeff1, &coeff2);
    calculateCoeff3(t, x, v, dt, function, coeff1, coeff2, &coeff3);
    calculateCoeff4(t, x, v, dt, function, coeff2, coeff3, &coeff4);

    *x_next = x + v * dt + (coeff1 + coeff2 + coeff3) * dt * dt / 6.;
    *v_next = v + (coeff1 + (2 * coeff2) + (2 * coeff3) + coeff4) * dt / 6.;

    return 0;
}

int performRungeKutta4th2ndODE(const double tInitial, const double xInitial, const double vInitial,
                               const double tFinal, const int numberStep,
                               int function(const double tTemp, const double xTemp, const double vTemp, double *result))
{
    int i;
    double temp_t = tInitial;
    double temp_x = xInitial;
    double temp_v = vInitial;

    double step_t = (tFinal - tInitial) / ((double)numberStep);

    writeHeaderForResults();
    writeResults(temp_t, temp_x, temp_v);

    for (i = 0; i < numberStep; i++)
    {
        calculateNext(temp_t, temp_x, temp_v, step_t, function, &temp_x, &temp_v);
        temp_t += step_t;

        writeResults(temp_t, temp_x, temp_v);
    }

    return 0;
}
