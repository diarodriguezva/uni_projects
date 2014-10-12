#include "cmac.h"
#include <iostream>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <iomanip>
CMAC::CMAC(const vector< vector<int> > &init_d,const vector<int> &init_resInput,
           const vector<double> &init_minInput, const vector<double> &init_maxInput,
           const int n_w, const int n_a,
           const int n_x, const int n_y, const double init_MSE_T,
           const double init_alpha, const int init_maxIterationNum)
{
    N_y = n_y;
    N_x = n_x;
    N_a = n_a;
    d = init_d;//the desplacement for AU i along input yi
    minInput = init_minInput;//2
    maxInput = init_maxInput;//2
    resInput = init_resInput;//2
    N_w = n_w;//number of physical CMAC weights per output
    MSE_T = init_MSE_T;
    sampleNum = 0;
    alpha = init_alpha;
    maxIterationNum = init_maxIterationNum;
    //each row is the weights array of one output
    W.resize(N_x);
    for(int i = 0; i < N_x; i++)
    {
        W[i].resize(N_w);
    }
    mu.resize(N_a);
    initProgramPath();
}

void CMAC::trainNeuralNetwork(bool displayMSE)
{
    //first calculate r
    r.resize(N_y);
    for(int k = 0; k < N_y; k++)
    {
        r[k] = (int)floor((resInput[k]-2)/N_a) + 2;
    }

    cout<<"training CMAC"<<endl;
    double MSE_current = cmacTargetTrain();
    int count = 0;
    while ((MSE_current > MSE_T)&&
           ((maxIterationNum == -1) || (count < maxIterationNum))
           )
    {
        if(displayMSE)
        {
            cout<<"train iteration "<<count++<<": current MSE = " << MSE_current << '\n';
        }
        MSE_current = cmacTargetTrain();
    }
    cout<<"CMAC training done"<<endl;
}

//map the CMAC input to its output
void CMAC::cmacMap(vector<double> &y, vector<double> &x)
{
    cmacQuantizeAndAssociate(y,mu);
    for(int i = 0; i < N_x; i++)
    {
        x[i] = 0;
        for(int j = 0; j < N_a; j++)
        {
            x[i] += W[i][mu[j]];
        }
    }
}
//get weight table indices
void CMAC::cmacQuantizeAndAssociate(vector<double> &y, vector<int> &mu)
{
    vector<double> q;
    q.resize(N_y);

    for(int i = 0; i < N_y; i++)
    {
        if (y[i] < minInput[i])
        {
            y[i] = minInput[i];
        }
        if (y[i] > maxInput[i])
        {
            y[i] = maxInput[i];
        }
        q[i] = resInput[i]*(y[i]-minInput[i])/(maxInput[i]-minInput[i]);
        q[i] = floor(q[i]);
        if(q[i] >= resInput[i])
        {
            q[i] = resInput[i] - 1;
        }
    }

    vector<int> p;
    p.resize(N_y);
    for(int i = 0; i < N_a; i++)
    {
        for(int j = 0; j < N_y; j++)
        {
            p[j] = (int)floor((q[j]+ d[i][j])/N_a);
        }
        mu[i] = cmacHash(p);
    }
}


//compute a virtual address for weight table indices p
int CMAC::cmacHash(vector<int> &p)
{
    int h = 0;
    for(int i = 0; i < N_y; i++)
    {
        h = h*r[i]+p[i];
    }
    return h;
}

//train the CMAC output to reach a given target
//this function only train once, using all samples
//return current MSE
double CMAC::cmacTargetTrain()
{
    //for each sample, update weights
    double increment;
    double sumSE = 0;//sum of squared error
    double error;
    for(int sampleIdx = 0; sampleIdx < sampleNum; sampleIdx++)
    {
        cmacMap(inputData[sampleIdx],x[sampleIdx]);
        cmacQuantizeAndAssociate(inputData[sampleIdx],mu);
        for(int i = 0; i < N_x; i++)
        {
            error = desiredOutput[sampleIdx][i] - x[sampleIdx][i];
            //cout<<"desiredOutput = "<<desiredOutput[sampleIdx][i]<<endl;
            //cout<<"x = "<<x[sampleIdx][i]<<endl<<endl;

            sumSE += 0.5*error*error;
            increment = alpha * error / N_a;
            for(int j = 0; j < N_a; j++)
            {
                W[i][mu[j]] += increment;
            }
        }
    }

    //return MSE of last epoch

    //cout<<"-----------------------------------------"<<endl;
    return sumSE/N_x/sampleNum;
}

