#include "NeuralNetwork.h"

using namespace std;

ostream& operator<<(ostream& os, const Point& p);

int main()
{
    Randomizer random;

    // Create a neural network
    NeuralNetwork nn(2);

    // Create a point
    Point p = {random.randDouble(), random.randDouble()};

    // Predict the label for the point using the neural network
    vector<double> prediction = nn.predict(p);
    cout << "got here" << endl;
    cout << prediction << endl;
    int label = maxIndex(prediction);

    // Print the predicted label
    cout << "Predicted label for point " << p << ": " << label << endl;

    return 0;
}

ostream& operator<<(ostream& os, const Point& p)
{
    os << '(' << p.x << ", " << p.y << ')';
    return os;
}