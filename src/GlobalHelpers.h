#ifndef GLOBALHELPERS_H
#define GLOBALHELPERS_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>
#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//returns a random double between 0 and 1
class Randomizer
{
private:
    std::mt19937 gen; // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> dis;
public:
    Randomizer() : gen(time(NULL)), dis(0, 1) { std::cout << "Initialized Randomizer" << std::endl; }

    double randDouble()
    {
        return dis(gen);
    }
};

// Calculates the dot product between two vectors
double dot(const std::vector<double>& a, const std::vector<double>& b);

int maxIndex(const std::vector<double>& v);

double  sigmoid(double x);

double dSigmoid(double x);

std::vector<double> softmax(const std::vector<double>& v);

template <typename vtype>
std::ostream& operator<<(std::ostream& os, const std::vector<vtype>& v)
{
    os << '[';
    for (size_t i = 0; i < v.size()-1; ++i) os << v[i] << ' ';
    os << v[v.size()-1] << ']';
    return os;
}

#endif