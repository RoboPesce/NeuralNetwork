#include "NeuralNetwork.h"
#include "GlobalHelpers.h"

using namespace std;

std::ostream& operator<<(std::ostream& os, const Point& p);

int main()
{
    srand(time(NULL));

    // Create a neural network
    NeuralNetwork nn(2);

    // Create a point
    Point p = {randDouble(),randDouble()};

    // Predict the label for the point using the neural network
    vector<double> prediction = nn.predict(p);
    int label = maxIndex(prediction);

    // Print the predicted label
    cout << "Predicted label for point " << p << ": " << label << endl;

    return 0;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << '(' << p.x << ", " << p.y << ')';
    return os;
}