vector<double> CMAC::getOutput(vector<double> &input)
{
    vector<double> output;
    if((int)input.size() != N_y)
    {
        return output;
    }
    output.resize(N_x);
    cmacMap(input,output);
    return output;
}
void CMAC::initProgramPath()
{
    char cCurrentPath[FILENAME_MAX];
    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        cout<<"ERROR: Can't find current path"<<endl;
    }

    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
    programPath = cCurrentPath;
}
void CMAC::saveNeuroNetwork(string path)
{
    std::ofstream infile;
    infile.open(path.c_str());
    for(int i = 0; i < N_x; i++)
    {
        infile<<"W["<<i+1<<"]:"<<endl;
        for(int j = 0; j< N_w; j++)
        {
            if(W[i][j] != 0)
            {
                infile<<"W["<<i<<"]["<<j<<"]: ";
                infile<<W[i][j]<<endl;
            }
        }
        infile<<endl;


    }
}

void CMAC::Test(int num_in1, int num_in2, string path)
{
    std::ofstream infile;
    infile.open(path.c_str());

    vector<double> in1(num_in1);
    for(int i = 0; i < (num_in1-1); i++)
    {
        in1[i] = (0.5+i)*320.0/double(num_in1-1);
    }
    vector<double> in2(num_in2);
    for(int i = 0; i < (num_in2-1); i++)
    {
        in2[i] = (0.5+i)*240.0/double(num_in2-1);
    }
    in1[num_in1-1] = 320;in2[num_in2-1] = 240;
    vector<double> input(2);
    vector<double> output(2);
    for(int i = 0; i<num_in1; i++)
    {
        for(int j = 0; j < num_in2; j++)
        {
            input[0] = in1[i];
            input[1] = in2[j];
            cmacMap(input, output);
            infile<< std::fixed<<std::setprecision(5)<<input[0]<<","<<input[1]<<","<<output[0]<<","<<output[1]<<","<<endl;
        }
    }

//    bool mark;
//    for(int i = 0; i < sampleNum; i++)
//    {
//        cmacMap(inputData[i],output);
//        mark = false;
//        for(int j=0;j<N_y;j++)
//        {
//            if (abs(output[j]-desiredOutput[i][j])>= 0.1)
//            {
//                mark = true;
//            }
//        }
//        if (mark) {
//            infile<<"##########this line is wrong#################";
//        }
//        for(int j=0;j<N_y;j++)
//        {
//            infile<<inputData[i][j]<<",";
//        }
//        for(int j=0;j<N_y;j++)
//        {
//            infile<<output[j]<<",";
//        }
//        infile<<endl;
//    }
    infile.close();
}



void CMAC::loadTrainingData(string path)
{
    cout<<"loading training data, please wait"<<endl;
    ifstream infile;
    infile.open(path.c_str());
    string sLine;
    string numString;
    if(!infile.eof())
    {
        //read the first line and do nothing.
        getline(infile, sLine);
        //read the seconde line and update dataNum (number of samples)
        getline(infile, sLine);
        numString = sLine.substr(12);
        sampleNum = atoi(numString.c_str());

        //read other two lines and update N_y/ N_x
        getline(infile, sLine);
        numString = sLine.substr(18);
        N_y = atoi(numString.c_str());

        getline(infile, sLine);
        numString = sLine.substr(18);
        N_x = atoi(numString.c_str());

        cout<<"sample Num = "<<sampleNum<<endl;
        cout<<"N_y = "<<N_y<<endl;
        cout<<"N_x = "<<N_x<<endl;
    }

    if(sampleNum > 0)
    {
        //remember to resize vectors
        inputData.resize(sampleNum);
        desiredOutput.resize(sampleNum);
        x.resize(sampleNum);
        for(int idx =0; idx < sampleNum; idx++)
        {
            inputData[idx].resize(N_y);
        }
        for(int idx =0; idx < sampleNum; idx++)
        {
            desiredOutput[idx].resize(N_x);
        }
        for(int idx = 0; idx < sampleNum; idx++)
        {
            x[idx].resize(N_x);
        }

        //read from file
        for(int idx = 0; idx < sampleNum; idx++)
        {
            for(int inputIdx = 0; inputIdx < N_y; inputIdx++)
            {
                std::getline(infile, numString, ',');
                inputData[idx][inputIdx] = atof(numString.c_str());
            }
            for(int outputIdx = 0; outputIdx < N_x; outputIdx++)
            {
                std::getline(infile, numString, ',');
                desiredOutput[idx][outputIdx] = atof(numString.c_str());
            }
            std::getline(infile, numString,'\n');
        }
    }
    infile.close();
}

void CMAC::dispTrainingData()
{
    for(int idx = 0; idx < sampleNum; idx++)
    {
        for(int i = 0; i < N_y; i++)
        {
            cout<< inputData[idx][i]<< ",";
        }
        for(int i = 0; i < N_x; i++)
        {
            cout<< desiredOutput[idx][i]<< ",";
        }
        cout<<endl;
    }
}
