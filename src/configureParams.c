#include <stdio.h>
#include <math.h>
#include <string.h>

// to solve dv/dt = f(t, x, v); dx/dt = g(t,x)
int configureParams1D2ndODE(double *timeInitial, double *coordInitial, double *velocityInitial, double *timeFinal, int *numberStep, char **msg)
{
    strcpy(*msg, "FUNCTION: ");
    strcat(*msg, __func__);
    strcat(*msg, "\n");

    printf("Enter Initial Condition\n");
    float ti, ci, vi, tf;
    int ns;
    printf("t0 = ");
    scanf("%f", &ti);
    *timeInitial = ti;

    printf("x(t0) = ");
    scanf("%f", &ci);
    *coordInitial = ci;

    printf("v(t0, x0) = ");
    scanf("%f", &vi);
    *velocityInitial = vi;

    printf("Enter final time value, tn = ");
    scanf("%f", &tf);
    *timeFinal = tf;

    printf("Enter number of steps: ");
    scanf("%d", &ns);
    *numberStep = ns;

    if ((*timeFinal - *timeInitial) < 0)
    {
        strcat(*msg, "\tStatus:ERROR. Invalid initial condition: (timeFinal - timeInitial) < 0\n");
        return -1;
    };
    if (fabs(*timeFinal - *timeInitial) <= 1.e-16)
    {
        strcat(*msg, "\tStatus:ERROR. Invalid initial condition!: fabs(finalArgue - initArgue) <= 1.e-16\n");
        return -1;
    };

    strcat(*msg, "\tStatus: SUCCESS. Parameters is configured.");
    return 0;
}
