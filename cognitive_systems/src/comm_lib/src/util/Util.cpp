#include <comm_lib/util/Util.h>

namespace util
{

Util::Util()
{

}
Util::~Util()
{

}

int Util::getNumberOfActors(const actor_msgs::ActorVec& actors)
{
    return actors.ActorVec.size();
}

bool Util::getActorPose(const actor_msgs::ActorVec& actors,
                        const std::string& targetType,
                        const std::string& targetProperty,
                        const int& targetId,
                        PoseVec& poseData)
{
    bool found = false;
    for(int t=0; t<actors.ActorVec.size(); ++t)
    {
        if(		actors.ActorVec[t].targetType.compare(targetType) == 0 &&
                        actors.ActorVec[t].targetProperty.compare(targetProperty) == 0 &&
                        actors.ActorVec[t].targetId == targetId)
        {
            found=true;

            poseData.erase(poseData.begin(),poseData.end());
            poseData.clear();
            poseData.resize(1);
            //            for(int p=0; p<poseData.size(); ++p)
            //            {
            poseData[0].resize(7);
            poseData[0](0)=actors.ActorVec[t].targetPoseVec[0].position.x;
            poseData[0](1)=actors.ActorVec[t].targetPoseVec[0].position.y;
            poseData[0](2)=actors.ActorVec[t].targetPoseVec[0].position.z;
            poseData[0](3)=actors.ActorVec[t].targetPoseVec[0].orientation.x;
            poseData[0](4)=actors.ActorVec[t].targetPoseVec[0].orientation.y;
            poseData[0](5)=actors.ActorVec[t].targetPoseVec[0].orientation.z;
            poseData[0](6)=actors.ActorVec[t].targetPoseVec[0].orientation.w;
            //            }

            return found;
        }

    }

    return found;
}


bool Util::getActorPose(const actor_msgs::ActorVec& actors,
                               const std::string& targetType,
                               PoseVec& poseData)
{
    bool found = false;
    for(int t=0; t<actors.ActorVec.size(); ++t)
    {
        if(actors.ActorVec[t].targetType.compare(targetType) == 0 )
        {
            found=true;

            poseData.resize(1);
            poseData[0].resize(6);
            poseData[0](0)=actors.ActorVec[t].targetPoseVec[0].position.x;
            poseData[0](1)=actors.ActorVec[t].targetPoseVec[0].position.y;
            poseData[0](2)=actors.ActorVec[t].targetPoseVec[0].position.z;
            poseData[0](3)=actors.ActorVec[t].targetPoseVec[0].orientation.x;
            poseData[0](4)=actors.ActorVec[t].targetPoseVec[0].orientation.y;
            poseData[0](5)=actors.ActorVec[t].targetPoseVec[0].orientation.z;
            return found;
        }
    }

    return found;
}

bool Util::getActorsOfType(const actor_msgs::ActorVec& actors,
                           const std::string& targetType,
                           actor_msgs::ActorVec& output)
{
    bool found = false;
    Util::clearActorsDataContainer(output);
    for(int t=0; t<actors.ActorVec.size(); ++t)
    {
        if( actors.ActorVec[t].targetType.compare(targetType) == 0)
        {
            found=true;
            output.ActorVec.push_back(actors.ActorVec[t]);
        }
    }

    return found;
}

bool Util::getActorsOfType(const actor_msgs::ActorVec& actors,
                           const std::string& targetType,
                           const std::string& targetProperty,
                           actor_msgs::ActorVec& output)
{
    bool found = false;
    Util::clearActorsDataContainer(output);
    for(int t=0; t<actors.ActorVec.size(); ++t)
    {
        if( actors.ActorVec[t].targetType.compare(targetType) == 0 &&
                actors.ActorVec[t].targetProperty.compare(targetProperty) == 0)
        {
            found=true;
            output.ActorVec.push_back(actors.ActorVec[t]);
        }
    }

    return found;
}

bool Util::getActorsOfType(const actor_msgs::ActorVec& actors,
                           const std::string& targetType,
                           const std::string& targetProperty,
                           const int& targetId,
                           actor_msgs::ActorVec& output)
{
    bool found = false;
    Util::clearActorsDataContainer(output);
    for(int t=0; t<actors.ActorVec.size(); ++t)
    {
        if( actors.ActorVec[t].targetType.compare(targetType) == 0 &&
                actors.ActorVec[t].targetProperty.compare(targetProperty) == 0 &&
                actors.ActorVec[t].targetId == targetId)
        {
            found=true;
            output.ActorVec.push_back(actors.ActorVec[t]);
        }
    }

    return found;
}

bool Util::isPresent(const actor_msgs::ActorVec& actors,
                     const std::string& targetType,
                     const std::string& targetProperty,
                     const int& targetId)
{
    bool found = false;
    for(int t=0; t<actors.ActorVec.size(); ++t)
    {
        if( actors.ActorVec[t].targetType.compare(targetType) == 0 &&
                actors.ActorVec[t].targetProperty.compare(targetProperty) == 0 &&
                actors.ActorVec[t].targetId == targetId)
        {
            found=true;
            break;
        }
    }

    return found;
}

bool Util::isPresent(const actor_msgs::ActorVec& actors,
                     const std::string& semanticName)
{
    bool found = false;
    for(int t=0; t<actors.ActorVec.size(); ++t)
    {
        if( actors.ActorVec[t].semanticName.compare(semanticName) == 0)
        {
            found=true;
            break;
        }
    }

    return found;
}


////get unique actor by passing a concatinated string of type and id eg "MetaChassis" + "18901" = "MetalChassis18901"
//bool Util::getActor(const actor_msgs::ActorVec& actors,
//                    const std::string& targetType_Id,
//                    actor_msgs::Actor& output)
//{
//    QString concat_name(targetType_Id.c_str());
//    QString concat_name1(targetType_Id.c_str());

//    //fixed length of actor ids
//    int id_length = 5;
//    QString actor_name = concat_name.remove(concat_name.length()-id_length, concat_name.length());
//    int actor_id = concat_name1.remove(0, concat_name1.length()-id_length).toInt();

//    std::cout << "Actor name and Id " << actor_name.toStdString() << " " << actor_id << std::endl;

//    bool found = false;

//    for(int t=0; t<actors.ActorVec.size(); ++t)
//    {
//        if( actors.ActorVec[t].targetType.compare(actor_name.toStdString().c_str()) == 0 &&
//                actors.ActorVec[t].targetId == actor_id)
//        {
//            copyActorData(actors.ActorVec[t], output);
//            found=true;
//        }
//    }

//    return found;
//}


bool Util::getActor(const actor_msgs::ActorVec& actors,
                    const std::string& semanticName,
                    actor_msgs::Actor& output)
{
    bool found = false;

    for(int t=0; t<actors.ActorVec.size(); ++t)
    {
        if( actors.ActorVec[t].semanticName.compare(semanticName.c_str()) == 0)
        {
            copyActorData(actors.ActorVec[t], output);
            found=true;
            break;
        }
    }

    return found;
}


void Util::copyActorData(const actor_msgs::Actor& src, actor_msgs::Actor& dst)
{
    dst.targetType = src.targetType;
    dst.targetProperty = src.targetProperty;
    dst.description = src.description;
    dst.semanticName = src.semanticName;
    dst.targetId = src.targetId;
    dst.targetPoseVec.erase(dst.targetPoseVec.begin(),dst.targetPoseVec.end());
    dst.targetPoseVec.resize(src.targetPoseVec.size());
    for(int p=0; p<src.targetPoseVec.size(); ++p)
    {
        dst.targetPoseVec[p].position.x = src.targetPoseVec[p].position.x;
        dst.targetPoseVec[p].position.y = src.targetPoseVec[p].position.y;
        dst.targetPoseVec[p].position.z = src.targetPoseVec[p].position.z;
        dst.targetPoseVec[p].orientation.x = src.targetPoseVec[p].orientation.x;
        dst.targetPoseVec[p].orientation.y = src.targetPoseVec[p].orientation.y;
        dst.targetPoseVec[p].orientation.z = src.targetPoseVec[p].orientation.z;
        dst.targetPoseVec[p].orientation.w = src.targetPoseVec[p].orientation.w;

    }
    dst.timeStamp = src.timeStamp;
}

void Util::copyActorDataContainer(const actor_msgs::ActorVec& src, actor_msgs::ActorVec& dst)
{

    dst.ActorVec.resize(src.ActorVec.size());

    for(int i=0; i<dst.ActorVec.size(); ++i)
    {
        dst.ActorVec[i].targetType = src.ActorVec[i].targetType;
        dst.ActorVec[i].targetProperty = src.ActorVec[i].targetProperty;
        dst.ActorVec[i].description = src.ActorVec[i].description;
        dst.ActorVec[i].semanticName = src.ActorVec[i].semanticName;
        dst.ActorVec[i].targetId = src.ActorVec[i].targetId;
        dst.ActorVec[i].targetPoseVec.resize(src.ActorVec[i].targetPoseVec.size());
        for(int p=0; p<src.ActorVec[i].targetPoseVec.size(); ++p)
        {
            dst.ActorVec[i].targetPoseVec[p].position.x = src.ActorVec[i].targetPoseVec[p].position.x;
            dst.ActorVec[i].targetPoseVec[p].position.y = src.ActorVec[i].targetPoseVec[p].position.y;
            dst.ActorVec[i].targetPoseVec[p].position.z = src.ActorVec[i].targetPoseVec[p].position.z;
            dst.ActorVec[i].targetPoseVec[p].orientation.x = src.ActorVec[i].targetPoseVec[p].orientation.x;
            dst.ActorVec[i].targetPoseVec[p].orientation.y = src.ActorVec[i].targetPoseVec[p].orientation.y;
            dst.ActorVec[i].targetPoseVec[p].orientation.z = src.ActorVec[i].targetPoseVec[p].orientation.z;
            dst.ActorVec[i].targetPoseVec[p].orientation.w = src.ActorVec[i].targetPoseVec[p].orientation.w;

        }
        dst.ActorVec[i].timeStamp = src.ActorVec[i].timeStamp;
    }
}

void Util::addActors(actor_msgs::ActorVec& new_actors,actor_msgs::ActorVec& actors_data)
{
    for(int i=0; i<new_actors.ActorVec.size(); ++i)
    {
        actors_data.ActorVec.push_back(new_actors.ActorVec[i]);
    }
}

void Util::clearActorsDataContainer(actor_msgs::ActorVec& data)
{
    for(int i=0;i<data.ActorVec.size();++i)
    {
        data.ActorVec[i].targetPoseVec.erase(data.ActorVec[i].targetPoseVec.begin(), data.ActorVec[i].targetPoseVec.end());
        data.ActorVec[i].targetPoseVec.clear();
    }
    data.ActorVec.erase(data.ActorVec.begin(), data.ActorVec.end());
    data.ActorVec.clear();
}

void Util::clearActionData(action_msgs::ActionVec& data)
{
    data.ActionVec.erase(data.ActionVec.begin(), data.ActionVec.end());
    data.ActionVec.clear();
}

}
