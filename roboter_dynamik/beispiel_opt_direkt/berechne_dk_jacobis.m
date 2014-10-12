function  rob=berechne_dk_jacobis(rob)
%Berechnung der Jacobi-Matrizen der Rotation und Translation
%   Vor dem Aufruf muss berechne_dk_positionen ausgefuehrt werden, damit
%   Drehmatrizen etc. aktualisiert werden
%   Allgemeine Anmerkungen: Siehe berechne_dk_positionen

% Berechnung fuer alle Koerper
for i=1:length(rob.kl)
    % Index des Vorgaengers merken
    vor=rob.kl(i).vorgaenger;
    
    %Jacobi-Matrix der Rotation, dargestellt im Bi-KOS (d(Bi_omega)/d(dot(q))
    if vor ~= -1
        %Anteil des Vorgaengers
        rob.kl(i).Bi_Jr=rob.kl(i).A_iv*rob.kl(vor).Bi_Jr;
    else
        rob.kl(i).Bi_Jr=zeros(3,length(rob.q));
    end
    % relativer Anteil (hier fuer Drehgelenk, Relativdrehung um z-Achse:
    % d(Bi_omega)/d(dot(q_i))
    rob.kl(i).Bi_Jr(3,rob.kl(i).fhg_no)=1.0;
    
    %Jacobi-Matrix der Translation, dargestellt im Bi-KOS
    if vor ~= -1
        rob.kl(i).Bi_Jt_o=rob.kl(i).A_iv*(rob.kl(vor).Bi_Jt_o - tilde(rob.kl(i).Bv_r_vi)*rob.kl(vor).Bi_Jr);
    else
        rob.kl(i).Bi_Jt_o=zeros(3,length(rob.q));
    end
end

%Jacobi-Matrix der Endeffektor-Position
rob.Jw=rob.kl(3).A_i0'*(rob.kl(3).Bi_Jt_o - tilde(rob.B3_r_3_tcp)*rob.kl(3).Bi_Jr);
end

