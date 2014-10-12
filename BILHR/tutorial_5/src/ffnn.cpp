#include "ffnn.h"
#include <fstream>

FFNN::FFNN(int initN_i, int initN_h, int initN_o,
           double initMSE_T, double initAlpha, double initBeta)
{
    N_i = initN_i;
    N_h = initN_h;
    N_o = initN_o;
    alpha = initAlpha;
    beta = initBeta;
    MSE_T = initMSE_T;
    dataNum = 0;

    //resize w to dim: N_i*N_h
    v.resize(N_i);
    for(int idx = 0; idx < N_i; idx++)
    {
        v[idx].resize(N_h);
    }
    //resize w to dim: N_h*N_o
    w.resize(N_h);
    for(int idx = 0; idx < N_h; idx++)
    {
        w[idx].resize(N_o);
    }

    upsilon.resize(N_h);//Dim: N_h
    phi.resize(N_o);//Dim: N_o
}

bool FFNN::saveNetwork(std::string path)
{

    std::ofstream infile;
    infile.open(path.c_str());
    infile<<"N_i="<<N_i<<", N_h="<<N_h<<", N_o="<<N_o<<std::endl;
    infile<<"phi\n";
    for(int i = 0; i < N_o; i++)
    {
        infile<<phi[i]<<",";
    }
    infile<<"\n";
    infile<<"upsilon\n";
    for(int i = 0; i < N_h; i++)
    {
        infile<<upsilon[i]<<",";
    }
    infile<<"\n";
    infile<<"v\n";
    for(int i = 0; i < N_i; i++)
    {
        for(int j=0; j<N_h;j++)
        {
            infile<<v[i][j]<<",";
        }
        infile<<"\n";
    }
    infile<<"w\n";
    for(int i = 0; i <N_h; i++)
    {
        for(int j=0; j<N_o;j++)
        {
            infile<<w[i][j]<<",";
        }
        infile<<"\n";
    }

    infile.close();
    cout<<"FFNN parameters saved"<<endl;
    return true;
}

bool FFNN::loadNetwork(std::string path)
{
    cout<<"loading network parameters"<<endl;
    std::ifstream infile;
    infile.open(path.c_str());
    std::string sLine;
    if(!infile.eof())
    {
        //read the first line and do nothing.
        std::getline(infile, sLine, '=');
        std::getline(infile, sLine, ',');
        N_i = atoi(sLine.c_str());
        std::getline(infile, sLine, '=');
        std::getline(infile, sLine, ',');
        N_h = atoi(sLine.c_str());
        std::getline(infile, sLine, '=');
        std::getline(infile, sLine, '\n');
        N_o = atoi(sLine.c_str());

        if(N_i >0 && N_h>0 && N_o >0)
        {
            phi.resize(N_o);
            upsilon.resize(N_h);
            v.resize(N_i);
            for(int i = 0; i< N_i; i++)
            {
                v[i].resize(N_h);
            }
            for(int i = 0; i< N_h; i++)
            {
                w[i].resize(N_o);
            }
            std::getline(infile, sLine);//"phi"
            //std::cout<<"phi: ";
            for(int i=0; i<N_o; i++)
            {
                std::getline(infile, sLine, ',');
                phi[i] = atof(sLine.c_str());
                //std::cout<<phi[i]<<",";
            }
            //std::cout<<"\n";
            std::getline(infile, sLine);//'\n'
            std::getline(infile, sLine);//"upsilon"
            //std::cout<<"upsilon: ";
            for(int i=0; i<N_h; i++)
            {
                std::getline(infile, sLine, ',');
                upsilon[i] = atof(sLine.c_str());
            }
            std::getline(infile, sLine);//'\n'
            std::getline(infile, sLine);//"v"
            //std::cout<<"v: ";
            for(int i=0;i<N_i; i++)
            {
                for(int j = 0; j < N_h; j++)
                {
                    std::getline(infile, sLine, ',');
                    v[i][j] = atof(sLine.c_str());
                    //std::cout<<v[i][j]<<",";
                }
                //std::cout<<"\n";
            }
            //std::cout<<"\n";
            std::getline(infile, sLine);//'\n'
            std::getline(infile, sLine);//"w"
           // std::cout<<"w: ";
            for(int i=0;i<N_h; i++)
            {
                for(int j = 0; j < N_o; j++)
                {
                    std::getline(infile, sLine, ',');
                    w[i][j] = atof(sLine.c_str());
                    //std::cout<<w[i][j]<<",";
                }
               // std::cout<<"\n";
            }
        }
    }
    infile.close();
    cout<<"network parameters loaded"<<endl;
    return true;
}

