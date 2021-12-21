#include "io.h"
#include "typedef.h"
#include "theory.h"
#include <string>
#include <iostream>

Setup setup(const std::string &filename) {
    auto config = read_config(filename);

    double L = std::any_cast<double>(config["xmax"]) - std::any_cast<double>(config["xmin"]);
    double nu = std::any_cast<double>(config["uwall"]) * L / std::any_cast<double>(config["Re"]);
    double tau = 3.0 * nu + 0.5;

    const struct Setup set {
        std::any_cast<int>(config["dim"]),
            std::any_cast<double>(config["xmin"]),
            std::any_cast<double>(config["xmax"]),
            std::any_cast<double>(config["ymin"]),
            std::any_cast<double>(config["ymax"]),
            std::any_cast<int>(config["nx"]), std::any_cast<int>(config["ny"]),
            std::any_cast<int>(config["nq"]),
            std::any_cast<double>(config["cfl"]),
            std::any_cast<double>(config["Re"]),
            std::any_cast<double>(config["uwall"]),
            nu,
            tau
    };

    return set;
}

Solution init_solution(Setup set) {
    Solution sol;
    int i, j, k;

    std::cout << "Preparing data structure -> ";

    sol.n = Matrix(set.nx+1, set.ny+1, 1.0);
    sol.u = MatrixVector(set.nx+1, set.ny+1, Vector(2, 0.0));
    sol.u0 = MatrixVector(set.nx+1, set.ny+1, Vector(2, 0.0));
    sol.F = MatrixVector(set.nx+1, set.ny+1, Vector(set.nq, 0.0));

    sol.f = MatrixVector(set.nx+1, set.ny+1, Vector(set.nq, 0.0));
    for(i = 0; i <= set.nx; i++) {
        for(j = 0; j <= set.ny; j++) {
            for (k = 0; k < set.nq; k++) {
                calc_M9(sol.f(i, j), sol.u(i, j), sol.n(i, j));
            }
        }
    }

    std::cout << "ready" << std::endl;

    return sol;
}