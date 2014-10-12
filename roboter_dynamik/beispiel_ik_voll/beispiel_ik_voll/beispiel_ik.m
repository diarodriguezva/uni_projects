%%% Beispiel zur inversen Kinematik fuer Knickarmroboter
close all
clear all

%% 1. Parameter und Strukturen initialisieren
%Parameter der Sollbahn
w_a=[0.75;0.0;0.0]; %Anfangsposition kartesisch
w_e=[0.0;0.75;0.75]; %Endposition kartesisch
T  = 1.0;       %Dauer der Sollbahn
dt = 1e-3;      %Laenge des Diskretisierungs-Intervalls
Kx = 1.0;       %Verstaerkung/Driftkompensation IK

%Robotermodell
rob=erstelle_roboter();

%% 2.  Inverse Kinematik initialisieren (Loesung fuer Startwert w_a)
%mit Newton-Raphson Verfahren
% Je nach Distanz zum Zielwert, kann die Iteration
% auch divergieren!
% In diesem Fall genuegt eine derart einfache
% Initialisierung nicht mehr.

ik_fehler=1e20; %eine grosse Zahl
maximale_anzahl_der_iterationen_die_zulaessig_sind=100;
iteration=1;

ik_fehler_historie=[];
while ik_fehler>1e-18
    %Direkte Kinematik berechnen
    rob=berechne_dk_positionen(rob);
    rob=berechne_dk_jacobis(rob);
    
    %Abweichung zum Zielpunkt
    dw=w_a-rob.w;
    %Newton-Schritt
    %rob.q=
    rob.q=rob.q+linsolve(rob.Jw,dw);
    
    %Fehler merken, um Konvergenz plotten zu können
    ik_fehler= norm(dw);
    ik_fehler_historie(end+1)=ik_fehler;
    
    %Ausgabe jedes 3. Mal aufrufen
    if mod(iteration,3) == 0
        fprintf('IK-Initialisierung, Fehler= %e, Iteration = %d\n', ...
            ik_fehler, iteration);
    end
    %Zur Veranschaulichung der Initialisierung
    %die folgenden Zeilen aktivieren: die
    %Konvergenz kann dann mit dem Animationsprogramm
    %betrachtet werden
    %rob.schreibe_daten(rob);
    rob.zeit=iteration;
    if iteration> maximale_anzahl_der_iterationen_die_zulaessig_sind
        error('Initialisierung Inverse Kinematik: keine Konvergenz!\n');
    end
    iteration=iteration+1;
end
%ok, alles gut gelaufen
%rob.q hat jetzt den richtigen Wert
plot(ik_fehler_historie,'+-')
title('IK Fehler bei Initialisierung');




%% 3. Der eigentliche IK Algorithmus
%Parameter initialisieren
ik_fehler=0;
ik_fehler_max=0;
schleife=1;

%Arrays fuer spaetere Plots initialisieren
plot_zeit=zeros(T/dt+1,1);

plot_sollwerte=zeros(T/dt+1,3);
plot_istwerte=zeros(T/dt+1,3);

plot_dot_sollwerte=zeros(T/dt+1,3);
plot_dot_istwerte=zeros(T/dt+1,3);

plot_q=zeros(T/dt+1,3);
plot_dot_q=zeros(T/dt+1,3);
plot_ddot_q=zeros(T/dt+1,3);

for zeit=0:dt:T
    %4.1 Sollwerte zum Zeitpunkt "zeit" berechnen
    rob.zeit=zeit;
    [w_d,dot_w_d] = sollwerte_w(rob.zeit,w_a, w_e, T);
    
    %4.2 Direkte Kinematik fuer MKS berechnen
    rob=berechne_dk_positionen(rob);
    rob=berechne_dk_geschwindigkeiten(rob); %nur zum plot von dot_w noetig!
    rob=berechne_dk_jacobis(rob);
    
    %4.3 Abweichung zum Zielpunkt
    dw=w_d-rob.w;
    %fuer die Analyse maximalen Fehler merken
    ik_fehler=norm(dw);
    if ik_fehler > ik_fehler_max
        ik_fehler_max = ik_fehler;
    end
    %4.4 effektive Sollgeschwindigkeit
    %dot_w_d_effektiv =
    dot_w_d_effektiv = dot_w_d + Kx/dt * dw;
    
    %4.5  Gelenkwinkelgeschwindigkeit
    %Verfahren der Inversen Jacobi oder Transponierten Jacobi
    %rob.dot_q=
    %( entweder 5.1 oder 5.2 aktivieren!)
    %4.5.1 Verfahren der Inversen Jacobi
    %rob.dot_q=linsolve(rob.Jw,dot_w_d_effektiv);
    %4.5.2 Verfahren der transponierten Jacobi
    rob.dot_q=rob.Jw'*dot_w_d_effektiv;
    
    %5. Gelenkwinkel durch numerische Integration bestimmen
    %rob.q=
    rob.q=rob.q + dt*rob.dot_q;
    
   
    %6. Ausgabe der Daten zur Visualisierung
    %  (nur alle 10 Zeitschritte schreiben)
    if mod(schleife,10) == 0
        rob=schreibe_daten(rob);
    end
    
    %7. Daten zur Analyse merken
    plot_sollwerte(schleife,:)=w_d;
    plot_istwerte(schleife,:)=rob.w;
    
    plot_dot_sollwerte(schleife,:)=dot_w_d;
    plot_dot_istwerte(schleife,:)=rob.dot_w;
    
    plot_q(schleife,:)=rob.q;
    plot_dot_q(schleife,:)=rob.dot_q;
    plot_ddot_q(schleife,:)=rob.ddot_q;
    
    %8. Gelegentlich die aktuelle Zeit ausgeben
    if mod(schleife,100) == 0
        fprintf('t= %e (T= %e)\n',rob.zeit,T);
    end
    schleife=schleife+1;
end
fprintf('Ende der Trajektorie. Maximaler Fehler der inversen Kinematik war: %e\n',...
    ik_fehler_max);

figure;
plot(plot_sollwerte,'-.');

hold on;
plot(plot_istwerte,'-');
legend('x_{soll}', 'y_{soll}', 'z_{soll}','x_{ist}', 'y_{ist}', 'z_{ist}');
xlabel('Zeitschritt')
ylabel('X/Y/Z-Wert')
title('Soll- und Istwerte im Arbeitsraum')

figure;

plot(plot_sollwerte-plot_istwerte)
legend('dx', 'dy', 'dz');
title('IK-Fehler im Arbeitsraum')

figure;
plot(plot_dot_sollwerte,'-.');

hold on;
plot(plot_dot_istwerte,'-');
legend('xp_{soll}', 'yp_{soll}', 'zp_{soll}','xp_{ist}', 'yp_{ist}', 'zp_{ist}');
xlabel('Zeitschritt')
ylabel('X/Y/Z-Geschwindigkeit')
title('Soll- und Istwerte im Arbeitsraum (Geschwindigkeit)')

