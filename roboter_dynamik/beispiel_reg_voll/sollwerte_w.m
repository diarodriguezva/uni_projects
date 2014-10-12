function [ w_d, dot_w_d, ddot_w_d] = sollwerte_w(zeit, w_a, w_e, T)
%Sollwerte fuer die Inverse Kinematik berechnen
%
%  Glatte Punkt-zu-Punkt Bewegung von w_a nach w_e
%  Vorsicht: Es wird davon ausgegangen, dass die Parameter konstant sind!
%
%  Eingabe:  Zeit
%            w_a (Anfangsposition)
%            w_e (Endposition)
%            T   (Zeitdauer)
%  Ausgabe   w_d (Arbeitsraumposition)
%            dot_w_d (Arbeitsraum-Geschwindigkeit)
%
%

%1. Parameter des Polynoms des Bahnparameters berechnen
as=berechne_as(w_a, w_e, T);

%2. Bahnparameter und Ableitung fuer aktuelle Zeit
%   (s laueft von 0 am Anfang bis 1 am Ende)
s=polyval(as,zeit);
dot_s=polyval(polyder(as),zeit);
ddot_s=polyval(polyder(polyder(as)),zeit);
w_d=  w_a + (w_e - w_a) * s;
dot_w_d=(w_e - w_a) * dot_s;
ddot_w_d=(w_e - w_a)*ddot_s;
end


function [as] = berechne_as(w_a, w_e, T)
%Berechnung des Bahnparameters als Polynom 5.Grades
% Randbedingungen: s(0)=0, d(s(0))/dt=0, d^2(s(0))/dt^2=0
%                  s(t_ende)=s_ende, d(s(t_ende))/dt=0, d^2(s(s_ende))/dt^2=0
% Parameter hier der Einfachheit halber fest vorgegeben
% Allgemein: durch Loesung eines linearen Gleichungssystems online rechnen
as(6)=0.0;
as(5)=0.0;
as(4)=0.0;
as(3)=10.0/(T^3.0);
as(2)=-15.0/(T^4.0);
as(1)= 6.0/(T^5.0);
end
