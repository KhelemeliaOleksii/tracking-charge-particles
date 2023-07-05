#ifndef CREATEPARTICLE_H
#define CREATEPARTICLE_H

/**
 * Documentation
 * @param centerX,centerY,centerZ - cartesian coordinates of the Sphere's center
 * @param radius - a radius of the Sphere
 * @return position - as pointer, a random cartesian coordinates of the partircle on the Sphere (like struct PositionParticleCartesian3D)
 * @version (Muller 1959, Marsaglia 1972)
 */
int setPositionOnSphereSurfaceCartesianMullerMarsagliaRandom(const double centerX, const double centerY, const double centerZ,
                                                             double radius,
                                                             struct PositionParticleCartesian3D *position,
                                                             char **msg);
/**
 * Documentation
 * @param energy - full energy of the paticle - sqrt(p^2c^2 + m^2c^4);
 * @param energy - calm energy of the paticle - mc^2
 * @return momentum - as pointer, a random momentum values of the partircle with the energy (like struct MomentumParticleCartesian3V)
 */
int setMomentumCartesianWithCustomEnergyRandom(const double energyFull, const double energyCalm,
                                               struct MomentumParticleCartesian3V *momentum,
                                               char **msg);

/**
 * Documentation
 * @param charge - charge of particle;
 * @param mass - mass of particle
 * @param position - x,y,z cordinates of the particle on the Sphere (like struct PositionParticleCartesian3D)
 * @param momentum - px,py,pz momentum components of the particle (like struct MomentumParticleCartesian3V)
 * @return particle - as pointer, a random momentum values of the partircle with the energy (like struct ParticleInCartesian3D3V)
 */
int createParticleCartesian3D3V(const double charge, const double mass,
                                struct PositionParticleCartesian3D position,
                                struct MomentumParticleCartesian3V momemtum,
                                struct ParticleInCartesian3D3V *particle);

#endif // CREATEPARTICLE_H