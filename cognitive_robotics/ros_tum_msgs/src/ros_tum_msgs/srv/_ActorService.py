"""autogenerated by genpy from ros_tum_msgs/ActorServiceRequest.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class ActorServiceRequest(genpy.Message):
  _md5sum = "d6a7063359b15cbc8bac77de0a1cc2cb"
  _type = "ros_tum_msgs/ActorServiceRequest"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """int32 object_id

"""
  __slots__ = ['object_id']
  _slot_types = ['int32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       object_id

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(ActorServiceRequest, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.object_id is None:
        self.object_id = 0
    else:
      self.object_id = 0

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      buff.write(_struct_i.pack(self.object_id))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      start = end
      end += 4
      (self.object_id,) = _struct_i.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      buff.write(_struct_i.pack(self.object_id))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      end = 0
      start = end
      end += 4
      (self.object_id,) = _struct_i.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_i = struct.Struct("<i")
"""autogenerated by genpy from ros_tum_msgs/ActorServiceResponse.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import geometry_msgs.msg
import ros_tum_msgs.msg

class ActorServiceResponse(genpy.Message):
  _md5sum = "64204c2e303c1517ed1193f650adc7a0"
  _type = "ros_tum_msgs/ActorServiceResponse"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """ActorVec actor_vec


================================================================================
MSG: ros_tum_msgs/ActorVec
Actor[] ActorVec

================================================================================
MSG: ros_tum_msgs/Actor
geometry_msgs/Pose[] targetPoseVec

string targetType

string targetProperty

string description

string timeStamp
	
string semanticName

int32 targetId

================================================================================
MSG: geometry_msgs/Pose
# A representation of pose in free space, composed of postion and orientation. 
Point position
Quaternion orientation

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

"""
  __slots__ = ['actor_vec']
  _slot_types = ['ros_tum_msgs/ActorVec']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       actor_vec

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(ActorServiceResponse, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.actor_vec is None:
        self.actor_vec = ros_tum_msgs.msg.ActorVec()
    else:
      self.actor_vec = ros_tum_msgs.msg.ActorVec()

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      length = len(self.actor_vec.ActorVec)
      buff.write(_struct_I.pack(length))
      for val1 in self.actor_vec.ActorVec:
        length = len(val1.targetPoseVec)
        buff.write(_struct_I.pack(length))
        for val2 in val1.targetPoseVec:
          _v1 = val2.position
          _x = _v1
          buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
          _v2 = val2.orientation
          _x = _v2
          buff.write(_struct_4d.pack(_x.x, _x.y, _x.z, _x.w))
        _x = val1.targetType
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = val1.targetProperty
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = val1.description
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = val1.timeStamp
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = val1.semanticName
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        buff.write(_struct_i.pack(val1.targetId))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.actor_vec is None:
        self.actor_vec = ros_tum_msgs.msg.ActorVec()
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.actor_vec.ActorVec = []
      for i in range(0, length):
        val1 = ros_tum_msgs.msg.Actor()
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        val1.targetPoseVec = []
        for i in range(0, length):
          val2 = geometry_msgs.msg.Pose()
          _v3 = val2.position
          _x = _v3
          start = end
          end += 24
          (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
          _v4 = val2.orientation
          _x = _v4
          start = end
          end += 32
          (_x.x, _x.y, _x.z, _x.w,) = _struct_4d.unpack(str[start:end])
          val1.targetPoseVec.append(val2)
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.targetType = str[start:end].decode('utf-8')
        else:
          val1.targetType = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.targetProperty = str[start:end].decode('utf-8')
        else:
          val1.targetProperty = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.description = str[start:end].decode('utf-8')
        else:
          val1.description = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.timeStamp = str[start:end].decode('utf-8')
        else:
          val1.timeStamp = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.semanticName = str[start:end].decode('utf-8')
        else:
          val1.semanticName = str[start:end]
        start = end
        end += 4
        (val1.targetId,) = _struct_i.unpack(str[start:end])
        self.actor_vec.ActorVec.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      length = len(self.actor_vec.ActorVec)
      buff.write(_struct_I.pack(length))
      for val1 in self.actor_vec.ActorVec:
        length = len(val1.targetPoseVec)
        buff.write(_struct_I.pack(length))
        for val2 in val1.targetPoseVec:
          _v5 = val2.position
          _x = _v5
          buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
          _v6 = val2.orientation
          _x = _v6
          buff.write(_struct_4d.pack(_x.x, _x.y, _x.z, _x.w))
        _x = val1.targetType
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = val1.targetProperty
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = val1.description
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = val1.timeStamp
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = val1.semanticName
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        buff.write(_struct_i.pack(val1.targetId))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.actor_vec is None:
        self.actor_vec = ros_tum_msgs.msg.ActorVec()
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.actor_vec.ActorVec = []
      for i in range(0, length):
        val1 = ros_tum_msgs.msg.Actor()
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        val1.targetPoseVec = []
        for i in range(0, length):
          val2 = geometry_msgs.msg.Pose()
          _v7 = val2.position
          _x = _v7
          start = end
          end += 24
          (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
          _v8 = val2.orientation
          _x = _v8
          start = end
          end += 32
          (_x.x, _x.y, _x.z, _x.w,) = _struct_4d.unpack(str[start:end])
          val1.targetPoseVec.append(val2)
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.targetType = str[start:end].decode('utf-8')
        else:
          val1.targetType = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.targetProperty = str[start:end].decode('utf-8')
        else:
          val1.targetProperty = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.description = str[start:end].decode('utf-8')
        else:
          val1.description = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.timeStamp = str[start:end].decode('utf-8')
        else:
          val1.timeStamp = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.semanticName = str[start:end].decode('utf-8')
        else:
          val1.semanticName = str[start:end]
        start = end
        end += 4
        (val1.targetId,) = _struct_i.unpack(str[start:end])
        self.actor_vec.ActorVec.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_i = struct.Struct("<i")
_struct_4d = struct.Struct("<4d")
_struct_3d = struct.Struct("<3d")
class ActorService(object):
  _type          = 'ros_tum_msgs/ActorService'
  _md5sum = 'ea0c69c9095c0628130382c8fdd34f8a'
  _request_class  = ActorServiceRequest
  _response_class = ActorServiceResponse