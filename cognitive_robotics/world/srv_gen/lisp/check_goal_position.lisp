; Auto-generated. Do not edit!


(cl:in-package world-srv)


;//! \htmlinclude check_goal_position-request.msg.html

(cl:defclass <check_goal_position-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass check_goal_position-request (<check_goal_position-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <check_goal_position-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'check_goal_position-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name world-srv:<check_goal_position-request> is deprecated: use world-srv:check_goal_position-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <check_goal_position-request>) ostream)
  "Serializes a message object of type '<check_goal_position-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <check_goal_position-request>) istream)
  "Deserializes a message object of type '<check_goal_position-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<check_goal_position-request>)))
  "Returns string type for a service object of type '<check_goal_position-request>"
  "world/check_goal_positionRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'check_goal_position-request)))
  "Returns string type for a service object of type 'check_goal_position-request"
  "world/check_goal_positionRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<check_goal_position-request>)))
  "Returns md5sum for a message object of type '<check_goal_position-request>"
  "001fde3cab9e313a150416ff09c08ee4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'check_goal_position-request)))
  "Returns md5sum for a message object of type 'check_goal_position-request"
  "001fde3cab9e313a150416ff09c08ee4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<check_goal_position-request>)))
  "Returns full string definition for message of type '<check_goal_position-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'check_goal_position-request)))
  "Returns full string definition for message of type 'check_goal_position-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <check_goal_position-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <check_goal_position-request>))
  "Converts a ROS message object to a list"
  (cl:list 'check_goal_position-request
))
;//! \htmlinclude check_goal_position-response.msg.html

(cl:defclass <check_goal_position-response> (roslisp-msg-protocol:ros-message)
  ((state
    :reader state
    :initarg :state
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass check_goal_position-response (<check_goal_position-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <check_goal_position-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'check_goal_position-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name world-srv:<check_goal_position-response> is deprecated: use world-srv:check_goal_position-response instead.")))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <check_goal_position-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world-srv:state-val is deprecated.  Use world-srv:state instead.")
  (state m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <check_goal_position-response>) ostream)
  "Serializes a message object of type '<check_goal_position-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'state) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <check_goal_position-response>) istream)
  "Deserializes a message object of type '<check_goal_position-response>"
    (cl:setf (cl:slot-value msg 'state) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<check_goal_position-response>)))
  "Returns string type for a service object of type '<check_goal_position-response>"
  "world/check_goal_positionResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'check_goal_position-response)))
  "Returns string type for a service object of type 'check_goal_position-response"
  "world/check_goal_positionResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<check_goal_position-response>)))
  "Returns md5sum for a message object of type '<check_goal_position-response>"
  "001fde3cab9e313a150416ff09c08ee4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'check_goal_position-response)))
  "Returns md5sum for a message object of type 'check_goal_position-response"
  "001fde3cab9e313a150416ff09c08ee4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<check_goal_position-response>)))
  "Returns full string definition for message of type '<check_goal_position-response>"
  (cl:format cl:nil "bool state~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'check_goal_position-response)))
  "Returns full string definition for message of type 'check_goal_position-response"
  (cl:format cl:nil "bool state~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <check_goal_position-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <check_goal_position-response>))
  "Converts a ROS message object to a list"
  (cl:list 'check_goal_position-response
    (cl:cons ':state (state msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'check_goal_position)))
  'check_goal_position-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'check_goal_position)))
  'check_goal_position-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'check_goal_position)))
  "Returns string type for a service object of type '<check_goal_position>"
  "world/check_goal_position")