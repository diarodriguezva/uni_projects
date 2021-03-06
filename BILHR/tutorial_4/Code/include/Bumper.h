/* Auto-generated by genmsg_cpp for file /home/pcnao02/fuerte_workspace/sandbox/BILHR_ros/msg/Bumper.msg */
#ifndef BILHR_ROS_MESSAGE_BUMPER_H
#define BILHR_ROS_MESSAGE_BUMPER_H
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
struct Bumper_ {
  typedef Bumper_<ContainerAllocator> Type;

  Bumper_()
  : bumper(0)
  , state(0)
  {
  }

  Bumper_(const ContainerAllocator& _alloc)
  : bumper(0)
  , state(0)
  {
  }

  typedef uint8_t _bumper_type;
  uint8_t bumper;

  typedef uint8_t _state_type;
  uint8_t state;

  enum { right = 0 };
  enum { left = 1 };
  enum { stateReleased = 0 };
  enum { statePressed = 1 };

  typedef boost::shared_ptr< ::BILHR_ros::Bumper_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::BILHR_ros::Bumper_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct Bumper
typedef  ::BILHR_ros::Bumper_<std::allocator<void> > Bumper;

typedef boost::shared_ptr< ::BILHR_ros::Bumper> BumperPtr;
typedef boost::shared_ptr< ::BILHR_ros::Bumper const> BumperConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::BILHR_ros::Bumper_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::BILHR_ros::Bumper_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace BILHR_ros

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::BILHR_ros::Bumper_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::BILHR_ros::Bumper_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::BILHR_ros::Bumper_<ContainerAllocator> > {
  static const char* value() 
  {
    return "4d423b2a165337e812d1b5a1cbab6b8d";
  }

  static const char* value(const  ::BILHR_ros::Bumper_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x4d423b2a165337e8ULL;
  static const uint64_t static_value2 = 0x12d1b5a1cbab6b8dULL;
};

template<class ContainerAllocator>
struct DataType< ::BILHR_ros::Bumper_<ContainerAllocator> > {
  static const char* value() 
  {
    return "BILHR_ros/Bumper";
  }

  static const char* value(const  ::BILHR_ros::Bumper_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::BILHR_ros::Bumper_<ContainerAllocator> > {
  static const char* value() 
  {
    return "# A message for Nao's bumpers on the feet\n\
\n\
uint8 bumper            # which bumper (left or right)\n\
uint8 state             # state of the bumper (pressed or released)\n\
\n\
uint8 right=0\n\
uint8 left=1\n\
\n\
uint8 stateReleased=0\n\
uint8 statePressed=1\n\
\n\
";
  }

  static const char* value(const  ::BILHR_ros::Bumper_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::BILHR_ros::Bumper_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::BILHR_ros::Bumper_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.bumper);
    stream.next(m.state);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct Bumper_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::BILHR_ros::Bumper_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::BILHR_ros::Bumper_<ContainerAllocator> & v) 
  {
    s << indent << "bumper: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.bumper);
    s << indent << "state: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.state);
  }
};


} // namespace message_operations
} // namespace ros

#endif // BILHR_ROS_MESSAGE_BUMPER_H

