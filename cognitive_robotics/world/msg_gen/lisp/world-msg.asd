
(cl:in-package :asdf)

(defsystem "world-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "is_cam_moving_msg" :depends-on ("_package_is_cam_moving_msg"))
    (:file "_package_is_cam_moving_msg" :depends-on ("_package"))
  ))