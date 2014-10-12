; Auto-generated. Do not edit!


(cl:in-package world-srv)


;//! \htmlinclude is_cam_moving_service-request.msg.html

(cl:defclass <is_cam_moving_service-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass is_cam_moving_service-request (<is_cam_moving_service-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <is_cam_moving_service-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'is_cam_moving_service-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name world-srv:<is_cam_moving_service-request> is deprecated: use world-srv:is_cam_moving_service-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <is_cam_moving_service-request>) ostream)
  "Serializes a message object of type '<is_cam_moving_service-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <is_cam_moving_service-request>) istream)
  "Deserializes a message object of type '<is_cam_moving_service-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<is_cam_moving_service-request>)))
  "Returns string type for a service object of type '<is_cam_moving_service-request>"
  "world/is_cam_moving_serviceRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'is_cam_moving_service-request)))
  "Returns string type for a service object of type 'is_cam_moving_service-request"
  "world/is_cam_moving_serviceRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<is_cam_moving_service-request>)))
  "Returns md5sum for a message object of type '<is_cam_moving_service-request>"
  "4f5186cce6f51e3392e21dd852d2725e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'is_cam_moving_service-request)))
  "Returns md5sum for a message object of type 'is_cam_moving_service-request"
  "4f5186cce6f51e3392e21dd852d2725e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<is_cam_moving_service-request>)))
  "Returns full string definition for message of type '<is_cam_moving_service-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'is_cam_moving_service-request)))
  "Returns full string definition for message of type 'is_cam_moving_service-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <is_cam_moving_service-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <is_cam_moving_service-request>))
  "Converts a ROS message object to a list"
  (cl:list 'is_cam_moving_service-request
))
;//! \htmlinclude is_cam_moving_service-response.msg.html

(cl:defclass <is_cam_moving_service-response> (roslisp-msg-protocol:ros-message)
  ((cam_state
    :reader cam_state
    :initarg :cam_state
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass is_cam_moving_service-response (<is_cam_moving_service-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <is_cam_moving_service-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'is_cam_moving_service-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name world-srv:<is_cam_moving_service-response> is deprecated: use world-srv:is_cam_moving_service-response instead.")))

(cl:ensure-generic-function 'cam_state-val :lambda-list '(m))
(cl:defmethod cam_state-val ((m <is_cam_moving_service-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world-srv:cam_state-val is deprecated.  Use world-srv:cam_state instead.")
  (cam_state m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <is_cam_moving_service-response>) ostream)
  "Serializes a message object of type '<is_cam_moving_service-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'cam_state) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <is_cam_moving_service-response>) istream)
  "Deserializes a message object of type '<is_cam_moving_service-response>"
    (cl:setf (cl:slot-value msg 'cam_state) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<is_cam_moving_service-response>)))
  "Returns string type for a service object of type '<is_cam_moving_service-response>"
  "world/is_cam_moving_serviceResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'is_cam_moving_service-response)))
  "Returns string type for a service object of type 'is_cam_moving_service-response"
  "world/is_cam_moving_serviceResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<is_cam_moving_service-response>)))
  "Returns md5sum for a message object of type '<is_cam_moving_service-response>"
  "4f5186cce6f51e3392e21dd852d2725e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'is_cam_moving_service-response)))
  "Returns md5sum for a message object of type 'is_cam_moving_service-response"
  "4f5186cce6f51e3392e21dd852d2725e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<is_cam_moving_service-response>)))
  "Returns full string definition for message of type '<is_cam_moving_service-response>"
  (cl:format cl:nil "bool cam_state~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'is_cam_moving_service-response)))
  "Returns full string definition for message of type 'is_cam_moving_service-response"
  (cl:format cl:nil "bool cam_state~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <is_cam_moving_service-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <is_cam_moving_service-response>))
  "Converts a ROS message object to a list"
  (cl:list 'is_cam_moving_service-response
    (cl:cons ':cam_state (cam_state msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'is_cam_moving_service)))
  'is_cam_moving_service-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'is_cam_moving_service)))
  'is_cam_moving_service-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'is_cam_moving_service)))
  "Returns string type for a service object of type '<is_cam_moving_service>"
  "world/is_cam_moving_service")