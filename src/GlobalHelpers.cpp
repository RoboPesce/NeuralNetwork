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