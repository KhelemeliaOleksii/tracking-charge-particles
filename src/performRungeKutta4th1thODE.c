#include <math.h>
#include <stdio.h>

int calculateCoeff1(const double t, const double x, const double dt,
                    int function(const double xTemp, const double tTemp, double *result),
                    double *result)
{
    function(x, t, result);
    *result *= dt;

    return 0;
};

int calculateCoeff2(const double t, const double x, const double dt,
                    int function(const double xTemp, const double tTemp, double *result),
                    const double coeffPrev,
                    double *result)
{
    function(x + coeffPrev / 2., t + dt / 2., result);
    *result *= dt;
    return 0;
};

int calculateCoeff3(const double t, const double x, const double dt,
                    int function(const double xTemp, const double tTemp, double *result),
                    const double coeffPrev,
                    double *result)
{
    function(x + coeffPrev / 2., t + dt / 2., result);
    *result *= dt;
    return 0;
};

int calculateCoeff4(const double t, const double x, const double dt,
                    int function(const double xTemp, const double tTemp, double *result),
                    const double coeffPrev,
                    double *result)
{
    function(x + coeffPrev, t + dt, result);
    *result *= dt;
    return 0;
}

int calculateNext(const double tPrev, const double xPrev, const double dt,
                  int function(const double t, const double x, double *result),
                  double *xNext)
{
    double coeff1, coeff2, coeff3, coeff4;

    calculateCoeff1(tPrev, xPrev, dt, function, &coeff1);
    calculateCoeff2(tPrev, xPrev, dt, function, coeff1, &coeff2);
    calculateCoeff3(tPrev, xPrev, dt, function, coeff2, &coeff3);
    calculateCoeff4(tPrev, xPrev, dt, function, coeff3, &coeff4);

    *xNext = xPrev + (coeff1 + (2 * coeff2) + (2 * coeff3) + coeff4) / 6.;
    return 0;
}

int writeResults(const double t, const double x)
{
    fprintf(stdout, "%e\t%e\n", t, x);
    return 0;
};

int writeHeaderForResults()
{
    fprintf(stdout, "t\tx(t)\n");
    return 0;
};

int performRungeKutta4th1thODE(const double tInitial, const double xInitial,
                               const double tFinal, const int numberStep,
                               int function(const double arguPrev, const double funcValuePrev, double *result))
{
    int i;
    double tTemp = tInitial;
    double xTemp = xInitial;
    double tStep = (tFinal - tInitial) / (double)numberStep;

    writeHeaderForResults();
    writeResults(tTemp, xTemp);

    for (i = 0; i < numberStep; i++)
    {
        calculateNext(tTemp, xTemp, tStep, function, &xTemp);
        tTemp = tTemp + tStep;
        writeResults(tTemp, xTemp);
    }

    return 0;
}
