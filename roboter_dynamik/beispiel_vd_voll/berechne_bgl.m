function rob=berechne_bgl(rob)
%Berechnung Bewegungsgleichungen des Systems (M, h und ddot_q)
%
% Alle notwendigen Funktionen werden von hier aus aufgerufen
%


%% 1. Berechnung des h-Vektors:  
% wegen M*ddot_q+h=tau gilt fuer ddot_q=0, h=tau
rob.ddot_q=zeros(rob.N_Q,1);
rob=berechne_id(rob);
rob.h=rob.tau_id; %tau_id= Gelenkmomente aus inverser Dynamik

%% 2. Berechnung der Massenmatrix
rob.M=zeros(rob.N_Q,rob.N_Q);

% Beitraege aller Koerper addieren
for i=1:length(rob.kl)
    %Anteil diese Koerpers
    dM=rob.kl(i).m*rob.kl(i).Bi_Jt_o'*...
        (rob.kl(i).Bi_Jt_o-tilde(rob.kl(i).Bi_r_s)*rob.kl(i).Bi_Jr)...
        +rob.kl(i).Bi_Jr'*(...
        rob.kl(i).I_o*rob.kl(i).Bi_Jr +  rob.kl(i).m*tilde(rob.kl(i).Bi_r_s)*rob.kl(i).Bi_Jt_o);
    %Anteil zur Gesamt-Massenmatrix addieren 
    rob.M=rob.M+dM;
end

%Die aktuellen Beschleunigungen berechnen
%Hier werden auch die Antriebsmomente der Regelung tau_reg beruecksichtigt
rob.ddot_q=linsolve(rob.M,rob.tau_reg-rob.h);
end

 
