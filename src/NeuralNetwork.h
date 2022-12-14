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
    std::vector<std::vector<std::vector<double>>> weights;
    // Vector of biases, where each element is a vector of biases for a layer of the network
    std::vector<std::vector<double>> biases;

    bool failed=false;
public:
    NeuralNetwork(std::string fname);

    // The forward propagation function, which takes in a point
    // and returns the predicted label for the point
    std::vector<double> predict(const std::vector<double>& input);

    /*
     Forward propagation which returns the preactivation (weighted) outputs at each level 
     as a 2D array
     Identical algorithm to predict(); use activations.back() and apply activation to each
     output to get predict() output
    */
    std::vector<std::vector<double>> predictGetWeightedOutputs(const std::vector<double>& input);

    //calculates the error for a single datapoint
    // @param predicted_output softmaxed output of neural network
    // @param desired_output one-hot category vector
    static double calculateLoss(const std::vector<double>& predicted_output, const std::vector<double>& desired_output);

    static std::vector<double> lossGradient(const std::vector<double>& predicted_output, const std::vector<double>& desired_output);

    void backpropagation(const std::vector<double>& input, const std::vector<double>& output, double learning_rate);

    //update the nsu file with the learned data
    void updateNetwork();

    friend std::ostream& operator<<(std::ostream& os, const NeuralNetwork& nn);

    operator bool() const;
};

#endif