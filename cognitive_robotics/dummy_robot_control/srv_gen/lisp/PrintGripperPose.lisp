; Auto-generated. Do not edit!


(cl:in-package dummy_robot_control-srv)


;//! \htmlinclude PrintGripperPose-request.msg.html

(cl:defclass <PrintGripperPose-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass PrintGripperPose-request (<PrintGripperPose-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PrintGripperPose-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PrintGripperPose-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dummy_robot_control-srv:<PrintGripperPose-request> is deprecated: use dummy_robot_control-srv:PrintGripperPose-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PrintGripperPose-request>) ostream)
  "Serializes a message object of type '<PrintGripperPose-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PrintGripperPose-request>) istream)
  "Deserializes a message object of type '<PrintGripperPose-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PrintGripperPose-request>)))
  "Returns string type for a service object of type '<PrintGripperPose-request>"
  "dummy_robot_control/PrintGripperPoseRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PrintGripperPose-request)))
  "Returns string type for a service object of type 'PrintGripperPose-request"
  "dummy_robot_control/PrintGripperPoseRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PrintGripperPose-request>)))
  "Returns md5sum for a message object of type '<PrintGripperPose-request>"
  "cc153912f1453b708d221682bc23d9ac")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PrintGripperPose-request)))
  "Returns md5sum for a message object of type 'PrintGripperPose-request"
  "cc153912f1453b708d221682bc23d9ac")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PrintGripperPose-request>)))
  "Returns full string definition for message of type '<PrintGripperPose-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PrintGripperPose-request)))
  "Returns full string definition for message of type 'PrintGripperPose-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PrintGripperPose-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PrintGripperPose-request>))
  "Converts a ROS message object to a list"
  (cl:list 'PrintGripperPose-request
))
;//! \htmlinclude PrintGripperPose-response.msg.html

(cl:defclass <PrintGripperPose-response> (roslisp-msg-protocol:ros-message)
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

(cl:defclass PrintGripperPose-response (<PrintGripperPose-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PrintGripperPose-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PrintGripperPose-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dummy_robot_control-srv:<PrintGripperPose-response> is deprecated: use dummy_robot_control-srv:PrintGripperPose-response instead.")))

(cl:ensure-generic-function 'x-val :lambda-list '(m))
(cl:defmethod x-val ((m <PrintGripperPose-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dummy_robot_control-srv:x-val is deprecated.  Use dummy_robot_control-srv:x instead.")
  (x m))

(cl:ensure-generic-function 'y-val :lambda-list '(m))
(cl:defmethod y-val ((m <PrintGripperPose-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dummy_robot_control-srv:y-val is deprecated.  Use dummy_robot_control-srv:y instead.")
  (y m))

(cl:ensure-generic-function 'z-val :lambda-list '(m))
(cl:defmethod z-val ((m <PrintGripperPose-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dummy_robot_control-srv:z-val is deprecated.  Use dummy_robot_control-srv:z instead.")
  (z m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PrintGripperPose-response>) ostream)
  "Serializes a message object of type '<PrintGripperPose-response>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PrintGripperPose-response>) istream)
  "Deserializes a message object of type '<PrintGripperPose-response>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PrintGripperPose-response>)))
  "Returns string type for a service object of type '<PrintGripperPose-response>"
  "dummy_robot_control/PrintGripperPoseResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PrintGripperPose-response)))
  "Returns string type for a service object of type 'PrintGripperPose-response"
  "dummy_robot_control/PrintGripperPoseResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PrintGripperPose-response>)))
  "Returns md5sum for a message object of type '<PrintGripperPose-response>"
  "cc153912f1453b708d221682bc23d9ac")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PrintGripperPose-response)))
  "Returns md5sum for a message object of type 'PrintGripperPose-response"
  "cc153912f1453b708d221682bc23d9ac")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PrintGripperPose-response>)))
  "Returns full string definition for message of type '<PrintGripperPose-response>"
  (cl:format cl:nil "float32 x~%float32 y~%float32 z~%~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PrintGripperPose-response)))
  "Returns full string definition for message of type 'PrintGripperPose-response"
  (cl:format cl:nil "float32 x~%float32 y~%float32 z~%~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PrintGripperPose-response>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PrintGripperPose-response>))
  "Converts a ROS message object to a list"
  (cl:list 'PrintGripperPose-response
    (cl:cons ':x (x msg))
    (cl:cons ':y (y msg))
    (cl:cons ':z (z msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'PrintGripperPose)))
  'PrintGripperPose-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'PrintGripperPose)))
  'PrintGripperPose-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PrintGripperPose)))
  "Returns string type for a service object of type '<PrintGripperPose>"
  "dummy_robot_control/PrintGripperPose")