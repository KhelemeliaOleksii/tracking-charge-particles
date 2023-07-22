#include <math.h>
#include "../include/types.h"

// Theory of magnetic moments
// After https://drive.google.com/drive/u/0/folders/1dF63TJR9pZ5Q7CBymBzxa8Irqo6EZyLe
//   or https://ccmc.gsfc.nasa.gov/static/files/Dipole.pdf
//
//  Theory of Magnetic Moments of Ganymede
//  Kivelson M.G. The Permanent and Inductive Magnetic Moments of Ganymede. Icarus 157, 507–522 (2002) doi:10.1006/icar.2002.6834
//   http://www.igpp.ucla.edu/people/mkivelson/Publications/ICRUS1572507.pdf

int calcUniformMagneticField(const double valueMagnetField, const double unionVector[3],
                             struct MagneticFieldCartesian *uniformMagneticField)
{
    // #Bj_nT = [0, 0, -113] #Jovian magnetic field, nT
    // Bj_nT = [ 0, -79, -79 ] #Jovian magnetic field,
    // double magneticMoment = 750e-3; //[Tesla]
    uniformMagneticField->Bx = valueMagnetField * unionVector[0];
    uniformMagneticField->By = valueMagnetField * unionVector[1];
    uniformMagneticField->Bz = valueMagnetField * unionVector[2];
    return 0;
}

int calcDipoleMagneticField(const double valueMagnetField, const double unionVector[3],
                            const struct PositionParticleCartesian3D coord,
                            struct MagneticFieldCartesian *dipoleMagneticField)
{
    // nT
    // M_nT = [ -24.7, 82.5, -716.8 ] #Ganymede dipole moment,
    // nT
    /** Magnetic dipole's field
     * B(r_i) = mu_0/4/pi * (3*r_i(r_i*M_i) - m_i r^2)/r^5
     */
    // 0,0011705070068684044225744983995; 0,03421267319091573736617538807081
    // 0,01305834108983605304323571888017; 0,11427309871459709849026192371834
    // 0,98577115190329554253418978272033; 0,99286008677119030542811814450058
    double magneticMoment = 750e-9; //[Tesla]
    double constSi = 1.e-7;         // mu_0/4/pi = 4*pi/4/pi*10^(-7) = 10^(-7);
    double radiusVector = sqrt(pow(coord.x, 2.) + pow(coord.y, 2.) + pow(coord.z, 2.));
    dipoleMagneticField->Bx = constSi * (3 * coord.x * (coord.x * (dipoleMagneticField->Bx)) - (dipoleMagneticField->Bx) * pow(radiusVector, 2.)) / pow(radiusVector, 5.);
    dipoleMagneticField->By = constSi * (3 * coord.y * (coord.y * (dipoleMagneticField->By)) - (dipoleMagneticField->By) * pow(radiusVector, 2.)) / pow(radiusVector, 5.);
    dipoleMagneticField->Bz = constSi * (3 * coord.z * (coord.z * (dipoleMagneticField->Bz)) - (dipoleMagneticField->Bz) * pow(radiusVector, 2.)) / pow(radiusVector, 5.);
    return 0;
}

// It is a stub
int calcQuadrupoleMagneticField(const double valueMagnetField, const double unionVector[3],
                                const struct PositionParticleCartesian coord,
                                struct MagneticFieldCartesian *quadrupoleMagneticField)
{
    *quadrupoleMagneticField->Bx = 0;
    *quadrupoleMagneticField->By = 0;
    *quadrupoleMagneticField->Bz = 0;
    return 0;
}

int calcMagneticFieldTotal(const double valueUniformMFJupiter, const double unionVectorUMFJ[3],
                           const double valueDipoleMomentMFSatelite, const double unionVectorDMMFS[3],
                           const double valueQuadrupoleMomentMFSatelite, const double unionVectorQMMFS[3],
                           const struct PositionParticleCartesian coord, struct MagneticFieldCartesian *result)
{
    struct MagneticFieldCartesian uniformJupiter, dipoleSatelite, quadrupoleSatelite, total;

    calcUniformMagneticField(valueUniformMFJupiter, unionVectorDMMFS, &uniformJupiter);
    calcDipoleMagneticField(valueDipoleMomentMFSatelite, unionVectorDMMFS, coord, &dipoleSatelite);
    calcQuadrupoleMagneticField(valueQuadrupoleMomentMFSatelite, unionVectorQMMFS, coord, &quadrupoleSatelite);

    *result->Bx = uniformJupoter.Bx + dipoleSatelite.Bx + quadrupoleSatelite.Bx;
    *result->By = uniformJupoter.By + dipoleSatelite.By + quadrupoleSatelite.By;
    *result->Bz = uniformJupoter.Bz + dipoleSatelite.Bz + quadrupoleSatelite.Bz;
}