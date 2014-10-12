#include <FFNN.h>

///////////////////////////////////////////////////////////////////////////
// object representing one training example with inputs and desired outputs
///////////////////////////////////////////////////////////////////////////
Training_set::Training_set(double *inputs,
                           uint inputcount,
                           double *outputs,
                           uint outputcount)
    :incount(inputcount),
      outcount(outputcount)
{
    in = (double*) malloc(inputcount*sizeof(double));
    out = (double*) malloc(outputcount*sizeof(double));

    for(uint i = 0; i<inputcount; i++)
        in[i] = inputs[i];

    for(uint i = 0; i<outputcount; i++)
        out[i] = outputs[i];
}

Training_set::~Training_set()
{
    free(in);
    free(out);
}

/////////////////////////////////////////////////////////////////////////////
// Normalizer to normalize the input values and denormalize the output values
/////////////////////////////////////////////////////////////////////////////
Normalizer::Normalizer(double inp_min, double inp_max, double norm_min, double norm_max)
    :_input_min(inp_min),
      _input_max(inp_max),
      _norm_min(norm_min),
      _norm_max(norm_max)
{}

Normalizer::~Normalizer(){}

// normalize the values
void Normalizer::normalize(double *value, uint count)
{
    for(uint i = 0; i < count; i++)
    {
        value[i] = (value[i] - _input_min) / (_input_max - _input_min);
        value[i] = (value[i] * (_norm_max - _norm_min) + _norm_min);
    }
}

// denormalize the values
void Normalizer::denormalize(double *value, uint count)
{
    for(uint i = 0; i < count; i++)
    {
        value[i] = (value[i] - _norm_min) / (_norm_max - _norm_min);
        value[i] = (value[i] * (_input_max - _input_min) + _input_min);
    }
}

// writes the normalizer data into the provided file
void Normalizer::save_data(FILE* file)
{
    fprintf(file, "n %lf %lf %lf %lf\n", _input_min, _input_max, _norm_min, _norm_max);
}

/////////////////////////////
// Node of the Neural Network
/////////////////////////////
FFNN_node::FFNN_node(uint inputcount)
    :_inputcount(inputcount),
      _bias(0.0)
{
    _weights = (double*) malloc(_inputcount*sizeof(double));
    _inputs = (double*) malloc(_inputcount*sizeof(double));

    for(uint i = 0; i < _inputcount; i++)
    {
        _weights[i] = 1.0;
        _inputs[i] = 0.0;
    }
}


FFNN_node::~FFNN_node()
{
    free(_weights);
    free(_inputs);
}

// sets one of the inputs of the node
bool FFNN_node::set_input(double value,
                     uint input_number)
{
    if(input_number >_inputcount)
        return false;
    else
    {
        _inputs[input_number] = value;
        return true;
    }
}

// initializes the weights random between -1 and 1
void FFNN_node::rnd_weights()
{
    for(uint i = 0; i < _inputcount; i++)
    {
        _weights[i] = ((double) rand() / RAND_MAX)*2 - 1;
    }
}

// sets one of the weights
bool FFNN_node::set_weight(double value,
                      uint input_number)
{
    if(input_number >_inputcount)
        return false;
    else
    {
        _weights[input_number] = value;
        return true;
    }
}

// sets the bias
void FFNN_node::set_bias(double value)
{
    _bias = value;
}

// initialize the bias random between -1 and 1
void FFNN_node::rnd_bias()
{
    _bias = ((double) rand() / RAND_MAX)*2 - 1;
}

// calculate output using the set inputs, the bias and the weights
void FFNN_node::calc_output()
{
    double outp = _bias;
    for(uint i = 0; i < _inputcount; i++)
    {
        outp += _weights[i]*_inputs[i];
    }
    outp = 1 / (1 + exp(-outp));
    _output = outp;
}

// return the output of the node
double FFNN_node::get_output()
{
    return _output;
}

// returns the error contribution from the selected node in the layer before
double FFNN_node::get_error_weighted(uint input_index)
{
    if(input_index > _inputcount)
        throw runtime_error("input doesn't exist!");
    return _weights[input_index]*_error;
}

// calculate the error of the node putting all the error contribution from this node to the next layer together
void FFNN_node::calc_error(double error_contribution)
{
    _error = _output*(1.0 - _output)*error_contribution;
    //cout << "error >-> " << _error << endl;
}

