#include "../include/types.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "../include/constants.h"

int setPositionOnSphereSurfaceCartesianMullerMarsagliaRandom(const double centerX, const double centerY, const double centerZ,
                                                             double radius,
                                                             struct PositionParticleCartesian3D *position,
                                                             char **msg)
{

    strcpy(*msg, "FUNCTION: ");
    strcat(*msg, __func__);
    strcat(*msg, "\n");

    if (radius <= 0)
    {
        strcat(*msg, "\tStatus:ERROR. Invalid initial condition: radius <= 0\n");
        return -1;
    }

    int x, y, z;
    double rVector;
    time_t tSeed;
    srand((unsigned)time(&tSeed));

    x = rand() % 10000;
    y = rand() % 10000;
    z = rand() % 10000;

    rVector = sqrt(x * x + y * y + z * z);
    // } while (rVector > 0);
    position->x = x / rVector * radius;
    position->y = y / rVector * radius;
    position->z = z / rVector * radius;

    return 0;
}

int setMomentumCartesianWithCustomEnergyRandom(const double energyFull, const double energyCalm,
                                               struct MomentumParticleCartesian3V *momentum,
                                               char **msg)
{
    strcpy(*msg, "FUNCTION: ");
    strcat(*msg, __func__);
    strcat(*msg, "\n");

    if (energyFull < 0)
    {
        strcat(*msg, "\tStatus:ERROR. Invalid initial condition: energyFull < 0\n");
        return -1;
    }
    if (energyCalm < 0)
    {
        strcat(*msg, "\tStatus:ERROR. Invalid initial condition: energyCalm < 0\n");
        return -1;
    }
    if ((energyFull - energyCalm) < 0)
    {
        strcat(*msg, "\tStatus:ERROR. Invalid initial condition: (energyFull - energyCalm) < 0\n");
        return -1;
    }
    int px, py, pz;
    double pVector;
    double pABS;
    double c = LIGHT_VELOCITY_SI;
    time_t tSeed;
    srand((unsigned)time(&tSeed));

    px = rand() % 10000;
    py = rand() % 10000;
    pz = rand() % 10000;
    pVector = sqrt(px * px + py * py + pz * pz);

    pABS = sqrt(pow(energyFull, 2.) - pow(energyCalm, 2.)) / c;

    momentum->px = px / pVector * pABS;
    momentum->py = py / pVector * pABS;
    momentum->pz = pz / pVector * pABS;

    return 0;
}

int createParticleCartesian3D3V(const double charge, const double mass,
                                struct PositionParticleCartesian3D position,
                                struct MomentumParticleCartesian3V momemtum,
                                struct ParticleInCartesian3D3V *particle)
{
    particle->charge = charge;
    particle->mass = mass;
    particle->r.x = position.x;
    particle->r.y = position.y;
    particle->r.z = position.z;
    particle->p.px = momemtum.px;
    particle->p.py = momemtum.py;
    particle->p.pz = momemtum.pz;
    return 0;
}
// int createSourceElipsoidSurface(const double centerX, const double centerY, const double centerZ,
//                                 const double minRadius, double maxRaduis){};

// int createSourcePointSurface(const double centerX, const double centerY, const double centerZ)
// {
// }

// int rundomizerMomentum(const double initMomentum, const double spreadMomentum, struct MomentumParticleCartesian *momentum)
// {
// }