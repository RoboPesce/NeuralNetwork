#include "GlobalHelpers.h"

NNvalue dot(const Layer& a, const Layer& b)
{
    NNvalue output = 0;

    // Loop over the elements of a and b.
    for (size_t i = 0; i < a.size(); i++)
    {
        // Calculate the dot product of the corresponding elements of a and b
        output += a[i] * b[i];
    }

    // Return the sum
    return output;
}

int maxIndex(const Layer& v)
{
    int maxind = 0;
    for(size_t i = 0; i < v.size(); i++) if(v[maxind] < v[i]) maxind = i;
    return maxind;
}

//converts raw probabilities to normalized probabilities
Layer softmax(const Layer& v)
{
    Layer soft = v;

    double den_sum = 0;
    for(size_t i = 0; i < soft.size(); i++) 
    {
        soft[i] = exp(soft[i]);
        den_sum += soft[i];
    }
    for(size_t i = 0; i < soft.size(); i++) soft[i] /= den_sum;

    return soft;
}