#include "bwfilter.h"

Butter2Order::Butter2Order(int inputcount, double A1, double A2, double A3, double B1, double B2, double B3)
    :_inputcount(inputcount),
      _valid(false)
{
    _A[0] = A1;
    _A[1] = A2;
    _A[2] = A3;
    _B[0] = B1;
    _B[1] = B2;
    _B[2] = B3;

    _x_1 = (double*) malloc(inputcount*sizeof(double));
    _x_2 = (double*) malloc(inputcount*sizeof(double));
    _xf_1 = (double*) malloc(inputcount*sizeof(double));
    _xf_2 = (double*) malloc(inputcount*sizeof(double));
    _xf = (double*) malloc(inputcount*sizeof(double));

}

Butter2Order::~Butter2Order()
{
}

void Butter2Order::filter(double* input, double* output)
{
    if(!_valid)
    {
        for(int i = 0; i < _inputcount; i++)
        {
            _x_1[i] = input[i];
            _x_2[i] = input[i];
            _xf_1[i] = input[i];
            _xf_2[i] = input[i];
            _xf[i] = input[i];
        }
        _valid = true;
    }
    else
    {
        for(int i = 0; i < _inputcount; i++)
        {
            _xf[i] = _B[0]*input[i] + _B[1]*_x_1[i] + _B[2]*_x_2[i] - _A[1]*_xf_1[i] - _A[2]*_xf_2[i];
            _x_2[i] = _x_1[i];
            _x_1[i] = input[i];
            _xf_2[i] = _xf_1[i];
            _xf_1[i] = _xf[i];
        }
    }
    for(int i = 0; i < _inputcount; i++)
    {
        output[i] = _xf[i];

    }
}

void Butter2Order::filter(int* input, int* output)
{
    double* temp = (double*) malloc(_inputcount*sizeof(double));

    for(int i = 0; i< _inputcount; i++)
    {
        temp[i] = (double) input[i];
    }

    filter(temp, temp);

    for(int i = 0; i< _inputcount; i++)
    {
        output[i] = (int) temp[i];
    }

}


void Butter2Order::reset()
{
    _valid = false;
}
