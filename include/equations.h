#ifndef EQUATIONS_H

#define EQUATION_H

int equestion2ndODE(const double time, const double coord, const double momentum, double *result);

int equationLorentzX(const double time, const struct Particle particle, const struct FieldsCartesian fields,
                     double *result);

#endif // EQUATION_H