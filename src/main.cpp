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
    int label = maxIndex(prediction);

    // Print the predicted label
    cout << "\nPredicted label for point " << p << ": " << label << endl;
    //hardcoded to assume that the label 0 -> y<x and label 1 -> x<=y
    vector<double> des_pred(2);
    des_pred[0] = (int) (p.y< p.x);
    des_pred[1] = (int) (p.x<=p.y);
    cout << "Desired: " << des_pred << endl;
    double error = nn.calculateError(prediction, des_pred);
    cout << "Error: " << error << endl;

    nn.updateNetwork();

    return 0;
}

