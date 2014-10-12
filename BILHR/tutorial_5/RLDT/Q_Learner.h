#ifndef Q_LEARNER_H
#define Q_LEARNER_H

#include <vector>
#include <cstdlib>
#include <stdio.h>

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
    ProbDist();
    void update(const State &state,const Action &action,const State &nextState);
    double getProb(const State &state,const Action &action,const State &nextState);

    int numOfVisits[75][25];
    int sumOfVisits[75];
};


class QLearner
{
public:
    QLearner(double gamma);
    ProbDist probDist;
    bool save_data(const char* filename);
    bool load_data(const char* filename);
    Action getAction(const State& state);
private:
    std::vector<QTable> QList;
    std::vector<QTable> policy;

    double _gamma;

    double someValue;

    double getQValue(const State& state, const Action& action);
    double getValue(const State& state);

    Action getBestAction(const State& state);
    void update(const State& state, const Action& action, const State& nextstate, int reward);

};



#endif // Q_LEARNER_H