void FFNN::setTrainingData(std::vector< std::vector<double> > &inputData_in, std::vector< std::vector<double> > &desiredOutput_in)
{
    inputData = inputData_in;
    desiredOutput = desiredOutput_in;
    dataNum = inputData_in[0].size();
}

bool FFNN::loadTrainingData(std::string path)
{
    cout<<"loading training data, please wait"<<endl;
    std::ifstream infile;
    infile.open(path.c_str());
    std::string sLine;
    if(!infile.eof())
    {
        //read the first line and do nothing.
        std::getline(infile, sLine);
        //read the seconde line and update dataNum (number of samples)
        std::getline(infile, sLine);
        //TODO read another line and update N_i/ N_o
        N_i=2;
        N_o=2;//TODO read from file

    }
    std::string sampleNumStr = sLine.substr(18);
    int sampleNum = atoi(sampleNumStr.c_str());
    if(sampleNum > 0)
    {
        dataNum = sampleNum;
        //remember to resize vectors
        inputData.resize(N_i);
        desiredOutput.resize(N_o);
        for(int idx =0; idx < N_i; idx++)
        {
            inputData[idx].resize(dataNum);
        }
        for(int idx =0; idx < N_o; idx++)
        {
            desiredOutput[idx].resize(dataNum);
        }

        //read from file
        std::string numStr;
        for(int idx = 0; idx < dataNum; idx++)
        {
            for(int outputIdx = 0; outputIdx < N_i; outputIdx++)
            {
                std::getline(infile, numStr, ',');
                desiredOutput[outputIdx][idx] = atof(numStr.c_str());
            }
            for(int inputIdx = 0; inputIdx < N_o; inputIdx++)
            {
                std::getline(infile, numStr, ',');

                inputData[inputIdx][idx] = atof(numStr.c_str());
            }
            std::getline(infile, numStr,'\n');
        }
    }
    infile.close();
    return true;
}

std::vector<double> FFNN::getOutput(std::vector<double> &input)
{
    std::vector<double> hiddenNeuronInput(N_h);
    std::vector<double> hiddenNeuronOuput(N_h);
    std::vector<double> outputNeuronInput(N_o);
    std::vector<double> outputNeuronOuput(N_o);

    for(int hiddenNeuronIdx = 0; hiddenNeuronIdx < N_h; hiddenNeuronIdx++)
    {
        hiddenNeuronInput[hiddenNeuronIdx] = upsilon[hiddenNeuronIdx];
        for(int inputNeuronIdx = 0; inputNeuronIdx < N_i; inputNeuronIdx++)
        {
            hiddenNeuronInput[hiddenNeuronIdx] +=  input[inputNeuronIdx] * v[inputNeuronIdx][hiddenNeuronIdx];
        }
        hiddenNeuronOuput[hiddenNeuronIdx] = sigmoidFunc(hiddenNeuronInput[hiddenNeuronIdx]);
    }

    for(int outputNeuronIdx = 0; outputNeuronIdx < N_o; outputNeuronIdx++)
    {
        outputNeuronInput[outputNeuronIdx] = phi[outputNeuronIdx];
        for(int hiddenNeuronIdx = 0; hiddenNeuronIdx < N_h; hiddenNeuronIdx++)
        {
            outputNeuronInput[outputNeuronIdx] +=  hiddenNeuronOuput[hiddenNeuronIdx] * w[hiddenNeuronIdx][outputNeuronIdx];
        }
        outputNeuronOuput[outputNeuronIdx] = sigmoidFunc(outputNeuronInput[outputNeuronIdx]);
    }
    return outputNeuronOuput;
}

