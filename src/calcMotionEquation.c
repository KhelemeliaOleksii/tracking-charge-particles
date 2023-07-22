// https://github.com/rand-asswad/Runge-Kutta/blob/master/main.c

#include <math.h>
#include "../include/performRungeKutta4th1thODE.h"
#include "../include/equations.h"
#include "../include/types.h"

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

bool isParticleFallDownOnMoon(const double radiusSphereInner, const struct PositionParticleCartesian3D position)
{
    const raduisvector = radiusvectorCartesian3D(position);
    const diff = radiusvector - radiusSphereInner;
    if (diff > 0)
    {
        return false
    }
    return true;
}

bool isParticleEscapeOuterSphere(const double radiusSphereOuter, const struct PositionParticleCartesian3D position)
{
    const raduisvector = radiusvectorCartesian3D(position);
    const diff = radiusvector - radiusSpahereInner;
    if (diff < 0)
    {
        return false
    }
    return true;
}

// bool isCalculationTimeOver(const double time, const struct MomentumParticleCartesian3V momentum,
//                            const double radiusSphereInner, const double radiusSphereOuter)
// {
bool isCalculationTimeOver(const double time, const double timeFinal)
{
    // double velocity = factor(momentum) * momentumCartesian3V(momentum);
    // double distance = radiusSphereOuter - radiusSphereInner;

    // double timeFinal = 100. * distance / velocity;
    if (timeFinal - time > 0)
    {
        return false;
    }
    return true;
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

double factor(const struct MomentumParticleCartesian3V momentum)
{
    double c = LIGHT_SPEED_SI;
    double m = ELECTRON_MASS_SI;
    double result =
        c * c /
        sqrt(
            pow(m, 2.) * pow(c, 4.) +
            (pow(momentum.px, 2.) + pow(momentum.py, 2.) + pow(momentum.pz, 2.)) * pow(c, 2.));
    return result;
}

int solveMotionEquation(const double radiusSphereInner, const double radiusSphereOuter,
                        const struct ParticleInCartesian3D3V particleInitial, const struct ParticleInCartesian3D3V *particleFinal,
                        int equationMotion(const double momentum, const double factor, double *result),
                        int solver(const double tInitial, const double xInitial,
                                   const double tFinal, const int numberStep,
                                   int function(const double arguPrev, const double funcValuePrev, double *result)))
{
    double timeInitial = 0;
    double tTemp = timeInitial;
    double velocityOfParticle = factor(particleFinal.p) * momentumCartesian3V(particleFinal.p);
    double distanceOfCalculation = radiusSphereOuter - radiusSphereInner;
    double timeOfCalculationMax = 100. * distanceOfCalculation / velocityOfParticle;

    double xTemp = particleInitial.r.x;
    double yTemp = particleInitial.r.y;
    double zTemp = particleInitial.r.z;
    double pxTemp = particleInitial.p.px;
    double pyTemp = particleInitial.p.py;
    double pzTemp = particleInitial.p.pz;

    calculateNext(tTemp, xTemp, ,
                  functionType function, double *xNext, double *xsNext)
        /* if the partircle fall down on the moon surface
        - particle final parameters is nullified */
        if (isParticleFallDownOnMoon(radiusSphereInner, *particleFinal.r))
    {
        nullify(particleFinal);
        return -1;
    }

    /* if the partircle has become a satelite of the moon and cannot  reach the outer sphere
    - particle final parameters is nullified */
    if (isCalculationTimeOver(tTemp, timeOfCalculationMax))
    {
        nullify(particleFinal);
        return -1;
    }

    /*  if the particle has left calculation region(escaped outside the outer sphere)
     - finish calculaion runtime */
    if (isParticleEscapeOuterSphere(radiusSphereOuter, particleFinal.r))
    {
        return 0;
    }
    // particleInitial.solver()
}