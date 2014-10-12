function rob = berechne_id(rob)
%Iinverse Dynamik fuer Roboter rob berechnen
% Die Ergebnisse werden wiederung in der Struktur rob.gespeichert
%
% Im einzelnen werden Impuls- und Drallaenderung aller Koerper berechnet und
% ueber die Jacobi-Matrizen in die zwangsfreien Richtungen projiziert.
% Im Ergebnis wird die "linke Seite der Bewegungsgleichung"
% M*ddot_q + h berechnet und in tau_id gespeichert
% Es werden alle noetigen Groessen hier berechnet

%1. Mit Null initialisieren
rob.tau_id=zeros(rob.N_Q,1);

%2. Kinematik berechnen
rob=berechne_dk_positionen(rob);
rob=berechne_dk_geschwindigkeiten(rob);
rob=berechne_dk_beschleunigungen(rob);
rob=berechne_dk_jacobis(rob);

%3. Berechnung fuer alle Koerper: Impuls- und Drallaenderung
for i=1:length(rob.kl)
    
    %Absolutbeschleunigung des Schwerpunkts: Mit Kreuzprodukt
    %     rob.kl(i).Bi_ddot_r_s = rob.kl(i).Bi_ddot_r_i+...
    %         cross(rob.kl(i).Bi_dot_omega,rob.kl(i).Bi_r_s)+...
    %         cross(rob.kl(i).Bi_omega,cross(rob.kl(i).Bi_omega,rob.kl(i).Bi_r_s));
    %
    %Alternativ mit Tilde-Operator
    rob.kl(i).Bi_ddot_r_s = rob.kl(i).Bi_ddot_r_i+...
        tilde(rob.kl(i).Bi_dot_omega)*rob.kl(i).Bi_r_s+...
        tilde(rob.kl(i).Bi_omega)*tilde(rob.kl(i).Bi_omega)*rob.kl(i).Bi_r_s;
    
    
    % Erdbeschleunigung im koerperfesten System
    rob.kl(i).Bi_g=rob.kl(i).A_i0*rob.B0_g;
    
    %Impulsaenderung - Schwerkraft
    F = rob.kl(i).m*(rob.kl(i).Bi_ddot_r_s-rob.kl(i).Bi_g);
    
    %Drallaenderung - Moment der Schwerkraft
    %     T = rob.kl(i).m*cross(rob.kl(i).Bi_r_s, rob.kl(i).Bi_ddot_r_i-rob.kl(i).Bi_g)...
    %         +rob.kl(i).I_o*rob.kl(i).Bi_dot_omega ...
    %         +cross(rob.kl(i).Bi_omega, rob.kl(i).I_o*rob.kl(i).Bi_omega);
    %
    %Alternativ mit Tilde-Operator
    T = rob.kl(i).m*tilde(rob.kl(i).Bi_r_s)*(rob.kl(i).Bi_ddot_r_i-rob.kl(i).Bi_g)...
        +rob.kl(i).I_o*rob.kl(i).Bi_dot_omega ...
        +tilde(rob.kl(i).Bi_omega)*rob.kl(i).I_o*rob.kl(i).Bi_omega;
    
    
    %Projektion auf zwangsfreie Richtungen und Addition zu tau_id
    rob.tau_id=rob.tau_id+ rob.kl(i).Bi_Jt_o'*F;
    rob.tau_id=rob.tau_id+ rob.kl(i).Bi_Jr'*T;
    
    %zuätzliche Reibung
    %rob.tau_id=rob.tau_id+1*rob.dot_q;
end
end



