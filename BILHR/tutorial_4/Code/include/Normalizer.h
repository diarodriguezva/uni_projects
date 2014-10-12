#ifndef NORMALIZER_H
#define NORMALIZER_H

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

#endif // NORMALIZER_H
