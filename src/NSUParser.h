#include "GlobalHelpers.h"

//The NSU (Network Set Up) file type is specifically for defining 
//the initial weights and biases of the network's layers
class NSUParser
{
public:
    NSUParser(char* fname);
    //returns 0 if all works, else returns 1
    int parse(std::vector<std::vector<std::vector<double>>> weights, std::vector<std::vector<double>> biases);
private:
    std::ifstream file;
};