# NeuralNetwork
Simple neural network practice to predict a label on a point.
Implements a basic feedforward network.


g++ -g -Wall src/main.cpp src/NeuralNetwork.cpp src/GlobalHelpers.cpp src/NSUParser.cpp -o neuralnet


How it works:

The neural network is an n-partite graph in a layered heirarchy. Each layer is fully connected to the previous and next, where each node (neuron, vertex) is assigned a bias and each edge is assigned a weight. The first layer is an input with some number of dimensions. For each successive layer, the output of a node is calculated by:

    1. Summing the outputs of all the previous nodes times the weights of the edges connecting those nodes to this one

    2. Adding the node's bias

    3. Applying an activation function to "normalize" and delinearize the output, setting it between 0 and 1 (using the sigmoid function)

The final output is then ran through a softmax function, which allows the output vector to be interpreted roughly as the probabilities of the input falling into each index category.

This is the simplest type of neural network, called a feedforward network. 



Training:

Under construction

Given some input, your output is essentially a function of all the parameters (weights and biases) of the neural network. Let's say that the function P for some input y is f_y(w1, w2, ..., b1, b2, ...), which is the softmaxed prediction. We then apply one more operation (the loss function, which in this case is cross-entropy loss). Let's call that L_y(w1, w2, ..., b1, b2, ...). We want to minimize this loss function, which roughly means taking its gradient and finding the values of parameters that set it closest to 0. But since it's pretty hard to just do that directly, we use an iterated learning process where we take small steps based on the computed derivatives until the loss converges to some value, which is hopefully the minimum. The size of the steps is called the learning rate.

In order to calculate the derivatives, we need to use the chain rule for multivariable equations. First, we calculate the partial derivative of the loss with respect to the outputs. Then, for each neuron in the last layer, we find the partial derivatives of the outputs with respect to the parameters of the neurons and multiply it with the loss derivatives. We update the parameters, then send the derivatives back to compute the next layer's derivatives -- hence backpropagation.