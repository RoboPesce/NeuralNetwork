#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "GlobalHelpers.h"
#include "NSUParser.h"

// A neural network with variable layers. Can read a network from a .nsu file.
class NeuralNetwork
{
private:
    //for parsing and writing NSU file
    NSUParser nsu;
    // Vector of weights, where each element is a vector of weights for a layer of the network
    Tensor weights;
    // Vector of biases, where each element is a vector of biases for a layer of the network
    Matrix biases;

    bool failed=false;
    
public:
    NeuralNetwork(std::string fname);

    //activation function
    static NNvalue  activation(NNvalue x);

    static NNvalue dActivation(NNvalue x);

    // The forward propagation function, which takes in a point
    // and returns the predicted label for the point
    Layer predict(const Layer& input);

    /*
     Forward propagation which returns the preactivation (weighted) outputs at each level 
     as a 2D array
     Identical algorithm to predict(); use activations.back() and apply activation to each
     output to get predict() output
    */
    Matrix predictGetWeightedOutputs(const Layer& input);

    //calculates the error for a single datapoint
    // @param predicted_output softmaxed output of neural network
    // @param desired_output one-hot category vector
    static NNvalue calculateLoss(const Layer& predicted_output, const Layer& desired_output);

    static Layer lossGradient(const Layer& predicted_output, const Layer& desired_output);

    void backpropagation(const Layer& input, const Layer& output, double learning_rate);

    //update the nsu file with the learned data
    void updateNetwork();

    friend std::ostream& operator<<(std::ostream& os, const NeuralNetwork& nn);

    operator bool() const;
};

#endif