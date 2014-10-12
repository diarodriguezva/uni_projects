"""autogenerated by genpy from ros_tum_msgs/Projector.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class Projector(genpy.Message):
  _md5sum = "956effeef4943baa5ec70ff6367bfec6"
  _type = "ros_tum_msgs/Projector"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """#Projector
int32 command
string actor_name
float64 pos_x
float64 pos_y
float64 pos_z
float64 dim_x
float64 dim_y
float64 dim_z

"""
  __slots__ = ['command','actor_name','pos_x','pos_y','pos_z','dim_x','dim_y','dim_z']
  _slot_types = ['int32','string','float64','float64','float64','float64','float64','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       command,actor_name,pos_x,pos_y,pos_z,dim_x,dim_y,dim_z

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(Projector, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.command is None:
        self.command = 0
      if self.actor_name is None:
        self.actor_name = ''
      if self.pos_x is None:
        self.pos_x = 0.
      if self.pos_y is None:
        self.pos_y = 0.
      if self.pos_z is None:
        self.pos_z = 0.
      if self.dim_x is None:
        self.dim_x = 0.
      if self.dim_y is None:
        self.dim_y = 0.
      if self.dim_z is None:
        self.dim_z = 0.
    else:
      self.command = 0
      self.actor_name = ''
      self.pos_x = 0.
      self.pos_y = 0.
      self.pos_z = 0.
      self.dim_x = 0.
      self.dim_y = 0.
      self.dim_z = 0.

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
      buff.write(_struct_i.pack(self.command))
      _x = self.actor_name
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_6d.pack(_x.pos_x, _x.pos_y, _x.pos_z, _x.dim_x, _x.dim_y, _x.dim_z))
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
      (self.command,) = _struct_i.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.actor_name = str[start:end].decode('utf-8')
      else:
        self.actor_name = str[start:end]
      _x = self
      start = end
      end += 48
      (_x.pos_x, _x.pos_y, _x.pos_z, _x.dim_x, _x.dim_y, _x.dim_z,) = _struct_6d.unpack(str[start:end])
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
      buff.write(_struct_i.pack(self.command))
      _x = self.actor_name
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_6d.pack(_x.pos_x, _x.pos_y, _x.pos_z, _x.dim_x, _x.dim_y, _x.dim_z))
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
      (self.command,) = _struct_i.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.actor_name = str[start:end].decode('utf-8')
      else:
        self.actor_name = str[start:end]
      _x = self
      start = end
      end += 48
      (_x.pos_x, _x.pos_y, _x.pos_z, _x.dim_x, _x.dim_y, _x.dim_z,) = _struct_6d.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_i = struct.Struct("<i")
_struct_6d = struct.Struct("<6d")