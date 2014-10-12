function [tau] = PD_regelung(roboter_soll, roboter_ist)
%Entkoppelte Einzelgelenkregelung durch PD-Regler

%1. Regelparameter Kp, Kd: aperiodisches Einschwingen
lambda=30.0;
Kp=lambda*lambda;
Kd=2.0*lambda;

%2. Regelgesetz
%   roboter_soll.q: Sollposition
%   roboter_ist.q:  Istposition
tau = Kp *(roboter_soll.q-roboter_ist.q) +...
    Kd *(roboter_soll.dot_q-roboter_ist.dot_q);
end

