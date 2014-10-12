"""autogenerated by genpy from world/detect_objectsRequest.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class detect_objectsRequest(genpy.Message):
  _md5sum = "d41d8cd98f00b204e9800998ecf8427e"
  _type = "world/detect_objectsRequest"
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
      super(detect_objectsRequest, self).__init__(*args, **kwds)

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
"""autogenerated by genpy from world/detect_objectsResponse.msg. Do not edit."""
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class detect_objectsResponse(genpy.Message):
  _md5sum = "43b52e66414248b834e9f282b4e0b20a"
  _type = "world/detect_objectsResponse"
  _has_header = False #flag to mark the presence of a Header object
  _full_text = """string[3] name
float32[3] x
float32[3] y
float32[3] z


"""
  __slots__ = ['name','x','y','z']
  _slot_types = ['string[3]','float32[3]','float32[3]','float32[3]']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       name,x,y,z

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(detect_objectsResponse, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.name is None:
        self.name = ['','','']
      if self.x is None:
        self.x = [0.,0.,0.]
      if self.y is None:
        self.y = [0.,0.,0.]
      if self.z is None:
        self.z = [0.,0.,0.]
    else:
      self.name = ['','','']
      self.x = [0.,0.,0.]
      self.y = [0.,0.,0.]
      self.z = [0.,0.,0.]

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
      for val1 in self.name:
        length = len(val1)
        if python3 or type(val1) == unicode:
          val1 = val1.encode('utf-8')
          length = len(val1)
        buff.write(struct.pack('<I%ss'%length, length, val1))
      buff.write(_struct_3f.pack(*self.x))
      buff.write(_struct_3f.pack(*self.y))
      buff.write(_struct_3f.pack(*self.z))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    try:
      end = 0
      self.name = []
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
        self.name.append(val1)
      start = end
      end += 12
      self.x = _struct_3f.unpack(str[start:end])
      start = end
      end += 12
      self.y = _struct_3f.unpack(str[start:end])
      start = end
      end += 12
      self.z = _struct_3f.unpack(str[start:end])
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
      for val1 in self.name:
        length = len(val1)
        if python3 or type(val1) == unicode:
          val1 = val1.encode('utf-8')
          length = len(val1)
        buff.write(struct.pack('<I%ss'%length, length, val1))
      buff.write(self.x.tostring())
      buff.write(self.y.tostring())
      buff.write(self.z.tostring())
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
      self.name = []
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
        self.name.append(val1)
      start = end
      end += 12
      self.x = numpy.frombuffer(str[start:end], dtype=numpy.float32, count=3)
      start = end
      end += 12
      self.y = numpy.frombuffer(str[start:end], dtype=numpy.float32, count=3)
      start = end
      end += 12
      self.z = numpy.frombuffer(str[start:end], dtype=numpy.float32, count=3)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e) #most likely buffer underfill

_struct_I = genpy.struct_I
_struct_3f = struct.Struct("<3f")
class detect_objects(object):
  _type          = 'world/detect_objects'
  _md5sum = '43b52e66414248b834e9f282b4e0b20a'
  _request_class  = detect_objectsRequest
  _response_class = detect_objectsResponse
