#include "constant.h"
#include "theory.h"
#include "typedef.h"

void evolve(Setup &set, Solution &sol) {
    int NX = set.nx;
    int NY = set.ny;
    int Q = set.nq;
    int i, j, k;
    int ip, jp;

    // update pdf
    for (i = 1; i < NX; i++) {
        for (j = 1; j < NY; j++) {
            for (k = 0; k < Q; k++) {
                ip = i - V9[k][0];
                jp = j - V9[k][1];
                sol.F(i, j)[k] =
                    sol.f(ip, jp)[k] +
                    (get_M9(W9[k], sol.n(ip, jp), V9[k], sol.u(ip, jp)) -
                     sol.f(ip, jp)[k]) /
                        set.tau;
            }
        }
    }

    // macroscopic variables
    for (i = 1; i < NX; i++) {
        for (j = 1; j < NY; j++) {
            sol.u0(i, j)[0] = sol.u(i, j)[0];
            sol.u0(i, j)[1] = sol.u(i, j)[1];
            sol.n(i, j) = 0.0;
            sol.u(i, j) = 0.0;

            for (k = 0; k < set.nq; k++) {
                sol.f(i, j)[k] = sol.F(i, j)[k];
                sol.n(i, j) += sol.f(i, j)[k];
                sol.u(i, j)[0] += V9[k][0] * sol.f(i, j)[k];
                sol.u(i, j)[1] += V9[k][1] * sol.f(i, j)[k];
            }
            sol.u(i, j)[0] /= sol.n(i, j);
            sol.u(i, j)[1] /= sol.n(i, j);
        }
    }

    // boundary
    for (j = 1; j < NY; j++) { // left & right
        for (k = 0; k < Q; k++) {
            sol.n(NX, j) = sol.n(NX - 1, j);
            sol.f(NX, j)[k] = get_M9(W9[k], sol.n(NX, j), V9[k], sol.u(NX, j)) + sol.f(NX-1, j)[k] -
                          get_M9(W9[k], sol.n(NX-1, j), V9[k], sol.u(NX-1, j));
            sol.n(0, j) = sol.n(1, j);
            sol.f(0, j)[k] = get_M9(W9[k], sol.n(0, j), V9[k], sol.u(0, j)) + sol.f(1, j)[k] -
                         get_M9(W9[k], sol.n(1, j), V9[k], sol.u(1, j));
        }
    }

    for (i = 0; i <= NX; i++) { // top & bottom
        for (k = 0; k < Q; k++) {
            sol.n(i, 0) = sol.n(i, 1);
            sol.f(i, 0)[k] = get_M9(W9[k], sol.n(i, 0), V9[k], sol.u(i, 0)) + sol.f(i, 1)[k] -
                         get_M9(W9[k], sol.n(i, 1), V9[k], sol.u(i, 1));

            sol.n(i, NY) = sol.n(i, NY-1);
            sol.u(i, NY)[0] = set.uwall;
            sol.f(i, NY)[k] = get_M9(W9[k], sol.n(i, NY), V9[k], sol.u(i, NY)) + sol.f(i, NY-1)[k] -
                          get_M9(W9[k], sol.n(i, NY-1), V9[k], sol.u(i, NY-1));
        }
    }
}