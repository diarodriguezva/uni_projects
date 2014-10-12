%%% Beispiel Skript zur Berechnung der inversen Dynamik eines
%%% Knickarmroboters

%Aufraeumen
close all
clear all

%% 1. Parameter Setzen und Modell aufbauen
% Parameter der Sollbahn
w_a=[0.75;0.0;0.0]; %Anfangsposition kartesisch
w_e=[0.0;0.75;0.5]; %Endposition kartesisch
T  = 1.0;       %Dauer der Sollbahn
dt = 1e-3;      %Laenge des Diskretisierungs-Intervalls
Kx = 1.0;       %Verstaerkung/Driftkompensation IK


%Modell fuer Regelung und inverse Kinematik
roboter=erstelle_roboter();

%% 3.  Inverse Kinematik initialisieren (Loesung fuer Startwert w_a)
%mit Newton-Raphson Verfahren
% Je nach Distanz zum Zielwert, kann die Iteration
% auch divergieren!
% In diesem Fall genuegt eine derart einfache
% Initialisierung nicht mehr.

ik_fehler=1e20; %eine grosse Zahl
maximale_anzahl_der_iterationen_die_zulaessig_sind=100;
iteration=1;

ik_fehler_historie=[];%Zur Visualisierung der Konvergenz
while ik_fehler>1e-6
    %Direkte Kinematik berechnen
    roboter=berechne_dk_positionen(roboter);
    roboter=berechne_dk_jacobis(roboter);
    
    %Abweichung zum Zielpunkt im Arbeitsraum
    dw=w_a-roboter.w;
    %Newton-Schritt
    roboter.q=roboter.q+linsolve(roboter.Jw,dw);
    %Fehler berechnen und merken
    ik_fehler= norm(dw);
    ik_fehler_historie(end+1)=ik_fehler;
    
    %Ausgabe jedes 5. Mal aufrufen
    if mod(iteration,5) == 0
        fprintf('IK-Initialisierung, Fehler= %e, Iteration = %d\n', ...
            ik_fehler, iteration);
    end
    %Zur Veranschaulichung der Initialisierung
    %die folgenden Zeilen aktivieren: die
    %Konvergenz kann dann mit dem Animationsprogramm
    %betrachtet werden
    %roboter.schreibe_daten(roboter);
    roboter.zeit=iteration;
    if iteration> maximale_anzahl_der_iterationen_die_zulaessig_sind
        error('Initialisierung Inverse Kinematik: keine Konvergenz!\n');
    end
    iteration=iteration+1;
end
%ok, alles gut gelaufen
%roboter.q hat jetzt den richtigen Wert
%plot(ik_fehler_historie)
%title('IK Fehler bei Initialisierung');



%% 4. Simulation der inversen Kinematik und inversen Dynamik
% Variablen initialisieren
ik_fehler=0;
ik_fehler_max=0;
dot_q_alt=zeros(roboter.N_Q,1);
schleife=1;

% Variablen, zur Datenspeicherung fuer spaetere Analyse
plot_zeit=zeros(T/dt+1,1);

plot_sollwerte=zeros(T/dt+1,3);

plot_dot_sollwerte=zeros(T/dt+1,3);

plot_q_soll=zeros(T/dt+1,3);
plot_dot_q_soll=zeros(T/dt+1,3);

plot_tau=zeros(T/dt+1,3);

