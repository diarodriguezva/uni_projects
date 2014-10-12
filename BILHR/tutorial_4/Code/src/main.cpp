#include "CMAC.h"

#define SAMPLE_COUNT 38
#define NEURONS_INPUT_LAYER 2
#define NEURONS_OUTPUT_LAYER 2
#define RESOLUTION 150
#define RECEPTIVE_FIELD 5
#define TRAINING_TIMEOUT 3600

static const char PATH_TRAINING_DATA[] = "/home/diego/fuerte_workspace/sandbox/Tut4/TrackedPositions.txt";
static const char PATH_TRAINING_DATA_NORMALIZED[] = "/home/diego/fuerte_workspace/sandbox/Tut4/TrackedPositionsNormalized.txt";
static const char PATH_SAVED_NETWORK[] = "net.save";

CMAC_network* net;

int main(int argc, char *argv[])
{
    uint** displace = (uint**)malloc(NEURONS_INPUT_LAYER*sizeof(uint*));
    for (uint i=0; i<NEURONS_INPUT_LAYER; i++)
        displace[i] = (uint*) malloc(RECEPTIVE_FIELD*sizeof(uint));

    // Values taken from Thesis
    displace[0][0]=3;
    displace[0][1]=1;
    displace[0][2]=4;
    displace[0][3]=2;
    displace[0][4]=0;

    displace[1][0]=2;
    displace[1][1]=3;
    displace[1][2]=4;
    displace[1][3]=0;
    displace[1][4]=1;

    net = new CMAC_network(NEURONS_INPUT_LAYER,NEURONS_OUTPUT_LAYER,RECEPTIVE_FIELD,RESOLUTION,displace);
    //cout << "NN sucessfully created" <<endl;
    net->load_training_data(PATH_TRAINING_DATA);
    //cout << "Data sucessfully loaded" <<endl;
    net->normalize_training_set();
    //cout << "Data sucessfully normalized" <<endl;
    net->save_normalized_data(PATH_TRAINING_DATA_NORMALIZED);
    cout << "Data sucessfully saved" <<endl;

    net->train();
    cout << "Net sucessfully trained" <<endl;
}
