#ifndef TYPES_H
#define TYPES_H

struct ElectricFieldCartesian
{
    double Ex;
    double Ey;
    double Ez;
};

struct MagneticFieldCartesian
{
    double Bx;
    double By;
    double Bz;
};

struct FieldsCartesian
{
    struct ElectricFieldCartesian eleFldCart;
    struct MagneticFieldCartesian magFldCart;
};

struct PositionParticleCartesian
{
    double x;
    double y;
    double z;
};

struct MomentumParticleCartesian
{
    double px;
    double py;
    double pz;
};

struct CoordsCartesian
{
    struct PositionParticleCartesian posPrtclCart;
    struct MomentumParticleCartesian momPrtclCart;
};

struct Particle
{
    struct PositionParticleCartesian r;
    struct MomentumParticleCartesian p;
    double mass;
    double charge;
};

#endif