//  /////////////
//  After   https://www.compadre.org/PICUP/resources/Numerical-Integration/
//          https://www.engr.colostate.edu/~thompson/hPage/CourseMat/Tutorials/CompMethods/Rungekutta.pdf
// relativistic motion - http://kfe.fjfi.cvut.cz/~vachal/edu/nme/cviceni/09_ODE/DOCS/relativistic_motion.pdf

//  ////////////

#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>

#include "../include/configureParams.h"
#include "../include/types.h"
#include "../include/performRungeKutta4th2ndODE.h"
#include "../include/equestion2ndODE.h"

int main()
{
    double timeInitial, coordInitial, velocityInitial, timeFinal;
    int numberStep;

    char *ptr_msg;
    ptr_msg = (char *)malloc(200 * sizeof(char));

    if (configureParams1D2ndODE(&timeInitial, &coordInitial, &velocityInitial, &timeFinal, &numberStep, &ptr_msg) < 0)
    {
        fprintf(stderr, "%s", ptr_msg);
        free(ptr_msg);
        return -1;
    }

    
    performRungeKutta4th2ndODE(timeInitial, coordInitial, velocityInitial, timeFinal, numberStep, equestion2ndODE);

    // printf("Press any key to exit...\n");
    // getch();
    free(ptr_msg);
    return 0;
}