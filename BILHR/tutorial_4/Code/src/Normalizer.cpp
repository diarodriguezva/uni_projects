#include <Normalizer.h>

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