%Schleife von Anfangs- bis Endzeit.
% dt ist der Reglertakt
for zeit=0:dt:T
    %1. Zeiten synchronisieren
    roboter.zeit=zeit;
    plot_zeit(schleife)=zeit;

    %2. Sollwerte berechnen
    [w_d,dot_w_d] = sollwerte_w(roboter.zeit,w_a, w_e, T);
    
    %3. Inverse Kinematik loesen
    %3.1 Direkte Kinematik berechnen
    roboter=berechne_dk_positionen(roboter);
    roboter=berechne_dk_jacobis(roboter);
    
    %3.2 Abweichung zum Zielpunkt
    dw=w_d-roboter.w;
    %fuer die Analyse maximalen Fehler merken
    ik_fehler=norm(dw);
    if ik_fehler > ik_fehler_max
        ik_fehler_max = ik_fehler;
    end
    
    %3.3 effektive Sollgeschwindigkeit berechnen
    dot_w_d_effektiv = dot_w_d + Kx/dt * dw;
    
    %3.4  Gelenkwinkelgeschwindigkeit berechnen
    %( entweder 3.4.1 oder 3.4.2 aktivieren!)
    %3.4.1 Verfahren der Inversen Jacobi
    roboter.dot_q=linsolve(roboter.Jw,dot_w_d_effektiv);
    %3.4.2 Verfahren der transponierten Jacobi
    %roboter.dot_q=roboter.Jw'*dot_w_d_effektiv;
    
    %3.5 Zur Analyse tatsaechliche Arbeitsraum-Geschwindigkeit berechnen
    % (der Sollvorgabe, nicht des virtuellen Roboters!)
    roboter=berechne_dk_geschwindigkeiten(roboter);
    
    %4 Soll-Gelenkwinkel und Beschleunigungen durch numerische
    %Differentiation bzw. Integration
    roboter.q=roboter.q + dt*roboter.dot_q;
    roboter.ddot_q=1/dt*(roboter.dot_q-dot_q_alt);
    %alten Zustand merken (fuer Berechnung ddot_q)
    dot_q_alt=roboter.dot_q;
    
    %5 Drehmomente aus inverser Dynamik
    roboter=berechne_id(roboter);
    
    %6. Ausgabe der Daten zur Visualisierung
    %  (nur alle 10 Zeitschritte schreiben)
    if mod(schleife,10) == 0
        roboter=schreibe_daten(roboter);
    end
    
    %7. Daten zur Analyse merken
    plot_sollwerte(schleife,:)=w_d;
    plot_istwerte(schleife,:)=roboter.w;
    
    plot_dot_sollwerte(schleife,:)=dot_w_d;
    plot_dot_istwerte(schleife,:)=roboter.dot_w;
        
    plot_q_soll(schleife,:)=roboter.q;
    plot_dot_q_soll(schleife,:)=roboter.dot_q;
    
    plot_tau(schleife,:)=roboter.tau_id;
    
    
    %9. Gelegentlich die aktuelle Zeit ausgeben
    if mod(schleife,100) == 0
        fprintf('t= %e (T= %e)\n',roboter.zeit,T);
    end
    schleife=schleife+1;
end

%%% Plots zur inversen Kinematik (ausgeblendet)
% figure;
% plot(plot_sollwerte,'-.');
%
% hold on;
% plot(plot_istwerte,'-');
% legend('x_{soll}', 'y_{soll}', 'z_{soll}','x_{ist}', 'y_{ist}', 'z_{ist}');
% xlabel('Zeitschritt')
% ylabel('X/Y/Z-Wert')
% title('Soll- und Istwerte im Arbeitsraum')
%
% figure;
%
% plot(plot_sollwerte-plot_istwerte)
% legend('dx', 'dy', 'dz');
% title('IK-Fehler im Arbeitsraum')
%
% figure;
% plot(plot_dot_sollwerte,'-.');
%
% hold on;
% plot(plot_dot_istwerte,'-');
% legend('xp_{soll}', 'yp_{soll}', 'zp_{soll}','xp_{ist}', 'yp_{ist}', 'zp_{ist}');
% xlabel('Zeitschritt')
% ylabel('X/Y/Z-Geschwindigkeit')
% title('Soll- und Istwerte im Arbeitsraum (Geschwindigkeit)')


figure
plot(plot_zeit,plot_q_soll,'-');
title ('Sollwerte Gelenkwinkel');
legend('q[1]','q[2]', 'q[3]');
xlabel('Zeit [sec]')
ylabel('Gelenkwinkel [rad]');

figure;
plot(plot_zeit,plot_tau,'-');
title ('Gelenkmomente (inverse Dynamik)');
legend('tau[1]','tau[2]', 'tau[3]');
xlabel('Zeit [sec]')
ylabel('Gelenkmomente [Nm]');
