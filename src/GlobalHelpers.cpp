#include "GlobalHelpers.h"

double dot(const std::vector<double>& a, const std::vector<double>& b)
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

int maxIndex(const std::vector<double>& v)
{
    int maxind = 0;
    for(size_t i = 0; i < v.size(); i++) if(v[maxind] < v[i]) maxind = i;
    return maxind;
}

//activation function
double sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

// Derivative of the activation function
double dSigmoid(double x) 
{
    double sig = sigmoid(x);
    return sig * (1.0 - sig);
}


//converts raw probabilities to normalized probabilities
std::vector<double> softmax(const std::vector<double>& v)
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