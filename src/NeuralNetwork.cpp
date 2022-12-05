#include "NeuralNetwork.h"

using namespace std;

double RandDouble();

NeuralNetwork::NeuralNetwork(string fname) : nsu(fname)
{
    if(nsu.parse(weights, biases)) cout << "File invalid." << endl;
}

// Predicts the output values for a given input point, using the current weights and biases
vector<double> NeuralNetwork::predict(const vector<double>& input)
{
    cout << "Attempting to predict " << input << endl;
    vector<double> next_input = input;

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
            output[i] =  dot(next_input, weights[layer][i]);
            output[i] += biases[layer][i];
            output[i] =  sigmoid(output[i]);
        }
        // Update the input for the next layer of the network
        next_input = output;
    }

    cout << "Raw probabilities: " << next_input << endl;
    // Return the predicted output values
    return next_input;
}

vector<vector<double>> NeuralNetwork::predictGetActivations(const vector<double>& input)
{
    //vector to be returned
    vector<vector<double>> activations(weights.size());

    vector<double> next_input = input;

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
            output[i] =  dot(next_input, weights[layer][i]);
            output[i] += biases[layer][i];
            output[i] =  sigmoid(output[i]);
        }
        //add the output (activations for this layer) to the activations vector
        activations[layer] = output;
        // Update the input for the next layer of the network
        next_input = output;
    }
    return activations;
}

// Calculates the cross-entropy loss between the predicted output
// and the desired output for a given input.
// @param predicted_output softmaxed output of neural network
// @param desired_output an array of 0s where index of desired category is 1
double NeuralNetwork::calculateError(const std::vector<double>& predicted_output, const std::vector<double>& desired_output) 
{
    //get the index of the desired category
    int true_ind = maxIndex(desired_output);
    return -log(predicted_output[true_ind]);
}

//Calculates derivative of error using chain rule
//dL/dz_i = p_i - t_i
// @param predicted_output softmaxed output of neural network
// @param desired_output an array of 0s where index of desired category is 1
std::vector<double> NeuralNetwork::errorGradient(const std::vector<double>& predicted_output, const std::vector<double>& desired_output)
{
    vector<double> gradient = predicted_output;
    int true_ind = maxIndex(desired_output);
    gradient[true_ind] -= 1;
    //other indices remain unchanged (p_i - 0)
    return gradient;
}

//Backpropagation to update parameters based on a single example
void NeuralNetwork::backpropagation(const vector<double>& input, const vector<double>& desired_output)
{
    vector<vector<double>> predicted_activations = predictGetActivations(input);
    vector<double> softmax_output = softmax(predicted_activations.back());

    double error = calculateError(softmax_output, desired_output);

}

void NeuralNetwork::updateNetwork()
{
    nsu.write(weights, biases);
}

