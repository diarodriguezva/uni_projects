#ifndef Q_LEARNER_H
#define Q_LEARNER_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#define INF 65535

static const int array_rewards[4] = {-20, -5, -1, 20};

using namespace std;

enum Action {MOVE_IN = 0, MOVE_OUT = 1, KICK = 2};

class State
{
public:
    State(int inp_x1, int inp_x2);
    int x1;
    int x2;

    bool isEqual(const State& compare) const;
};

class StateAction
{
public:
    StateAction(State inp_s, Action inp_a);

    State s;
    Action a;

    bool isEqual(const StateAction &compare) const;
};

class QTable
{
public:
    QTable(StateAction inp_sa, double inp_qvalue);

    StateAction sa;
    double qvalue;
};

class ProbDist
{
public:
    ProbDist(int row_elem, int col_elem);
    void updateTransition(const State &state,const Action &action,const State &nextState);
    void updateReward(const State &state,const Action &action,const int &reward);

    double getProb(const State &state,const Action &action,const State &nextState);
    double getReward(const State &state,const Action &action);

    // This could be optimized !!!
    int numOfVisits[75][25];
    int sumOfVisits[75];
};


class QLearner
{
public:
    QLearner(double gamma);
    ProbDist probDistTransitions;
    ProbDist probDistReward;

    bool save_data(const char* filename);
    bool load_data(const char* filename);
    Action getAction(const State& state);

    void update(const State& state, const Action& action, const State& nextstate, int reward);
    Action getBestAction(const State& state);

    void checkPolicy(const State& state);
    void computeValues();

private:
    std::vector<QTable> QList;
    std::vector<QTable> policy;

    double _gamma;
    double someValue;
    bool exp;
    double RMax;
    int _maxSteps;

    double K[25];

    double getQValue(const State& state, const Action& action);
    double getValue(const State& state);
    void setQValue(const State& state, const Action& action, double QValue);
};



#endif // Q_LEARNER_H
