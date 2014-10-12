; Auto-generated. Do not edit!


(cl:in-package robot_control-srv)


;//! \htmlinclude MoveToCS-request.msg.html

(cl:defclass <MoveToCS-request> (roslisp-msg-protocol:ros-message)
  ((effector
    :reader effector
    :initarg :effector
    :type cl:string
    :initform "")
   (x
    :reader x
    :initarg :x
    :type cl:float
    :initform 0.0)
   (y
    :reader y
    :initarg :y
    :type cl:float
    :initform 0.0)
   (z
    :reader z
    :initarg :z
    :type cl:float
    :initform 0.0))
)

(cl:defclass MoveToCS-request (<MoveToCS-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MoveToCS-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MoveToCS-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_control-srv:<MoveToCS-request> is deprecated: use robot_control-srv:MoveToCS-request instead.")))

(cl:ensure-generic-function 'effector-val :lambda-list '(m))
(cl:defmethod effector-val ((m <MoveToCS-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-srv:effector-val is deprecated.  Use robot_control-srv:effector instead.")
  (effector m))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <MoveToCS-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-srv:x-val is deprecated.  Use robot_control-srv:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <MoveToCS-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-srv:y-val is deprecated.  Use robot_control-srv:y instead.")
  (y m))

(cl:ensure-generic-function 'z-val :lambda-list '(m))
(cl:defmethod z-val ((m <MoveToCS-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-srv:z-val is deprecated.  Use robot_control-srv:z instead.")
  (z m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MoveToCS-request>) ostream)
  "Serializes a message object of type '<MoveToCS-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'effector))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'effector))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'z))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MoveToCS-request>) istream)
  "Deserializes a message object of type '<MoveToCS-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'effector) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'effector) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'z) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MoveToCS-request>)))
  "Returns string type for a service object of type '<MoveToCS-request>"
  "robot_control/MoveToCSRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MoveToCS-request)))
  "Returns string type for a service object of type 'MoveToCS-request"
  "robot_control/MoveToCSRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MoveToCS-request>)))
  "Returns md5sum for a message object of type '<MoveToCS-request>"
  "2464e453aaaf739bd4026551e66fcf6a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MoveToCS-request)))
  "Returns md5sum for a message object of type 'MoveToCS-request"
  "2464e453aaaf739bd4026551e66fcf6a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MoveToCS-request>)))
  "Returns full string definition for message of type '<MoveToCS-request>"
  (cl:format cl:nil "string effector~%float32 x~%float32 y~%float32 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MoveToCS-request)))
  "Returns full string definition for message of type 'MoveToCS-request"
  (cl:format cl:nil "string effector~%float32 x~%float32 y~%float32 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MoveToCS-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'effector))
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MoveToCS-request>))
  "Converts a ROS message object to a list"
  (cl:list 'MoveToCS-request
    (cl:cons ':effector (effector msg))
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':z (z msg))
))
;//! \htmlinclude MoveToCS-response.msg.html

(cl:defclass <MoveToCS-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass MoveToCS-response (<MoveToCS-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MoveToCS-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MoveToCS-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_control-srv:<MoveToCS-response> is deprecated: use robot_control-srv:MoveToCS-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <MoveToCS-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-srv:success-val is deprecated.  Use robot_control-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MoveToCS-response>) ostream)
  "Serializes a message object of type '<MoveToCS-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MoveToCS-response>) istream)
  "Deserializes a message object of type '<MoveToCS-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MoveToCS-response>)))
  "Returns string type for a service object of type '<MoveToCS-response>"
  "robot_control/MoveToCSResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MoveToCS-response)))
  "Returns string type for a service object of type 'MoveToCS-response"
  "robot_control/MoveToCSResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MoveToCS-response>)))
  "Returns md5sum for a message object of type '<MoveToCS-response>"
  "2464e453aaaf739bd4026551e66fcf6a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MoveToCS-response)))
  "Returns md5sum for a message object of type 'MoveToCS-response"
  "2464e453aaaf739bd4026551e66fcf6a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MoveToCS-response>)))
  "Returns full string definition for message of type '<MoveToCS-response>"
  (cl:format cl:nil "bool success~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MoveToCS-response)))
  "Returns full string definition for message of type 'MoveToCS-response"
  (cl:format cl:nil "bool success~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MoveToCS-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MoveToCS-response>))
  "Converts a ROS message object to a list"
  (cl:list 'MoveToCS-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'MoveToCS)))
  'MoveToCS-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'MoveToCS)))
  'MoveToCS-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MoveToCS)))
  "Returns string type for a service object of type '<MoveToCS>"
  "robot_control/MoveToCS")