// adjust the weights using the backpropagated error and the set inputs of the Node
void FFNN_node::learn(double learning_rate)
{
    for(uint index; index < _inputcount; index++)
    {
        //cout << "weight before " << _weights[index] << endl;
        _weights[index] += learning_rate*_inputs[index]*_error;
       // cout << "weight change = "
        //        << learning_rate
        //        << " * "
        //        << _inputs[index]
        //        << " * "
       //         << _error
        //        << endl;
    }
    _bias += learning_rate*_error;
}

// writes bias and the weights in the provided file to allow loading
void FFNN_node::save_data(FILE* file)
{
    fprintf(file, "%lf", _bias);
    for(uint inp_index = 0; inp_index < _inputcount; inp_index++)
    {
        fprintf(file, " %lf", _weights[inp_index]);
    }
    fprintf(file, "\n");
}

/////////////////////////////////////////////////////////////////////
// FF Neural Network using one input, one hidden and one output layer
/////////////////////////////////////////////////////////////////////
FFNN_network::FFNN_network(uint N_input,
                           uint N_hidden,
                           uint N_output,
                           double MSE)
    :_N_input_layer(N_input),
      _N_hidden_layer(N_hidden),
      _N_output_layer(N_output),
      _MAX_MSE(MSE)
{
    FFNN_node* temp;
    for(uint i = 0; i < _N_input_layer; i++)
    {
        temp = new FFNN_node(1);
        _input_nodes.push_back(temp);
    }
    for(uint i = 0; i < _N_hidden_layer; i++)
    {
        temp = new FFNN_node(_N_input_layer);
        temp->rnd_weights();
        temp->rnd_bias();
        _hidden_nodes.push_back(temp);
    }
    for(uint i = 0; i < _N_output_layer; i++)
    {
        temp = new FFNN_node(_N_hidden_layer);
        temp->rnd_weights();
        temp->rnd_bias();
        _output_nodes.push_back(temp);
    }
}

FFNN_network::FFNN_network()
    :_N_input_layer(0),
      _N_hidden_layer(0),
      _N_output_layer(0)
{

}

// starts backpropagation at the output layer and goes through the network
// in principle allows the use of multiple hidden layers by adding steps
void FFNN_network::propagate_back(double *des_output,
                                  uint outputcount)
{
    if(outputcount != _N_output_layer)
        throw runtime_error("Wrong size of output vector for backpropagation!");

    double error_contr;

    for(uint i = 0; i < _N_output_layer; i++)
    {
        error_contr = des_output[i] - _output_nodes.at(i)->get_output();
        _output_nodes.at(i)->calc_error(error_contr);
    }
    propagate_back_step(_hidden_nodes, _output_nodes);
}

// Backpropagation step to go one layer back from the already computed errors in the neighbouring layer
void FFNN_network::propagate_back_step(vector<FFNN_node*>& layer_left,
                                       vector<FFNN_node*>& layer_right)
{
    double error_contr;

    for(uint index_left = 0; index_left < layer_left.size(); index_left++)
    {
        error_contr = 0;
        for(uint index_right = 0; index_right < layer_right.size(); index_right++)
        {
            error_contr += layer_right.at(index_right)->get_error_weighted(index_left);
        }
        layer_left.at(index_left)->calc_error(error_contr);
    }
}

// calculate the complete network
// allows the use of multiple hidden layers by adding steps
void FFNN_network::calc_feedforward()
{
    calc_feedforward_step(_input_nodes, _hidden_nodes);
    calc_feedforward_step(_hidden_nodes, _output_nodes);
}

// uses the outputs of the current layer to calculate the outputs of the next layer
void FFNN_network::calc_feedforward_step(vector<FFNN_node*>& layer_left,
                                         vector<FFNN_node*>& layer_right)
{
    for(uint j = 0; j < layer_right.size(); j++)
    {
        for(uint i = 0; i < layer_left.size(); i++)
        {
            layer_right.at(j)->set_input(layer_left.at(i)->get_output(), i);
        }
        layer_right.at(j)->calc_output();
        //cout << "node "
          //   << j
          //   << " output - "
          //   << layer_right.at(j)->get_output()
          //   << endl;
    }
}

// let every Node learn using the learn function of the Nodes
// in principal allows the use of multiple hidden layers by adding steps
void FFNN_network::learn(double learning_rate)
{
    learn_step(learning_rate, _hidden_nodes);
    learn_step(learning_rate, _output_nodes);
}

