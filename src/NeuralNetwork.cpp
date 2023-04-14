#include "NeuralNetwork.h"

#define alpha 0.01

using namespace std;

NNvalue RandValue();

NeuralNetwork::NeuralNetwork(string fname) : nsu(fname)
{
    if(nsu.parse(weights, biases)) 
    {
        cout << "File invalid." << endl;
        failed = true;
    }
}

// Predicts the output values for a given input point, using the current weights and biases
Layer NeuralNetwork::predict(const Layer& input)
{
    //cout << "Attempting to predict " << input << endl;
    Layer next_input = input;

    // Loop over the layers of the network
    for (size_t layer = 0; layer < weights.size(); layer++)
    {
        // The output vector will be the number of nodes in the layer
        Layer output(biases[layer].size());

        // 1 sum the weighted values of inputs
        // 2 add bias
        // 3 apply the activation function
        for (size_t node = 0; node < output.size(); node++)
        {
            output[node] =  dot(next_input, weights[layer][node]);
            output[node] += biases[layer][node];
            output[node] =  activation(output[node]);
        }
        // Update the input for the next layer of the network
        next_input = output;
        //cout << "output for layer " << layer << ": " << output << endl;
    }

    // Return the predicted output values
    return next_input;
}

Matrix NeuralNetwork::predictGetWeightedOutputs(const Layer& input)
{
    //vector to be returned
    Matrix outputs(weights.size());

    Layer next_input = input;

    // Loop over the layers of the network
    for (size_t layer = 0; layer < weights.size(); layer++)
    {
        // The output vector will be the number of nodes in the layer
        Layer output(biases[layer].size());

        // 1 sum the weighted values of inputs
        // 2 add bias
        // 3 apply the activation function (after adding output to array)
        for (size_t i = 0; i < output.size(); i++)
        {
            output[i] =  dot(next_input, weights[layer][i]);
            output[i] += biases[layer][i];
        }
        //add the output to the outputs vector
        outputs[layer] = output;
        //apply activation
        for (size_t i = 0; i < output.size(); i++) output[i] = activation(output[i]);
        
        // Update the input for the next layer of the network
        next_input = output;
    }
    return outputs;
}

/*
 Calculates the cross-entropy loss between the predicted output
 and the desired output for a given input.
 @param predicted_output softmaxed output of neural network
 param desired_output an array of 0s where entry of desired category index is 1
*/
NNvalue NeuralNetwork::calculateLoss(const Layer& predicted_output, const Layer& desired_output) 
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
Layer NeuralNetwork::lossGradient(const Layer& predicted_output, const Layer& desired_output)
{
    Layer gradient = predicted_output;
    int true_ind = maxIndex(desired_output);
    gradient[true_ind] -= 1;
    //other indices remain unchanged (p_i - 0)
    return gradient;
}

//Backpropagation to update parameters based on a single example
void NeuralNetwork::backpropagation(const Layer& input, const Layer& desired_output, double learning_rate)
{
    //get array of neuron outputs pre-activation
    Matrix weighted_outputs = predictGetWeightedOutputs(input);
    //calculate softmax of output layer
    Layer softmax_output = weighted_outputs.back();
    //for(size_t i = 0; i < softmax_output.size(); i++) softmax_output[i] = activation(softmax_output[i]);
    softmax_output = softmax(softmax_output);

    //Vector of partial derivatives of output activations with respect to loss
    //dL/ds_i, where s = activation of ith neuron
    Layer activation_gradient = lossGradient(softmax_output, desired_output);
    
    /*
     Now main backprop loop occurs:
    1. calculate partial derivatives dL/dw_ij of weights, dL/db_i of biases, dL/ds_j of next layer's neurons
    2. Use partial derivatives to update parameters based on the learning rate
    3. update activationGradient to contain next layer's dL/ds_j
     Call the weighted output of neuron i (before activation) a_i
     Note that dL/da_i = dL/ds_i * ds_i/da_i, where ds_i/da_i = dActivation(a_i)
     Also a_i derivatives with respect to parameters are simply linear
     Since s_i = activation(a_i) ds_i/any parameter is dL/s_i * dActivation(a_i) * the parameter's coefficient
     Partial derivatives are calculated as follows:
    dL/dw_ij = dL/ds_i * dActivation(a_i) * s_j
    dL/db_i = dL/ds_i * dActivation(a_i)          (coefficient of 1)
    dL/ds_j must be a sum over dL/ds_i * dActivation(a_i) * w_ij for all neurons i in the layer
     so these will be kept track of in a vector that will be assigned to activationGradient later
    */

    //start loop at last layer
    Layer next_activation_gradient;
    for(int layer = weights.size()-1; layer >= 0; layer--)
    {
        //Store gradient of next layer's dL/ds_j. Its size is determined by 
        //the number of weights any neuron on this layer has
        next_activation_gradient.resize(weights[layer][0].size(), 0);

        //loop through neurons
        for(size_t node = 0; node < activation_gradient.size(); node++)
        {
            //calculate dL/ds_i * dActivation(a_i), since this is used in all calculations
            NNvalue sig_prime = activation_gradient[node] * dActivation(weighted_outputs[layer][node]);
            //calculate bias derivative and update bias
            NNvalue dL_db = sig_prime;
            biases[layer][node] -= dL_db * learning_rate;
            //now loop through previous layer's neurons in order to update weights and calculate next activation gradient
            //note that we must use the input as s_j for the final layer
            for(size_t j_node = 0; j_node < weights[layer][node].size(); j_node++)
            {
                NNvalue s_j;
                if(layer == 0) s_j = input[j_node];
                else s_j = weighted_outputs[layer-1][j_node]; //access previous layer
                //temporarily store weight
                NNvalue j_weight = weights[layer][node][j_node];
                //get weight derivative and update weight
                NNvalue dL_dwij = sig_prime * s_j;
                weights[layer][node][j_node] -= dL_dwij * learning_rate;
                //dL/ds_j is the sum of dL/ds_i * dL/ds_j for all neurons, so we're adding
                next_activation_gradient[j_node] += sig_prime * j_weight;
            }
        }
        //update activation gradient with the next layer's activations
        activation_gradient = next_activation_gradient;
    }
}

void NeuralNetwork::updateNetwork()
{
    nsu.write(weights, biases);
}

std::ostream& operator<<(std::ostream& os, const NeuralNetwork& nn)
{
    for(size_t layer = 0; layer < nn.weights.size(); layer++)
    {
        for(size_t node = 0; node < nn.weights[layer].size(); node++)
        {
            os << nn.biases[layer][node] << " [ ";
            for (size_t pnode = 0; pnode < nn.weights[layer][node].size(); pnode++)
            {
                os << nn.weights[layer][node][pnode] << ' ';
            }
            os << "] ";
        }
        os << std::endl;
    }
    return os;
}

NeuralNetwork::operator bool() const
{
    return failed;
}

//activation function is leaky RELU
NNvalue NeuralNetwork::activation(NNvalue x)
{
    return (x<0)*alpha*x + (x>=0)*x;
}

// Derivative of the activation function
NNvalue NeuralNetwork::dActivation(NNvalue x) 
{
    return (x<0)*alpha + (x>=0);
}