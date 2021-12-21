#include <map>
#include <any>
#include "typedef.h"

void print_welcome();
std::string parse_args(int argc, char *argv[]);
std::map<std::string, std::any> read_config(const std::string& filename);
void write_sol(Setup &set, Solution &sol, int m);
double get_residual(Setup &set, Solution &sol);