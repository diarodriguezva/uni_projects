#ifndef FFNN_H
#define FFNN_H


#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <math.h>
#include <cstdio>


using namespace std;

///////////////////////////////////////////////////////////////////////////
// object representing one training example with inputs and desired outputs
///////////////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////////////////
// Normalizer to normalize the input values and denormalize the output values
/////////////////////////////////////////////////////////////////////////////
class Normalizer
{
public:
    Normalizer(double inp_min, double inp_max, double norm_min = 0.0, double norm_max = 1.0);
    ~Normalizer();

    // normalize the values
    void normalize(double* value, uint count = 1);
    // denormalize the values
    void denormalize(double* value, uint count = 1);
    // writes the normalizer data into the provided file
    void save_data(FILE* file);
private:
    double _input_min;
    double _input_max;
    double _norm_min;
    double _norm_max;
};

/////////////////////////////
// Node of the Neural Network
/////////////////////////////
class FFNN_node
{
public:
    FFNN_node(uint inputcount);
    ~FFNN_node();

    // sets one of the inputs of the node
    bool set_input(double value, uint input_number);
    // initializes the weights random between -1 and 1
    void rnd_weights();
    // sets one of the weights
    bool set_weight(double value, uint input_number);
    // sets the bias
    void set_bias(double value);
    // initialize the bias random between -1 and 1
    void rnd_bias();
    // calculate output using the set inputs, the bias and the weights
    void calc_output();
    // return the output of the node
    double get_output();
    // returns the error contribution from the selected node in the layer before
    double get_error_weighted(uint input_index);
    // calculate the error of the node putting all the error contribution from this node to the next layer together
    void calc_error(double error_contribution);
    // adjust the weights using the backpropagated error and the set inputs of the Node
    void learn(double learning_rate);
    // writes bias and the weights in the provided file to allow loading
    void save_data(FILE* file);

private:

    uint _inputcount;


    double* _weights;
    double* _inputs;
    double _bias;

    double _output;
    double _error;


};

/////////////////////////////////////////////////////////////////////
// FF Neural Network using one input, one hidden and one output layer
/////////////////////////////////////////////////////////////////////
class FFNN_network
{
public:
    FFNN_network(uint N_input,
                 uint N_hidden,
                 uint N_output,
                 double MSE);
    FFNN_network();

    // starts backpropagation at the output layer and goes through the network
    // in principle allows the use of multiple hidden layers by adding steps
    void propagate_back(double* des_output,
                        uint outputcount);
    // Backpropagation step to go one layer back from the already computed errors in the neighbouring layer
    void propagate_back_step(vector<FFNN_node*>& layer_left,
                             vector<FFNN_node*>& layer_right);
    // calculate the complete network
    // allows the use of multiple hidden layers by adding steps
    void calc_feedforward();
    // uses the outputs of the current layer to calculate the outputs of the next layer
    void calc_feedforward_step(vector<FFNN_node*>& layer_left,
                               vector<FFNN_node*>& layer_right);
    // let every Node learn using the learn function of the Nodes
    // in principal allows the use of multiple hidden layers by adding steps
    void learn(double learning_rate);
    // learning step goes through the current layer and learns
    void learn_step(double learning_rate,
                    vector<FFNN_node*>& layer);
    // train the Neural Network using the training samples given to the network
    void train(double abort_time);
    // calculates Mean Square Error using the training samples given to the Network
    double calc_MSE();

    // set the inputs of the network explicitly already normalized so the network doesn't do it
    bool set_inputs_normalized(double* inputs,
                               uint inputcount);
    // get the output with the given input already denormalized
    double get_output_denormalized(uint index);
    // takes the double array inputs, normalize all the inputs and calculate the output
    // at the end the function puts the denormalized outputs in the provided double array outputs
    // make sure that the array lengths are the same as you say with inputcount and outputcount!
    bool request_output(double* inputs,
                        uint inputcount,
                        double* outputs,
                        uint outputcont);

    // add single training sample to the training data
    void add_training_set(Training_set* set);
    // load training data from a file
    /* file format has to be:
    inputs: 2 outputs: 2
    Here you can write any text you want but make sure there is a line with "---" at the end
    ... for example data names
    pos_x	pos_y	s_pitch		s_roll
    ---
    110     40      -0.64884	0.228524
    163     54      -0.64884	0.0966001
    200     54      -0.673384	-0.01845
    223     77      -0.691792	-0.0997519
    274     72      -0.647306	-0.200996
    172     97      -0.546062	0.0413761
    */
    // in principal this can also be used for a different number of inputs and outputs
    /* ... for example the XOR:
    inputs: 2 outputs: 1
    inp_1	inp_2	outp
    ---
    0	0	0
    1	0	1
    0	1	1
    1	1	0
    */
    bool load_training_data(const char* file);
    // use training data to determine the needed normalizer and normalize the data
    void normalize_training_set();

    // resize a layer of the network to another size
    // make sure you also change the input count of the following layer by using resize
    void resize(vector<FFNN_node*>& layer, uint size, uint inputs);
    // save the network data to a file
    // including network size, Max_MSE, weights, biases and the normalizer data
    void save(const char* file);
    // load the network data from a file
    // including network size, Max_MSE, weights, biases and the normalizer data
    void load(const char* file);

    void save_normalized_data(const char* file);

private:
    uint _N_input_layer;
    uint _N_hidden_layer;
    uint _N_output_layer;

    double _MAX_MSE;

    vector<FFNN_node*> _input_nodes;
    vector<FFNN_node*> _hidden_nodes;
    vector<FFNN_node*> _output_nodes;

    vector<Training_set*> _training_data;
    vector<Normalizer*> _input_normalizer;
    vector<Normalizer*> _output_normalizer;
};


#endif // FFNN_H
