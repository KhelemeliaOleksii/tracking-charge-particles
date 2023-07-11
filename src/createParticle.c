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

    strcat(*msg, "FUNCTION: ");
    strcat(*msg, __func__);
    strcat(*msg, "\n");

    if (radius <= 0)
    {
        strcat(*msg, "\tStatus:ERROR. Invalid initial condition: radius <= 0\n");
        return -1;
    }

    int x, y, z;
    int divisor = 10000;
    double rVector;
    // time_t tSeed;
    // srand((unsigned)time(&tSeed));

    x = rand() % divisor;
    x = (double)divisor / 2. - x;
    y = rand() % divisor;
    y = (double)divisor / 2. - y;
    z = rand() % divisor;
    z = (double)divisor / 2. - z;

    rVector = sqrt(x * x + y * y + z * z);
    // } while (rVector > 0);
    position->x = x / rVector * radius;
    position->y = y / rVector * radius;
    position->z = z / rVector * radius;
    // fprintf(stdout, "unit r vector = %f\n", sqrt(pow(position->x, 2.) + pow(position->y, 2.) + pow(position->z, 2.)));

    return 0;
}

int setMomentumCartesianWithCustomEnergyRandom(const double energyFull, const double energyRest,
                                               struct MomentumParticleCartesian3V *momentum,
                                               char **msg)
{
    strcat(*msg, "FUNCTION: ");
    strcat(*msg, __func__);
    strcat(*msg, "\n");

    if (energyFull < 0)
    {
        strcat(*msg, "\tStatus:ERROR. Invalid initial condition: energyFull < 0\n");
        return -1;
    }
    if (energyRest < 0)
    {
        strcat(*msg, "\tStatus:ERROR. Invalid initial condition: energyCalm < 0\n");
        return -1;
    }
    if ((energyFull - energyRest) < 0)
    {
        strcat(*msg, "\tStatus:ERROR. Invalid initial condition: (energyFull - energyCalm) < 0\n");
        return -1;
    }
    int px, py, pz;
    int divisor = 10000;
    double pVector;
    double pABS;
    double c = LIGHT_VELOCITY_SI;
    // time_t tSeed;
    // srand((unsigned)time(&tSeed));

    px = rand() % divisor;
    px = (double)divisor / 2. - px;
    py = rand() % divisor;
    py = (double)divisor / 2. - py;
    pz = rand() % divisor;
    pz = (double)divisor / 2. - pz;

    pVector = sqrt(px * px + py * py + pz * pz);
    pABS = sqrt(pow(energyFull, 2.) - pow(energyRest, 2.)) / c;

    momentum->px = px / pVector * pABS;
    momentum->py = py / pVector * pABS;
    momentum->pz = pz / pVector * pABS;

    // fprintf(stdout, "unit p vector = %f\n", sqrt(pow(momentum->px, 2.) + pow(momentum->py, 2.) + pow(momentum->pz, 2.)));

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

int createParticleOnSphereSurfaceCartesian3DRandom3VRandom(const double charge, const double mass,
                                                           const double energyFull, const double energyRest,
                                                           const double sphereRadius,
                                                           struct ParticleInCartesian3D3V *particle,
                                                           char **msg)
{
    strcpy(*msg, "FUNCTION: ");
    strcat(*msg, __func__);
    strcat(*msg, "\n");

    struct PositionParticleCartesian3D positionInitial;
    struct MomentumParticleCartesian3V momentumInitial;

    if (setPositionOnSphereSurfaceCartesianMullerMarsagliaRandom(0, 0, 0, sphereRadius, &positionInitial, msg) < 0)
    {
        // strcat(*msg, "\n");
        // fprintf(stderr, "%s", msg);
        return -1;
    }
    if (setMomentumCartesianWithCustomEnergyRandom(energyFull, energyRest, &momentumInitial, msg) < 0)
    {
        // fprintf(stderr, "%s", msg);
        return -1;
    }
    createParticleCartesian3D3V(charge, mass, positionInitial, momentumInitial, particle);
    return 0;
}