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

vector<vector<double>> NeuralNetwork::predictGetWeightedOutputs(const vector<double>& input)
{
    //vector to be returned
    vector<vector<double>> outputs(weights.size());

    vector<double> next_input = input;

    // Loop over the layers of the network
    for (size_t layer = 0; layer < weights.size(); layer++)
    {
        // The output vector will be the number of nodes in the layer
        vector<double> output(biases[layer].size());

        // 1 sum the weighted values of inputs
        // 2 add bias
        // 3 apply the sigmoid function (after adding output to array)
        for (size_t i = 0; i < output.size(); i++)
        {
            output[i] =  dot(next_input, weights[layer][i]);
            output[i] += biases[layer][i];
        }
        //add the output (activations for this layer) to the activations vector
        outputs[layer] = output;
        //apply sigmoid
        for (size_t i = 0; i < output.size(); i++) output[i] =  sigmoid(output[i]);
        // Update the input for the next layer of the network
        next_input = output;
    }
    return outputs;
}

/*
 Calculates the cross-entropy loss between the predicted output
 and the desired output for a given input.
 @param predicted_output softmaxed output of neural network
 param desired_output an array of 0s where index of desired category is 1
*/
double NeuralNetwork::calculateLoss(const std::vector<double>& predicted_output, const std::vector<double>& desired_output) 
{
    //get the index of the desired category
    int true_ind = maxIndex(desired_output);
    return -log(predicted_output[true_ind]);
}

/*
 Calculates derivative of error using chain rule
 dL/dz_i = p_i - t_i
 @param predicted_output softmaxed output of neural network
 @param desired_output an array of 0s where index of desired category is 1
*/
std::vector<double> NeuralNetwork::lossGradient(const std::vector<double>& predicted_output, const std::vector<double>& desired_output)
{
    vector<double> gradient = predicted_output;
    int true_ind = maxIndex(desired_output);
    gradient[true_ind] -= 1;
    //other indices remain unchanged (p_i - 0)
    return gradient;
}

//Backpropagation to update parameters based on a single example
void NeuralNetwork::backpropagation(const vector<double>& input, const vector<double>& desired_output, double learning_rate)
{
    //get array of neuron outputs pre-activation
    vector<vector<double>> weighted_outputs = predictGetWeightedOutputs(input);
    //calculate softmax of output layer
    vector<double> softmax_output = weighted_outputs.back();
    for(size_t i = 0; i < softmax_output.size(); i++) softmax_output[i] = sigmoid(softmax_output[i]);
    softmax_output = softmax(softmax_output);

    //get error, might be unecessary
    double error = calculateLoss(softmax_output, desired_output);
    //Vector of partial derivatives of output activations with respect to loss
    //dL/ds_i, where s = sigmoid of ith neuron
    vector<double> activationGradient = lossGradient(softmax_output, desired_output);
    
    /*
     Now main backprop loop occurs:
    1. calculate partial derivatives dL/dw_ij of weights, dL/db_i of biases, dL/ds_j of next layer's neurons
    2. Use partial derivatives to update parameters based on learning rate
    3. update activationGradient to contain next layer's dL/ds_j
     Call the weighted output of neuron i (before activation) a_i
     Note that dL/da_i = dL/ds_i * ds_i/da_i, where ds_i/da_i = d_sigmoid(a_i)
     Also a_i derivatives with respect to parameters are simply linear
     Partial derivatives are calculated as follows:
    dL/dw_ij = dL/ds_i * d_sigmoid(a_i) * s_j
    dL/db_i = dL/ds_i * d_sigmoid(a_i)
    dL/ds_j must be a sum over dL/ds_i * d_sigmoid(a_i) * w_ij for all neurons i in the layer
     so these will be kept track of in a vector that will be assigned to activationGradient later
    */
   //start loop at last layer
   for(size_t layer = weights.size()-1; layer >= 0; layer++)
    {
        //Store gradient of next layer's dL/ds_j. Its size is determined by 
        //the number of weights any neuron on this layer has
        vector<double> next_activationGradient(weights[layer][0].size());

        
    }
}

void NeuralNetwork::updateNetwork()
{
    nsu.write(weights, biases);
}

