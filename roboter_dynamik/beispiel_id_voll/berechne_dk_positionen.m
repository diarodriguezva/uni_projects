function rob=berechne_dk_positionen(rob)
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
    %Verschiebungsvektor vom Vorgaenger zum Koerper i im KOS des Vorgaengers (Bv)
    rob.kl(i).Bv_r_vi=[rob.kl(i).a;...
                      -sin(rob.kl(i).alpha)*rob.kl(i).d;...
                       cos(rob.kl(i).alpha)*rob.kl(i).d];
    
    
    %Drehmatrix vom Vorgaenger zum i-ten Koerper
    rob.kl(i).A_iv=Az(rob.q(rob.kl(i).fhg_no))*Ax(rob.kl(i).alpha);
    
    %% Absolute Position und Orientierung
    % Drehmatrix vom Bi-KOS ins B0-KOS:
    %rob.kl(i).A_i0=
    if vor ~= -1 %Wurzelkoerper
        rob.kl(i).A_i0=rob.kl(i).A_iv*rob.kl(vor).A_i0;
    else %Koerper mit Vorgaenger
        rob.kl(i).A_i0=rob.kl(i).A_iv;
    end
    %Position des Ursprungs des i-ten Koerpers im Bi-KOS:
    %rob.kl(i).Bi_r_i=
    rob.kl(i).Bi_r_i= rob.kl(i).A_iv*rob.kl(i).Bv_r_vi;
    % falls der Koerper einen Vorgaenger hat, diese Position dazu addieren
    if vor ~= -1
        rob.kl(i).Bi_r_i=rob.kl(i).Bi_r_i+rob.kl(i).A_iv*rob.kl(vor).Bi_r_i;
    end
    %Position des Ursprungs im B0-System (fuer Animation benötigt): 
    %rob.kl(i).B0_r_i=
    rob.kl(i).B0_r_i=rob.kl(i).A_i0'*rob.kl(i).Bi_r_i;        
    
end
%Position des TCP im B0-System berechnen
%rob.w= 
rob.w= rob.kl(3).B0_r_i + rob.kl(3).A_i0'*rob.B3_r_3_tcp;
end


