"""autogenerated by genpy from ball_detection/midpoints.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class midpoints(genpy.Message):
  _md5sum = "c49b7ac74776a47d415a17d96ee8bc0b"
  _type = "ball_detection/midpoints"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """int32 x_blue
int32 y_blue
int32 x_yellow
int32 y_yellow
int32 x_red
int32 y_red
int32 x_green
int32 y_green

"""
  __slots__ = ['x_blue','y_blue','x_yellow','y_yellow','x_red','y_red','x_green','y_green']
  _slot_types = ['int32','int32','int32','int32','int32','int32','int32','int32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       x_blue,y_blue,x_yellow,y_yellow,x_red,y_red,x_green,y_green

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(midpoints, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.x_blue is None:
        self.x_blue = 0
      if self.y_blue is None:
        self.y_blue = 0
      if self.x_yellow is None:
        self.x_yellow = 0
      if self.y_yellow is None:
        self.y_yellow = 0
      if self.x_red is None:
        self.x_red = 0
      if self.y_red is None:
        self.y_red = 0
      if self.x_green is None:
        self.x_green = 0
      if self.y_green is None:
        self.y_green = 0
    else:
      self.x_blue = 0
      self.y_blue = 0
      self.x_yellow = 0
      self.y_yellow = 0
      self.x_red = 0
      self.y_red = 0
      self.x_green = 0
      self.y_green = 0

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
      _x = self
      buff.write(_struct_8i.pack(_x.x_blue, _x.y_blue, _x.x_yellow, _x.y_yellow, _x.x_red, _x.y_red, _x.x_green, _x.y_green))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      _x = self
      start = end
      end += 32
      (_x.x_blue, _x.y_blue, _x.x_yellow, _x.y_yellow, _x.x_red, _x.y_red, _x.x_green, _x.y_green,) = _struct_8i.unpack(str[start:end])
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
      _x = self
      buff.write(_struct_8i.pack(_x.x_blue, _x.y_blue, _x.x_yellow, _x.y_yellow, _x.x_red, _x.y_red, _x.x_green, _x.y_green))
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
      _x = self
      start = end
      end += 32
      (_x.x_blue, _x.y_blue, _x.x_yellow, _x.y_yellow, _x.x_red, _x.y_red, _x.x_green, _x.y_green,) = _struct_8i.unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_8i = struct.Struct("<8i")
