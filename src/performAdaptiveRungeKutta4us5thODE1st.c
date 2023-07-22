/*
**************
Method: Runge–Kutta
**************
Source: Wiki - https://en.wikipedia.org/wiki/Runge%E2%80%93Kutta_methods
        github - https://github.com/rand-asswad/Runge-Kutta/blob/master/main.c#L124

Type: Runge–Kutta–Fehlberg method

Butcher tableau MATRIX
0   |
c2  |  a21
c3  |  a31  a32
c4  |  a41  a42 a43
c5  |  a51  a52 a53 a54
c6  |  a61  a62 a63 a64 a65
--------------------------------------------------------------------
    |   b1  b2  b3  b4  b5  b6
    |   b*1 b*2 b*3 b*4 b*5 b*6

Butcher tableau - coefficients
0       |
1/4     |   1/4
3/8     |   3/32        9/32
12/13   |   1932/2197   -7200/2197  7296/2197
1       |   439/216     -8          3680/513    -845/4104
1/2     |   -8/27       2           -3544/2565  1859/4104   -11/40
--------------------------------------------------------------------
        |   16/135      0           6656/12825  28561/56430 -9/50   2/55
        |   25/216      0           1408/2565   2197/4104   -1/5    0

High order step is given by
yn+1 = yn + h summ(bi ki)

Lower order step is given by
y*n+1 = yn + h summ(b*i ki)

ki are the same as for high-order method

k1 = f(tn, yn)
k2 = f(tn + c2 h, yn + (a21 k1) h)
k3 = f(tn + c3 h, yn + (a31 k1 + a32 k2)h)
...
ks = f(tn + cs h, yn + (as1 k1 + as2 k2 + ... + as,s-1 ks-1)h)

error
en+1 = yn+1 - y*n+1 = h sum ((bi - b*i) ki)
 */

#include <math.h>
#include <stdio.h>

typedef double (*functionType)(const double tTemp, const double xTemp);

int calculateNext(const double tPrev, const double xPrev, const double dt,
                  functionType function, double *xNext, double *xsNext)
{

    double bs6 = 0.036363636; // 2/55
    double bs5 = -0.2;        //-1/5
    double b5 = −0.18;        //-9/50
    double bs4 = 0.535331384; // 2197/4104
    double b4 = 0.50613149;   // 28561/56430
    double bs3 = 0.548927875; // 1408/2565
    double b3 = 0.518986355;  // 6656/12825
    double bs2 = 0.;
    double b2 = 0.;
    double bs1 = 0.115740741; // 25/216
    double b1 = 0.118518519;  // 16/135

    double c2 = 0.25;         // 1/4
    double c3 = 0.375;        // 3/8
    double c4 = 0, 923076923; // 12./13.
    double c5 = 1.;
    double c6 = 0.5; // 1/2

    double a21 = 0.25;          // 1/4
    double a31 = 0, 09375;      // 3/32
    double a32 = 0, 28125;      // 9/32
    double a41 = 0, 879380974;  // 1932/2197
    double a42 = −3, 277196177; // -7200/2197
    double a43 = 3, 277196177;  // 7200/2197
    double a51 = 2, 032407407;  // 439/216
    double a52 = -8.;
    double a53 = 7, 173489279;  // 3680/513
    double a54 = −0, 205896686; //-845/4104
    double a61 = −0, 296296296; //-8/27
    double a62 = 2.;
    double a63 = −1, 381676413; //-3544/2565
    double a64 = 0, 45297271;   // 1859/4104
    double a65 = −0, 275;       //-11/40

    double coeff1, coeff2, coeff3, coeff4;
    double coeff1s, coeff2s, coeff3s, coeff4s;

    coeff1 = function(tPrev, xPrev);
    coeff2 = function(tPrev + c2 * dt, xPrev + (a21 * coeff1) * dt);
    coeff3 = function(tPrev + c3 * dt, xPrev + (a31 * coeff1 + a32 * coeff2) * dt);
    coeff4 = function(tPrev + c4 * dt, xPrev + (a41 * coeff1 + a42 * coeff2 + a43 * coeff3) * dt);
    coeff5 = function(tPrev + c5 * dt, xPrev + (a51 * coeff1 + a52 * coeff2 + a53 * coeff3 + a54 * coeff4) * dt);
    coeff6 = function(tPrev + c6 * dt, xPrev + (a61 * coeff1 + a62 * coeff2 + a63 * coeff3 + a64 * coeff4 + a65 * coeff5) * dt);

    *xNext = xPrev + h * (b1 * coeff1 + b2 * coeff2 + b3 * coeff3 + b4 * coeff4 + b5 * coeff5 + b6 * coeff6);
    *xsNext = xPrev + h * (bs1 * coeff1 + bs2 * coeff2 + bs3 * coeff3 + bs4 * coeff4 + bs5 * coeff5);
    return 0;
}

