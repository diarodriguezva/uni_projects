#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "Q_Learner.h"

class Simulator
{
public:
    Simulator(int initialX1, int initialX2);
    void move(Action &action,int &reward, int &nextX1, int &nextX2, bool &targetReached);
private:
    int currentX1;
    int currentX2;
    int targetX1;
    int targetX2;
};

#endif // SIMULATOR_H
