; Auto-generated. Do not edit!


(cl:in-package world-msg)


;//! \htmlinclude is_cam_moving_msg.msg.html

(cl:defclass <is_cam_moving_msg> (roslisp-msg-protocol:ros-message)
  ((cam_state
    :reader cam_state
    :initarg :cam_state
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass is_cam_moving_msg (<is_cam_moving_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <is_cam_moving_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'is_cam_moving_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name world-msg:<is_cam_moving_msg> is deprecated: use world-msg:is_cam_moving_msg instead.")))

(cl:ensure-generic-function 'cam_state-val :lambda-list '(m))
(cl:defmethod cam_state-val ((m <is_cam_moving_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world-msg:cam_state-val is deprecated.  Use world-msg:cam_state instead.")
  (cam_state m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <is_cam_moving_msg>) ostream)
  "Serializes a message object of type '<is_cam_moving_msg>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'cam_state) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <is_cam_moving_msg>) istream)
  "Deserializes a message object of type '<is_cam_moving_msg>"
    (cl:setf (cl:slot-value msg 'cam_state) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<is_cam_moving_msg>)))
  "Returns string type for a message object of type '<is_cam_moving_msg>"
  "world/is_cam_moving_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'is_cam_moving_msg)))
  "Returns string type for a message object of type 'is_cam_moving_msg"
  "world/is_cam_moving_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<is_cam_moving_msg>)))
  "Returns md5sum for a message object of type '<is_cam_moving_msg>"
  "4f5186cce6f51e3392e21dd852d2725e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'is_cam_moving_msg)))
  "Returns md5sum for a message object of type 'is_cam_moving_msg"
  "4f5186cce6f51e3392e21dd852d2725e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<is_cam_moving_msg>)))
  "Returns full string definition for message of type '<is_cam_moving_msg>"
  (cl:format cl:nil "bool cam_state~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'is_cam_moving_msg)))
  "Returns full string definition for message of type 'is_cam_moving_msg"
  (cl:format cl:nil "bool cam_state~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <is_cam_moving_msg>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <is_cam_moving_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'is_cam_moving_msg
    (cl:cons ':cam_state (cam_state msg))
))
