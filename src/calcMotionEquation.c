// https://github.com/rand-asswad/Runge-Kutta/blob/master/main.c

#include <math.h>
#include "../include/performRungeKutta4th1thODE.h"
#include "../include/equations.h"
#include "../include/types.h"

int isParticleFallDownOnMoon(const double radiusSphereInner, const struct PositionParticleCartesian3D position)
{
    const raduisvector = radiusvectorCartesian3D(position);
    const diff = radiusvector - radiusSpahereInner;
    if (diff <= 0)
    {
        return -1
    }
    return 0;
}

int isCalculationTimeOver(const double time, const struct MomentumParticleCartesian3V momentum,
                          const double radiusSphereInner, const double radiusSphereOuter)
{
    double velocity = factor(momentum) * momentumCartesian3V(momentum);
    double distance = radiusSphereOuter - radiusSphereInner;

    double timeFinal = 100. * distance / velocity;
    if (timeFinal - time <= 0)
    {
        return -1;
    }
    return 0;
}

int nullifyParticle(const struct ParticleInCartesian3D3V *particleInitial)
{
    particleFinal.r.x = NULL;
    particleFinal.r.y = NULL;
    particleFinal.r.z = NULL;
    particleFinal.p.px = NULL;
    particleFinal.p.py = NULL;
    particleFinal.p.pz = NULL;
    return 0;
}

int solveMotionEquation(const double radiusSphereInner, const double radiusSphereOuter,
                        const struct ParticleInCartesian3D3V particleInitial, const struct ParticleInCartesian3D3V *particleFinal,
                        int equationMotion(const double momentum, const double factor, double *result),
                        int solver(const double tInitial, const double xInitial,
                                   const double tFinal, const int numberStep,
                                   int function(const double arguPrev, const double funcValuePrev, double *result)))
{
    double timeInitial = 0;

    if (isParticleFallDownOnMoon < 0)
    {
        nullify(particleFinal);
        return -1;
    }

    if (isCalculationTimeOver < 0)
    {
        nullify(particleFinal);
        return -1;
    }

    particleInitial.solver()
}