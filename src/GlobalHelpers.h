#ifndef GLOBALHELPERS_H
#define GLOBALHELPERS_H

#include <ctime>
#include <random>
#include <vector>
#include <iostream>

//returns a random double between 0 and 1
double randDouble();

// Calculates the dot product between two vectors
double dot(std::vector<double>& a, std::vector<double>& b);

int maxIndex(std::vector<double>& v);

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v);

#endif