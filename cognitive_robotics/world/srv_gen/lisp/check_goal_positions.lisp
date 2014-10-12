; Auto-generated. Do not edit!


(cl:in-package world-srv)


;//! \htmlinclude check_goal_positions-request.msg.html

(cl:defclass <check_goal_positions-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass check_goal_positions-request (<check_goal_positions-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <check_goal_positions-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'check_goal_positions-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name world-srv:<check_goal_positions-request> is deprecated: use world-srv:check_goal_positions-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <check_goal_positions-request>) ostream)
  "Serializes a message object of type '<check_goal_positions-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <check_goal_positions-request>) istream)
  "Deserializes a message object of type '<check_goal_positions-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<check_goal_positions-request>)))
  "Returns string type for a service object of type '<check_goal_positions-request>"
  "world/check_goal_positionsRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'check_goal_positions-request)))
  "Returns string type for a service object of type 'check_goal_positions-request"
  "world/check_goal_positionsRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<check_goal_positions-request>)))
  "Returns md5sum for a message object of type '<check_goal_positions-request>"
  "001fde3cab9e313a150416ff09c08ee4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'check_goal_positions-request)))
  "Returns md5sum for a message object of type 'check_goal_positions-request"
  "001fde3cab9e313a150416ff09c08ee4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<check_goal_positions-request>)))
  "Returns full string definition for message of type '<check_goal_positions-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'check_goal_positions-request)))
  "Returns full string definition for message of type 'check_goal_positions-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <check_goal_positions-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <check_goal_positions-request>))
  "Converts a ROS message object to a list"
  (cl:list 'check_goal_positions-request
))
;//! \htmlinclude check_goal_positions-response.msg.html

(cl:defclass <check_goal_positions-response> (roslisp-msg-protocol:ros-message)
  ((state
    :reader state
    :initarg :state
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass check_goal_positions-response (<check_goal_positions-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <check_goal_positions-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'check_goal_positions-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name world-srv:<check_goal_positions-response> is deprecated: use world-srv:check_goal_positions-response instead.")))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <check_goal_positions-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader world-srv:state-val is deprecated.  Use world-srv:state instead.")
  (state m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <check_goal_positions-response>) ostream)
  "Serializes a message object of type '<check_goal_positions-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'state) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <check_goal_positions-response>) istream)
  "Deserializes a message object of type '<check_goal_positions-response>"
    (cl:setf (cl:slot-value msg 'state) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<check_goal_positions-response>)))
  "Returns string type for a service object of type '<check_goal_positions-response>"
  "world/check_goal_positionsResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'check_goal_positions-response)))
  "Returns string type for a service object of type 'check_goal_positions-response"
  "world/check_goal_positionsResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<check_goal_positions-response>)))
  "Returns md5sum for a message object of type '<check_goal_positions-response>"
  "001fde3cab9e313a150416ff09c08ee4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'check_goal_positions-response)))
  "Returns md5sum for a message object of type 'check_goal_positions-response"
  "001fde3cab9e313a150416ff09c08ee4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<check_goal_positions-response>)))
  "Returns full string definition for message of type '<check_goal_positions-response>"
  (cl:format cl:nil "bool state~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'check_goal_positions-response)))
  "Returns full string definition for message of type 'check_goal_positions-response"
  (cl:format cl:nil "bool state~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <check_goal_positions-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <check_goal_positions-response>))
  "Converts a ROS message object to a list"
  (cl:list 'check_goal_positions-response
    (cl:cons ':state (state msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'check_goal_positions)))
  'check_goal_positions-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'check_goal_positions)))
  'check_goal_positions-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'check_goal_positions)))
  "Returns string type for a service object of type '<check_goal_positions>"
  "world/check_goal_positions")