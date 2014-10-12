%%% Beispiel Skript zur Regelung eines Knickarmroboter

%Aufraeumen
%close all
%clear all

%% 1. Parameter Setzen und Modell aufbauen
% Parameter der Sollbahn
w_a=[0.75;0.0;0.0]; %Anfangsposition kartesisch
w_e=[0.0;0.75;0.5]; %Endposition kartesisch
T  = 1;       %Dauer der Sollbahn
dt = 1e-3;      %Laenge des Diskretisierungs-Intervalls
Kx = 1.0;       %Verstaerkung/Driftkompensation IK
%Regler-Parameter
lambda=30.0;
Kp=lambda*lambda;
Kd=2.0*lambda;
%regler-typ einstellen
regler='JInv';%Jacobi-Invers
regler='JTra';%Jacobi-Transponiert
%regler='FBLin';%feedback-linearisierung

%anfaenglicher Regelfehler (im Gelenkraum)
regelfehler_anfang=0;

%Modell fuer Regelung und inverse Kinematik
roboter_regler=erstelle_roboter();
%Modell fuer Simulation ("virtueller Roboter);
roboter_sim=erstelle_roboter();

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
    roboter_regler=berechne_dk_positionen(roboter_regler);
    roboter_regler=berechne_dk_jacobis(roboter_regler);
    
    %Abweichung zum Zielpunkt im Arbeitsraum
    dw=w_a-roboter_regler.w;
    %Newton-Schritt
    roboter_regler.q=roboter_regler.q+linsolve(roboter_regler.Jw,dw);
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
    %roboter_regler.schreibe_daten(roboter_regler);
    roboter_regler.zeit=iteration;
    if iteration> maximale_anzahl_der_iterationen_die_zulaessig_sind
        error('Initialisierung Inverse Kinematik: keine Konvergenz!\n');
    end
    iteration=iteration+1;
end
%ok, alles gut gelaufen
%roboter_regler.q hat jetzt den richtigen Wert
%plot(ik_fehler_historie)
%title('IK Fehler bei Initialisierung');



%% 4. Simulation der Regelung
% Variablen initialisieren
dot_q_alt=zeros(roboter_regler.N_Q,1);
schleife=1;

%Istwerte auf Sollwerte setzen
roboter_sim.q=roboter_regler.q+ones(3,1)*regelfehler_anfang;


% Variablen, zur Datenspeicherung fuer spaetere Analyse
plot_zeit=zeros(T/dt+1,1);

plot_sollwerte=zeros(T/dt+1,3);
plot_istwerte=zeros(T/dt+1,3);


%Schleife von Anfangs- bis Endzeit.
% dt ist der Reglertakt
Jw_alt=roboter_regler.Jw;
for zeit=0:dt:T
    %1. Zeiten synchronisieren
    roboter_regler.zeit=zeit;
    roboter_sim.zeit=zeit;
    plot_zeit(schleife)=zeit;

    %2. Sollwerte berechnen
    [w_d,dot_w_d,ddot_w_d] = sollwerte_w(roboter_regler.zeit,w_a, w_e, T);
    
    %3. "Messwerte" auf Robotermodell der Regelung Uebertragen
    % und Kinematik auswerten
    roboter_regler.q=roboter_sim.q;
    roboter_regler.dot_q=roboter_sim.dot_q;
    roboter_regler=berechne_dk_positionen(roboter_regler);
    roboter_regler=berechne_dk_geschwindigkeiten(roboter_regler);
    roboter_regler=berechne_dk_jacobis(roboter_regler);
    
    %4 Abweichung zum Zielpunkt
    dw=w_d-roboter_regler.w;
    dot_dw=dot_w_d-roboter_regler.dot_w;
    
   
    %5. Regelung   
    switch regler
        case 'JInv'
        %5.1: Inverse Jacobi
        % a) Abweichung im Gelenkraum
        dq=linsolve(roboter_regler.Jw,dw);
        dot_q=linsolve(roboter_regler.Jw,dot_dw);
        % b) Regelung
        tau_reg=Kp*dq+Kd*dot_q;
        case 'JTra'
        %5.2: transponierte Jacobi
        % a) Regelung im Arbeitsraum
        Fw=Kp*dw+Kd*dot_dw;
        % b) Stellgroesse im Gelenkraum
        tau_reg=roboter_regler.Jw'*Fw;
        case 'FBLin'
         %5.3: Feedback linearisierung
        %a: lineares Regelungsgesetz
        ddot_w=ddot_w_d+Kp*dw+Kd*dot_dw;
        %b: Beschleunigung ddot_q hierfuer
        %Zeitableitung der Jacobi: diese koennte auch analytisch/rekursiv berechnet werden.
        dot_Jw=(roboter_regler.Jw-Jw_alt)/dt;
        Jw_alt=roboter_regler.Jw;
        roboter_regler.ddot_q=linsolve(roboter_regler.Jw,ddot_w-dot_Jw*roboter_regler.dot_q);
        %c: Stellkraefte aus inverser Dynamik
        roboter_regler=berechne_id(roboter_regler);
        tau_reg=roboter_regler.tau_id;        
    end
    %Stellmomente auf Simulationsmodell geben
    roboter_sim.tau_reg=tau_reg;
    
    %6. Zeitintegration
    % Das Antriebsdrehmoment  wird ueber den Reglertakt konstant gehalten
    % Hinweis: Im allgemeinen Fall sollten Verfahren hoeherer Ordnung vorgezogen
    % werden (z.B. ode45)
    % Hier wird zur klareren Darstellung des Ablaufs das Euler-Verfahren
    % bevorzugt
    N_INT=10.0;%Integrationsschritte pro Reglertakt
    dt_sim=dt/N_INT;
    for i=1:N_INT
        roboter_sim=berechne_bgl(roboter_sim);
        roboter_sim.q= roboter_sim.q + dt_sim*roboter_sim.dot_q;
        roboter_sim.dot_q= roboter_sim.dot_q + dt_sim*roboter_sim.ddot_q;
    end
    
    %7. Ausgabe der Daten zur Visualisierung
    %  (nur alle 10 Zeitschritte schreiben)
    if mod(schleife,10) == 0
        roboter_sim=schreibe_daten(roboter_sim);
    end
    
    %8. Daten zur Analyse merken
    plot_sollwerte(schleife,:)=w_d;
    plot_istwerte(schleife,:)=roboter_regler.w;
        
    plot_q_ist(schleife,:)=roboter_sim.q;
    
    
    %9. Gelegentlich die aktuelle Zeit ausgeben
    if mod(schleife,100) == 0
        fprintf('t= %e (T= %e)\n',roboter_regler.zeit,T);
    end
    schleife=schleife+1;
