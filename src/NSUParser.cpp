#include "NSUParser.h"

using namespace std;

NSUParser::NSUParser(string fname) : file(fname, ios::in), fpath(fname) {}

int NSUParser::parse(vector<vector<vector<double>>>& weights, vector<vector<double>>& biases)
{
    //in case this is being called a second time
    file.clear();
    cout << "Loading network from file..." << endl;
    int plsize; //will be used to keep track of previous layer size
    file >> plsize;
    int numlayers;
    file >> numlayers;
    if(!file.good())
    {
        cout << "Issue parsing network size." << endl;
        return 1;
    }
    cout << "Network will have " << numlayers << " layers and take in input of size " << plsize << endl;
    //subtract 1 layer since we are not counting the input layer
    biases.resize(numlayers);
    weights.resize(numlayers);

    for(int layer = 0; layer < numlayers; layer++)
    {
        int lsize;
        file >> lsize;

        cout << "Parsing layer " << layer+1 << " of size " << lsize << endl;

        vector<double>& lbiases = biases[layer];
        vector<vector<double>>& lweights = weights[layer];
        lbiases.resize(lsize);
        lweights.resize(lsize);
        for(int i = 0; i < lsize; i++) lweights[i].resize(plsize);

        for(int i = 0; i < lsize; i++)
        {
            file >> lbiases[i];
            //parse out weight array
            file.ignore(numeric_limits<streamsize>::max(), '[');
            if(file.eof()) 
            {
                cout << "Issue parsing start of weight array of layer " << i+1 << ", node " << i+1 << '.' << endl;
                return 1;
            }
            
            string array;
            getline(file, array, ']');
            stringstream ss(array);
            for(int j = 0; j < plsize; j++) ss >> lweights[i][j];

            if(ss.fail())
            {
                cout << "Issue parsing weight array of layer " << i+1 << ", node " << i+1 << '.' << endl;
                return 1;
            }
        }

        if(file.fail())
        {
            cout << "Issue parsing layer " << layer+1 << '.' << endl;
            return 1;
        }
        //set the previous layer size to this layer's size for the next layer
        plsize = lsize;
    }

    cout << "Biases: " << biases << endl;
    cout << "Weights: " << weights << endl;
    cout << "Succeeded parsing file.\n" << endl;
    hasParsed = true;

    return 0;
}

void NSUParser::write(vector<vector<vector<double>>>& weights, vector<vector<double>>& biases)
{
    if(!hasParsed) return;
    file.close();
    //clear contents and write to file
    file.open(fpath, ios::out | ios::trunc);

    //append input size and layer count
    file << weights[0][0].size() << '\n' << biases.size();
    
    for(size_t layer = 0; layer < biases.size(); layer++)
    {
        file << "\n\n";
        //append layer size
        file << biases[layer].size() << '\n';
        for(size_t node = 0; node < biases[layer].size(); node++)
        {
            //append node bias
            file << biases[layer][node] << " [ ";
            //append weight array
            for(size_t pnode = 0; pnode < weights[layer][node].size(); pnode++) file << weights[layer][node][pnode] << ' ';
            file << "] ";
        }
    }
    file << endl;
    file.close();
}

NSUParser::~NSUParser()
{
    file.close();
}