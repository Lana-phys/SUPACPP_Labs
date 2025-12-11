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

    //Metropolis
    NormalDistribution NDR(2, 1,"Random Normal Distribution"); 

    // Random number generator
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_real_distribution<> distr(-5.0, 5.0);
    double x_i = distr(eng);
    int iterations = 10000;
    std::vector<double> Samples;
    for (int i = 0; i < iterations; ++i) {
        double y = NDR.generateRandom(x_i, 1.0); 
        double f_x_i = NDR.callFunction(x_i);
        double f_y = NDR.callFunction(y);
        double A = std::min(f_y / f_x_i, 1.0);
        std::uniform_real_distribution<> distT(0.0, 1.0);  // Uniform distribution between 0 and 1
        double T = distT(eng);  // Generate a random number T
    if (T < A) {
     x_i = y; 
     Samples.push_back(y);
}
}
    NDR.plotFunction();
    NDR.plotData(Samples, 100, false);
}