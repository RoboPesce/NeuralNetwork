#include "NSUParser.h"

using namespace std;

NSUParser::NSUParser(char* fname) : file(fname) {}

int NSUParser::parse(vector<vector<vector<double>>> weights, vector<vector<double>> biases)
{
    cout << "Loading network from file..." << endl;
    int numlayers;
    file >> numlayers;
    cout << "Network will have " << numlayers << " layers." << endl;

    file.close();
    return 0;
}