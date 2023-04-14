#ifndef GLOBALHELPERS_H
#define GLOBALHELPERS_H

#define M_PI 3.141592653
#define M_E 2.7182818284
#include <cmath>
#include <ctime>
#include <random>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// typedefs for NN structure
typedef float NNvalue;
typedef std::vector<NNvalue> Layer;
typedef std::vector<Layer> Matrix;
typedef std::vector<Matrix> Tensor;

//returns a random double between 0 and 1
class Randomizer
{
private:
    std::mt19937 gen; // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<NNvalue> dis;
public:
    Randomizer() : gen(time(NULL)), dis(0, 1) { std::cout << "Initialized Randomizer" << std::endl; }

    NNvalue randValue()
    {
        return dis(gen);
    }
};

// Calculates the dot product between two vectors
NNvalue dot(const Layer& a, const Layer& b);

int maxIndex(const Layer& v);

Layer softmax(const Layer& v);

template <typename vtype>
std::ostream& operator<<(std::ostream& os, const std::vector<vtype>& v)
{
    os << '[';
    for (size_t i = 0; i < v.size()-1; ++i) os << v[i] << ' ';
    os << v[v.size()-1] << ']';
    return os;
}

#endif