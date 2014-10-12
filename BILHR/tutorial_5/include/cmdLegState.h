/* Auto-generated by genmsg_cpp for file /home/groupc/fuerte_workspace/sandbox/BILHR_ros/msg/cmdLegState.msg */
#ifndef BILHR_ROS_MESSAGE_CMDLEGSTATE_H
#define BILHR_ROS_MESSAGE_CMDLEGSTATE_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace BILHR_ros
{
template <class ContainerAllocator>
struct cmdLegState_ {
  typedef cmdLegState_<ContainerAllocator> Type;

  cmdLegState_()
  : cmdLegState(0)
  {
  }

  cmdLegState_(const ContainerAllocator& _alloc)
  : cmdLegState(0)
  {
  }

  typedef uint8_t _cmdLegState_type;
  uint8_t cmdLegState;


  typedef boost::shared_ptr< ::BILHR_ros::cmdLegState_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::BILHR_ros::cmdLegState_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct cmdLegState
typedef  ::BILHR_ros::cmdLegState_<std::allocator<void> > cmdLegState;

typedef boost::shared_ptr< ::BILHR_ros::cmdLegState> cmdLegStatePtr;
typedef boost::shared_ptr< ::BILHR_ros::cmdLegState const> cmdLegStateConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::BILHR_ros::cmdLegState_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::BILHR_ros::cmdLegState_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace BILHR_ros

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::BILHR_ros::cmdLegState_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::BILHR_ros::cmdLegState_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::BILHR_ros::cmdLegState_<ContainerAllocator> > {
  static const char* value() 
  {
    return "375411f849b3e02129d1cc3f6a0e758d";
  }

  static const char* value(const  ::BILHR_ros::cmdLegState_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x375411f849b3e021ULL;
  static const uint64_t static_value2 = 0x29d1cc3f6a0e758dULL;
};

template<class ContainerAllocator>
struct DataType< ::BILHR_ros::cmdLegState_<ContainerAllocator> > {
  static const char* value() 
  {
    return "BILHR_ros/cmdLegState";
  }

  static const char* value(const  ::BILHR_ros::cmdLegState_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::BILHR_ros::cmdLegState_<ContainerAllocator> > {
  static const char* value() 
  {
    return "uint8 cmdLegState\n\
\n\
";
  }

  static const char* value(const  ::BILHR_ros::cmdLegState_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::BILHR_ros::cmdLegState_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::BILHR_ros::cmdLegState_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.cmdLegState);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct cmdLegState_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::BILHR_ros::cmdLegState_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::BILHR_ros::cmdLegState_<ContainerAllocator> & v) 
  {
    s << indent << "cmdLegState: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.cmdLegState);
  }
};


} // namespace message_operations
} // namespace ros

#endif // BILHR_ROS_MESSAGE_CMDLEGSTATE_H
