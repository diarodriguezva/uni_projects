#include <CMAC.h>

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

CMAC_network::CMAC_network():_N_input_layer(0),
    _N_output_layer(0),
    _number_asociations(0),
    _resolution(0),
    _learning_rate(0.3){
}

CMAC_network::CMAC_network(uint n_inputs, uint n_outputs, uint n_asociations, uint res, uint** displace)
    : _N_input_layer(n_inputs),
      _N_output_layer(n_outputs),
      _number_asociations(n_asociations),
      _resolution(res),
      _displacement(displace)
{
    _learning_rate = 0.3;
    _index_AU = (uint*) malloc(_number_asociations*sizeof(uint));


    uint rk = floor((_resolution-2)/_number_asociations) + 2;
    _nw = rk*rk;  // number of physical CMAC weights per Output
    _weights_output = (double**)malloc(_N_output_layer*sizeof(double*));
    for (uint i=0; i<_N_output_layer; i++){
        _weights_output[i] = (double*) malloc(_nw*sizeof(double));
        for(uint j=0; j<_nw; j++){
            _weights_output[i][j] = 0;
        }
    }

    min_input = (double*) malloc(_N_input_layer*sizeof(double));
    max_input = (double*) malloc(_N_input_layer*sizeof(double));


}

CMAC_network::~CMAC_network(){
    for (uint i=0; i<_N_output_layer; i++)
        free(_weights_output[i]);
    free(_weights_output);

    free(min_input);
    free(max_input);
}

void CMAC_network::set_learning_rate(double learning){
    _learning_rate = learning;
}

void CMAC_network::CMAC_Map(double *inputs, double* outputs){
    CMAC_Quantize_Associate(inputs);
    for(uint i=0; i<_N_output_layer; i++){
        outputs[i] = 0;
        for(uint j=0; j<_number_asociations; j++){
            outputs[i] += _weights_output[i][_index_AU[j]];
            //cout << "index: " << _index_AU[j] << endl;
            //cout << "weight: " << _weights_output[i][_index_AU[j]] << endl;
            //cout << "--- weight: " << _weights_output[i][_index_AU[j]] << endl;
            //cout << "output:  " << outputs[i] << endl;
        }
    }
}

void CMAC_network::CMAC_Quantize_Associate(double* inputs){
    double* inp = (double*) malloc(_N_input_layer*sizeof(double));
    uint* q = (uint*) malloc(_N_input_layer*sizeof(uint));

   // double** p = (double**)malloc(_N_input_layer*sizeof(double*));
    uint* p = (uint*) malloc(2*sizeof(uint));

    //for (uint i=0; i<_N_input_layer; i++)
    //    p[i] = (double*) malloc(_number_asociations*sizeof(double));



    for(uint i=0; i<_N_input_layer; i++){
        inp[i] = inputs[i];

        if(inp[i] > max_input[i])
            inp[i] = max_input[i];
        else if(inp[i] < min_input[i])
            inp[i] = min_input[i];


        q[i] = (uint) floor(((double)_resolution)*(inp[i]-min_input[i])/(max_input[i]-min_input[i]));

        //cout << "i: " << i << " inp: " << inp[i] << endl;

        if(q[i] >= _resolution){
            q[i] = _resolution - 1;
        }
        //cout << "q[i]: " << q[i] << endl;
    }

    for(uint i=0; i<_number_asociations; i++){
        for(uint j=0; j< _N_input_layer; j++){
            //p[j][i] = floor((q[j] + _displacement[j][i])/_number_asociations);
            p[j] = floor((q[j] + _displacement[j][i])/_number_asociations);
            // cout << "q[j]: " << q[j] << endl;
            //cout << "disp[" << j << "][" << i << "]: " << _displacement[j][i] << endl;
            // cout << "i: " << i << " j: " << j << " p: " << p[j][i] << endl;
            // cout << "j: " << j << " i: " << i <<" q: " << q[j] << endl;
        }
        _index_AU[i] = CMAC_Hash(i,p);
        //cout << "index: " << _index_AU[i] << endl;
    }

    //free(inp);
    free(q);
    free(p);
}

uint CMAC_network::CMAC_Hash(uint i,uint *p){  //Algorithm 1 - Software
    uint h = 0;
    uint r = floor((_resolution-2)/_number_asociations) + 2;
    for(uint j=0; j<_N_input_layer; j++){
        h = h*r + p[j];
        //cout << "r: " << r << " h: " << h << endl;
        //cout << p[j][i] << endl;
    }
    return h;
}

