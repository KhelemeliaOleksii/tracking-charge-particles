#ifndef CALCULATEMAGNETICFIELD_H
#define CALCULATEMAGNETICFIELD_H

int calcMagneticFieldTotal(const double valueUniformMFJupiter, const double unionVectorUMFJ[3],
                           const double valueDipoleMomentMFSatelite, const double unionVectorDMMFS[3],
                           const double valueQuadrupoleMomentMFSatelite, const double unionVectorQMMFS[3],
                           const struct PositionParticleCartesian coord, struct MagneticFieldCartesian *result);

#endif // CALCULATEMAGNETICFIELD_H
