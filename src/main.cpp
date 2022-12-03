#include "NeuralNetwork.h"

using namespace std;

int main()
{
    Randomizer random;

    // Create a neural network
    NeuralNetwork nn(1);

    // Create a point
    Point p = {random.randDouble(), random.randDouble()};

    // Predict the label for the point using the neural network
    vector<double> prediction = nn.predict(p);

    for(size_t i = 0; i < prediction.size(); i++) cout << prediction[i] << ' ';
    cout << endl;

    cout << prediction << endl;
    int label = maxIndex(prediction);

    // Print the predicted label
    cout << "Predicted label for point " << p << ": " << label << endl;

    return 0;
}

