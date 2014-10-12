; Auto-generated. Do not edit!


(cl:in-package robot_control-srv)


;//! \htmlinclude MoveToOS-request.msg.html

(cl:defclass <MoveToOS-request> (roslisp-msg-protocol:ros-message)
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

(cl:defclass MoveToOS-request (<MoveToOS-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MoveToOS-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MoveToOS-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_control-srv:<MoveToOS-request> is deprecated: use robot_control-srv:MoveToOS-request instead.")))

(cl:ensure-generic-function 'effector-val :lambda-list '(m))
(cl:defmethod effector-val ((m <MoveToOS-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-srv:effector-val is deprecated.  Use robot_control-srv:effector instead.")
  (effector m))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <MoveToOS-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-srv:x-val is deprecated.  Use robot_control-srv:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <MoveToOS-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-srv:y-val is deprecated.  Use robot_control-srv:y instead.")
  (y m))

(cl:ensure-generic-function 'z-val :lambda-list '(m))
(cl:defmethod z-val ((m <MoveToOS-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-srv:z-val is deprecated.  Use robot_control-srv:z instead.")
  (z m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MoveToOS-request>) ostream)
  "Serializes a message object of type '<MoveToOS-request>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MoveToOS-request>) istream)
  "Deserializes a message object of type '<MoveToOS-request>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MoveToOS-request>)))
  "Returns string type for a service object of type '<MoveToOS-request>"
  "robot_control/MoveToOSRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MoveToOS-request)))
  "Returns string type for a service object of type 'MoveToOS-request"
  "robot_control/MoveToOSRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MoveToOS-request>)))
  "Returns md5sum for a message object of type '<MoveToOS-request>"
  "2464e453aaaf739bd4026551e66fcf6a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MoveToOS-request)))
  "Returns md5sum for a message object of type 'MoveToOS-request"
  "2464e453aaaf739bd4026551e66fcf6a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MoveToOS-request>)))
  "Returns full string definition for message of type '<MoveToOS-request>"
  (cl:format cl:nil "string effector~%float32 x~%float32 y~%float32 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MoveToOS-request)))
  "Returns full string definition for message of type 'MoveToOS-request"
  (cl:format cl:nil "string effector~%float32 x~%float32 y~%float32 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MoveToOS-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'effector))
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MoveToOS-request>))
  "Converts a ROS message object to a list"
  (cl:list 'MoveToOS-request
    (cl:cons ':effector (effector msg))
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':z (z msg))
))
;//! \htmlinclude MoveToOS-response.msg.html

(cl:defclass <MoveToOS-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass MoveToOS-response (<MoveToOS-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MoveToOS-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MoveToOS-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name robot_control-srv:<MoveToOS-response> is deprecated: use robot_control-srv:MoveToOS-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <MoveToOS-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader robot_control-srv:success-val is deprecated.  Use robot_control-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MoveToOS-response>) ostream)
  "Serializes a message object of type '<MoveToOS-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MoveToOS-response>) istream)
  "Deserializes a message object of type '<MoveToOS-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MoveToOS-response>)))
  "Returns string type for a service object of type '<MoveToOS-response>"
  "robot_control/MoveToOSResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MoveToOS-response)))
  "Returns string type for a service object of type 'MoveToOS-response"
  "robot_control/MoveToOSResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MoveToOS-response>)))
  "Returns md5sum for a message object of type '<MoveToOS-response>"
  "2464e453aaaf739bd4026551e66fcf6a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MoveToOS-response)))
  "Returns md5sum for a message object of type 'MoveToOS-response"
  "2464e453aaaf739bd4026551e66fcf6a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MoveToOS-response>)))
  "Returns full string definition for message of type '<MoveToOS-response>"
  (cl:format cl:nil "bool success~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MoveToOS-response)))
  "Returns full string definition for message of type 'MoveToOS-response"
  (cl:format cl:nil "bool success~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MoveToOS-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MoveToOS-response>))
  "Converts a ROS message object to a list"
  (cl:list 'MoveToOS-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'MoveToOS)))
  'MoveToOS-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'MoveToOS)))
  'MoveToOS-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MoveToOS)))
  "Returns string type for a service object of type '<MoveToOS>"
  "robot_control/MoveToOS")