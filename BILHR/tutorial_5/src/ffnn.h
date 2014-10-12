#ifndef FFNN_H
#define FFNN_H
#include <cmath>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

using namespace std;
class FFNN
{
public:
    FFNN(int N_i, int N_h, int N_o,
         double MSE_T = 0.00003, double alpha = 0.7, double beta = 0.7);
    bool saveNetwork(std::string path);
    bool loadNetwork(std::string path);
    bool loadTrainingData(std::string path);
    void setTrainingData(std::vector< std::vector<double> > &inputData_in, std::vector< std::vector<double> > &desiredOutput_in);
    void trainNetwork(bool plotMSE);

    //for adjusting parameters
    void setAlpha(const double newAlpha){alpha = newAlpha;}
    void setBeta(const double newBeta){beta = newBeta;}
    void setMSE_T(const double newMSE_T){MSE_T = newMSE_T;}

    std::vector<double> getOutput(std::vector<double> &input);
private:
    //functions during training
    double trainOneEpoch();//return MSE after training one epoch
    double sigmoidFunc(double u){return 1.0/(1+exp(-1.0*u));}


    //network settings
    int N_i;//number of neurons of the input layer
    int N_h;//number of neurons of the hidden layer
    int N_o;//number of neurons of the output layer
    double MSE_T;//threshold of mean square error, to stop training

    //network parameters
    std::vector< std::vector<double> > v;//Dim: N_i*N_h
    std::vector< std::vector<double> > w;//Dim: N_h*N_o
    std::vector<double> upsilon;//Dim: N_h
    std::vector<double> phi;//Dim: N_o
    double alpha;//learning rate [0, 1]
    double beta;//learning rate [0, 1]


    //training data
    int dataNum;
    std::vector< std::vector<double> > inputData;//Dim: N_i * dataNum
    std::vector< std::vector<double> > desiredOutput;//Dim: N_o * dataNum
};

#endif // FFNN_H
