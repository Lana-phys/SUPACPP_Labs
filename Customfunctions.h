#ifndef CUSTOMFUNCTIONS_H
#define CUSTOMFUNCTIONS_H

#include <string>
#include <vector>
#include <utility>

//Point is (x, y)
using Point = std::pair<float, float>;

//read files
std::vector<Point> readData(const std::string& filename);
std::vector<Point> readError(const std::string&filename);
double recursivePower(double x, int y);
//print data 
void print(const std::vector<Point>& data, int N); 
void print(const std::vector<float>& magnitudes);
void print(const std::vector<double>& powerResults);
//compute the magnitude, fit, 
std::vector<float> computeMagnitudes(const std::vector<Point>& data); // computer magnitude
std::vector<double> computePowerForData(const std::vector<Point>& data);
//Save outputs 
bool saveOutput(const std::vector<float>& magnitudes, const std::string& outFilename = "Magnitudes.txt");
bool saveOutput(const std::vector<double>& powers, const std::string& outFilename = "Powers.txt");
bool fitAndSave(const std::vector<Point>& data, const std::vector<Point>& errors ,const std::string& outFilename);
#endif 