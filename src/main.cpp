#include "NeuralNetwork.h"

using namespace std;

int main(int argc, char** argv)
{
    if(argc < 4) 
    {
        cout << "first arg: training size | second arg: step size | third arg: 0 for no overwrite, 1 for overwrite" << endl;
        return 1;
    }
    
    Randomizer random;

    // Create a neural network
    NeuralNetwork nn("testnet.nsu");
    if(nn) return 1;

    /* 
    Create some random training data
    Assume that the label 0 -> 0.5sin(2pi x)+0.5<y and label 1 -> 0.5sin(2pi x)+0.5>=y
    */
    int train_size = atoi(argv[1]);
    vector<vector<double>> training_data(train_size);
    vector<vector<double>> desired_outputs(train_size);
    for(int i = 0; i < train_size; i++)
    {
        training_data[i].resize(2);
        training_data[i][0] = random.randDouble();
        training_data[i][1] = random.randDouble();
        desired_outputs[i].resize(2);
        desired_outputs[i][0] = 0.5 * sin(training_data[i][0] * 2 * M_PI) + 0.5 <  training_data[i][1]; //casting bool to double sets it to 0/1
        desired_outputs[i][1] = 0.5 * sin(training_data[i][0] * 2 * M_PI) + 0.5 >= training_data[i][1];
    }

    cout << "\nNetwork before:" << endl;
    cout << nn << endl;

    vector<double> p(2);
    double avg_loss = 0;
    for(double i = 0; i < 1; i+=.1)
    {
        for(double j = 0; j < 1; j+=.1)
        {
            p[0] = i;
            p[1] = j;
            vector<double> prediction = softmax(nn.predict(p));
            cout << maxIndex(prediction);
            //turn p into the expected output
            p[0] = (0.5 * sin(i * 2 * M_PI) + 0.5 >  j);
            p[1] = (0.5 * sin(i * 2 * M_PI) + 0.5 <= j);
            avg_loss += nn.calculateLoss(prediction, p);
        }
        cout << endl;
    }
    avg_loss /= 100;
    cout << "Average loss: " << avg_loss << endl;

    cout << "Entering training\n" << endl;
    double learning_rate = atof(argv[2]);
    for(int i = 0; i < train_size; i++) 
    {
        cout << "for point " << training_data[i] << " (" << desired_outputs[i] << ')' << endl;
        cout << "loss before: " << NeuralNetwork::calculateLoss(nn.predict(training_data[i]), desired_outputs[i]) << endl;
        nn.backpropagation(training_data[i], desired_outputs[i], learning_rate);
        cout << "loss after: " << NeuralNetwork::calculateLoss(nn.predict(training_data[i]), desired_outputs[i]) << endl;
    }

    cout << "\nNetwork after: \n" << nn << endl;

    //sample 100 points in [0, 1]^2
    cout << "desired output:" << endl;
    for(double i = 0; i < 1; i+=.1) 
    { 
        for(double j = 0; j < 1; j+=.1) cout << (0.5 * sin(i * 2 * M_PI) + 0.5 >= j);
        cout << endl;
    }
    
    avg_loss = 0;
    cout << "\nactual output:" << endl;
    for(double i = 0; i < 1; i+=.1)
    {
        for(double j = 0; j < 1; j+=.1)
        {
            p[0] = i;
            p[1] = j;
            vector<double> prediction = softmax(nn.predict(p));
            cout << maxIndex(prediction);
            //turn p into the expected output
            p[0] = (0.5 * sin(i * 2 * M_PI) + 0.5 >  j);
            p[1] = (0.5 * sin(i * 2 * M_PI) + 0.5 <= j);
            avg_loss += nn.calculateLoss(prediction, p);
        }
        cout << endl;
    }
    avg_loss /= 100;
    cout << "Average loss: " << avg_loss << '\n' << endl;

    //only update if user wants
    if(argv[3][0] == '1') nn.updateNetwork();

    return 0;
}

