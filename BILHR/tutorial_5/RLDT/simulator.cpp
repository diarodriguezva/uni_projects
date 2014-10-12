#include "simulator.h"
#include <iostream>
using namespace std;
Simulator::Simulator(int initialX1, int initialX2):currentX1(initialX1), currentX2(initialX2)
{
    targetX1 = 4;
    targetX2 = 3;
}

void Simulator::move(Action &action,int &reward, int &nextX1, int &nextX2, bool &targetReached)
{
    targetReached = false;
    if(action == MOVE_IN)
    {
        if(currentX1 == 0)
        {
            //REACH WALL
            reward = -10;
            nextX1 = currentX1;
            nextX1 = currentX2;
        }
        else
        {
            reward = -1;
            nextX1 = currentX1 - 1;
            nextX1 = currentX2;
        }
    }
    else if(action == MOVE_OUT)
    {
        if(currentX1 == 4)
        {
            //REACH WALL
            reward = -10;
            nextX1 = currentX1;
            nextX1 = currentX2;
        }
        else
        {
            reward = -1;
            nextX1 = currentX1 + 1;
            nextX1 = currentX2;
        }
    }
    else {
        if(currentX2 == 4)
        {
            //REACH WALL
            reward = -10;
            nextX1 = currentX1;
            nextX1 = currentX2;
        }
        else
        {
            reward = -1;
            nextX1 = currentX1;
            nextX1 = currentX2+1;
        }
    }

    if((currentX1 == targetX1) && (currentX2 == targetX2))
    {
        reward = 20;
        targetReached = true;
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if((currentX1 == i) && (currentX2 == j))
            {
                cout<<"R,";
            }
            else if((targetX1 == i) && (targetX2 == j))
            {
                cout<<"X,";
            }
            else
            {
                cout<<"O,";
            }
        }
        cout<<"\n";
    }
    cout<<"\n";
    cout<<"reward = "<<reward<<"\n";
}
