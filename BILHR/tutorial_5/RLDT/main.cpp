#include <iostream>
#include "Q_Learner.h"
#include "simulator.h"
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    QLearner qlearner(0.1);

    int initialX1 = 2;
    int initialX2 = 2;
    Simulator simulator(initialX1,initialX2);
    bool targetReached = false;
    State currentState(initialX1,initialX2);
    Action action;
    int reward;
    int nextX1, nextX2;
    int count = 0;
    while(!targetReached)
    {
        count++;
        if(count > 20)
        {
            break;
        }
        action = qlearner.getAction(currentState);
        simulator.move(action,reward,nextX1, nextX2, targetReached);
        currentState.x1 = nextX1;
        currentState.x2 = nextX2;
    }
    return 0;
}

