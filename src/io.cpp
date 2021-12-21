#include "typedef.h"
#include <algorithm>
#include <any>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

void print_welcome() {
    std::cout << "==============================================================" << std::endl;
    std::cout << "CloudLB: Portable Lattice Boltzmann Simulator" << std::endl;
    std::cout << "==============================================================" << std::endl;
}

bool is_number(std::string line) {
    char *p;
    strtod(line.c_str(), &p);
    return *p == 0;
}

bool is_integer(std::string line) {
    char *p;
    strtol(line.c_str(), &p, 10);
    return *p == 0;
}

std::string parse_args(int argc, char *argv[]) {
    std::string inputFile;
    std::string usage_help = "\n"
                             "Usage: " +
                             std::string(argv[0]) + " inputfile\n";

    if (argc < 2) {
        std::cout << usage_help;
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-h") {
            std::cout << usage_help;
            exit(EXIT_SUCCESS);
        } else {
            inputFile = std::string(argv[i]);
            std::ifstream f(inputFile);
            if (!f.is_open()) {
                std::cout << ("unable to open inputfile '" + inputFile + "'.")
                          << std::endl;
            }
        }
    }
    return inputFile;
}

std::map<std::string, std::any> read_config(const std::string &filename) {
    std::map<std::string, std::any> config;
    std::ifstream cFile(filename);
    bool isNum, isInt;

    if (cFile.is_open()) {
        std::cout << "Reading config from " << filename << '\n';
        std::cout
            << "--------------------------------------------------------------"
            << '\n';
        std::string line;
        while (getline(cFile, line)) {
            line.erase(std::remove_if(line.begin(), line.end(), ::isspace),
                       line.end());
            if (line[0] == '#' || line.empty())
                continue;
            auto delimiterPos = line.find("=");
            std::string name = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);
            std::cout << name << " = " << value << '\n';

            isNum = is_number(value);
            if (isNum) {
                isInt = is_integer(value);
                if (isInt) {
                    config[name] = std::stoi(value);
                } else {
                    config[name] = std::stod(value);
                }
            } else {
                config[name] = value;
            }
        }
        std::cout
            << "--------------------------------------------------------------"
            << '\n';
    } else {
        std::cerr << "Couldn't open config file for reading.\n";
    }

    return config;
}

void write_sol(Setup &set, Solution &sol, int m) {
    int i, j, Z;

    int NX = set.nx;
    int NY = set.ny;
    int Q = set.nq;

    // header
    std::ostringstream name;
    name << "cavity_" << m << ".dat";
    std::ofstream out(name.str().c_str());
    out << "Title= \"LBM Lid Driven Flow\"" << std::endl
        << "VARIABLES=\"X\",\"Y\",\"U\",\"V\"" << std::endl
        << "ZONE Nodes=" << (NX + 1) * (NY + 1) << ","
        << "Elements=" << NX * NY << ","
        << "DATAPACKING=point"
        << ","
        << "ZONETYPE=FEQUADRILATERAL" << std::endl;

    // solution
    for (j = 0; j <= NY; j++)
        for (i = 0; i <= NX; i++) {
            out << double(i) << " " << double(j) << " " << sol.u(i, j)[0] << " "
                << sol.u(i, j)[1] << std::endl;
        }

    for (Z = 2; Z <= NX * (NY + 1); Z++)
        if ((Z - 1) % (NX + 1) == 0) {
            out << " " << std::endl;
        } else {
            out << Z << " " << Z - 1 << " " << Z + NX << " " << Z + (NX + 1)
                << std::endl;
        }
}

double get_residual(Setup &set, Solution &sol) {
    int NX = set.nx;
    int NY = set.ny;
    int i, j;
    double temp1 = 0.0;
    double temp2 = 0.0;

    for (i = 1; i < NX; i++) {
        for (j = 1; j < NY; j++) {
            temp1 += ((sol.u(i, j)[0] - sol.u0(i, j)[0]) * (sol.u(i, j)[0] - sol.u0(i, j)[0]) +
                      (sol.u(i, j)[1] - sol.u0(i, j)[1]) * (sol.u(i, j)[1] - sol.u0(i, j)[1]));
            temp2 += (sol.u(i, j)[0] * sol.u(i, j)[0] + sol.u(i, j)[1] * sol.u(i, j)[1]);
        }
    }

    return sqrt(temp1) / (sqrt(temp2) + 1e-7);
}