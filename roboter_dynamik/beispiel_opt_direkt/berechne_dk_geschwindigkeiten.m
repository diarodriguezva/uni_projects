function rob=berechne_dk_geschwindigkeiten(rob)
%Berechnung der Geschwindigkeitsgroessen direkten Kinematik
% Ergebnisse werden in rob gespeichert
%
% Allgemeine Anmerkungen: Siehe berechne_dk_positionen
%
%Parameter: rob (Roboter Daten)


% Berechnung fuer alle Koerper
for i=1:length(rob.kl)
    % Index des Vorgaengers merken
    vor=rob.kl(i).vorgaenger;
    %% absolute Winkelgeschwindigkeit berechnen
    if vor ~= -1 % hat Vorgaenger
        rob.kl(i).Bi_omega=rob.kl(i).A_iv*rob.kl(vor).Bi_omega;
    else
        rob.kl(i).Bi_omega=zeros(3,1);
    end
    %relativer Anteil
    rob.kl(i).Bi_omega_rel=[0;0;rob.dot_q(rob.kl(i).fhg_no)];
    
    rob.kl(i).Bi_omega=rob.kl(i).Bi_omega+rob.kl(i).Bi_omega_rel;
    %% absolute Translationsgeschwindigkeit berechnen
    if vor ~= -1 % hat Vorgaenger
        %Version mit Kreuzprodukt
        %rob.kl(i).Bi_dot_r_i=rob.kl(i).A_iv*(rob.kl(vor).Bi_dot_r_i...
        %+cross(rob.kl(vor).Bi_omega,rob.kl(i).Bv_r_vi));
        %Version mit tilde
        rob.kl(i).Bi_dot_r_i=rob.kl(i).A_iv*(rob.kl(vor).Bi_dot_r_i+tilde(rob.kl(vor).Bi_omega)*rob.kl(i).Bv_r_vi);
    else
        rob.kl(i).Bi_dot_r_i=zeros(3,1);
    end
    
end
%Geschwindigkeit des TCP im B0-System berechnen
%Version mit Kreuzprodukt
%rob.dot_w=  rob.kl(3).A_i0'*(rob.kl(3).Bi_dot_r_i +cross(rob.kl(3).Bi_omega,rob.B3_r_3_tcp));
%Version mit Tilde
rob.dot_w=  rob.kl(3).A_i0'*(rob.kl(3).Bi_dot_r_i +tilde(rob.kl(3).Bi_omega)*rob.B3_r_3_tcp);
end