int performAdaptiveRungeKutta4us5thODE1stToTime(const double tInitial, const double xInitial,
                                                const double tFinal, const int numberStep,
                                                functionType function, const double tolerance)
{

    int i;
    double tTemp = tInitial;
    double xTemp = xInitial;
    double xsTemp = xInitial;
    double tStep = (tFinal - tInitial) / (double)numberStep;
    double epsError = 1.;
    double tStepCorrectionFactor = 0.8;
    // writeHeaderForResults();
    // writeResults(tTemp, xTemp);
    while (tTemp <= tFinal)
    {

        /* If the error tolerance is too small, it might need an tStep smaller that the double precision
         * in that case, we resolve the problem by increasing the error tolerance by a factor of 10 */
        if (tStep < DBL_EPSILON)
        {
            tStep = (tFinal - tInitial) / (double)numberStep; // re-initalize argument step - tStep
            epsError *= 10;
        }

        calculateNext(tTemp, xTemp, tStep, function, &xTemp, &xsTemp);

        /* estimate calculation error
            adapt arument value - tStep */
        epsError = fabs(xTemp - xsTemp);
        if (eps >= tolerance)
        {
            tStep *= tStepCorrectionFactor * pow(tollerance / epsError, 0.2);
        }
        else
        {
            tStep *= tStepCorrectionFactor * pow(tollerance / epsError, 0.25);
        }
    }
    // for (i = 0; i < numberStep; i++)
    // {
    //     calculateNext(tTemp, xTemp, tStep, function, &xTemp);
    //     tTemp = tTemp + tStep;
    //     writeResults(tTemp, xTemp);
    // }

    return 0;
}
int performAdaptiveRungeKutta4us5thODE1stToPosition(const double tInitial, const double xInitial,
                                                    const double tStep, const double xFinal,
                                                    functionType function, const double tolerance)
{

    int i;
    double tTemp = tInitial;
    double xTemp = xInitial;
    double xsTemp = xInitial;
    double tStep = (tFinal - tInitial) / (double)numberStep;
    double epsError = 1.;
    double tStepCorrectionFactor = 0.8;
    // writeHeaderForResults();
    // writeResults(tTemp, xTemp);
    while (tTemp <= tFinal)
    {

        /* If the error tolerance is too small, it might need an tStep smaller that the double precision
         * in that case, we resolve the problem by increasing the error tolerance by a factor of 10 */
        if (tStep < DBL_EPSILON)
        {
            tStep = (tFinal - tInitial) / (double)numberStep; // re-initalize argument step - tStep
            epsError *= 10;
        }

        calculateNext(tTemp, xTemp, tStep, function, &xTemp, &xsTemp);

        /* estimate calculation error
            adapt arument value - tStep */
        epsError = fabs(xTemp - xsTemp);
        if (eps >= tolerance)
        {
            tStep *= tStepCorrectionFactor * pow(tollerance / epsError, 0.2);
        }
        else
        {
            tStep *= tStepCorrectionFactor * pow(tollerance / epsError, 0.25);
        }
    }
    // for (i = 0; i < numberStep; i++)
    // {
    //     calculateNext(tTemp, xTemp, tStep, function, &xTemp);
    //     tTemp = tTemp + tStep;
    //     writeResults(tTemp, xTemp);
    // }

    return 0;
}
