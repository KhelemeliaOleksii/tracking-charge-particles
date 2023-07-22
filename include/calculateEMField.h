#ifndef CALCULATEEMFIELD_H
#define CALCULATEEMFIELD_H

int calculateElectroMagneticField(const double valueUniformMFJupiter, const double unionVectorUMFJ[3],
                                  const double valueDipoleMomentMFSatelite, const double unionVectorDMMFS[3],
                                  const double valueQuadrupoleMomentMFSatelite, const double unionVectorQMMFS[3],
                                  const struct PositionParticleCartesian3D coord, struct EMFieldCartesian *field);

#endif // CALCULATEEMFIELD_H