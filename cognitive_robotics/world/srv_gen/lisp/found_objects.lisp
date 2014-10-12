; Auto-generated. Do not edit!


(cl:in-package world-srv)


;//! \htmlinclude found_objects-request.msg.html

(cl:defclass <found_objects-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass found_objects-request (<found_objects-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <found_objects-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'found_objects-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name world-srv:<found_objects-request> is deprecated: use world-srv:found_objects-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <found_objects-request>) ostream)
  "Serializes a message object of type '<found_objects-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <found_objects-request>) istream)
  "Deserializes a message object of type '<found_objects-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<found_objects-request>)))
  "Returns string type for a service object of type '<found_objects-request>"
  "world/found_objectsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'found_objects-request)))
  "Returns string type for a service object of type 'found_objects-request"
  "world/found_objectsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<found_objects-request>)))
  "Returns md5sum for a message object of type '<found_objects-request>"
  "43b52e66414248b834e9f282b4e0b20a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'found_objects-request)))
  "Returns md5sum for a message object of type 'found_objects-request"
  "43b52e66414248b834e9f282b4e0b20a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<found_objects-request>)))
  "Returns full string definition for message of type '<found_objects-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'found_objects-request)))
  "Returns full string definition for message of type 'found_objects-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <found_objects-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <found_objects-request>))
  "Converts a ROS message object to a list"
  (cl:list 'found_objects-request
))
;//! \htmlinclude found_objects-response.msg.html

(cl:defclass <found_objects-response> (roslisp-msg-protocol:ros-message)
  ((name
    :reader name
    :initarg :name
    :type (cl:vector cl:string)
   :initform (cl:make-array 3 :element-type 'cl:string :initial-element ""))
   (x
    :reader x
    :initarg :x
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (y
    :reader y
    :initarg :y
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (z
    :reader z
    :initarg :z
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass found_objects-response (<found_objects-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <found_objects-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'found_objects-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name world-srv:<found_objects-response> is deprecated: use world-srv:found_objects-response instead.")))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <found_objects-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world-srv:name-val is deprecated.  Use world-srv:name instead.")
  (name m))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <found_objects-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world-srv:x-val is deprecated.  Use world-srv:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <found_objects-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world-srv:y-val is deprecated.  Use world-srv:y instead.")
  (y m))

(cl:ensure-generic-function 'z-val :lambda-list '(m))
(cl:defmethod z-val ((m <found_objects-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world-srv:z-val is deprecated.  Use world-srv:z instead.")
  (z m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <found_objects-response>) ostream)
  "Serializes a message object of type '<found_objects-response>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((__ros_str_len (cl:length ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) ele))
   (cl:slot-value msg 'name))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'x))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'y))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'z))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <found_objects-response>) istream)
  "Deserializes a message object of type '<found_objects-response>"
  (cl:setf (cl:slot-value msg 'name) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'name)))
    (cl:dotimes (i 3)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:aref vals i) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))))
  (cl:setf (cl:slot-value msg 'x) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'x)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'y) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'y)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  (cl:setf (cl:slot-value msg 'z) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'z)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<found_objects-response>)))
  "Returns string type for a service object of type '<found_objects-response>"
  "world/found_objectsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'found_objects-response)))
  "Returns string type for a service object of type 'found_objects-response"
  "world/found_objectsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<found_objects-response>)))
  "Returns md5sum for a message object of type '<found_objects-response>"
  "43b52e66414248b834e9f282b4e0b20a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'found_objects-response)))
  "Returns md5sum for a message object of type 'found_objects-response"
  "43b52e66414248b834e9f282b4e0b20a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<found_objects-response>)))
  "Returns full string definition for message of type '<found_objects-response>"
  (cl:format cl:nil "string[3] name~%float32[3] x~%float32[3] y~%float32[3] z~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'found_objects-response)))
  "Returns full string definition for message of type 'found_objects-response"
  (cl:format cl:nil "string[3] name~%float32[3] x~%float32[3] y~%float32[3] z~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <found_objects-response>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'name) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'x) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'y) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'z) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <found_objects-response>))
  "Converts a ROS message object to a list"
  (cl:list 'found_objects-response
    (cl:cons ':name (name msg))
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':z (z msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'found_objects)))
  'found_objects-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'found_objects)))
  'found_objects-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'found_objects)))
  "Returns string type for a service object of type '<found_objects>"
  "world/found_objects")