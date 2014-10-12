; Auto-generated. Do not edit!


(cl:in-package ball_detection-msg)


;//! \htmlinclude midpoints.msg.html

(cl:defclass <midpoints> (roslisp-msg-protocol:ros-message)
  ((x_blue
    :reader x_blue
    :initarg :x_blue
    :type cl:integer
    :initform 0)
   (y_blue
    :reader y_blue
    :initarg :y_blue
    :type cl:integer
    :initform 0)
   (x_yellow
    :reader x_yellow
    :initarg :x_yellow
    :type cl:integer
    :initform 0)
   (y_yellow
    :reader y_yellow
    :initarg :y_yellow
    :type cl:integer
    :initform 0)
   (x_red
    :reader x_red
    :initarg :x_red
    :type cl:integer
    :initform 0)
   (y_red
    :reader y_red
    :initarg :y_red
    :type cl:integer
    :initform 0)
   (x_green
    :reader x_green
    :initarg :x_green
    :type cl:integer
    :initform 0)
   (y_green
    :reader y_green
    :initarg :y_green
    :type cl:integer
    :initform 0))
)

(cl:defclass midpoints (<midpoints>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <midpoints>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'midpoints)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ball_detection-msg:<midpoints> is deprecated: use ball_detection-msg:midpoints instead.")))

(cl:ensure-generic-function 'x_blue-val :lambda-list '(m))
(cl:defmethod x_blue-val ((m <midpoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-msg:x_blue-val is deprecated.  Use ball_detection-msg:x_blue instead.")
  (x_blue m))

(cl:ensure-generic-function 'y_blue-val :lambda-list '(m))
(cl:defmethod y_blue-val ((m <midpoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-msg:y_blue-val is deprecated.  Use ball_detection-msg:y_blue instead.")
  (y_blue m))

(cl:ensure-generic-function 'x_yellow-val :lambda-list '(m))
(cl:defmethod x_yellow-val ((m <midpoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-msg:x_yellow-val is deprecated.  Use ball_detection-msg:x_yellow instead.")
  (x_yellow m))

(cl:ensure-generic-function 'y_yellow-val :lambda-list '(m))
(cl:defmethod y_yellow-val ((m <midpoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-msg:y_yellow-val is deprecated.  Use ball_detection-msg:y_yellow instead.")
  (y_yellow m))

(cl:ensure-generic-function 'x_red-val :lambda-list '(m))
(cl:defmethod x_red-val ((m <midpoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-msg:x_red-val is deprecated.  Use ball_detection-msg:x_red instead.")
  (x_red m))

(cl:ensure-generic-function 'y_red-val :lambda-list '(m))
(cl:defmethod y_red-val ((m <midpoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-msg:y_red-val is deprecated.  Use ball_detection-msg:y_red instead.")
  (y_red m))

(cl:ensure-generic-function 'x_green-val :lambda-list '(m))
(cl:defmethod x_green-val ((m <midpoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-msg:x_green-val is deprecated.  Use ball_detection-msg:x_green instead.")
  (x_green m))

(cl:ensure-generic-function 'y_green-val :lambda-list '(m))
(cl:defmethod y_green-val ((m <midpoints>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-msg:y_green-val is deprecated.  Use ball_detection-msg:y_green instead.")
  (y_green m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <midpoints>) ostream)
  "Serializes a message object of type '<midpoints>"
  (cl:let* ((signed (cl:slot-value msg 'x_blue)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'y_blue)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'x_yellow)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'y_yellow)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'x_red)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'y_red)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'x_green)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'y_green)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <midpoints>) istream)
  "Deserializes a message object of type '<midpoints>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'x_blue) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'y_blue) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'x_yellow) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'y_yellow) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'x_red) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'y_red) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'x_green) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'y_green) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<midpoints>)))
  "Returns string type for a message object of type '<midpoints>"
  "ball_detection/midpoints")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'midpoints)))
  "Returns string type for a message object of type 'midpoints"
  "ball_detection/midpoints")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<midpoints>)))
  "Returns md5sum for a message object of type '<midpoints>"
  "c49b7ac74776a47d415a17d96ee8bc0b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'midpoints)))
  "Returns md5sum for a message object of type 'midpoints"
  "c49b7ac74776a47d415a17d96ee8bc0b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<midpoints>)))
  "Returns full string definition for message of type '<midpoints>"
  (cl:format cl:nil "int32 x_blue~%int32 y_blue~%int32 x_yellow~%int32 y_yellow~%int32 x_red~%int32 y_red~%int32 x_green~%int32 y_green~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'midpoints)))
  "Returns full string definition for message of type 'midpoints"
  (cl:format cl:nil "int32 x_blue~%int32 y_blue~%int32 x_yellow~%int32 y_yellow~%int32 x_red~%int32 y_red~%int32 x_green~%int32 y_green~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <midpoints>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <midpoints>))
  "Converts a ROS message object to a list"
  (cl:list 'midpoints
    (cl:cons ':x_blue (x_blue msg))
    (cl:cons ':y_blue (y_blue msg))
    (cl:cons ':x_yellow (x_yellow msg))
    (cl:cons ':y_yellow (y_yellow msg))
    (cl:cons ':x_red (x_red msg))
    (cl:cons ':y_red (y_red msg))
    (cl:cons ':x_green (x_green msg))
    (cl:cons ':y_green (y_green msg))
))
