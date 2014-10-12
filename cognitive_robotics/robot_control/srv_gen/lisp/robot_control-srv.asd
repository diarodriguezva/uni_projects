
(cl:in-package :asdf)

(defsystem "robot_control-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "MoveJoints" :depends-on ("_package_MoveJoints"))
    (:file "_package_MoveJoints" :depends-on ("_package"))
    (:file "PrintGripperPose" :depends-on ("_package_PrintGripperPose"))
    (:file "_package_PrintGripperPose" :depends-on ("_package"))
    (:file "MoveToOS" :depends-on ("_package_MoveToOS"))
    (:file "_package_MoveToOS" :depends-on ("_package"))
    (:file "MoveToCS" :depends-on ("_package_MoveToCS"))
    (:file "_package_MoveToCS" :depends-on ("_package"))
    (:file "PrintPose" :depends-on ("_package_PrintPose"))
    (:file "_package_PrintPose" :depends-on ("_package"))
  ))