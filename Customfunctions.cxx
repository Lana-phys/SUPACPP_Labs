#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include "Customfunctions.h"

//read the data and print the outputs as a vector 
std::vector<Point> readData(const std::string& filename) {
std::ifstream data_file(filename);
std::vector<Point> data; // container for (x, y) pairs

    if (!data_file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'\n";
        return data; //returns empty vector
    }

    std::cout << "The data in this file is:\n";

    std::string line;
     bool isHeader = true; // first line is header
    while (std::getline(data_file, line)) {
        if (isHeader) {  // skip header
            isHeader = false;
            continue;
        }

        std::stringstream ss(line);
        std::string xStr, yStr;
//theres commas in the file 
        if (std::getline(ss, xStr, ',') && std::getline(ss, yStr)) {
            try {
                float x = std::stof(xStr);
                float y = std::stof(yStr);
                data.emplace_back(x, y);
            } catch (const std::invalid_argument&) {
                std::cerr << "Warning: invalid line skipped -> " << line << "\n";
            }
        }
    }
    data_file.close();
    return data;
}
//read the error file
std::vector<Point> readError(const std::string& filename) {
std::ifstream errors_file(filename);
std::vector<Point> errors; // container

    if (!errors_file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'\n";
        return errors; //returns empty vector
    }
    std::cout << "The data in this file is:\n";
    std::string line;
     bool isHeader = true; // first line is header
    while (std::getline(errors_file, line)) {
        if (isHeader) {  // skip header
            isHeader = false;
            continue;
        }
        std::stringstream ss(line);
        std::string xStr, yStr;
        if (std::getline(ss, xStr, ',') && std::getline(ss, yStr)) {
            try {
                float x = std::stof(xStr);
                float y = std::stof(yStr);
                errors.emplace_back(x, y);
            } catch (const std::invalid_argument&) {
                std::cerr << "Warning: invalid line skipped -> " << line << "\n";
            }
        }
    }
    errors_file.close();
    return errors;
}

// Another function to take the input from terminal to print n lines of data out to terminal
void print(const std::vector<Point>& data, int N) {
    int total = static_cast<int>(data.size());
    if (N > total) {
        std::cerr << "Warning: Requested " << N 
                  << " lines, but only " << total 
                  << " data points available. Printing first 5 lines instead.\n";
        N = std::min(total, 5);
    }
    std::cout << "Printing " << N << " data points:\n";
    for (int i = 0; i < N; ++i) {
        std::cout << "(" << data[i].first << ", " << data[i].second << ")\n";
    }
}
//the magnitude of the vecotor 
std::vector<float> computeMagnitudes(const std::vector<Point>& data){
std::vector<float> magnitudes;
    magnitudes.reserve(data.size());
    for (const auto& [x, y] : data) {
        float mag = std::sqrt(x * x + y * y);
        magnitudes.push_back(mag);
    }

    return magnitudes;
}
//print the magnitudes 
void print(const std::vector<float>& magnitudes) {
    std::cout << "\nMagnitudes of data points:\n";
    for (size_t i = 0; i < magnitudes.size(); ++i) {
        std::cout << "Point " << i + 1 << ": " << magnitudes[i] << '\n';
    }
}
//save magnitudes to file 
bool saveOutput(const std::vector<float>& magnitudes, const std::string& outFilename) {
    std::ostringstream oss;
    oss << "Magnitudes.\n";
    for(float m : magnitudes){
        oss << m << "\n"; // one magnitude per line
    }
    std::string funcStr = oss.str();
    // Save to file
    std::ofstream out(outFilename);
    out << funcStr << "\n";
    out.close();

    std::cout << "Magnitudes saved to: " << outFilename << "\n";
    return true;
}
//Stright line function modified to calculate chi and chi/ndorf
bool fitAndSave(const std::vector<Point>& data, const std::vector<Point>& errors ,const std::string& outFilename) {

    // Compute sums needed for least squares modify for chi2
    const size_t N = data.size();
    double sumX = 0.0; 
    double sumY = 0.0;
    double sumXX = 0.0;
    double sumXY = 0.0;

    for (const auto& p : data) {
        double x = static_cast< double>(p.first);
        double y = static_cast< double>(p.second);
        sumX += x;
        sumY += y;
        sumXX += x * x;
        sumXY += x * y;
    }

     double denom = (static_cast<double>(N) * sumXX) - (sumX * sumX);
     double a = (static_cast<double>(N) * sumXY - sumX * sumY) / denom;
     double b = (sumY - a * sumX) / static_cast<double>(N);
    //chi2
    double chi2 =0.0;
    for (size_t i = 0; i <N; ++i) {
        double x = static_cast<double>(data[i].first);
        double y = static_cast<double>(data[i].second);
        double line = a * x + b;
        double resid = y - line;
        double sigma_x = static_cast<double>(errors[i].first);
        double sigma_y = static_cast<double>(errors[i].second);
        double sigma_sq = (sigma_y * sigma_y) + (a * a * sigma_x * sigma_x);
        chi2 += (resid * resid) / sigma_sq;
        }
        double ndof = static_cast<double>(N) - 2.0L;
        double chi2_per_ndof = chi2 / ndof;
    
    // Create function string 
    std::ostringstream oss;
    oss << "y = " << static_cast<double>(a) << "*x + " << static_cast<double>(b);
    oss << "chi2 = "<< static_cast<double>(chi2) ;
    oss << "chi2/ndof = " << static_cast<double>(chi2_per_ndof) ;
    std::string funcStr = oss.str();

    // Print to terminal
    std::cout << "Chi and chi2/ndof:\n";
    std::cout << funcStr << "\n";
    std::cout << "chi2 = " << static_cast<double>(chi2);
    std::cout << "chi2/ndof = " << static_cast<double>(chi2_per_ndof);
    // Save to file
    std::ofstream out(outFilename);
    out << funcStr << "\n";
    out.close();

    std::cout << " Chi and chi2/ndof saved to: " << outFilename << "\n";
    return true;
}
// functio for x^y
double recursivePower(double x , int y){
    if (y ==0)
    return 1.0;
    if(y < 0)
    return 1 / recursivePower(x,-y);
    return x* recursivePower(x,y-1);
}
std::vector<double> computePowerForData(const std::vector<Point>& data) {
    std::vector<double> results;
    results.reserve(data.size());

    for (const auto &p : data) {
        double x = static_cast<double>(p.first);
        double y = static_cast<double>(p.second);
        // round y to nearest integer 
        int yRounded = static_cast<int>(std::round(y));
        double val = recursivePower(x, yRounded);
        results.push_back(val);
    }

    return results;
}
void print(const std::vector<double>& powerResults) {
    std::cout << "\nComputed x^round(y) for each data point (index: value):\n";
    for (size_t i = 0; i < powerResults.size(); ++i) {
        std::cout << (i + 1) << ": " << powerResults[i] << '\n';
    }
}
bool saveOutput(const std::vector<double>& powerResults, const std::string& outFilename) {
    std::ostringstream oss;
    oss << "x^y Results\n";
    for(double p : powerResults){
        oss << p << "\n"; // one per line
    }
    std::string funcStr = oss.str();
    // Save to file
    std::ofstream out(outFilename);
    out << funcStr << "\n";
    out.close();

    std::cout << "Powers saved to: " << outFilename << "\n";
    return true;
}