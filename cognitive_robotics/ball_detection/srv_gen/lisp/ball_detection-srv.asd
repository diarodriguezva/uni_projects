
(cl:in-package :asdf)

(defsystem "ball_detection-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "find_balls" :depends-on ("_package_find_balls"))
    (:file "_package_find_balls" :depends-on ("_package"))
    (:file "find_boxes" :depends-on ("_package_find_boxes"))
    (:file "_package_find_boxes" :depends-on ("_package"))
  ))