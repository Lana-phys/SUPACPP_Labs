#include "Customfunctions.h"

#include <iostream>
#include <string>

int main() {
    std::string inputfile = "/workspaces/SUPACPP_Labs/Exercises/Lab1and2/input2D_float.txt";
    std::string errorfile = "/workspaces/SUPACPP_Labs/Exercises/Lab1and2/error2D_float.txt";
    // Read data once (full file)
    auto data = readData(inputfile);
    if (data.empty()) {
        std::cerr << "No data read from file. Exiting.\n";
        return 1;
    }
    while (true){
    // Prompt user which function to use
    std::cout << "Action Menu:\n";
    std::cout << "  1) Print N lines of data\n";
    std::cout << "  2) Compute and print the magnitude\n";
    std::cout << "  3) Fit a straight line and calculate chi^2 and chi^2/nodf\n ";
    std::cout << "  4) Compute x^y using recursion with a rounded y\n";
    std::cout << "  5) Exit\n";
    std::cout << "Choose an option\n";

    int choice = 0;
    if (!(std::cin >> choice)) {
        std::cerr << "Invalid choice input. Exiting.\n";
        return 1;
    }

    if (choice == 1) {
        std::cout << "Enter number of lines to print (N): ";
        int N;
        if (!(std::cin >> N)) {
            std::cerr << "Invalid N. Exiting.\n";
            return 1;
        }
        print(data, N);

    } else if (choice == 2) {
        auto magnitudes = computeMagnitudes(data);
        print(magnitudes);
        saveOutput(magnitudes,"Magnitude.txt");
    } else if (choice == 3) {
        std::string outFile = "FitResults.txt";
        auto errors = readError(errorfile);
        fitAndSave(data, errors, outFile);
        
    } else if (choice == 4){
        auto powerResults = computePowerForData(data);
        print(powerResults);
        saveOutput(powerResults,"Powers.txt");
    }
        else if(choice == 5){
        std::cout << "Exiting...\n";
        break;

    }
    std::cout << "\n Press ENTER to see the Action Menu again ";
    std::cin.get();
 }
    return 0;
}