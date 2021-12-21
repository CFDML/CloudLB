// --------------------------------------------------------------
// CloudLB: Portable Lattice Boltzmann Simulation Library
// Copyright (c) 2021, Tianbai Xiao
// --------------------------------------------------------------

#include "theory.h"
#include "typedef.h"
#include "io.h"
#include "setup.h"
#include "typedef.h"
#include "evolve.h"
#include <iostream>

int main(int argc, char **argv) {
    int iter = 1;
    double t = 0.0;
    double res;

    print_welcome();
    const std::string filename = parse_args(argc, argv);
    Setup set = setup(filename);
    Solution sol = init_solution(set);
    write_sol(set, sol, iter);
    std::cout << "Starting main loop" << std::endl;
    std::cout
            << "--------------------------------------------------------------"
            << '\n';

    for (iter = 1; iter < 100000; iter++) {
        evolve(set, sol);
        
        if (iter % 200 == 0) {
            res = get_residual(set, sol);
            std::cout << "iteration: " << iter << ", residual: " << res << std::endl;
        }
        if (iter % 10000 == 0) {
            write_sol(set, sol, iter);
        }
        if (iter > 1000 && res < 1e-6) {
            break;
        }
    }

    write_sol(set, sol, iter);

    return 0;
}