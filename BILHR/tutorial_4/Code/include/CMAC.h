#ifndef CMAC_H
#define CMAC_H

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <math.h>
#include <cstdio>


using namespace std;

class Training_set
{
public:
    Training_set(double* inputs,
                 uint inputcount,
                 double* outputs,
                 uint outputcount);
    ~Training_set();

    double* in;
    double* out;

    uint incount;
    uint outcount;
};

class CMAC_network{
public:

    CMAC_network(uint n_inputs, uint n_outputs, uint n_asociations, uint res, uint** displace);
    CMAC_network();
    ~CMAC_network();

    void set_learning_rate(double learning);

    void CMAC_Map(double* inputs, double* outputs);
    void CMAC_Quantize_Associate(double* inputs);
    uint CMAC_Hash(uint, uint* p);
    void CMAC_Target_Train(double* outputs, double* desired_output);

    void train_set(Training_set* set);
    void train();
    double calc_MSE();

    void add_training_set(Training_set* set);
    bool load_training_data(const char* file);
    void get_min_max();

private:
    uint _N_input_layer;
    uint _N_output_layer;
    uint _number_asociations;
    uint _resolution;
    uint _nw;
    uint** _displacement;
    double _learning_rate;

    uint* _index_AU;
    double** _weights_output;

    vector<Training_set*> _training_data;

    double* min_input;
    double* max_input;

    FILE* error_file;
};

#endif // CMAC_H

