#ifndef GLOBALHELPERS_H
#define GLOBALHELPERS_H

#include <ctime>
#include <random>
#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

// A simple struct to represent a 2D point
struct Point
{
    double x;
    double y;
};

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
double dot(std::vector<double>& a, std::vector<double>& b);

int maxIndex(std::vector<double>& v);

std::ostream& operator<<(std::ostream& os, const Point& p);

template <typename vtype>
std::ostream& operator<<(std::ostream& os, const std::vector<vtype>& v)
{
    os << '[';
    for (size_t i = 0; i < v.size()-1; ++i) os << v[i] << ' ';
    os << v[v.size()-1] << ']';
    return os;
}

#endif