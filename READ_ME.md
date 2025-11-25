You should have 3 files AnalyseData, Customfunctions.h and Customfunctions.cxx
You will have need the relevent paths to 2D float data and the error data, i have added them in from my end but they may change depending where these files are saved in the AnalyseData file for input and error file you can change the relevent paths.
I personally compile my files in the terminal and then call upon them 
To do this in the terminal compile the files using  g++ -std=c++17 -Wall -Wextra -O2 AnalyseData.cxx Customfunctions.cxx -o AnalyseData
open using ./AnalyseData
then select your option!