void FFNN::trainNetwork(bool plotMSE)
{
    cout<<"training FFNN"<<endl;
    //initialize all parameters
    for(int i = 0; i < N_i; i++)
    {
        for(int j = 0; j < N_h; j++)
        {
            v[i][j] = (((double) rand() / (RAND_MAX)) - 0.5) * 2;
        }
    }

    for(int i = 0; i < N_h; i++)
    {
        for(int j = 0; j < N_o; j++)
        {
            w[i][j] = (((double) rand() / (RAND_MAX)) - 0.5) * 2;
        }
    }

    for(int i = 0; i < N_h; i++)
    {
        upsilon[i] = (((double) rand() / (RAND_MAX)) - 0.5) * 2;
    }

    for(int i = 0; i < N_o; i++)
    {
        phi[i] = (((double) rand() / (RAND_MAX)) - 0.5) * 2;
    }


    //start training
    double MSE_current = trainOneEpoch();
    int count = 0;
    while (MSE_current > MSE_T)
    {

        if(plotMSE)
        {
            //TODO Visualization
            std::cout<<"train epoch "<<count++<<": current MSE = " << MSE_current << '\n';
        }
        MSE_current = trainOneEpoch();


//        for(int idx = 0; idx < dataNum; idx++)
//        {
//            std::cout<<"sampleIdx: "<<idx<<"\n";
//            std::cout<<"input: ";
//            for(int i = 0; i<N_i; i++)
//            {
//                std::cout<<inputData[i][idx]<<",";
//            }
//            std::cout<<"\n";
//            std::cout<<"output: ";
//            for(int i = 0; i<N_o; i++)
//            {
//                std::cout<<desiredOutput[i][idx]<<",";
//            }
//            std::cout<<"\n\n";
//        }


//        //TO DELETE
//        if(count >= 300)
//        {
//            break;
//        }

        //END TO DELETE
    }
    cout<<"FFNN training done"<<endl;
}

