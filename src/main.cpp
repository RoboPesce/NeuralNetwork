#include "NeuralNetwork.h"

using namespace std;

int main()
{
    Randomizer random;

    // Create a neural network
    NeuralNetwork nn("network1.nsu");

    // Create a point
    Point p = {random.randDouble(), random.randDouble()};

    // Predict the label for the point using the neural network
    vector<double> prediction = nn.predict(p);

    cout << "Probabilities: " << prediction << endl;
    int label = maxIndex(prediction);

    // Print the predicted label
    cout << "Predicted label for point " << p << ": " << label << endl;

    return 0;
}