// learning step goes through the current layer and learns
void FFNN_network::learn_step(double learning_rate,
                              vector<FFNN_node*>& layer)
{
    for(uint index = 0; index < layer.size(); index++)
    {
        layer.at(index)->learn(learning_rate);
    }
}

// train the Neural Network using the training samples given to the network
void FFNN_network::train(double abort_time)
{
    int starting_time = time(0);

    //FILE* outpfile = fopen(PATH_MSE_OUTPUT_FILE,"w");

    uint epoch = 0;
    while(1)
    {
        for(uint i = 0; i < _training_data.size(); i++)
        {
            Training_set* tset = _training_data.at(i);
            set_inputs_normalized(tset->in,tset->incount);
            //cout << tset->in[0] << "   " << tset->in[1] << endl;

            calc_feedforward();

            propagate_back(tset->out, tset->outcount);
            learn(0.6);

        }

        //fprintf(outpfile, "%d %lf\n", epoch, calc_MSE());

        if((time(0)-starting_time) > abort_time)
        {
            //fclose(outpfile);
            return;
        }
        if(calc_MSE() < _MAX_MSE)
        {
            //fclose(outpfile);
            return;
        }
        epoch++;

        if(epoch%1000 == 0)
        {
            cout << "epoch: " << epoch << " MSE: " << calc_MSE() << endl;
        }


    }
}

// calculates Mean Square Error using the training samples given to the Network
double FFNN_network::calc_MSE()
{
    double MSE = 0;

    for(uint i = 0; i < _training_data.size(); i++)
    {
        Training_set* tset = _training_data.at(i);
        set_inputs_normalized(tset->in,tset->incount);
        calc_feedforward();
        for(uint j = 0; j < _N_output_layer; j++)
        {
            MSE += 0.5*(tset->out[j] - _output_nodes.at(j)->get_output())*(tset->out[j] - _output_nodes.at(j)->get_output());
        }

    }

    MSE = MSE / (_training_data.size() * _N_output_layer);
    return MSE;
}

// set the inputs of the network explicitly already normalized so the network doesn't do it
bool FFNN_network::set_inputs_normalized(double* inputs,
                                         uint inputcount)
{
    if(inputcount != _input_nodes.size())
    {
        cout << "Wrong input size for FFNN (Is "
             << inputcount
             << "-> should be "
             << _input_nodes.size()
             << ")"
             << endl;
        return false;
    }
    for(uint i = 0; i < inputcount; i++)
    {
        _input_nodes.at(i)->set_input(inputs[i],0);
        _input_nodes.at(i)->calc_output();
    }
    return true;
}

// get the output with the given input already denormalized
double FFNN_network::get_output_denormalized(uint index)
{
    if(index < _N_output_layer)
    {
        double outp = _output_nodes.at(index)->get_output();
        _output_normalizer.at(index)->denormalize(&outp);
        return outp;
    }
    else
        throw std::runtime_error("unknown output requested!");
}

// takes the double array inputs, normalize all the inputs and calculate the output
// at the end the function puts the denormalized outputs in the provided double array outputs
// make sure that the array lengths are the same as you say with inputcount and outputcount!
bool FFNN_network::request_output(double *inputs,
                                  uint inputcount,
                                  double *outputs,
                                  uint outputcont)
{
    if((inputcount != _N_input_layer) || (outputcont != _N_output_layer))
        return false;
    else
    {
        double* inp = (double*) malloc(inputcount*sizeof(double));
        for(uint i = 0; i < inputcount; i++)
        {
            inp[i] = inputs[i];
            _input_normalizer.at(i)->normalize(&inp[i]);
        }

        set_inputs_normalized(inp, inputcount);
        calc_feedforward();

        for(uint i = 0; i < outputcont; i++)
        {
            outputs[i] = get_output_denormalized(i);
        }

        free(inp);
    }

}

