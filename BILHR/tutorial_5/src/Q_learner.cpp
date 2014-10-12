/*
     Written by: Wolfgang, Bing, Diego, Usama
 */

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

bool StateAction::isEqual(const StateAction &compare) const
{
    if((compare.s.isEqual(this->s)) && (compare.a == this->a))
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
    :_gamma(gamma),
      someValue(0.4*20),
      RMax(0.1),
      _maxSteps(5),
      probDistTransitions(75,25),
      probDistReward(75,4)
{
}

double QLearner::getQValue(const State &state,
                           const Action &action)
{
    std::vector<QTable>::iterator iter;
    StateAction sa(state,action);

    for(iter = QList.begin(); iter != QList.end(); ++iter)
    {
        if(sa.isEqual(iter->sa))
            return iter->qvalue;
    }

    QTable Q_new(StateAction(state,action), 0.1);

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
    cout << getValue(state) << endl;
    Action nextAction;
    if(getValue(state) < someValue) // Exploration Mode
    {
        nextAction = static_cast<Action>(rand() % 3);
    }
    else
    {  // Exploitation Mode
        nextAction = getBestAction(state);
    }

    return nextAction;
}

void QLearner::checkPolicy(const State &state)
{
    if(getValue(state) < someValue) // Exploration Mode - 0
        exp = false;
    else{  // Explotation Mode - 1
        exp = true;
    }
}

void QLearner::computeValues()
{
    State s(0,0);
    State next_s(0,0);

    double new_Q_value = 0;
    double max_change = 0;

    bool converged = false;

    while(!converged)
    {
        max_change = 0;

        for(int sx1 = 0; sx1 < 5; sx1++)
        {
            for(int sx2 = 0; sx2 < 5; sx2++)
            {
                s.x1 = sx1;
                s.x2 = sx2;



                for(int act = 0; act < 3; act++)
                {
                    int indRow = sx1*15+sx2*3+act;
                    Action a = static_cast<Action>(act);
                    new_Q_value = 0;

                    for(int nextsx1 = 0; nextsx1 < 5; nextsx1++)
                    {
                        for(int nextsx2 = 0; nextsx2 < 5; nextsx2++)
                        {
                            next_s.x1 = nextsx1;
                            next_s.x2 = nextsx2;

                            int indCol = nextsx1*5+nextsx2;

                            if(probDistTransitions.numOfVisits[indRow][indCol] != 0)
                            {
                                new_Q_value += probDistTransitions.getProb(s,a,next_s)*getValue(next_s);
                            }
                        }
                    }

                    new_Q_value *= _gamma;
                    new_Q_value += probDistReward.getReward(s,a);

                    if(std::fabs(getQValue(s,a) - new_Q_value) > max_change)
                    {
                        max_change = std::fabs(getQValue(s,a) - new_Q_value);
                    }

                    setQValue(s,a,new_Q_value);
                }

            }
        }
        if(max_change < 0.01)
        {
            converged = true;
        }
    }
}

void QLearner::setQValue(const State& state, const Action& action, double QValue)
{
    std::vector<QTable>::iterator iter;
    StateAction sa(state,action);

    for(iter = QList.begin(); iter != QList.end(); ++iter)
    {
        if(sa.isEqual(iter->sa)){
            iter->qvalue = QValue;
            return;
        }
    }

    QTable Q_new(StateAction(state,action), QValue);
    QList.push_back(Q_new);
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

ProbDist::ProbDist(int row_elem, int col_elem)
{
    for(int i = 0; i < row_elem; i++)
    {
        for(int j = 0; j < col_elem; j++)
        {
            numOfVisits[i][j] = 0;
        }
        sumOfVisits[i] = 0;
    }
}

void ProbDist::updateTransition(const State &state,const Action &action,const State &nextState)
{
    int idxRow = 15*state.x1 + 3*state.x2 + action;
    int idxCol = 5*nextState.x1 + nextState.x2;
    numOfVisits[idxRow][idxCol]++;
    sumOfVisits[idxRow]++;

}

void ProbDist::updateReward(const State &state,const Action &action,const int &reward)
{
    int idxRow = 15*state.x1 + 3*state.x2 + action;
    int idxCol = 0;

    switch(reward){
    case -20:
        idxCol = 0;
        break;
    case -5:
        idxCol = 1;
        break;
    case -1:
        idxCol = 2;
        break;
    case 20:
        idxCol = 3;
        break;
    default:
        printf("Please check the rewards");
        break;
    }

    numOfVisits[idxRow][idxCol]++;
    sumOfVisits[idxRow]++;
}

double ProbDist::getProb(const State &state,const Action &action,const State &nextState)
{
    int idxRow = 15*state.x1 + 3*state.x2 + action;
    int idxCol = 5*nextState.x1 + nextState.x2;
    return (double)numOfVisits[idxRow][idxCol]/(double)sumOfVisits[idxRow];
}

double ProbDist::getReward(const State &state,const Action &action)
{
    double average = 0;
    int idxRow = 15*state.x1 + 3*state.x2 + action;
    for(int idxCol=0; idxCol<4; idxCol++)
    {
        average += numOfVisits[idxRow][idxCol]*array_rewards[idxCol];
    }

    if(sumOfVisits[idxRow] == 0)
        return 0;
    else
        return average/sumOfVisits[idxRow];
}


void QLearner::update(const State &state,
                      const Action &action,
                      const State &nextstate,
                      int reward)
{
    probDistTransitions.updateTransition(state,action,nextstate);
    probDistReward.updateReward(state,action,reward);

    computeValues();
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
            fprintf(file,"%d,",probDistTransitions.numOfVisits[i][j]);
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