void CMAC_network::CMAC_Target_Train(double* outputs, double* desired_output){
    double increment = 0;
    for (uint i=0; i<_N_output_layer; i++){
        increment = _learning_rate*(desired_output[i]-outputs[i])/(_number_asociations);
        for(uint j=0; j<_number_asociations; j++){

            _weights_output[i][_index_AU[j]] += increment;
            //cout << "Index: " << _index_AU[j] << endl;
            //cout << "Increment: " << increment << endl;
        }
        //cout << "desired: " << desired_output[i] << "\toutput: " << outputs[i] << endl;
        //cout << "Error: " << desired_output[i] - outputs[i] << endl;
    }
}

void CMAC_network::train_set(Training_set* set){
    double* temp = (double*) malloc(_N_output_layer*sizeof(double));

    CMAC_Map(set->in,temp);
    CMAC_Target_Train(temp, set->out);

    free(temp);
}

void CMAC_network::train(){
    //int k = 0;
    set_learning_rate(0.3);
    error_file = fopen("Error.txt","w");
    for(uint k=0; k<200; k++){
    //while(calc_MSE() > 0,003){
      //  k++;
        //set_learning_rate(0.6*exp(-(double)(k/10)));
        //cout << "L. " << _learning_rate << endl;
        for(uint i=0; i<_training_data.size(); i++){
            train_set(_training_data.at(i));
        }

        fprintf(error_file,"%lf\n",calc_MSE());
        cout << "MSE: " << calc_MSE() << "k:" << k << endl;
    }
    fclose(error_file);

    FILE* weights_file = fopen("weights.txt", "w");

    for(int i = 0; i < 2; i++)
    {
        fprintf(weights_file, "outp1\n");
        for(int j = 0; j < _nw; j++)
            fprintf(weights_file, "%lf\n", _weights_output[i][j]);
    }
    fclose(weights_file);
}

// calculates Mean Square Error using the training samples given to the Network
double CMAC_network::calc_MSE()
{
    double MSE = 0;
    double* temp = (double*) malloc(_N_output_layer*sizeof(double));

    for(uint i = 0; i < _training_data.size(); i++)
    {
        Training_set* tset = _training_data.at(i);
        CMAC_Map(tset->in, temp);

        for(uint j = 0; j < _N_output_layer; j++)
        {
            MSE += 0.5*(tset->out[j] - temp[j])*(tset->out[j] - temp[j]);
        }

    }
    MSE = MSE / (_training_data.size() * _N_output_layer);
    return MSE;
}

// add single training sample to the training data
void CMAC_network::add_training_set(Training_set *set)
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

// in principal this can also be used for a different number of inputs and outputs
... for example the XOR:
inputs: 2 outputs: 1
inp_1	inp_2	outp
---
0	0	0
1	0	1
0	1	1
1	1	0
*/
bool CMAC_network::load_training_data(const char *file)
{
    FILE* training_data = fopen(file, "r");
    uint inputcount, outputcount;

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
    free(temp_inp);
    free(temp_outp);

    // Get minimum and maximum values
    get_min_max();

    return true;

}

void CMAC_network::get_min_max()
{
    for(uint i = 0; i < _N_input_layer; i++)
    {
        min_input[i] = _training_data.at(0)->in[i];
        max_input[i] = _training_data.at(0)->in[i];
    }

    for(uint i = 0; i < _training_data.size(); i++)
    {
        for(uint j = 0; j < _N_input_layer; j++)
        {
            min_input[j] = min(min_input[j], _training_data.at(i)->in[j]);
            max_input[j] = max(max_input[j], _training_data.at(i)->in[j]);
        }
    }

}

// use training data to determine the needed normalizer and normalize the data
/*void CMAC_network::normalize_training_set()
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
        Normalizer* normi = new Normalizer(min_input[i],max_input[i]);
        _input_normalizer.push_back(normi);
    }

    for(uint i = 0; i < _N_output_layer; i++)
    {
        Normalizer* normi = new Normalizer(min_output[i],max_output[i]);
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

void CMAC_network::save_normalized_data(const char *file)
{
    FILE* outfile = fopen(file,"w");

    fprintf(outfile, "inputs: %d outputs: %d\n",_N_input_layer,_N_output_layer);
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
*/