end


%rms regelfehler ausgeben
fprintf('RMS fehler fuer %s-regler war: [%e %e %e]\n', regler, rms(plot_sollwerte-plot_istwerte,1))

figure
plot(plot_zeit,plot_q_ist,'-');
title (strcat('Istwerte der Gelenkwinkel (regler: ',regler,')'));
xlabel('Zeit [sec]')
ylabel('Gelenkwinkel [rad]');
legend('q_{ist}(1)','q_{ist}(2)','q_{ist}(3)');
plot(plot_zeit,plot_q_ist,'-');


figure;
hold on;
title (strcat('Sollwerte/Istwerte (regler: ',regler,')'));
xlabel('Zeit [sec]')
ylabel('Position Soll-/Istwerte');
plot(plot_zeit,plot_sollwerte,'-');
plot(plot_zeit,plot_istwerte,'-.');

legend('w_{soll}(1)','w_{soll}(2)','w_{soll}(3)','w_{ist}(1)','w_{ist}(2)','w_{ist}(3)');


figure;
plot(plot_zeit,plot_sollwerte-plot_istwerte,'-');
title (strcat('Regelfehler Arbeitsraum (soll-ist; regler: ', regler, ')'));
xlabel('Zeit [sec]')
ylabel('Position [m]');
legend('Delta x','Delta y','Delta z');
