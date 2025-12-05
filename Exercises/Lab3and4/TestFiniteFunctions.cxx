#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include "FiniteFunctions.h"
#include "gnuplot-iostream.h"

int main() {
    std::ifstream inputfile("MysteryData24011.txt");
    if (!inputfile.is_open()){
        std::cerr << "Error" << std::endl;
        return 1;
    }
    std::vector<double> Mystery;
    double value;
    while (inputfile>> value){
        Mystery.push_back(value);
    }
    inputfile.close();

    //FiniteFunction function{};
    //function.setRangeMin(-10);
    //function.setRangeMax(10);
    //function.plotFunction();
    //function.plotData(Mystery,100,true);
    //Normal Distribution
    NormalDistribution NormalDistribution(-1, 2);
    NormalDistribution.plotFunction();
    NormalDistribution.plotData(Mystery, 100, true);
    //
    return 0;
}