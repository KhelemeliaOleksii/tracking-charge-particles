#include "../include/types.h"
#include "../include/calculateElectricField.h"
#include "../include/calculateMagneticField.h"
#include "calculateEMField.h"

int calculateElectroMagneticField(const double valueUniformMFJupiter, const double unionVectorUMFJ[3],
                                  const double valueDipoleMomentMFSatelite, const double unionVectorDMMFS[3],
                                  const double valueQuadrupoleMomentMFSatelite, const double unionVectorQMMFS[3],
                                  const PositionParticleCartesian3D coord, struct EMFieldCartesian *field)
{
    struct MagneticFieldCartesian mField;
    struct ElectricFieldCartesian eField;

    calcMagneticFieldTotal(valueUniformMFJupiter, unionVectorUMFJ,
                           valueDipoleMomentMFSatelite, unionVectorDMMFS,
                           valueQuadrupoleMomentMFSatelite, unionVectorQMMFS,
                           coord, &mField);

    calcMagneticFieldTotal(&eField);

    *field->eField.Ex = eField.Ex;
    *field->eField.Ey = eField.Ey;
    *field->eField.Ez = eField.Ez;
    *field->mField.Mx = mField.Mx;
    *field->mField.My = mField.My;
    *field->mField.Mz = mField.Mz;
    return 0;
}
