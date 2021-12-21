#include "constant.h"
#include "typedef.h"

double get_M9(double w, double rho, const int *V, Vector &u) {
    double eu = (V[0] * u[0] + V[1] * u[1]);
    double uv = (u[0] * u[0] + u[1] * u[1]);
    double feq = w * rho * (1.0 + 3.0 * eu + 4.5 * eu * eu - 1.5 * uv);
    
    return feq;
}

void calc_M9(Vector &M, Vector &u, double rho) {
    double u2 = u[0] * u[0] + u[1] * u[1];
    double eu;
    int k;

    for (k = 0; k < 9; k++) {
        eu = V9[k][0] * u[0] + V9[k][1] * u[1];
        M[k] = W9[k] * rho * (1.0 + 3.0 * eu + 4.5 * eu * eu - 1.5 * u2);
    }
}