#include "NeuralNetwork.h"

using namespace std;

int main()
{
    Randomizer random;

    // Create a neural network
    NeuralNetwork nn("testnet.nsu");

    //Create some random training data
    //Assume that the label 0 -> x^2<y and label 1 -> x^2>=y
    int train_size = 50;
    vector<vector<double>> training_data(train_size);
    vector<vector<double>> desired_outputs(train_size);
    for(int i = 0; i < train_size; i++)
    {
        training_data[i] = vector<double>(2);
        training_data[i][0] = random.randDouble();
        training_data[i][1] = random.randDouble();
        desired_outputs[i] = vector<double>(2);
        desired_outputs[i][0] = training_data[i][0] <  training_data[i][1]; //casting bool to double sets it to 0/1
        desired_outputs[i][1] = training_data[i][0] >= training_data[i][1];
    }
    cout << "Training data: " << training_data << endl;
    cout << "Desired outputs: " << desired_outputs << endl;

    cout << "Network before:" << endl;
    cout << nn << endl;

    vector<double> p(2);
    for(double i = 0; i < 20; i++)
    {
        for(double j = 0; j < 20; j++)
        {
            p[0] = i/20;
            p[1] = j/20;
            cout << maxIndex(softmax(nn.predict(p)));
        }
        cout << endl;
    }

    /*
    cout << "Losses before: " << endl;
    for(int i = 0; i < train_size; i++) 
        cout << "Point " << training_data[i] << ": " << nn.calculateLoss(nn.predict(training_data[i]), desired_outputs[i]) << endl;
    */

    double learning_rate = 1;
    for(int i = 0; i < train_size; i++) nn.backpropagation(training_data[i], desired_outputs[i], learning_rate);

    cout << "\nNetwork after: \n" << nn << endl;

    cout << "desired output:" << endl;
    for(double i = 0; i < 20; i++) 
    { 
        for(double j = 0; j < 20; j++) cout << (i >= j);
        cout << endl;
    }
    cout << "actual output:" << endl;
    for(double i = 0; i < 20; i++)
    {
        for(double j = 0; j < 20; j++)
        {
            p[0] = i/20;
            p[1] = j/20;
            cout << maxIndex(softmax(nn.predict(p)));
        }
        cout << endl;
    }

    /*
    cout << "Losses after: " << endl;
    for(int i = 0; i < train_size; i++) 
        cout << "Point " << training_data[i] << ": " << nn.calculateLoss(nn.predict(training_data[i]), desired_outputs[i]) << endl;
    */

    nn.updateNetwork();

    return 0;
}

