function [tau] = FBLin_regelung(roboter_soll, roboter_ist)
%Feedback Linearisierung: 
%Nichtlineare Entkopplung und Linearisierung durch Invertierung des
%Systemmodells

%%1. Regelparameter Kp, Kd: aperiodisches Einschwingen
lambda=30.0;
Kp=lambda*lambda;
Kd=2.0*lambda;

%%2. Regelgesetz
%roboter_soll.q: Sollposition
%roboter_ist.q:  Istposition

%%Rueckfuehrung (Feedback) des Ist-Zustands
q_merk=roboter_soll.q;
dot_q_merk=roboter_soll.dot_q;

%Soll-Beschleunigung aus Gewuenschter (linearer) Fehlerdynamik 
roboter_soll.ddot_q=roboter_soll.ddot_q+Kp*(roboter_soll.q-roboter_ist.q) + Kd*(roboter_soll.dot_q-roboter_ist.dot_q);

%Ist-Werte in das Modell Uebernehmen:
%dies entspricht der Messung/Sensordatenerfassung
%im realen System
%(Rueckfuehrung zur Linearisierung)
roboter_soll.q=roboter_ist.q;
roboter_soll.dot_q=roboter_ist.dot_q;

%nichtlineare Dynamik des Systems (Inverse Dynamik) berechnen
%dies entspricht der Entkopplung
roboter_soll=berechne_id(roboter_soll);
%Stellkraefte, die gemaess dem Dynamik-Modell der Gewuenschten
%Beschleunigung entsprechen
tau = roboter_soll.tau_id;

%alte Werte zurueckschreiben
roboter_soll.q=q_merk;
roboter_soll.dot_q=dot_q_merk;
%nochmals DK berechnen, damit in der Ausgabe auch die Sollwerte erscheinen
%da diese durch Funktionsaufruf berechne_id() ueberschrieben
roboter_soll=berechne_dk_positionen(roboter_soll);
end

