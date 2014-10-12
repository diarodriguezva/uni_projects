/* Auto-generated by genmsg_cpp for file /home/diego/fuerte_workspace/sandbox/Cognitive/world/srv/find_balls.srv */
#ifndef WORLD_SERVICE_FIND_BALLS_H
#define WORLD_SERVICE_FIND_BALLS_H
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




namespace world
{
template <class ContainerAllocator>
struct find_ballsRequest_ {
  typedef find_ballsRequest_<ContainerAllocator> Type;

  find_ballsRequest_()
  {
  }

  find_ballsRequest_(const ContainerAllocator& _alloc)
  {
  }


  typedef boost::shared_ptr< ::world::find_ballsRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::world::find_ballsRequest_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct find_ballsRequest
typedef  ::world::find_ballsRequest_<std::allocator<void> > find_ballsRequest;

typedef boost::shared_ptr< ::world::find_ballsRequest> find_ballsRequestPtr;
typedef boost::shared_ptr< ::world::find_ballsRequest const> find_ballsRequestConstPtr;


template <class ContainerAllocator>
struct find_ballsResponse_ {
  typedef find_ballsResponse_<ContainerAllocator> Type;

  find_ballsResponse_()
  : x()
  , y()
  , name()
  {
    x.assign(0);
    y.assign(0);
  }

  find_ballsResponse_(const ContainerAllocator& _alloc)
  : x()
  , y()
  , name()
  {
    x.assign(0);
    y.assign(0);
    name.assign(std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > (_alloc));
  }

  typedef boost::array<int32_t, 3>  _x_type;
  boost::array<int32_t, 3>  x;

  typedef boost::array<int32_t, 3>  _y_type;
  boost::array<int32_t, 3>  y;

  typedef boost::array<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , 3>  _name_type;
  boost::array<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , 3>  name;


  typedef boost::shared_ptr< ::world::find_ballsResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::world::find_ballsResponse_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct find_ballsResponse
typedef  ::world::find_ballsResponse_<std::allocator<void> > find_ballsResponse;

typedef boost::shared_ptr< ::world::find_ballsResponse> find_ballsResponsePtr;
typedef boost::shared_ptr< ::world::find_ballsResponse const> find_ballsResponseConstPtr;

struct find_balls
{

typedef find_ballsRequest Request;
typedef find_ballsResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;
}; // struct find_balls
} // namespace world

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::world::find_ballsRequest_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::world::find_ballsRequest_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::world::find_ballsRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const  ::world::find_ballsRequest_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::world::find_ballsRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "world/find_ballsRequest";
  }

  static const char* value(const  ::world::find_ballsRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::world::find_ballsRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "\n\
";
  }

  static const char* value(const  ::world::find_ballsRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::world::find_ballsRequest_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros


namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::world::find_ballsResponse_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::world::find_ballsResponse_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::world::find_ballsResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "4a85c1094e1f74e9e69b7de7af5cb575";
  }

  static const char* value(const  ::world::find_ballsResponse_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x4a85c1094e1f74e9ULL;
  static const uint64_t static_value2 = 0xe69b7de7af5cb575ULL;
};

template<class ContainerAllocator>
struct DataType< ::world::find_ballsResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "world/find_ballsResponse";
  }

  static const char* value(const  ::world::find_ballsResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::world::find_ballsResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "int32[3] x\n\
int32[3] y\n\
string[3] name\n\
\n\
\n\
\n\
";
  }

  static const char* value(const  ::world::find_ballsResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::world::find_ballsRequest_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct find_ballsRequest_
} // namespace serialization
} // namespace ros


namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::world::find_ballsResponse_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.x);
    stream.next(m.y);
    stream.next(m.name);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct find_ballsResponse_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace service_traits
{
template<>
struct MD5Sum<world::find_balls> {
  static const char* value() 
  {
    return "4a85c1094e1f74e9e69b7de7af5cb575";
  }

  static const char* value(const world::find_balls&) { return value(); } 
};

template<>
struct DataType<world::find_balls> {
  static const char* value() 
  {
    return "world/find_balls";
  }

  static const char* value(const world::find_balls&) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<world::find_ballsRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "4a85c1094e1f74e9e69b7de7af5cb575";
  }

  static const char* value(const world::find_ballsRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<world::find_ballsRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "world/find_balls";
  }

  static const char* value(const world::find_ballsRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<world::find_ballsResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "4a85c1094e1f74e9e69b7de7af5cb575";
  }

  static const char* value(const world::find_ballsResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<world::find_ballsResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "world/find_balls";
  }

  static const char* value(const world::find_ballsResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace service_traits
} // namespace ros

#endif // WORLD_SERVICE_FIND_BALLS_H

