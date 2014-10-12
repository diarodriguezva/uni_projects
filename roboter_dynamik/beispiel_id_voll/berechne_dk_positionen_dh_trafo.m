function rob=berechne_dk_positionen_dh_trafo(rob)
%Berechnung der Positions-Groessen der direkten Kinematik
% (Lagen und Orientierungen)
%
% Die Koerper muessen entsprechend der Baumstruktur wie folgt sortiert werden:
% ist Koerper A naeher an der Wurzel als Koerper B, so belegt der
% Freiheitsgrad von A im Vektor der Freiheitsgrade q einen kleineren Index
% als B
% ==> Dann kann die Kinematik in einer Schleife berechnet werden,
%     wobei stets gewaehrleistet ist, dass die Kinematik des
%     Vorgaenger-Koerpers bereits berechnet wurde
%
%Parameter: rob (Roboter Daten)


% Berechnung fuer alle Koerper
for i=1:length(rob.kl)
    % Index des Vorgaengers merken
    vor=rob.kl(i).vorgaenger;
    
    %% Relativkinematik: Position und Orientierung relativ zum Vorgaenger        
    %Homogene Transformationsmatrix vom i-ten Koerper zum Vorgaenger
    %rob.kl(i).D_vi=
    rob.kl(i).D_vi=dh_trafo(rob.kl(i).alpha, rob.kl(i).a, ...
            rob.kl(i).d, rob.q(rob.kl(i).fhg_no));
            
    %% Absolute Position und Orientierung
    % Homogene Transformationsmatrix
    % Homogene Transformationsmatrix: rob.kl(i).D_0i
    if vor ~= -1
        rob.kl(i).D_0i=rob.kl(vor).D_0i*rob.kl(i).D_vi;
    else
        rob.kl(i).D_0i=rob.kl(i).D_vi;
    end
    
    %Abspeichern von Absoluten Position und Orientierung 
    %(fuer die Ausgabe in der Animationsdatei)
    rob.kl(i).B0_r_i=rob.kl(i).D_0i(1:3,4);
    rob.kl(i).A_i0=(rob.kl(i).D_0i(1:3,1:3))';    
    
end
%Position des TCP im B0-System berechnen
w= rob.kl(3).D_0i * [rob.B3_r_3_tcp; 1];
rob.w=w(1:3);
end