// add single training sample to the training data
void FFNN_network::add_training_set(Training_set *set)
{
    _training_data.push_back(set);
}

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
bool FFNN_network::load_training_data(const char *file)
{
    FILE* training_data = fopen(file, "r");
    int inputcount, outputcount;

    if(fscanf(training_data, "inputs: %d outputs: %d\n",&inputcount,&outputcount))
    {
        if((inputcount != _N_input_layer) || (outputcount != _N_output_layer))
        {
            fclose(training_data);
            return false;
        }

    }
    else
    {
        cout << "couldn't read data header -> first line should be \"inputs: x outputs: y\"" << endl;
        fclose(training_data);
        return false;
    }
    char c;
    while(!fscanf(training_data, "-%c-\n",&c))
    {
        c = fgetc(training_data);
    }

    double* temp_inp = (double*) malloc(inputcount*sizeof(double));
    double* temp_outp = (double*) malloc(outputcount*sizeof(double));
    while(!feof(training_data))
    {
        for(uint i = 0; i < inputcount; i++)
        {
            if(!fscanf(training_data, "%lf", &temp_inp[i]))
            {
                fclose(training_data);
                return false;
            }
        }
        for(uint i = 0; i < outputcount - 1; i++)
        {

            if(!fscanf(training_data, "%lf", &temp_outp[i]))
            {
                fclose(training_data);
                return false;
            }
        }
        if(!fscanf(training_data, "%lf\n", &temp_outp[outputcount - 1]))
        {
            fclose(training_data);
            return false;
        }

        Training_set* temp = new Training_set(temp_inp,inputcount,temp_outp,outputcount);
        add_training_set(temp);
    }
    fclose(training_data);
    return true;
}

// use training data to determine the needed normalizer and normalize the data
void FFNN_network::normalize_training_set()
{
    while(_input_normalizer.size() > 0)
    {
        delete _input_normalizer.back();
        _input_normalizer.pop_back();
    }
    while(_output_normalizer.size() > 0)
    {
        delete _output_normalizer.back();
        _output_normalizer.pop_back();
    }

    double* min_input = (double*) malloc(_N_input_layer*sizeof(double));
    double* max_input = (double*) malloc(_N_input_layer*sizeof(double));
    double* min_output = (double*) malloc(_N_output_layer*sizeof(double));
    double* max_output = (double*) malloc(_N_output_layer*sizeof(double));

    for(uint i = 0; i < _N_input_layer; i++)
    {
        min_input[i] = _training_data.at(0)->in[i];
        max_input[i] = _training_data.at(0)->in[i];
    }
    for(uint i = 0; i < _N_output_layer; i++)
    {
        min_output[i] = _training_data.at(0)->out[i];
        max_output[i] = _training_data.at(0)->out[i];
    }

    for(uint i = 0; i < _training_data.size(); i++)
    {
        for(uint j = 0; j < _N_input_layer; j++)
        {
            min_input[j] = min(min_input[j], _training_data.at(i)->in[j]);
            max_input[j] = max(max_input[j], _training_data.at(i)->in[j]);
        }
        for(uint j = 0; j < _N_output_layer; j++)
        {
            min_output[j] = min(min_output[j], _training_data.at(i)->out[j]);
            max_output[j] = max(max_output[j], _training_data.at(i)->out[j]);
        }
    }

    for(uint i = 0; i < _N_input_layer; i++)
    {
        Normalizer* normi =new Normalizer(min_input[i],max_input[i]);
        _input_normalizer.push_back(normi);
    }

    for(uint i = 0; i < _N_output_layer; i++)
    {
        Normalizer* normi =new Normalizer(min_output[i],max_output[i]);
        _output_normalizer.push_back(normi);
    }

    for(uint i = 0; i < _training_data.size(); i++)
    {
        for(uint j = 0; j < _N_input_layer; j++)
        {
            _input_normalizer.at(j)->normalize(&_training_data.at(i)->in[j]);
        }
        for(uint j = 0; j < _N_output_layer; j++)
        {
            _output_normalizer.at(j)->normalize(&_training_data.at(i)->out[j]);
        }
    }

    free(min_input);
    free(max_input);
    free(min_output);
    free(max_output);
}

// resize a layer of the network to another size
// make sure you also change the input count of the following layer by using resize
void FFNN_network::resize(vector<FFNN_node*>& layer, uint size, uint inputs)
{
    FFNN_node* temp;

    while(layer.size() > 0)
    {
        delete layer.back();
        layer.pop_back();
    }

    for(uint i = 0; i < size; i++)
    {
        temp = new FFNN_node(inputs);
        temp->rnd_weights();
        temp->rnd_bias();
        layer.push_back(temp);
    }

}

