#include "NSUParser.h"

using namespace std;

NSUParser::NSUParser(char* fname) : file(fname) {}

int NSUParser::parse(vector<vector<vector<double>>> weights, vector<vector<double>> biases)
{
    cout << "Loading network from file..." << endl;
    int inputsize;
    file >> inputsize;
    int numlayers;
    file >> numlayers;
    if(!file.good())
    {
        cout << "Issue parsing network size." << endl;
        return 1;
    }
    cout << "Network will have " << numlayers << " layers and take in input of size " << inputsize << endl;

    for(int layer = 0; layer < numlayers; layer++)
    {
        int lsize;
        file >> lsize;

        for(int i = 0; i < lsize; i++)
        {
            
        }

        if(!file.good())
        {
            cout << "Issue parsing layer " << layer+2 << '.' << endl;
            return 1;
        }
    }

    file.close();
    return 0;
}