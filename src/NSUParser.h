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
    int parse(Tensor& weights, Matrix& biases);

    void write(Tensor& weights, Matrix& biases);
private:
    std::fstream file;
    std::string fpath;
};

#endif