#include <math.h>
#include "../include/types.h"
#include "../include/constants.h"

int equestion2ndODE(const double t, const double x, const double p, double *result)
{
    *result = sin(t);
    return 0;
}

/**
 * @desc relativistic motion - http://kfe.fjfi.cvut.cz/~vachal/edu/nme/cviceni/09_ODE/DOCS/relativistic_motion.pdf
 */

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

double momentumCartesian3V(const struct MomentumParticleCartesian3V momentum)
{
    return sqrt(pow(momentum.px, 2.) + pow(momentum.py, 2.) + pow(momentum.pz, 2.));
}

double radiusvectorCartesian3D(const struct PositionParticleCartesian3D position)
{
    return sqrt(pow(position.x, 2.) + pow(position.y, 2.) + pow(position.z, 2.));
}

int equationLorentzCartesianX(const double time, const struct Particle particle, const struct FieldsCartesian fields, const double factor,
                              double *result)
{
    *result = particle.charge * (fields.eleFldCart.Ex +
                                 fields.magFldCart.Bz * particle.p.py * factor -
                                 fields.magFldCart.By * particle.p.pz * factor);
    return 0;
}
int equationLorentzCartesianY(const double time, const struct Particle particle, const struct FieldsCartesian fields, const double factor,
                              double *result)
{
    *result = particle.charge * (fields.eleFldCart.Ey +
                                 fields.magFldCart.Bx * particle.p.pz * factor -
                                 fields.magFldCart.Bz * particle.p.px * factor);
    return 0;
}
int equationLorentzCartesianZ(const double time, const struct Particle particle, const struct FieldsCartesian fields, const double factor,
                              double *result)
{
    *result = particle.charge * (fields.eleFldCart.Ez +
                                 fields.magFldCart.By * particle.p.px * factor -
                                 fields.magFldCart.Bx * particle.p.py * factor);
    return 0;
}

int equationMotionCartesian(const double momentum, const double factor, double *result)
{
    *result = momentum * factor;
    return 0;
}