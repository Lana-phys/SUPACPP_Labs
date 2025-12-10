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
    NormalDistribution ND(2, 1,"NormalDistribution");
    ND.plotFunction();
    ND.plotData(Mystery, 100, true);
    ND.printInfo();
    //Cauchy lorentz distribution
    CauchyLorentzDistribution CLD(2, 1.2, "CauchyLorentzDistribution");
    CLD.plotFunction();
    CLD.plotData(Mystery, 100, true);
    CLD.printInfo();
    //Crystal Ball 
    CrystalBallDistribution CBD(2, 1,1,3,"CrystalBallDistribution");
    CBD.plotFunction();
    CBD.plotData(Mystery, 100, true);
    CBD.printInfo();
    //Metropolis algorithm 
    // New crystal ball
    auto samples = CBD.Metropolis(-5,10, 0.5);
    CBD.plotData(samples, 100, false);
}