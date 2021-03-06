"""autogenerated by genpy from ros_tum_msgs/ActionVec.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct

import geometry_msgs.msg
import ros_tum_msgs.msg

class ActionVec(genpy.Message):
  _md5sum = "58b93cb4f038844c222f2bde6ec82e5b"
  _type = "ros_tum_msgs/ActionVec"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """#Action Vector

Action[] ActionVec

================================================================================
MSG: ros_tum_msgs/Action
#Action Structure

int32 name

Actor actor

string uniqueIdentifier

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
  __slots__ = ['ActionVec']
  _slot_types = ['ros_tum_msgs/Action[]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       ActionVec

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(ActionVec, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.ActionVec is None:
        self.ActionVec = []
    else:
      self.ActionVec = []

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
      length = len(self.ActionVec)
      buff.write(_struct_I.pack(length))
      for val1 in self.ActionVec:
        buff.write(_struct_i.pack(val1.name))
        _v1 = val1.actor
        length = len(_v1.targetPoseVec)
        buff.write(_struct_I.pack(length))
        for val3 in _v1.targetPoseVec:
          _v2 = val3.position
          _x = _v2
          buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
          _v3 = val3.orientation
          _x = _v3
          buff.write(_struct_4d.pack(_x.x, _x.y, _x.z, _x.w))
        _x = _v1.targetType
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = _v1.targetProperty
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = _v1.description
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = _v1.timeStamp
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = _v1.semanticName
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        buff.write(_struct_i.pack(_v1.targetId))
        _x = val1.uniqueIdentifier
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      if self.ActionVec is None:
        self.ActionVec = None
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.ActionVec = []
      for i in range(0, length):
        val1 = ros_tum_msgs.msg.Action()
        start = end
        end += 4
        (val1.name,) = _struct_i.unpack(str[start:end])
        _v4 = val1.actor
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        _v4.targetPoseVec = []
        for i in range(0, length):
          val3 = geometry_msgs.msg.Pose()
          _v5 = val3.position
          _x = _v5
          start = end
          end += 24
          (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
          _v6 = val3.orientation
          _x = _v6
          start = end
          end += 32
          (_x.x, _x.y, _x.z, _x.w,) = _struct_4d.unpack(str[start:end])
          _v4.targetPoseVec.append(val3)
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          _v4.targetType = str[start:end].decode('utf-8')
        else:
          _v4.targetType = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          _v4.targetProperty = str[start:end].decode('utf-8')
        else:
          _v4.targetProperty = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          _v4.description = str[start:end].decode('utf-8')
        else:
          _v4.description = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          _v4.timeStamp = str[start:end].decode('utf-8')
        else:
          _v4.timeStamp = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          _v4.semanticName = str[start:end].decode('utf-8')
        else:
          _v4.semanticName = str[start:end]
        start = end
        end += 4
        (_v4.targetId,) = _struct_i.unpack(str[start:end])
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.uniqueIdentifier = str[start:end].decode('utf-8')
        else:
          val1.uniqueIdentifier = str[start:end]
        self.ActionVec.append(val1)
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
      length = len(self.ActionVec)
      buff.write(_struct_I.pack(length))
      for val1 in self.ActionVec:
        buff.write(_struct_i.pack(val1.name))
        _v7 = val1.actor
        length = len(_v7.targetPoseVec)
        buff.write(_struct_I.pack(length))
        for val3 in _v7.targetPoseVec:
          _v8 = val3.position
          _x = _v8
          buff.write(_struct_3d.pack(_x.x, _x.y, _x.z))
          _v9 = val3.orientation
          _x = _v9
          buff.write(_struct_4d.pack(_x.x, _x.y, _x.z, _x.w))
        _x = _v7.targetType
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = _v7.targetProperty
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = _v7.description
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = _v7.timeStamp
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        _x = _v7.semanticName
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
        buff.write(_struct_i.pack(_v7.targetId))
        _x = val1.uniqueIdentifier
        length = len(_x)
        if python3 or type(_x) == unicode:
          _x = _x.encode('utf-8')
          length = len(_x)
        buff.write(struct.pack('<I%ss'%length, length, _x))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    try:
      if self.ActionVec is None:
        self.ActionVec = None
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      self.ActionVec = []
      for i in range(0, length):
        val1 = ros_tum_msgs.msg.Action()
        start = end
        end += 4
        (val1.name,) = _struct_i.unpack(str[start:end])
        _v10 = val1.actor
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        _v10.targetPoseVec = []
        for i in range(0, length):
          val3 = geometry_msgs.msg.Pose()
          _v11 = val3.position
          _x = _v11
          start = end
          end += 24
          (_x.x, _x.y, _x.z,) = _struct_3d.unpack(str[start:end])
          _v12 = val3.orientation
          _x = _v12
          start = end
          end += 32
          (_x.x, _x.y, _x.z, _x.w,) = _struct_4d.unpack(str[start:end])
          _v10.targetPoseVec.append(val3)
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          _v10.targetType = str[start:end].decode('utf-8')
        else:
          _v10.targetType = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          _v10.targetProperty = str[start:end].decode('utf-8')
        else:
          _v10.targetProperty = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          _v10.description = str[start:end].decode('utf-8')
        else:
          _v10.description = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          _v10.timeStamp = str[start:end].decode('utf-8')
        else:
          _v10.timeStamp = str[start:end]
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          _v10.semanticName = str[start:end].decode('utf-8')
        else:
          _v10.semanticName = str[start:end]
        start = end
        end += 4
        (_v10.targetId,) = _struct_i.unpack(str[start:end])
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1.uniqueIdentifier = str[start:end].decode('utf-8')
        else:
          val1.uniqueIdentifier = str[start:end]
        self.ActionVec.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_i = struct.Struct("<i")
_struct_4d = struct.Struct("<4d")
_struct_3d = struct.Struct("<3d")
