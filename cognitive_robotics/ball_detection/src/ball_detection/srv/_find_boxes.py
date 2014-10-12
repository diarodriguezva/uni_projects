"""autogenerated by genpy from ball_detection/find_boxesRequest.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class find_boxesRequest(genpy.Message):
  _md5sum = "d41d8cd98f00b204e9800998ecf8427e"
  _type = "ball_detection/find_boxesRequest"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """
"""
  __slots__ = []
  _slot_types = []

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(find_boxesRequest, self).__init__(*args, **kwds)

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
      pass
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
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
      pass
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
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
"""autogenerated by genpy from ball_detection/find_boxesResponse.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class find_boxesResponse(genpy.Message):
  _md5sum = "ca3cd3dd6596c92aacbb3410f2ee428a"
  _type = "ball_detection/find_boxesResponse"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """int32[3] x_min
int32[3] x_max
int32[3] y_min
int32[3] y_max
string[3] color


"""
  __slots__ = ['x_min','x_max','y_min','y_max','color']
  _slot_types = ['int32[3]','int32[3]','int32[3]','int32[3]','string[3]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       x_min,x_max,y_min,y_max,color

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(find_boxesResponse, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.x_min is None:
        self.x_min = [0,0,0]
      if self.x_max is None:
        self.x_max = [0,0,0]
      if self.y_min is None:
        self.y_min = [0,0,0]
      if self.y_max is None:
        self.y_max = [0,0,0]
      if self.color is None:
        self.color = ['','','']
    else:
      self.x_min = [0,0,0]
      self.x_max = [0,0,0]
      self.y_min = [0,0,0]
      self.y_max = [0,0,0]
      self.color = ['','','']

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
      buff.write(_struct_3i.pack(*self.x_min))
      buff.write(_struct_3i.pack(*self.x_max))
      buff.write(_struct_3i.pack(*self.y_min))
      buff.write(_struct_3i.pack(*self.y_max))
      for val1 in self.color:
        length = len(val1)
        if python3 or type(val1) == unicode:
          val1 = val1.encode('utf-8')
          length = len(val1)
        buff.write(struct.pack('<I%ss'%length, length, val1))
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
      end += 12
      self.x_min = _struct_3i.unpack(str[start:end])
      start = end
      end += 12
      self.x_max = _struct_3i.unpack(str[start:end])
      start = end
      end += 12
      self.y_min = _struct_3i.unpack(str[start:end])
      start = end
      end += 12
      self.y_max = _struct_3i.unpack(str[start:end])
      self.color = []
      for i in range(0, 3):
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1 = str[start:end].decode('utf-8')
        else:
          val1 = str[start:end]
        self.color.append(val1)
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
      buff.write(self.x_min.tostring())
      buff.write(self.x_max.tostring())
      buff.write(self.y_min.tostring())
      buff.write(self.y_max.tostring())
      for val1 in self.color:
        length = len(val1)
        if python3 or type(val1) == unicode:
          val1 = val1.encode('utf-8')
          length = len(val1)
        buff.write(struct.pack('<I%ss'%length, length, val1))
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
      end += 12
      self.x_min = numpy.frombuffer(str[start:end], dtype=numpy.int32, count=3)
      start = end
      end += 12
      self.x_max = numpy.frombuffer(str[start:end], dtype=numpy.int32, count=3)
      start = end
      end += 12
      self.y_min = numpy.frombuffer(str[start:end], dtype=numpy.int32, count=3)
      start = end
      end += 12
      self.y_max = numpy.frombuffer(str[start:end], dtype=numpy.int32, count=3)
      self.color = []
      for i in range(0, 3):
        start = end
        end += 4
        (length,) = _struct_I.unpack(str[start:end])
        start = end
        end += length
        if python3:
          val1 = str[start:end].decode('utf-8')
        else:
          val1 = str[start:end]
        self.color.append(val1)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_3i = struct.Struct("<3i")
class find_boxes(object):
  _type          = 'ball_detection/find_boxes'
  _md5sum = 'ca3cd3dd6596c92aacbb3410f2ee428a'
  _request_class  = find_boxesRequest
  _response_class = find_boxesResponse
