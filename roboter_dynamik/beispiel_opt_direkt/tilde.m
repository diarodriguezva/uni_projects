function [ T ] = tilde( v )
%tilde Berechnung des "Schlangentensors" aus Vektor v 
% (schiefsymmetrische Matrix, sodass tilde(v)*w = cross(v,w)
% 
% Eigentlich sollte hier eine Sicherheitsabfrage der Dimension kommen...

T=[0.0,-v(3),v(2);...
   v(3),0.0, -v(1);...
   -v(2),v(1),0.0];
end

