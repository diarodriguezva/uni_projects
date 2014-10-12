
(cl:in-package :asdf)

(defsystem "ball_detection-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Detection" :depends-on ("_package_Detection"))
    (:file "_package_Detection" :depends-on ("_package"))
    (:file "midpoints" :depends-on ("_package_midpoints"))
    (:file "_package_midpoints" :depends-on ("_package"))
  ))