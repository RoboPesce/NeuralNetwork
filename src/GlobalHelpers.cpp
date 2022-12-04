#include "GlobalHelpers.h"

double dot(std::vector<double>& a, std::vector<double>& b)
{
    double output = 0;

    // Loop over the elements of a and b.
    for (size_t i = 0; i < a.size(); i++)
    {
        // Calculate the dot product of the corresponding elements of a and b
        output += a[i] * b[i];
    }

    // Return the sum
    return output;
}

int maxIndex(std::vector<double>& v)
{
    int maxind = 0;
    for(size_t i = 0; i < v.size(); i++) if(v[maxind] < v[i]) maxind = i;
    return maxind;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << '(' << p.x << ", " << p.y << ')';
    return os;
}

//activation function
double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

//converts raw probabilities to normalized probabilities
std::vector<double> softmax(std::vector<double>& v)
{
    std::vector<double> soft = v;

    double den_sum = 0;
    for(size_t i = 0; i < soft.size(); i++) 
    {
        soft[i] = exp(soft[i]);
        den_sum += soft[i];
    }
    for(size_t i = 0; i < soft.size(); i++) soft[i] /= den_sum;

    return soft;
}