# NeuralNetwork
Simple neural network practice to predict a label on a point.
Implements a basic feedforward network.

g++ -g -Wall src/main.cpp src/NeuralNetwork.cpp src/GlobalHelpers.cpp src/NSUParser.cpp -o neuralnet

How it works:
The neural network is an n-partite complete graph where each node is assigned a bias and each edge is assigned a weight. The first layer is an input with some number of dimensions. For each successive layer, the output of a node is calculated by:
    1. Summing the outputs of all the previous nodes times the weights of the edges connecting those nodes to this one
    2. Adding the node's bias
    3. Applying an activation function to "normalize" and delinearize the output, setting it between 0 and 1 (using the sigmoid function)
The final output is then ran through a softmax function, which allows the output vector to be interpreted roughly as the probabilities
of the input falling into each index category.
This is the simplest type of neural network, called a feedforward network. 

Training:
Under construction