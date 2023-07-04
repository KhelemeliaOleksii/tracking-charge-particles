#include "../include/types.h";

int createSourceSphereSurfaceRandomRP(const double centerX, const double centerY, const double centerZ,
                                      double radius, double const mass, double const charge,
                                      struct Particle *particle)
{
    *particle.mass = mass;
    *particle.charge = charge;
};

int createSourceElipsoidSurface(const double centerX, const double centerY, const double centerZ,
                                const double minRadius, double maxRaduis){};

int createSourcePointSurface(const double centerX, const double centerY, const double centerZ)
{
}

int rundomizerMomentum(const double initMomentum, const double spreadMomentum, struct MomentumParticleCartesian *momentum)
{
}