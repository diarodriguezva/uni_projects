/* Auto-generated by genmsg_cpp for file /home/diego/fuerte_workspace/sandbox/Cognitive/robot_control/srv/MoveToOS.srv */
#ifndef ROBOT_CONTROL_SERVICE_MOVETOOS_H
#define ROBOT_CONTROL_SERVICE_MOVETOOS_H
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
struct MoveToOSRequest_ {
  typedef MoveToOSRequest_<ContainerAllocator> Type;

  MoveToOSRequest_()
  : effector()
  , x(0.0)
  , y(0.0)
  , z(0.0)
  {
  }

  MoveToOSRequest_(const ContainerAllocator& _alloc)
  : effector(_alloc)
  , x(0.0)
  , y(0.0)
  , z(0.0)
  {
  }

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _effector_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  effector;

  typedef float _x_type;
  float x;

  typedef float _y_type;
  float y;

  typedef float _z_type;
  float z;


  typedef boost::shared_ptr< ::robot_control::MoveToOSRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robot_control::MoveToOSRequest_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct MoveToOSRequest
typedef  ::robot_control::MoveToOSRequest_<std::allocator<void> > MoveToOSRequest;

typedef boost::shared_ptr< ::robot_control::MoveToOSRequest> MoveToOSRequestPtr;
typedef boost::shared_ptr< ::robot_control::MoveToOSRequest const> MoveToOSRequestConstPtr;


template <class ContainerAllocator>
struct MoveToOSResponse_ {
  typedef MoveToOSResponse_<ContainerAllocator> Type;

  MoveToOSResponse_()
  : success(false)
  {
  }

  MoveToOSResponse_(const ContainerAllocator& _alloc)
  : success(false)
  {
  }

  typedef uint8_t _success_type;
  uint8_t success;


  typedef boost::shared_ptr< ::robot_control::MoveToOSResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robot_control::MoveToOSResponse_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct MoveToOSResponse
typedef  ::robot_control::MoveToOSResponse_<std::allocator<void> > MoveToOSResponse;

typedef boost::shared_ptr< ::robot_control::MoveToOSResponse> MoveToOSResponsePtr;
typedef boost::shared_ptr< ::robot_control::MoveToOSResponse const> MoveToOSResponseConstPtr;

struct MoveToOS
{

typedef MoveToOSRequest Request;
typedef MoveToOSResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;
}; // struct MoveToOS
} // namespace robot_control

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::robot_control::MoveToOSRequest_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::robot_control::MoveToOSRequest_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::robot_control::MoveToOSRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "284bc3bb430e8a299d9900b74ed977c6";
  }

  static const char* value(const  ::robot_control::MoveToOSRequest_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x284bc3bb430e8a29ULL;
  static const uint64_t static_value2 = 0x9d9900b74ed977c6ULL;
};

template<class ContainerAllocator>
struct DataType< ::robot_control::MoveToOSRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "robot_control/MoveToOSRequest";
  }

  static const char* value(const  ::robot_control::MoveToOSRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::robot_control::MoveToOSRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "string effector\n\
float32 x\n\
float32 y\n\
float32 z\n\
\n\
";
  }

  static const char* value(const  ::robot_control::MoveToOSRequest_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros


namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::robot_control::MoveToOSResponse_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::robot_control::MoveToOSResponse_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::robot_control::MoveToOSResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "358e233cde0c8a8bcfea4ce193f8fc15";
  }

  static const char* value(const  ::robot_control::MoveToOSResponse_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x358e233cde0c8a8bULL;
  static const uint64_t static_value2 = 0xcfea4ce193f8fc15ULL;
};

template<class ContainerAllocator>
struct DataType< ::robot_control::MoveToOSResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "robot_control/MoveToOSResponse";
  }

  static const char* value(const  ::robot_control::MoveToOSResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::robot_control::MoveToOSResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "bool success\n\
\n\
\n\
\n\
";
  }

  static const char* value(const  ::robot_control::MoveToOSResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::robot_control::MoveToOSResponse_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::robot_control::MoveToOSRequest_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.effector);
    stream.next(m.x);
    stream.next(m.y);
    stream.next(m.z);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct MoveToOSRequest_
} // namespace serialization
} // namespace ros


namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::robot_control::MoveToOSResponse_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.success);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct MoveToOSResponse_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace service_traits
{
template<>
struct MD5Sum<robot_control::MoveToOS> {
  static const char* value() 
  {
    return "2464e453aaaf739bd4026551e66fcf6a";
  }

  static const char* value(const robot_control::MoveToOS&) { return value(); } 
};

template<>
struct DataType<robot_control::MoveToOS> {
  static const char* value() 
  {
    return "robot_control/MoveToOS";
  }

  static const char* value(const robot_control::MoveToOS&) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<robot_control::MoveToOSRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "2464e453aaaf739bd4026551e66fcf6a";
  }

  static const char* value(const robot_control::MoveToOSRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<robot_control::MoveToOSRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "robot_control/MoveToOS";
  }

  static const char* value(const robot_control::MoveToOSRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<robot_control::MoveToOSResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "2464e453aaaf739bd4026551e66fcf6a";
  }

  static const char* value(const robot_control::MoveToOSResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<robot_control::MoveToOSResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "robot_control/MoveToOS";
  }

  static const char* value(const robot_control::MoveToOSResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace service_traits
} // namespace ros

#endif // ROBOT_CONTROL_SERVICE_MOVETOOS_H
