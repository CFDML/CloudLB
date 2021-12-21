// gcc test.cpp -lstdc++ -lm -std=c++17 -o test

#include <map>
#include <string>
#include <any>
#include <iostream>

int main()
{
    std::map<std::string, std::any> notebook;

    std::string name{ "Pluto" };
    //int year = 2015;
    double year = 2015.1;

    notebook["PetName"] = name;
    notebook["Born"] = year;

    std::string name2 = std::any_cast<std::string>(notebook["PetName"]); // = "Pluto"
    //int year2 = std::any_cast<int>(notebook["Born"]); // = 2015
    double year2 = std::any_cast<double>(notebook["Born"]); // = 2015.1

    std::cout << name2 << " was born in " << year2 << '\n';
}