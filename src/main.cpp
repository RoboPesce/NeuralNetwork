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

    
    cout << "Before training:" << endl;
    cout << nn << endl;

    //Create some random training data
    //Assume that the label 0 -> x<y and label 1 -> x>=y
    vector<vector<double>> training_data(10);
    vector<vector<double>> desired_outputs(10);
    for(int i = 0; i < 10; i++)
    {
        training_data[i] = vector<double>(2);
        training_data[i][0] = random.randDouble();
        training_data[i][1] = random.randDouble();
        desired_outputs[i] = vector<double>(2);
        desired_outputs[i][0] = training_data[i][0] <  training_data[i][1]; //casting bool to double sets it to 0/1
        desired_outputs[i][1] = training_data[i][0] >= training_data[i][1];
    }
    cout << "Training data: " << training_data << endl;
    cout << "Desired outputs: " << desired_outputs << '\n' << endl;

    cout << "Network before:" << endl;
    cout << nn << '\n' << endl;

    cout << "Losses before: " << endl;
    for(int i = 0; i < 10; i++) 
        cout << "Loss for point " << training_data[i] << ": " << nn.calculateLoss(nn.predict(training_data[i]), desired_outputs[i]) << endl;

    double learning_rate = .5;
    for(int i = 0; i < 10; i++) nn.backpropagation(training_data[i], desired_outputs[i], learning_rate);

    cout << "\nNetwork after: \n" << nn << '\n' << endl;

    cout << "Losses after: " << endl;
    for(int i = 0; i < 10; i++) 
        cout << "Loss for point " << training_data[i] << ": " << nn.calculateLoss(nn.predict(training_data[i]), desired_outputs[i]) << endl;

    return 0;
}

