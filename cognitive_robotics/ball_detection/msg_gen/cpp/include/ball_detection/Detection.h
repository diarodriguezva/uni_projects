/* Auto-generated by genmsg_cpp for file /home/diego/fuerte_workspace/sandbox/Cognitive/ball_detection/msg/Detection.msg */
#ifndef BALL_DETECTION_MESSAGE_DETECTION_H
#define BALL_DETECTION_MESSAGE_DETECTION_H
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


namespace ball_detection
{
template <class ContainerAllocator>
struct Detection_ {
  typedef Detection_<ContainerAllocator> Type;

  Detection_()
  : x(0)
  , y(0)
  {
  }

  Detection_(const ContainerAllocator& _alloc)
  : x(0)
  , y(0)
  {
  }

  typedef int32_t _x_type;
  int32_t x;

  typedef int32_t _y_type;
  int32_t y;


  typedef boost::shared_ptr< ::ball_detection::Detection_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ball_detection::Detection_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct Detection
typedef  ::ball_detection::Detection_<std::allocator<void> > Detection;

typedef boost::shared_ptr< ::ball_detection::Detection> DetectionPtr;
typedef boost::shared_ptr< ::ball_detection::Detection const> DetectionConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::ball_detection::Detection_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::ball_detection::Detection_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace ball_detection

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::ball_detection::Detection_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::ball_detection::Detection_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::ball_detection::Detection_<ContainerAllocator> > {
  static const char* value() 
  {
    return "bd7b43fd41d4c47bf5c703cc7d016709";
  }

  static const char* value(const  ::ball_detection::Detection_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xbd7b43fd41d4c47bULL;
  static const uint64_t static_value2 = 0xf5c703cc7d016709ULL;
};

template<class ContainerAllocator>
struct DataType< ::ball_detection::Detection_<ContainerAllocator> > {
  static const char* value() 
  {
    return "ball_detection/Detection";
  }

  static const char* value(const  ::ball_detection::Detection_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::ball_detection::Detection_<ContainerAllocator> > {
  static const char* value() 
  {
    return "int32 x\n\
int32 y\n\
\n\
";
  }

  static const char* value(const  ::ball_detection::Detection_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::ball_detection::Detection_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::ball_detection::Detection_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.x);
    stream.next(m.y);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct Detection_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ball_detection::Detection_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::ball_detection::Detection_<ContainerAllocator> & v) 
  {
    s << indent << "x: ";
    Printer<int32_t>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<int32_t>::stream(s, indent + "  ", v.y);
  }
};


} // namespace message_operations
} // namespace ros

#endif // BALL_DETECTION_MESSAGE_DETECTION_H
