/*
     Written by: Wolfgang
 */


#include <ros/ros.h>

#include <BILHR_ros/LegPosition.h>
#include <BILHR_ros/cmdLegState.h>
#include <BILHR_ros/GoaliePos.h>
#include <Q_Learner.h>



#include <iostream>
#include <fstream>

using namespace std;


ros::Publisher cmd_leg_pub;
ros::Subscriber goal_state_sub;
ros::Subscriber leg_state_sub;


QLearner qlearner(0.9);

State currentState(1,1);
State lastState(1,1);



void goalStateCB(const BILHR_ros::GoaliePos & msg)
{
    currentState.x1 = msg.position - 1;
    cout << "got new goal pos" << currentState.x1 << endl;
}

void legStateCB(const BILHR_ros::LegPosition & msg)
{
    currentState.x2 = msg.LegPos - 1;
    cout << "got new leg pos" << currentState.x2 << endl;
}

void sendAction(Action a)
{
    BILHR_ros::cmdLegState msg;

    if(a == MOVE_IN)
        msg.cmdLegState = 1;

    if(a == MOVE_OUT)
        msg.cmdLegState = 2;

    if(a == KICK)
        msg.cmdLegState = 3;

    cmd_leg_pub.publish(msg);
}

int askForReward()
{
    cout << "Executed action -> what is my reward?" << endl;
    cout << "1) -1" << endl;
    cout << "2) -5" << endl;
    cout << "3) 20" << endl;
    cout << "9) Exit" << endl;

    while(1)
    {
        char c = getchar();
        if(c == '1')
            return -1;
        if(c == '2')
            return -5;
        if(c == '3')
            return 20;
        if(c == '9')
            return 0;
    }
}

bool isRobotReady()
{
    cout << "Press Enter when the robot is ready for the trial" << endl;
    getchar();

}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "central_node");
    ros::NodeHandle nh;

    // initialize random seed
    srand(time(0));

    cmd_leg_pub = nh.advertise<BILHR_ros::cmdLegState>("cmd_Leg_State", 1);

    goal_state_sub = nh.subscribe("goalie_tracker", 1, &goalStateCB);
    leg_state_sub = nh.subscribe("leg_state", 1, &legStateCB);

    Action bestAction;
    int reward;
    int count = 0;
    int MaxCountToStop = 100;

    vector<int> moves;

    FILE* file = NULL;
    file = fopen("/home/groupc/fuerte_workspace/sandbox/BILHR_ros/data/cummulative_reward.txt", "w");
    fprintf(file,"Cumulative Reward\n");
    fclose(file);

    for(int i = 0; i<200; i++)
    {
        isRobotReady();
        count = 0;
        bool targetReached = false;
        while(!targetReached)
        {
            cout << "Count: " << count << endl;
            count++;

            if(count > MaxCountToStop)
            {
                break;
            }

            bestAction = qlearner.getAction(currentState);

            lastState = currentState;

            sendAction(bestAction);

            reward = askForReward();

            if (reward == 0){
                for(int i = 0; i < moves.size(); i++)
                {
                    cout << moves.at(i) << endl;
                }
                return 0;
            }

            file = fopen("/home/groupc/fuerte_workspace/sandbox/BILHR_ros/data/cummulative_reward.txt", "a");
            fprintf(file,"%d\n",reward);
            fclose(file);

            ros::spinOnce();

            qlearner.update(lastState,bestAction,currentState,reward);

            if(reward == 20)
                break;
        }
        moves.push_back(count);
        qlearner.save_data("/home/groupc/fuerte_workspace/sandbox/BILHR_ros/data/qlearner_file.txt");
    }

    ros::spin();
    return 0;
}

