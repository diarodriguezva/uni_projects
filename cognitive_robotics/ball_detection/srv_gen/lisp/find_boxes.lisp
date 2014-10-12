; Auto-generated. Do not edit!


(cl:in-package ball_detection-srv)


;//! \htmlinclude find_boxes-request.msg.html

(cl:defclass <find_boxes-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass find_boxes-request (<find_boxes-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <find_boxes-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'find_boxes-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ball_detection-srv:<find_boxes-request> is deprecated: use ball_detection-srv:find_boxes-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <find_boxes-request>) ostream)
  "Serializes a message object of type '<find_boxes-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <find_boxes-request>) istream)
  "Deserializes a message object of type '<find_boxes-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<find_boxes-request>)))
  "Returns string type for a service object of type '<find_boxes-request>"
  "ball_detection/find_boxesRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'find_boxes-request)))
  "Returns string type for a service object of type 'find_boxes-request"
  "ball_detection/find_boxesRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<find_boxes-request>)))
  "Returns md5sum for a message object of type '<find_boxes-request>"
  "ca3cd3dd6596c92aacbb3410f2ee428a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'find_boxes-request)))
  "Returns md5sum for a message object of type 'find_boxes-request"
  "ca3cd3dd6596c92aacbb3410f2ee428a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<find_boxes-request>)))
  "Returns full string definition for message of type '<find_boxes-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'find_boxes-request)))
  "Returns full string definition for message of type 'find_boxes-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <find_boxes-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <find_boxes-request>))
  "Converts a ROS message object to a list"
  (cl:list 'find_boxes-request
))
;//! \htmlinclude find_boxes-response.msg.html

(cl:defclass <find_boxes-response> (roslisp-msg-protocol:ros-message)
  ((x_min
    :reader x_min
    :initarg :x_min
    :type (cl:vector cl:integer)
   :initform (cl:make-array 3 :element-type 'cl:integer :initial-element 0))
   (x_max
    :reader x_max
    :initarg :x_max
    :type (cl:vector cl:integer)
   :initform (cl:make-array 3 :element-type 'cl:integer :initial-element 0))
   (y_min
    :reader y_min
    :initarg :y_min
    :type (cl:vector cl:integer)
   :initform (cl:make-array 3 :element-type 'cl:integer :initial-element 0))
   (y_max
    :reader y_max
    :initarg :y_max
    :type (cl:vector cl:integer)
   :initform (cl:make-array 3 :element-type 'cl:integer :initial-element 0))
   (color
    :reader color
    :initarg :color
    :type (cl:vector cl:string)
   :initform (cl:make-array 3 :element-type 'cl:string :initial-element "")))
)

(cl:defclass find_boxes-response (<find_boxes-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <find_boxes-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'find_boxes-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ball_detection-srv:<find_boxes-response> is deprecated: use ball_detection-srv:find_boxes-response instead.")))

(cl:ensure-generic-function 'x_min-val :lambda-list '(m))
(cl:defmethod x_min-val ((m <find_boxes-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-srv:x_min-val is deprecated.  Use ball_detection-srv:x_min instead.")
  (x_min m))

(cl:ensure-generic-function 'x_max-val :lambda-list '(m))
(cl:defmethod x_max-val ((m <find_boxes-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-srv:x_max-val is deprecated.  Use ball_detection-srv:x_max instead.")
  (x_max m))

(cl:ensure-generic-function 'y_min-val :lambda-list '(m))
(cl:defmethod y_min-val ((m <find_boxes-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-srv:y_min-val is deprecated.  Use ball_detection-srv:y_min instead.")
  (y_min m))

(cl:ensure-generic-function 'y_max-val :lambda-list '(m))
(cl:defmethod y_max-val ((m <find_boxes-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-srv:y_max-val is deprecated.  Use ball_detection-srv:y_max instead.")
  (y_max m))

(cl:ensure-generic-function 'color-val :lambda-list '(m))
(cl:defmethod color-val ((m <find_boxes-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ball_detection-srv:color-val is deprecated.  Use ball_detection-srv:color instead.")
  (color m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <find_boxes-response>) ostream)
  "Serializes a message object of type '<find_boxes-response>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'x_min))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'x_max))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'y_min))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'y_max))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((__ros_str_len (cl:length ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) ele))
   (cl:slot-value msg 'color))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <find_boxes-response>) istream)
  "Deserializes a message object of type '<find_boxes-response>"
  (cl:setf (cl:slot-value msg 'x_min) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'x_min)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))))
  (cl:setf (cl:slot-value msg 'x_max) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'x_max)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))))
  (cl:setf (cl:slot-value msg 'y_min) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'y_min)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))))
  (cl:setf (cl:slot-value msg 'y_max) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'y_max)))
    (cl:dotimes (i 3)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))))
  (cl:setf (cl:slot-value msg 'color) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'color)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<find_boxes-response>)))
  "Returns string type for a service object of type '<find_boxes-response>"
  "ball_detection/find_boxesResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'find_boxes-response)))
  "Returns string type for a service object of type 'find_boxes-response"
  "ball_detection/find_boxesResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<find_boxes-response>)))
  "Returns md5sum for a message object of type '<find_boxes-response>"
  "ca3cd3dd6596c92aacbb3410f2ee428a")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'find_boxes-response)))
  "Returns md5sum for a message object of type 'find_boxes-response"
  "ca3cd3dd6596c92aacbb3410f2ee428a")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<find_boxes-response>)))
  "Returns full string definition for message of type '<find_boxes-response>"
  (cl:format cl:nil "int32[3] x_min~%int32[3] x_max~%int32[3] y_min~%int32[3] y_max~%string[3] color~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'find_boxes-response)))
  "Returns full string definition for message of type 'find_boxes-response"
  (cl:format cl:nil "int32[3] x_min~%int32[3] x_max~%int32[3] y_min~%int32[3] y_max~%string[3] color~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <find_boxes-response>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'x_min) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'x_max) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'y_min) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'y_max) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'color) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4 (cl:length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <find_boxes-response>))
  "Converts a ROS message object to a list"
  (cl:list 'find_boxes-response
    (cl:cons ':x_min (x_min msg))
    (cl:cons ':x_max (x_max msg))
    (cl:cons ':y_min (y_min msg))
    (cl:cons ':y_max (y_max msg))
    (cl:cons ':color (color msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'find_boxes)))
  'find_boxes-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'find_boxes)))
  'find_boxes-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'find_boxes)))
  "Returns string type for a service object of type '<find_boxes>"
  "ball_detection/find_boxes")