; Auto-generated. Do not edit!


(cl:in-package ball_detection-srv)


;//! \htmlinclude find_balls-request.msg.html

(cl:defclass <find_balls-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass find_balls-request (<find_balls-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <find_balls-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'find_balls-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ball_detection-srv:<find_balls-request> is deprecated: use ball_detection-srv:find_balls-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <find_balls-request>) ostream)
  "Serializes a message object of type '<find_balls-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <find_balls-request>) istream)
  "Deserializes a message object of type '<find_balls-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<find_balls-request>)))
  "Returns string type for a service object of type '<find_balls-request>"
  "ball_detection/find_ballsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'find_balls-request)))
  "Returns string type for a service object of type 'find_balls-request"
  "ball_detection/find_ballsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<find_balls-request>)))
  "Returns md5sum for a message object of type '<find_balls-request>"
  "4a85c1094e1f74e9e69b7de7af5cb575")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'find_balls-request)))
  "Returns md5sum for a message object of type 'find_balls-request"
  "4a85c1094e1f74e9e69b7de7af5cb575")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<find_balls-request>)))
  "Returns full string definition for message of type '<find_balls-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'find_balls-request)))
  "Returns full string definition for message of type 'find_balls-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <find_balls-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <find_balls-request>))
  "Converts a ROS message object to a list"
  (cl:list 'find_balls-request
))
;//! \htmlinclude find_balls-response.msg.html

(cl:defclass <find_balls-response> (roslisp-msg-protocol:ros-message)
  ((x
    :reader x
    :initarg :x
    :type (cl:vector cl:integer)
   :initform (cl:make-array 3 :element-type 'cl:integer :initial-element 0))
   (y
    :reader y
    :initarg :y
    :type (cl:vector cl:integer)
   :initform (cl:make-array 3 :element-type 'cl:integer :initial-element 0))
   (name
    :reader name
    :initarg :name
    :type (cl:vector cl:string)
   :initform (cl:make-array 3 :element-type 'cl:string :initial-element "")))
)

(cl:defclass find_balls-response (<find_balls-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <find_balls-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'find_balls-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ball_detection-srv:<find_balls-response> is deprecated: use ball_detection-srv:find_balls-response instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <find_balls-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-srv:x-val is deprecated.  Use ball_detection-srv:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <find_balls-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-srv:y-val is deprecated.  Use ball_detection-srv:y instead.")
  (y m))

(cl:ensure-generic-function 'name-val :lambda-list '(m))
(cl:defmethod name-val ((m <find_balls-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-srv:name-val is deprecated.  Use ball_detection-srv:name instead.")
  (name m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <find_balls-response>) ostream)
  "Serializes a message object of type '<find_balls-response>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'x))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'y))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((__ros_str_len (cl:length ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) ele))
   (cl:slot-value msg 'name))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <find_balls-response>) istream)
  "Deserializes a message object of type '<find_balls-response>"
  (cl:setf (cl:slot-value msg 'x) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'x)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))))
  (cl:setf (cl:slot-value msg 'y) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'y)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))))
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
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<find_balls-response>)))
  "Returns string type for a service object of type '<find_balls-response>"
  "ball_detection/find_ballsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'find_balls-response)))
  "Returns string type for a service object of type 'find_balls-response"
  "ball_detection/find_ballsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<find_balls-response>)))
  "Returns md5sum for a message object of type '<find_balls-response>"
  "4a85c1094e1f74e9e69b7de7af5cb575")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'find_balls-response)))
  "Returns md5sum for a message object of type 'find_balls-response"
  "4a85c1094e1f74e9e69b7de7af5cb575")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<find_balls-response>)))
  "Returns full string definition for message of type '<find_balls-response>"
  (cl:format cl:nil "int32[3] x~%int32[3] y~%string[3] name~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'find_balls-response)))
  "Returns full string definition for message of type 'find_balls-response"
  (cl:format cl:nil "int32[3] x~%int32[3] y~%string[3] name~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <find_balls-response>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'x) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'y) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'name) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <find_balls-response>))
  "Converts a ROS message object to a list"
  (cl:list 'find_balls-response
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':name (name msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'find_balls)))
  'find_balls-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'find_balls)))
  'find_balls-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'find_balls)))
  "Returns string type for a service object of type '<find_balls>"
  "ball_detection/find_balls")