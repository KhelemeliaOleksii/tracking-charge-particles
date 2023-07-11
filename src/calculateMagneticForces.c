#include <math.h>
#include "../include/types.h"

// Theory of magnetic moments
// After https://drive.google.com/drive/u/0/folders/1dF63TJR9pZ5Q7CBymBzxa8Irqo6EZyLe
//   or https://ccmc.gsfc.nasa.gov/static/files/Dipole.pdf
//
//  Theory of Magnetic Moments of Ganymede
//  Kivelson M.G. The Permanent and Inductive Magnetic Moments of Ganymede. Icarus 157, 507–522 (2002) doi:10.1006/icar.2002.6834
//   http://www.igpp.ucla.edu/people/mkivelson/Publications/ICRUS1572507.pdf

int calcUniformMagneticField(struct MagneticFieldCartesian *dipoleMagneticField)
{
    double magneticMoment = 750e-3; //[Tesla]
    dipoleMagneticField.Bx = 0;
    dipoleMagneticField.By = 0;
    dipoleMagneticField.Bz = 0;

    return 0;
}

int calcDipoleMagneticField(const struct PositionParticleCartesian coord, struct MagneticFieldCartesian *dipoleMagneticField)
{
    double magneticMoment = 750e-3; //[Tesla]
    dipoleMagneticField.Bx = 0;
    dipoleMagneticField.By = 0;
    dipoleMagneticField.Bz = 0;

    return 0;
}

int calcQuadrupoleMagneticField(const struct PositionParticleCartesian coord, struct MagneticFieldCartesian *quadrupoleMagneticField)
{
    quadrupoleMagneticField.Bx = 0;
    quadrupoleMagneticField.By = 0;
    quadrupoleMagneticField.Bz = 0;
    return 0;
}

int calcMagneticFieldTotal(const struct MagneticFieldCartesian uniform, const struct MagneticFieldCartesian dipole,
                           const struct MagneticFieldCartesian quadrupole, struct MagneticFieldCartesian *result)
{
    result.Bx = uniform.Bx + dipole.Bx + quadrupole.Bx;
    result.By = uniform.By + dipole.By + quadrupole.By;
    result.Bz = uniform.Bz + dipole.Bz + quadrupole.Bz;
}

int calculateForcesCartesian(const struct PositionParticleCartesian coord, struct FieldsCartesian *fields)
{
    // Magnetic field of Jupiter // [Tesla]
    struct MagneticFieldCartesian MagneticFieldJupiterUniform;
    calcUniformMagneticField(&MagneticFieldJupiterUniform);

    struct MagneticFieldCartesian MagneticDipoleSatelite;
    calcDipoleMagneticField(coord, &MagneticDipoleSatelite);

    struct MagneticFieldCartesian MagneticQuadrupoleSatelite;
    calcDipoleMagneticField(coord, &MagneticQuadrupoleSatelite);

    struct MagneticFieldCartesian MagneticFieldTotal;
    calcMagneticFieldTotal(MagneticFieldJupiterUniform, MagneticDipoleSatelite, MagneticQuadrupoleSatelite, &MagneticFieldTotal);

    fields->magFldCart.Bx = MagneticFieldTotal.Bx;
    fields->magFldCart.By = MagneticFieldTotal.By;
    fields->magFldCart.Bz = MagneticFieldTotal.Bz;

    fields->eleFldCart.Ex = 0;
    fields->eleFldCart.Ey = 0;
    fields->eleFldCart.Ez = 0;

    return 0;
}
