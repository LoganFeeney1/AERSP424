/************************************************************************************************************************
Logan Feeney
Homework 1
Problem 2
2/10/24
************************************************************************************************************************/

#include <iostream>
#include <map>
#include <string>

int main()
{
    // Define container
    std::map<std::string, std::map<std::string, int>> Distance;

    // Distances from State Colleg to Philly, Chicago, and Newark
    Distance["SCE"]["PHL"] = 160;
    Distance["SCE"]["ORD"] = 640;
    Distance["SCE"]["EWR"] = 220;
}