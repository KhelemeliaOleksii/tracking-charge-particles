//  /////////////
//  After   https://www.compadre.org/PICUP/resources/Numerical-Integration/
//          https://www.engr.colostate.edu/~thompson/hPage/CourseMat/Tutorials/CompMethods/Rungekutta.pdf
// relativistic motion - http://kfe.fjfi.cvut.cz/~vachal/edu/nme/cviceni/09_ODE/DOCS/relativistic_motion.pdf

//  ////////////

#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

// #include "../include/configureParams.h"
#include "../include/types.h"
// #include "../include/performRungeKutta4th2ndODE.h"
// #include "../include/equations.h"
#include "../include/createParticle.h"
#include "../include/calculateEMField.h"
#include "../include/constants.h"

int main()
{
    FILE *file_ptr;
    struct ParticleInCartesian3D3V particleInitial;
    double charge = 1.; // sinf=gle charge
    double mass = 16.;
    double radiusSphereInner = 1.;
    // double radiusSphereOuter = radiusSphereInner * 10.;
    double energyFull = 1000000.; // eV
    double energyRest = 500000.;  // eV

    struct EMFieldCartesian field;
    double directionUniformMagnFieldJupiter[3] = {0, -sqrt(2) / 2, -sqrt(2) / 2}; //(0, -45deg, -45deg);
    double valueUniformMagnFieldJupiter = 113;                                    // nT
    double directionDipoleMagnFieldSatelite[3] = {1, 0, 1.095};
    double valueDipoleMomentMFSatelite = 750; // nT
    double directionQuadMagnFieldSatelite[3] = {1, 0, 0};
    double valueQuadrupoleMomentMFSatelite = 0; // nT

    time_t tSeed;
    srand((unsigned)time(&tSeed));

    char *msg_ptr; // message container of results how the procedures work
    msg_ptr = (char *)malloc(400 * sizeof(char));

    file_ptr = fopen("resultsRun.dat", "a");

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

    for (int i = 0; i < 2; i++)
    {
        createParticleOnSphereSurfaceCartesian3DRandom3VRandom(charge, mass, energyFull, energyRest, radiusSphereInner,
                                                               &particleInitial, &msg_ptr);
        calculateElectroMagneticField(valueUniformMagnFieldJupiter, directionUniformMagnFieldJupiter,
                                      valueDipoleMomentMFSatelite, directionDipoleMagnFieldSatelite,
                                      valueQuadrupoleMomentMFSatelite, directionQuadMagnFieldSatelite,
                                      particleInitial.r, &field);
        fprintf(file_ptr, "%e\t%e\t%e\t%e\t%e\t%e\t%e\t%e\n",
                particleInitial.charge, particleInitial.mass,
                particleInitial.r.x, particleInitial.r.y, particleInitial.r.z,
                particleInitial.p.px, particleInitial.p.py, particleInitial.p.pz);
    }

    // if (setPositionOnSphereSurfaceCartesianMullerMarsagliaRandom(0, 0, 0, radius, &positionInitial, &msg_ptr) < 0)
    // {
    //     fprintf(stderr, "%s", msg_ptr);
    //     fclose(file_ptr);
    //     free(msg_ptr);
    //     return -1;
    // }
    // if (setMomentumCartesianWithCustomEnergyRandom(energyFull, energyCalm, &momentumInitial, &msg_ptr) < 0)
    // {
    //     fprintf(stderr, "%s", msg_ptr);
    //     fclose(file_ptr);
    //     free(msg_ptr);
    //     return -1;
    // }
    // createParticleCartesian3D3V(charge, mass, positionInitial, momentumInitial, &particle);

    fclose(file_ptr);
    free(msg_ptr);
    return 0;
}