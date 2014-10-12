#include <Q_Learner.h>
#include <fstream>

State::State(int inp_x1, int inp_x2)
    :x1(inp_x1),
      x2(inp_x2)
{}

bool State::isEqual(const State &compare) const
{
    if((compare.x1 == this->x1) && (compare.x2 == this->x2))
        return true;
    else
        return false;
}

StateAction::StateAction(State inp_s,
                         Action inp_a)
    :s(inp_s),
      a(inp_a)
{}

QTable::QTable(StateAction inp_sa,
               double inp_qvalue)
    :sa(inp_sa),
      qvalue(inp_qvalue)
{}

QLearner::QLearner(double gamma)
    :_gamma(gamma)
{}

double QLearner::getQValue(const State &state,
                           const Action &action)
{
    std::vector<QTable>::iterator iter;
    for(iter = QList.begin(); iter != QList.end(); ++iter)
    {
        if(state.isEqual(iter->sa.s))
            return iter->qvalue;
    }

    QTable Q_new(StateAction(state,action), 0.0);

//    Q_new.sa.s = state;
//    Q_new.sa.a = action;
//    Q_new.qvalue = 0.0;

    QList.push_back(Q_new);
    return 0.0;
}

double QLearner::getValue(const State &state)
{
    std::vector<QTable>::iterator iter;

    double max = 0.0;

    for(iter = QList.begin(); iter != QList.end(); ++iter)
    {
        if(state.isEqual(iter->sa.s))
        {
            if(iter->qvalue > max)
                max = iter->qvalue;
        }
    }

    return max;
}

Action QLearner::getAction(const State &state)
{
    Action nextAction;

    if(getValue(state) < someValue)
        nextAction = static_cast<Action>(rand() % 3);
    else
        nextAction = getBestAction(state);

    return nextAction;
}

Action QLearner::getBestAction(const State &state)
{
    std::vector<QTable>::iterator iter;

    double max = 0.0;
    Action bestAction = MOVE_IN;

    for(iter = QList.begin(); iter != QList.end(); ++iter)
    {
        if(state.isEqual(iter->sa.s))
        {
            if(iter->qvalue > max)
            {
                bestAction = iter->sa.a;
                max = iter->qvalue;
            }
        }
    }

    return bestAction;
}

ProbDist::ProbDist()
{
    for(int i = 0; i < 75; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            numOfVisits[i][j] = 0;
        }
        sumOfVisits[i] = 0;
    }
}

void ProbDist::update(const State &state,const Action &action,const State &nextState)
{
    int idxRow = 15*state.x1 + 3*state.x2 + action;
    int idxCol = 5*nextState.x1 + nextState.x2;
    numOfVisits[idxRow][idxCol]++;
    sumOfVisits[idxRow]++;

}

double ProbDist::getProb(const State &state,const Action &action,const State &nextState)
{
    int idxRow = 15*state.x1 + 3*state.x2 + action;
    int idxCol = 5*nextState.x1 + nextState.x2;
    return (double)numOfVisits[idxRow][idxCol]/(double)sumOfVisits[idxRow];
}


void QLearner::update(const State &state,
                      const Action &action,
                      const State &nextstate,
                      int reward)
{
    probDist.update(state,action,nextstate);
    State possibleNextState(0,0);

    double sumProb = 0;
    for (int nextX1 = 0; nextX1 < 5; nextX1++)
    {
        for (int nextX2 = 0; nextX2 < 5; nextX2++)
        {
             possibleNextState.x1 = nextX1;
             possibleNextState.x2 = nextX2;
             sumProb += probDist.getProb(state,action,possibleNextState)*getValue(possibleNextState);
        }
    }
    sumProb *= _gamma;
    sumProb += reward;
}

bool QLearner::save_data(const char* filename)
{
    FILE* file = NULL;
    file = fopen(filename, "w");
    if(!file)
    {
        return false;
    }

    fprintf(file,"QList Data. x1,x2,action:qvalue\n");
    //save QList
    fprintf(file,"Element Count: %d\n",QList.size());
    std::vector<QTable>::iterator iter;
    for(iter = QList.begin(); iter != QList.end(); ++iter)
    {
        fprintf(file,"%d,%d,%d:%lf\n",iter->sa.s.x1,iter->sa.s.x2,iter->sa.a, iter->qvalue);
    }
    fprintf(file,"ProbDist Data.\n");
    for(int i = 0; i < 75; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            fprintf(file,"%d,",probDist.numOfVisits[i][j]);
        }
        fprintf(file,"\n");
    }
    return true;
}
bool QLearner::load_data(const char* filename)
{
    FILE* file = NULL;
    file = fopen(filename, "r");
    if(!file)
    {
        return false;
    }
    int QListSize;
    bool tmp = fscanf(file,"QList Data. x1,x2,action:qvalue\nElement Count: %d\n",&QListSize);
    //QList.resize(0);
    int tmpAction;
    double tmpQValue;
    State tmpState(0,0);
    for(int i = 0; i < QListSize; i++)
    {
        tmp = fscanf(file,"%d,%d,%d:%lf\n",&tmpState.x1,&tmpState.x2,&tmpAction,&tmpQValue);

        QList.push_back(QTable(StateAction(tmpState,static_cast<Action>(tmpAction)), tmpQValue));
    }
    return true;
}