// save the network data to a file
// including network size, Max_MSE, weights, biases and the normalizer data
void FFNN_network::save(const char *file)
{
    FILE* FFNN_save = fopen(file, "w");

    fprintf(FFNN_save, "%d %d %d %lf \n", _N_input_layer, _N_hidden_layer, _N_output_layer, _MAX_MSE);

    for(uint node = 0; node < _N_input_layer; node++)
    {
        _input_nodes.at(node)->save_data(FFNN_save);
    }
    for(uint node = 0; node < _N_hidden_layer; node++)
    {
        _hidden_nodes.at(node)->save_data(FFNN_save);
    }
    for(uint node = 0; node < _N_output_layer; node++)
    {
        _output_nodes.at(node)->save_data(FFNN_save);
    }
    for(uint node = 0; node < _N_input_layer; node++)
    {
        _input_normalizer.at(node)->save_data(FFNN_save);
    }
    for(uint node = 0; node < _N_output_layer; node++)
    {
        _output_normalizer.at(node)->save_data(FFNN_save);
    }
    fclose(FFNN_save);
}

// load the network data from a file
// including network size, Max_MSE, weights, biases and the normalizer data
void FFNN_network::load(const char *file)
{
    FILE* FFNN_save = fopen(file, "r");

    fscanf(FFNN_save, "%d %d %d %lf \n", &_N_input_layer, &_N_hidden_layer, &_N_output_layer, &_MAX_MSE);

    resize(_input_nodes, _N_input_layer, 1);
    resize(_hidden_nodes, _N_hidden_layer, _N_input_layer);
    resize(_output_nodes, _N_output_layer, _N_hidden_layer);

    for(uint node = 0; node < _N_input_layer; node++)
    {
        double bias, weight;
        fscanf(FFNN_save, "%lf %lf\n", &bias, &weight);
        _input_nodes.at(node)->set_bias(bias);
        _input_nodes.at(node)->set_weight(weight,0);
    }

    for(uint node = 0; node < _N_hidden_layer; node++)
    {
        double bias, weight;
        fscanf(FFNN_save, "%lf", &bias);
        _hidden_nodes.at(node)->set_bias(bias);
        for(uint inp_index = 0; inp_index < _N_input_layer; inp_index++)
        {
            fscanf(FFNN_save, " %lf", &weight);
            _hidden_nodes.at(node)->set_weight(weight,inp_index);
        }
    }

    for(uint node = 0; node < _N_output_layer; node++)
    {
        double bias, weight;
        fscanf(FFNN_save, "%lf", &bias);
        _output_nodes.at(node)->set_bias(bias);
        for(uint inp_index = 0; inp_index < _N_hidden_layer; inp_index++)
        {
            fscanf(FFNN_save, " %lf", &weight);
            _output_nodes.at(node)->set_weight(weight,inp_index);
        }
    }

    while(_input_normalizer.size() > 0)
    {
        delete _input_normalizer.back();
        _input_normalizer.pop_back();
    }
    while(_output_normalizer.size() > 0)
    {
        delete _output_normalizer.back();
        _output_normalizer.pop_back();
    }

    for(uint node = 0; node < _N_input_layer; node++)
    {
        double input_min, input_max, norm_min, norm_max;
        fscanf(FFNN_save, " n %lf %lf %lf %lf", &input_min, &input_max, &norm_min, &norm_max);
        Normalizer* temp = new Normalizer(input_min, input_max, norm_min, norm_max);
        _input_normalizer.push_back(temp);
    }

    for(uint node = 0; node < _N_output_layer; node++)
    {
        double input_min, input_max, norm_min, norm_max;
        fscanf(FFNN_save, " n %lf %lf %lf %lf", &input_min, &input_max, &norm_min, &norm_max);
        Normalizer* temp = new Normalizer(input_min, input_max, norm_min, norm_max);
        _output_normalizer.push_back(temp);
    }
    fclose(FFNN_save);
}

void FFNN_network::save_normalized_data(const char *file)
{
    FILE* outfile = fopen(file,"w");

    fprintf(outfile, "inputs: %d outputs: %d\n");
    fprintf(outfile, "This is normalized data\n");
    fprintf(outfile, "---\n");

    for(uint i = 0; i < _training_data.size(); i++)
    {
        fprintf(outfile,"%lf %lf %lf %lf\n",
                _training_data.at(i)->in[0],
                _training_data.at(i)->in[1],
                _training_data.at(i)->out[0],
                _training_data.at(i)->out[1]);

    }

    fclose(outfile);

}
