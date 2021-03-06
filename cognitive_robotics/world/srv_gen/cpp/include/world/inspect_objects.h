/* Auto-generated by genmsg_cpp for file /home/diego/fuerte_workspace/sandbox/Cognitive/world/srv/inspect_objects.srv */
#ifndef WORLD_SERVICE_INSPECT_OBJECTS_H
#define WORLD_SERVICE_INSPECT_OBJECTS_H
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
struct inspect_objectsRequest_ {
  typedef inspect_objectsRequest_<ContainerAllocator> Type;

  inspect_objectsRequest_()
  {
  }

  inspect_objectsRequest_(const ContainerAllocator& _alloc)
  {
  }


  typedef boost::shared_ptr< ::world::inspect_objectsRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::world::inspect_objectsRequest_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct inspect_objectsRequest
typedef  ::world::inspect_objectsRequest_<std::allocator<void> > inspect_objectsRequest;

typedef boost::shared_ptr< ::world::inspect_objectsRequest> inspect_objectsRequestPtr;
typedef boost::shared_ptr< ::world::inspect_objectsRequest const> inspect_objectsRequestConstPtr;


template <class ContainerAllocator>
struct inspect_objectsResponse_ {
  typedef inspect_objectsResponse_<ContainerAllocator> Type;

  inspect_objectsResponse_()
  : name()
  , x()
  , y()
  , z()
  {
    x.assign(0.0);
    y.assign(0.0);
    z.assign(0.0);
  }

  inspect_objectsResponse_(const ContainerAllocator& _alloc)
  : name()
  , x()
  , y()
  , z()
  {
    name.assign(std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > (_alloc));
    x.assign(0.0);
    y.assign(0.0);
    z.assign(0.0);
  }

  typedef boost::array<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , 3>  _name_type;
  boost::array<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > , 3>  name;

  typedef boost::array<float, 3>  _x_type;
  boost::array<float, 3>  x;

  typedef boost::array<float, 3>  _y_type;
  boost::array<float, 3>  y;

  typedef boost::array<float, 3>  _z_type;
  boost::array<float, 3>  z;


  typedef boost::shared_ptr< ::world::inspect_objectsResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::world::inspect_objectsResponse_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct inspect_objectsResponse
typedef  ::world::inspect_objectsResponse_<std::allocator<void> > inspect_objectsResponse;

typedef boost::shared_ptr< ::world::inspect_objectsResponse> inspect_objectsResponsePtr;
typedef boost::shared_ptr< ::world::inspect_objectsResponse const> inspect_objectsResponseConstPtr;

struct inspect_objects
{

typedef inspect_objectsRequest Request;
typedef inspect_objectsResponse Response;
Request request;
Response response;

typedef Request RequestType;
typedef Response ResponseType;
}; // struct inspect_objects
} // namespace world

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::world::inspect_objectsRequest_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::world::inspect_objectsRequest_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::world::inspect_objectsRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const  ::world::inspect_objectsRequest_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::world::inspect_objectsRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "world/inspect_objectsRequest";
  }

  static const char* value(const  ::world::inspect_objectsRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::world::inspect_objectsRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "\n\
";
  }

  static const char* value(const  ::world::inspect_objectsRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::world::inspect_objectsRequest_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros


namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::world::inspect_objectsResponse_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::world::inspect_objectsResponse_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::world::inspect_objectsResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "43b52e66414248b834e9f282b4e0b20a";
  }

  static const char* value(const  ::world::inspect_objectsResponse_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x43b52e66414248b8ULL;
  static const uint64_t static_value2 = 0x34e9f282b4e0b20aULL;
};

template<class ContainerAllocator>
struct DataType< ::world::inspect_objectsResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "world/inspect_objectsResponse";
  }

  static const char* value(const  ::world::inspect_objectsResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::world::inspect_objectsResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "string[3] name\n\
float32[3] x\n\
float32[3] y\n\
float32[3] z\n\
\n\
\n\
";
  }

  static const char* value(const  ::world::inspect_objectsResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::world::inspect_objectsRequest_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct inspect_objectsRequest_
} // namespace serialization
} // namespace ros


namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::world::inspect_objectsResponse_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.name);
    stream.next(m.x);
    stream.next(m.y);
    stream.next(m.z);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct inspect_objectsResponse_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace service_traits
{
template<>
struct MD5Sum<world::inspect_objects> {
  static const char* value() 
  {
    return "43b52e66414248b834e9f282b4e0b20a";
  }

  static const char* value(const world::inspect_objects&) { return value(); } 
};

template<>
struct DataType<world::inspect_objects> {
  static const char* value() 
  {
    return "world/inspect_objects";
  }

  static const char* value(const world::inspect_objects&) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<world::inspect_objectsRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "43b52e66414248b834e9f282b4e0b20a";
  }

  static const char* value(const world::inspect_objectsRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<world::inspect_objectsRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "world/inspect_objects";
  }

  static const char* value(const world::inspect_objectsRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct MD5Sum<world::inspect_objectsResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "43b52e66414248b834e9f282b4e0b20a";
  }

  static const char* value(const world::inspect_objectsResponse_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct DataType<world::inspect_objectsResponse_<ContainerAllocator> > {
  static const char* value() 
  {
    return "world/inspect_objects";
  }

  static const char* value(const world::inspect_objectsResponse_<ContainerAllocator> &) { return value(); } 
};

} // namespace service_traits
} // namespace ros

#endif // WORLD_SERVICE_INSPECT_OBJECTS_H

