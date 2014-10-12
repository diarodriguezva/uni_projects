; Auto-generated. Do not edit!


(cl:in-package dummy_robot_control-srv)


;//! \htmlinclude PrintPose-request.msg.html

(cl:defclass <PrintPose-request> (roslisp-msg-protocol:ros-message)
  ((effector
    :reader effector
    :initarg :effector
    :type cl:string
    :initform ""))
)

(cl:defclass PrintPose-request (<PrintPose-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PrintPose-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PrintPose-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dummy_robot_control-srv:<PrintPose-request> is deprecated: use dummy_robot_control-srv:PrintPose-request instead.")))

(cl:ensure-generic-function 'effector-val :lambda-list '(m))
(cl:defmethod effector-val ((m <PrintPose-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dummy_robot_control-srv:effector-val is deprecated.  Use dummy_robot_control-srv:effector instead.")
  (effector m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PrintPose-request>) ostream)
  "Serializes a message object of type '<PrintPose-request>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'effector))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'effector))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PrintPose-request>) istream)
  "Deserializes a message object of type '<PrintPose-request>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'effector) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'effector) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PrintPose-request>)))
  "Returns string type for a service object of type '<PrintPose-request>"
  "dummy_robot_control/PrintPoseRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PrintPose-request)))
  "Returns string type for a service object of type 'PrintPose-request"
  "dummy_robot_control/PrintPoseRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PrintPose-request>)))
  "Returns md5sum for a message object of type '<PrintPose-request>"
  "d0ffb32f80ee108381d60594e2651233")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PrintPose-request)))
  "Returns md5sum for a message object of type 'PrintPose-request"
  "d0ffb32f80ee108381d60594e2651233")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PrintPose-request>)))
  "Returns full string definition for message of type '<PrintPose-request>"
  (cl:format cl:nil "string effector~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PrintPose-request)))
  "Returns full string definition for message of type 'PrintPose-request"
  (cl:format cl:nil "string effector~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PrintPose-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'effector))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PrintPose-request>))
  "Converts a ROS message object to a list"
  (cl:list 'PrintPose-request
    (cl:cons ':effector (effector msg))
))
;//! \htmlinclude PrintPose-response.msg.html

(cl:defclass <PrintPose-response> (roslisp-msg-protocol:ros-message)
  ((x
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

(cl:defclass PrintPose-response (<PrintPose-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PrintPose-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PrintPose-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dummy_robot_control-srv:<PrintPose-response> is deprecated: use dummy_robot_control-srv:PrintPose-response instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <PrintPose-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dummy_robot_control-srv:x-val is deprecated.  Use dummy_robot_control-srv:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <PrintPose-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dummy_robot_control-srv:y-val is deprecated.  Use dummy_robot_control-srv:y instead.")
  (y m))

(cl:ensure-generic-function 'z-val :lambda-list '(m))
(cl:defmethod z-val ((m <PrintPose-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dummy_robot_control-srv:z-val is deprecated.  Use dummy_robot_control-srv:z instead.")
  (z m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PrintPose-response>) ostream)
  "Serializes a message object of type '<PrintPose-response>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PrintPose-response>) istream)
  "Deserializes a message object of type '<PrintPose-response>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PrintPose-response>)))
  "Returns string type for a service object of type '<PrintPose-response>"
  "dummy_robot_control/PrintPoseResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PrintPose-response)))
  "Returns string type for a service object of type 'PrintPose-response"
  "dummy_robot_control/PrintPoseResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PrintPose-response>)))
  "Returns md5sum for a message object of type '<PrintPose-response>"
  "d0ffb32f80ee108381d60594e2651233")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PrintPose-response)))
  "Returns md5sum for a message object of type 'PrintPose-response"
  "d0ffb32f80ee108381d60594e2651233")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PrintPose-response>)))
  "Returns full string definition for message of type '<PrintPose-response>"
  (cl:format cl:nil "float32 x~%float32 y~%float32 z~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PrintPose-response)))
  "Returns full string definition for message of type 'PrintPose-response"
  (cl:format cl:nil "float32 x~%float32 y~%float32 z~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PrintPose-response>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PrintPose-response>))
  "Converts a ROS message object to a list"
  (cl:list 'PrintPose-response
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':z (z msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'PrintPose)))
  'PrintPose-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'PrintPose)))
  'PrintPose-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PrintPose)))
  "Returns string type for a service object of type '<PrintPose>"
  "dummy_robot_control/PrintPose")