#ifndef CMAC_H
#define CMAC_H
#include <vector>
#include <string>
#include <stdio.h>
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

using namespace std;

class CMAC
{
public:
    CMAC(const vector< vector<int> > &init_d,const vector<int> &init_resInput,
         const vector<double> &init_minInput, const vector<double> &init_maxInput,
         const int n_w = 8*2048, const int n_a = 5,
         const int n_x = 2, const int n_y = 2,
         const double init_MSE_T = 0.00003, const double init_alpha = 0.4,
         const int init_maxIterationNum = -1);
    void trainNeuralNetwork(bool displayMSE);
    void loadTrainingData(string path);
    void dispTrainingData();
    vector<double> getOutput(vector<double> &input);
    void Test(int num_in1, int num_in2,string path = "test.txt");
    string getProgramPath(){return programPath;}
    void saveNeuroNetwork(string path);
private:

    //get program path and store it in private variable programPath
    void initProgramPath();

    //map the CMAC input to its output
    void cmacMap(vector<double> &y, vector<double> &x);//map inputs(y) to outputs(x)

    //get weight table indices
    void cmacQuantizeAndAssociate(vector<double> &y, vector<int> &mu);//input y, get mu as output

    //train the CMAC output to reach a given target
    //this function only train once, using all samples
    //return current MSE
    double cmacTargetTrain();

    //compute a virtual address for weight table indices p
    int cmacHash(vector<int> &p);


    string programPath;

    //network settings
    double alpha;//learning rate
    int N_y;//number of inputs
    int N_x;//number of outputs
    int N_a;//number of association units
    double MSE_T;//threshold of mean square error, to stop training
    //maxium number of iterations
    //if this value is larger than 0, then training stops when iteration count reachs this value.
    //When this variable is -1,then training will not stop until MSE goes lower than threshold
    int maxIterationNum;

    //network parameters
    //note: first vector inpu corresponds to 320 pixel input and second to 240 pixel input
    vector< vector<int> > d;//dim N_a * Ny, d[i][j] is the desplacement for AU i along input yi
    vector<double> minInput;//2
    vector<double> maxInput;//2
    vector<int> resInput;//2
    int N_w;//number of physictal CMAC weights per output
    vector< vector<double> > W;//each row is the weights array of one output
    vector<int> mu;//N_a
    vector<int> r;//the number of different values of pj_k, see paper page 39

    //training data
    int sampleNum;
    vector< vector<double> > inputData;//Dim:  sampleNum * N_y
    vector< vector<double> > desiredOutput;//Dim: sampleNum * N_x
    vector< vector<double> > x;//output of neural network, Dim: sampleNum * N_x
};

#endif // CMAC_H
