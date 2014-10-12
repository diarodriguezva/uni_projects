function [tau] = FFLin_regelung(roboter_soll, roboter_ist)
%Vereinfachte Implementierung der Feedforward-Linearisierung: 
%Vorsteuerung der Kraefte aus der inversen Dynamik fuer die Sollbahn
%+lineare Regelung (hier nur entkoppelt PD-Regler)
% Besseres Regelungs-Verhalten mit Beruecksichtigung der dynamischen
% Kopplungen der Gelenke waere ueber einen Mehrgroessenregler moeglich
% (siehe Skript). Auf die Linearisierung der BGL wurde hier verzichtet.

%%1. Regelparameter Kp, Kd: aperiodisches Einschwingen
lambda=30.0;
Kp=lambda*lambda;
Kd=2.0*lambda;

%%2. Regelgesetz
%roboter_soll.q: Sollposition
%roboter_ist.q:  Istposition

%% 2.2 Inverse Dynamik fuer Sollwerte zur Vorsteuerung berechnen
roboter_soll=berechne_id(roboter_soll);
%Stellkraefte zurueckgeben
tau= roboter_soll.tau_id + Kp*(roboter_soll.q-roboter_ist.q) + Kd*(roboter_soll.dot_q-roboter_ist.dot_q);
end

