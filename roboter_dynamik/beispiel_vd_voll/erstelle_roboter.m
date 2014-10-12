function [roboter]=erstelle_roboter()
%Struktur (mit Parametern)  fuer Knickarm-Roboter mit drei Freiheitsgraden
%erstellen
%
% Die Parameter werden in der Struktur roboter und der darin enthaltenen 
% liste der Koerper kl (Koerper Liste) gespeichert

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%1.  Initialisierung der Daten des Roboters
% 1.1 Allgemeine Daten/Konstanten
roboter.N_Q=3;   %Anzahl der Freiheitsgrade (Dimension von q)
roboter.B0_g=[0;0;-9.81];  %Erdbeschleunigung
b1=0.08; %Breite Koerper 1
b2=0.05; %Breite Koerper 2
b3=0.03; %Breite Koerper 3
l1=0.5;  %Laenge Koerper 1
m1=3.0;  %Masse Koerper 1
l2=0.5;  %Laenge Koerper 2
m2=3.0;  %Masse Koerper 2
l3=0.5;  %Laenge Koerper 3
m3=2.0;  %Masse Koerper 3



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%1.2 erster Koerper: homogener Quader mit Dimension l1xb1xb1, Masse m1
%name
roboter.kl(1).name='koerper1';
% der koerper hat keinen Vorgaenger ==> Index=-1
roboter.kl(1).vorgaenger=-1;
% Freiheitsgrad, der vom Koerper belegt wird (d.h. hier theta=q(fhg_no)
roboter.kl(1).fhg_no=1;
% Geometriedaten (fuer Animations-Datei) : offset_x, offset_y, offset_z, laenge_x, laenge_y, laenge_z
roboter.kl(1).geometrie=[0,0,-0.5*l1,b1,b1,l1];
% masse
roboter.kl(1).m=m1;
%Schwerpunkt relativ zum Koerper-Ursprung: 0.5*Laenge in y-Richtung
roboter.kl(1).Bi_r_s=[0;l1*0.5;0];
%Traegheitstensor bezueglich des Koerper-Ursprungs
roboter.kl(1).I_o=[m1*(b1*b1/6.0),0,0;
    0,m1*(l1*l1/12.0+b1*b1/12.0+0.25*l1*l1),0;
    0,0,m1*(l1*l1/12.0+b1*b1/12.0+0.25*l1*l1)];
%DH-Parameter
roboter.kl(1).alpha=0.0;
roboter.kl(1).a=0;
roboter.kl(1).d=0;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%1.3 zweiter Koerper: homogener Quader mit l2xb2xb2, Masse m2
roboter.kl(2).name='koerper2';
% Vorgaenger ist 'koerper1'
roboter.kl(2).vorgaenger=1;
% Freiheitsgrad, der vom Koerper belegt wird (d.h. hier theta=q(fhg_no)
roboter.kl(2).fhg_no=2;
% Geometriedaten (fuer Animations-Datei) : offset_x, offset_y, offset_z, laenge_x, laenge_y, laenge_z
roboter.kl(2).geometrie=[0.5*l2,0,0,l2,b2,b2];
% masse
roboter.kl(2).m=m2;
% Schwerpunkt relativ zum Ursprung
roboter.kl(2).Bi_r_s=[l2*0.5;0;0];
% Traegheitstensor relativ zum Ursprung
roboter.kl(2).I_o= [m2*(b2*b2/6.0), 0, 0;
    0, m2*(l2*l2/12.0+b2*b2/12.0+0.25*l2*l2),0 ;
    0, 0, m2*(l2*l2/12.0+b2*b2/12.0+0.25*l2*l2)];
%DH-Parameter
roboter.kl(2).alpha=-pi/2.0;
roboter.kl(2).a=0;
roboter.kl(2).d=0;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%1.3 dritter Koerper: homogener Quader mit l3xb3xb3, Masse m3
roboter.kl(3).name='koerper3';
% Vorganger ist "koerper2"
roboter.kl(3).vorgaenger=2;
% Freiheitsgrad, der vom Koerper belegt wird (d.h. hier theta=q(fhg_no)
roboter.kl(3).fhg_no=3;
% Geometriedaten (fuer Animations-Datei) : offset_x, offset_y, offset_z, laenge_x, laenge_y, laenge_z
roboter.kl(3).geometrie=[0,0.5*l3,0,b3,l3,b3];
% Masse
roboter.kl(3).m=m3;
% Schwerpunkt relativ zum Ursprung
roboter.kl(3).Bi_r_s=[0.0;l3*0.5;0.0];
% Traegheitstensor relativ zum Ursprung
roboter.kl(3).I_o= [m3*(l3*l3/12.0+b3*b3/12.0+0.25*l3*l3), 0, 0;
    0, m3*(b3*b3/6.0), 0;
    0,0,m3*(l3*l3/12.0+b3*b3/12.0+0.25*l3*l3)];

roboter.kl(3).alpha=0.0;
roboter.kl(3).a=l2;
roboter.kl(3).d=0;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%1.4 Vektor zum TCP, relativ zum koerperfesten Koordinatensystem des letzten Koerpers
roboter.B3_r_3_tcp=[0;l3;0];



%%2. Zusaetzliche Daten
%2.1 File-IDs auf -1 setzen, damit die Dateien beim ersten Aufruf der Speicher-Funktion
% geoeffnet werden
roboter.animations_datei=zeros(length(roboter.kl),1);
for i=1:length(roboter.kl)
    roboter.animations_datei(i)=-1;
end

%%2.2 Vektor der generalisierten Koordinaten, Geschwindigkeiten und Beschleunigungen
roboter.q=zeros(roboter.N_Q,1);
roboter.dot_q=zeros(roboter.N_Q,1);
roboter.ddot_q=zeros(roboter.N_Q,1);

%%2.3 Dynamische Groessen fuer Bewegungsgleichung M*ddot_q+h=tau
roboter.M=zeros(roboter.N_Q,roboter.N_Q);
roboter.h=zeros(roboter.N_Q,1);
%2.4 Gelenkmomente aus inverser Dynamik
roboter.tau_id=zeros(roboter.N_Q,1);
%2.5 Gelenkmomente aus Regelung (Eingang)
roboter.tau_reg=zeros(roboter.N_Q,1);

%2.6 zeit beginnt bei 0
roboter.zeit=0;

%2.7 Werte der direkten Kinematik anlegen
for i=1:roboter.N_Q
    %Verschiebungsvektor vom Vorgaenger zum Koerper i im KOS des Vorgaengers (Bv)
    roboter.kl(i).Bv_r_vi=zeros(3,1);
    %Drehmatrix vom Vorgaenger zum i-ten Koerper
    roboter.kl(i).A_iv=eye(3);
    % Drehmatrix vom i-ten Koerper ins Inertialsystem (=B0)
    roboter.kl(i).A_i0=eye(3);
    %Position des Ursprungs des i-ten Koerpers im KOS des i-ten Koerpers
    roboter.kl(i).Bi_r_i= zeros(3,1);
    %Position des Ursprungs B0-System (inertial)
    roboter.kl(i).B0_r_i=zeros(3,1);
    %Homogene Transformationsmatrix vom i-ten Koerper zum Vorgaenger
    roboter.kl(i).D_vi=eye(4);
    %Homogene Transformationsmatrix vom i-ten Koerper ins Intertialsystem
    roboter.kl(i).D_0i=eye(4);
end

end


