//  /////////////
//  After   https://www.compadre.org/PICUP/resources/Numerical-Integration/
//          https://www.engr.colostate.edu/~thompson/hPage/CourseMat/Tutorials/CompMethods/Rungekutta.pdf
// relativistic motion - http://kfe.fjfi.cvut.cz/~vachal/edu/nme/cviceni/09_ODE/DOCS/relativistic_motion.pdf

//  ////////////

#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>

// #include "../include/configureParams.h"
#include "../include/types.h"
// #include "../include/performRungeKutta4th2ndODE.h"
// #include "../include/equations.h"
#include "../include/createParticle.h"
#include "../include/constants.h"

int main()
{
    FILE *file_ptr;
    struct ParticleInCartesian3D3V particle;
    struct PositionParticleCartesian3D positionInitial;
    struct MomentumParticleCartesian3V momentumInitial;
    double charge = 1;
    double mass = 1;
    double radius = 20;
    double energyFull = 1000000;
    double energyCalm = 500000;

    char *msg_ptr; // message container of results how the procedures work
    msg_ptr = (char *)malloc(200 * sizeof(char));

    file_ptr = fopen("run_results.dat", "a");

    if (file_ptr == NULL)
    {
        fprintf(stderr, "File cannot be created!");
        return -1;
    }
    fseek(file_ptr, 0, SEEK_END);
    if (ftell(file_ptr) == 0)
    {
        fprintf(file_ptr, "Charge\tMass\tXInit\tYInit\tZInit\tPxInit\tPyInit\tPzInit\n");
    }

    if (setPositionOnSphereSurfaceCartesianMullerMarsagliaRandom(0, 0, 0, radius, &positionInitial, &msg_ptr) < 0)
    {
        // fprintf(stderr, "%s", msg_ptr);

        fclose(file_ptr);
        free(msg_ptr);
        return -1;
    }
    if (setMomentumCartesianWithCustomEnergyRandom(energyFull, energyCalm, &momentumInitial, &msg_ptr) < 0)
    {
        // fprintf(stderr, "%s", msg_ptr);

        fclose(file_ptr);
        free(msg_ptr);
        return -1;
    }

    createParticleCartesian3D3V(charge, mass, positionInitial, momentumInitial, &particle);

    fprintf(file_ptr, "%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\n",
            mass, charge,
            positionInitial.x, positionInitial.y, positionInitial.z,
            momentumInitial.px, momentumInitial.py, momentumInitial.pz);

    fclose(file_ptr);
    free(msg_ptr);
    return 0;
}