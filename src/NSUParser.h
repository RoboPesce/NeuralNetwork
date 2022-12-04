#ifndef NSUPARSER_H
#define NSUPARSER_H

#include "GlobalHelpers.h"

//The NSU (Network Set Up) file type is specifically for defining 
//the initial weights and biases of the network's layers
class NSUParser
{
public:
    NSUParser(std::string fname);
    //closes file
    ~NSUParser();
    //returns 0 if all works, else returns 1
    int parse(std::vector<std::vector<std::vector<double>>>& weights, std::vector<std::vector<double>>& biases);

    void write(std::vector<std::vector<std::vector<double>>>& weights, std::vector<std::vector<double>>& biases);
private:
    std::fstream file;
    std::string fpath;
    bool hasParsed=false;
};

#endif