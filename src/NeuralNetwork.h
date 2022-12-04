#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "GlobalHelpers.h"
#include "NSUParser.h"

// A simple class to represent a neural network
// with two input nodes, one hidden layer with two nodes,
// and one output node.
class NeuralNetwork
{
private:
    //for parsing NSU file
    NSUParser nsu;
    // Vector of weights, where each element is a vector of weights for a layer of the network
    std::vector<std::vector<std::vector<double>>> weights;
    // Vector of biases, where each element is a vector of biases for a layer of the network
    std::vector<std::vector<double>> biases;
public:
    NeuralNetwork(std::string fname);

    // The activation function for the nodes in the network
    double sigmoid(double x);

    // The forward propagation function, which takes in a point
    // and returns the predicted label (0 or 1) for the point
    std::vector<double> predict(Point& point);

    double calculateError(const std::vector<double>& predicted_output, const std::vector<double>& desired_output);
};

#endif