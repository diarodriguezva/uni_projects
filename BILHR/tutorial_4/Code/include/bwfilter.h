#ifndef BWFILTER_H
#define BWFILTER_H

#include <cstdlib>

class Butter2Order
{
public:
    Butter2Order(int inputcount, double A1, double A2, double A3, double B1, double B2, double B3);
    ~Butter2Order();

    // input the new value -> returns the filtered value
    void filter(double* input, double* output);
    void filter(int* input, int* output);

    // reset to start with the next input value
    void reset();
private:
    int _inputcount;

    bool _valid;

    double _A[3];
    double _B[3];

    double* _x_1; //previous input value
    double* _x_2; //previous previous input value
    double* _xf_1; //previous filtered value
    double* _xf_2; //previous previous filtered value

    double* _xf; //filtered value
};

#endif //BWFILTER_H
