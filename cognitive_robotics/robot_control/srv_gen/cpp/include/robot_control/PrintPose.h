/* Auto-generated by genmsg_cpp for file /home/diego/fuerte_workspace/sandbox/Cognitive/robot_control/srv/PrintPose.srv */
#ifndef ROBOT_CONTROL_SERVICE_PRINTPOSE_H
#define ROBOT_CONTROL_SERVICE_PRINTPOSE_H
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

#include "ros/service_traits.h"




namespace robot_control
{
template <class ContainerAllocator>
struct PrintPoseRequest_ {
  typedef PrintPoseRequest_<ContainerAllocator> Type;

  PrintPoseRequest_()
  : effector()
  {
  }

  PrintPoseRequest_(const ContainerAllocator& _alloc)
  : effector(_alloc)
  {
  }

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _effector_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  effector;


  typedef boost::shared_ptr< ::robot_control::PrintPoseRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robot_control::PrintPoseRequest_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct PrintPoseRequest
typedef  ::robot_control::PrintPoseRequest_<std::allocator<void> > PrintPoseRequest;

typedef boost::shared_ptr< ::robot_control::PrintPoseRequest> PrintPoseRequestPtr;
typedef boost::shared_ptr< ::robot_control::PrintPoseRequest const> PrintPoseRequestConstPtr;


template <class ContainerAllocator>
struct PrintPoseResponse_ {
  typedef PrintPoseResponse_<ContainerAllocator> Type;

  PrintPoseResponse_()
  : x(0.0)
  , y(0.0)
  , z(0.0)
  {
  }

  PrintPoseResponse_(const ContainerAllocator& _alloc)
  : x(0.0)
  , y(0.0)
  , z(0.0)
  {
  }

  typedef float _x_type;
  float x;

  typedef float _y_type;
  float y;

  typedef float _z_type;
  float z;


  typedef boost::shared_ptr< ::robot_control::PrintPoseResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robot_control::PrintPoseResponse_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct PrintPoseResponse
typedef  ::robot_control::PrintPoseResponse_<std::allocator<void> > PrintPoseResponse;

typedef boost::shared_ptr< ::robot_control::PrintPoseResponse> PrintPoseResponsePtr;
typedef boost::shared_ptr< ::robot_control::PrintPoseResponse const> PrintPoseResponseConstPtr;

struct PrintPose
{

typedef PrintPoseRequest Request;
typedef PrintPoseResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;
}; // struct PrintPose
} // namespace robot_control

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::robot_control::PrintPoseRequest_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::robot_control::PrintPoseRequest_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::robot_control::PrintPoseRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "7dcb90cdeb97b9caa21ae9afcbb84a18";
  }

  static const char* value(const  ::robot_control::PrintPoseRequest_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x7dcb90cdeb97b9caULL;
  static const uint64_t static_value2 = 0xa21ae9afcbb84a18ULL;
};

template<class ContainerAllocator>
struct DataType< ::robot_control::PrintPoseRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "robot_control/PrintPoseRequest";
  }

  static const char* value(const  ::robot_control::PrintPoseRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::robot_control::PrintPoseRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "string effector\n\
\n\
";
  }

  static const char* value(const  ::robot_control::PrintPoseRequest_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros


namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::robot_control::PrintPoseResponse_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::robot_control::PrintPoseResponse_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::robot_control::PrintPoseResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "cc153912f1453b708d221682bc23d9ac";
  }

  static const char* value(const  ::robot_control::PrintPoseResponse_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xcc153912f1453b70ULL;
  static const uint64_t static_value2 = 0x8d221682bc23d9acULL;
};

template<class ContainerAllocator>
struct DataType< ::robot_control::PrintPoseResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "robot_control/PrintPoseResponse";
  }

  static const char* value(const  ::robot_control::PrintPoseResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::robot_control::PrintPoseResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "float32 x\n\
float32 y\n\
float32 z\n\
\n\
\n\
";
  }

  static const char* value(const  ::robot_control::PrintPoseResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::robot_control::PrintPoseResponse_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::robot_control::PrintPoseRequest_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.effector);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct PrintPoseRequest_
} // namespace serialization
} // namespace ros


namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::robot_control::PrintPoseResponse_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.x);
    stream.next(m.y);
    stream.next(m.z);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct PrintPoseResponse_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace service_traits
{
template<>
struct MD5Sum<robot_control::PrintPose> {
  static const char* value() 
  {
    return "d0ffb32f80ee108381d60594e2651233";
  }

  static const char* value(const robot_control::PrintPose&) { return value(); } 
};

template<>
struct DataType<robot_control::PrintPose> {
  static const char* value() 
  {
    return "robot_control/PrintPose";
  }

  static const char* value(const robot_control::PrintPose&) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<robot_control::PrintPoseRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "d0ffb32f80ee108381d60594e2651233";
  }

  static const char* value(const robot_control::PrintPoseRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<robot_control::PrintPoseRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "robot_control/PrintPose";
  }

  static const char* value(const robot_control::PrintPoseRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<robot_control::PrintPoseResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "d0ffb32f80ee108381d60594e2651233";
  }

  static const char* value(const robot_control::PrintPoseResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<robot_control::PrintPoseResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "robot_control/PrintPose";
  }

  static const char* value(const robot_control::PrintPoseResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace service_traits
} // namespace ros

#endif // ROBOT_CONTROL_SERVICE_PRINTPOSE_H

