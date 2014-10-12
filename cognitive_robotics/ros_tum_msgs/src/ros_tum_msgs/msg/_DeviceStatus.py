"""autogenerated by genpy from ros_tum_msgs/DeviceStatus.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class DeviceStatus(genpy.Message):
  _md5sum = "58f4ef410d11b4029bfa14d919c14d93"
  _type = "ros_tum_msgs/DeviceStatus"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """string deviceName

int32 mode

int32 action

string actionIdentifier

int32 result
	
string timeStamp

"""
  __slots__ = ['deviceName','mode','action','actionIdentifier','result','timeStamp']
  _slot_types = ['string','int32','int32','string','int32','string']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       deviceName,mode,action,actionIdentifier,result,timeStamp

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(DeviceStatus, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.deviceName is None:
        self.deviceName = ''
      if self.mode is None:
        self.mode = 0
      if self.action is None:
        self.action = 0
      if self.actionIdentifier is None:
        self.actionIdentifier = ''
      if self.result is None:
        self.result = 0
      if self.timeStamp is None:
        self.timeStamp = ''
    else:
      self.deviceName = ''
      self.mode = 0
      self.action = 0
      self.actionIdentifier = ''
      self.result = 0
      self.timeStamp = ''

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
      _x = self.deviceName
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_2i.pack(_x.mode, _x.action))
      _x = self.actionIdentifier
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_struct_i.pack(self.result))
      _x = self.timeStamp
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
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.deviceName = str[start:end].decode('utf-8')
      else:
        self.deviceName = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.mode, _x.action,) = _struct_2i.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.actionIdentifier = str[start:end].decode('utf-8')
      else:
        self.actionIdentifier = str[start:end]
      start = end
      end += 4
      (self.result,) = _struct_i.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.timeStamp = str[start:end].decode('utf-8')
      else:
        self.timeStamp = str[start:end]
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
      _x = self.deviceName
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_2i.pack(_x.mode, _x.action))
      _x = self.actionIdentifier
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      buff.write(_struct_i.pack(self.result))
      _x = self.timeStamp
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
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.deviceName = str[start:end].decode('utf-8')
      else:
        self.deviceName = str[start:end]
      _x = self
      start = end
      end += 8
      (_x.mode, _x.action,) = _struct_2i.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.actionIdentifier = str[start:end].decode('utf-8')
      else:
        self.actionIdentifier = str[start:end]
      start = end
      end += 4
      (self.result,) = _struct_i.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.timeStamp = str[start:end].decode('utf-8')
      else:
        self.timeStamp = str[start:end]
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_i = struct.Struct("<i")
_struct_2i = struct.Struct("<2i")