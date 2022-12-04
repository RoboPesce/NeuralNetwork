#include "NeuralNetwork.h"

using namespace std;

double RandDouble();

NeuralNetwork::NeuralNetwork(string fname) : nsu(fname)
{
    if(nsu.parse(weights, biases)) cout << "File invalid." << endl;
    cout << weights.size() << " " << biases.size() << endl;
}

double NeuralNetwork::sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}

// Predicts the output values for a given input point, using the current weights and biases
vector<double> NeuralNetwork::predict(Point& p)
{
    cout << "Attempting to predict " << p << endl;
    // Initialize the input vector with the coordinates of the input point
    vector<double> input = {p.x, p.y};

    // Loop over the layers of the network
    for (size_t layer = 0; layer < weights.size(); layer++)
    {
        // The output vector will be the number of nodes in the layer
        vector<double> output(biases[layer].size());

        // 1 sum the weighted values of inputs
        // 2 add bias
        // 3 apply the sigmoid function
        for (size_t i = 0; i < output.size(); i++)
        {
            output[i] =  dot(input, weights[layer][i]);
            output[i] += biases[layer][i];
            output[i] =  sigmoid(output[i]);
        }
        // Update the input for the next layer of the network
        cout << "Output for layer " << layer+2 << ": " << output << endl;
        input = output;
    }

    // Return the predicted output values
    return input;
}
