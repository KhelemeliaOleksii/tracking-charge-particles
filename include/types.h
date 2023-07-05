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

struct PositionParticleCartesian3D
{
    double x;
    double y;
    double z;
};

struct MomentumParticleCartesian3V
{
    double px;
    double py;
    double pz;
};

struct CoordsCartesian3D3V
{
    struct PositionParticleCartesian3D positionParticle;
    struct MomentumParticleCartesian3V momentumParticle;
};

struct ParticleInCartesian3D3V
{
    struct PositionParticleCartesian3D r;
    struct MomentumParticleCartesian3V p;
    double mass;
    double charge;
};

#endif