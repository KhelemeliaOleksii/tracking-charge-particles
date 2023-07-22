#include <math.h>
#include "../include/types.h"

// Theory of magnetic moments
// After https://drive.google.com/drive/u/0/folders/1dF63TJR9pZ5Q7CBymBzxa8Irqo6EZyLe
//   or https://ccmc.gsfc.nasa.gov/static/files/Dipole.pdf
//
//  Theory of Magnetic Moments of Ganymede
//  Kivelson M.G. The Permanent and Inductive Magnetic Moments of Ganymede. Icarus 157, 507–522 (2002) doi:10.1006/icar.2002.6834
//   http://www.igpp.ucla.edu/people/mkivelson/Publications/ICRUS1572507.pdf

int calcMagneticFieldTotal(struct ElectricFieldCartesian *result)
{
    result.Ex = 0;
    result.Ey = 0;
    result.Ez = 0;
}