//return MSE after training one epoch
double FFNN::trainOneEpoch()
{
    double squaredErrorSum = 0;
    std::vector<double> hiddenNeuronOutputs(N_h);//Dim: N_h
    std::vector<double> outputNeuronOutputs(N_o);//Dim: N_o
    std::vector<double> dArray(N_o);//Dim: N_o
    std::vector<double> eArray(N_h);//Dim: N_h

    std::vector< std::vector<double> > deltaWSum(N_h);//Dim: N_h*N_o
    std::vector< std::vector<double> > deltaVSum(N_i);//Dim: N_i*N_h
    for (int i = 0; i< N_h; i++)
    {
        deltaWSum[i].resize(N_o);
        for(int j = 0; j< N_o; j++)
        {
            deltaWSum[i][j] = 0;
        }
    }
    for (int i = 0; i< N_i; i++)
    {
        deltaVSum[i].resize(N_h);
        for(int j = 0; j< N_h; j++)
        {
            deltaVSum[i][j] = 0;
        }
    }
    std::vector<double> deltaPhiSum(N_o);//Dim: N_o
    std::vector<double> deltaUpsilonSum(N_h);//Dim: N_h
    for (int i = 0; i< N_o; i++)
    {
        deltaPhiSum[i] = 0;
    }
    for (int i = 0; i< N_h; i++)
    {
        deltaUpsilonSum[i] = 0;
    }

    double hiddenNeuronInput, outputNeuronInput;
    //for each pair sample (inputData, desiredOutput), calculate delta for each parameters
    for(int dataIdx = 0; dataIdx < dataNum; dataIdx++)
    {
        //step a: output of hidden neurons
        for(int hiddenNeuronIdx = 0; hiddenNeuronIdx < N_h; hiddenNeuronIdx++)
        {
            hiddenNeuronInput = upsilon[hiddenNeuronIdx];// add offset
            for(int inputIdx = 0; inputIdx < N_i; inputIdx++)
            {
                hiddenNeuronInput += inputData[inputIdx][dataIdx] * v[inputIdx][hiddenNeuronIdx];
            }
            hiddenNeuronOutputs[hiddenNeuronIdx] = sigmoidFunc(hiddenNeuronInput);
            //std::cout<<"hidden neuron ["<<hiddenNeuronIdx<<"]: "<< hiddenNeuronOutputs[hiddenNeuronIdx]<<"\n";
        }

        //std::cout<<"sample index: "<<dataIdx<<"\n";
        //step b: output of output neurons
        for(int outputNeuronIdx = 0; outputNeuronIdx < N_o; outputNeuronIdx++)
        {
            outputNeuronInput = phi[outputNeuronIdx];
            for(int hiddenNeuronIdx = 0; hiddenNeuronIdx < N_h; hiddenNeuronIdx++)
            {
                outputNeuronInput += hiddenNeuronOutputs[hiddenNeuronIdx] * w[hiddenNeuronIdx][outputNeuronIdx];
            }
            outputNeuronOutputs[outputNeuronIdx] = sigmoidFunc(outputNeuronInput);
            //std::cout<<"outputNeuron"<< outputNeuronOutputs[outputNeuronIdx]<<"\n";
        }


        //step c: calculate term dArray
        for(int outputNeuronIdx = 0; outputNeuronIdx < N_o; outputNeuronIdx++)
        {
            double tmp = outputNeuronOutputs[outputNeuronIdx];
            dArray[outputNeuronIdx] = tmp * (1 - tmp) * (desiredOutput[outputNeuronIdx][dataIdx] - tmp);
        }

        //step d: calculate term eArray
        for(int hiddenNeuronIdx = 0; hiddenNeuronIdx < N_h; hiddenNeuronIdx++)
        {
            double sum_wd = 0;
            for(int j = 0; j < N_o; j++)
            {
                sum_wd += w[hiddenNeuronIdx][j] * dArray[j];
            }
            double tmp = hiddenNeuronOutputs[hiddenNeuronIdx];
            eArray[hiddenNeuronIdx] = tmp * (1- tmp) * sum_wd;
        }

        //step e: update sum of delta w
        for(int i = 0; i < N_h; i++)
        {
            for(int j = 0; j < N_o; j++)
            {
                deltaWSum[i][j] += alpha * hiddenNeuronOutputs[i] * dArray[j];
            }
        }

        //step f: update sum of delta phi
        for (int i = 0; i< N_o; i++)
        {
            deltaPhiSum[i] += alpha * dArray[i];
        }

        //step h: update sum of delta v
        for(int k = 0; k < N_i; k++)
        {
            for(int i = 0; i < N_h; i++)
            {
                deltaVSum[k][i] += beta * inputData[k][dataIdx] * eArray[i];
            }
        }

        //step g: update sum of delta upsilon
        for (int i = 0; i< N_h; i++)
        {
            deltaUpsilonSum[i] += beta * eArray[i];
        }

        //calculate mean squared error
        //this is actually the sum of squaredError of last epoch, not this epoch, but it doesn't matter.

        for(int neuronIdx = 0; neuronIdx < N_o; neuronIdx++)
        {
            squaredErrorSum += 0.5 * pow(desiredOutput[neuronIdx][dataIdx] - outputNeuronOutputs[neuronIdx],2);
        }

    }

    //update each parameter
    for(int i = 0; i < N_h; i++)
    {
        for(int j = 0; j < N_o; j++)
        {
            //std::cout<<"w["<<i<<"]["<<j<<"] ="<<w[i][j]<<'\n';
            w[i][j] += deltaWSum[i][j] / (double)dataNum;
        }
    }

    for(int i = 0; i < N_i; i++)
    {
        for(int j = 0; j < N_h; j++)
        {
            //std::cout<<"v["<<i<<"]["<<j<<"] ="<<v[i][j]<<'\n';
            v[i][j] += deltaVSum[i][j] / (double)dataNum;
        }
    }

    for(int i = 0; i < N_o; i++)
    {
        phi[i] += deltaPhiSum[i] / (double)dataNum;
    }

    for(int i = 0; i < N_h; i++)
    {
        upsilon[i] += deltaUpsilonSum[i] / (double)dataNum;
    }

    //return MSE of last epoch
    return squaredErrorSum/double(N_o)/double(dataNum);
}
