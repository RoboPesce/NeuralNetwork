#include "NeuralNetwork.h"

using namespace std;

int main()
{
    Randomizer random;

    // Create a neural network
    NeuralNetwork nn("network1.nsu");

    // Create a point
    vector<double> point(2);
    point[0] = random.randDouble();
    point[1] = random.randDouble();

    // Predict the label for the point using the neural network
    vector<double> prediction = softmax(nn.predict(point));
    int label = maxIndex(prediction);

    // Print the predicted label
    cout << "Probabilities: " << prediction << endl;
    cout << "\nPredicted label for point " << point << ": " << label << endl;

    //hardcoded to assume that the label 0 -> y<x and label 1 -> x<=y
    /*
    vector<double> des_pred(2);
    des_pred[0] = (int) (p.y< p.x);
    des_pred[1] = (int) (p.x<=p.y);
    cout << "Desired: " << des_pred << endl;
    double error = nn.calculateError(prediction, des_pred);
    cout << "Error: " << error << endl;
    */
    //nn.updateNetwork();

    return 0;
}

