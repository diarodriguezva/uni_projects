%%% Beispiel Skript zur Regelung eines Knickarmroboters im Gelenkraum

%Aufraeumen
%close all
clear all

%% 1. Parameter Setzen und Modell aufbauen
% Parameter der Sollbahn
w_a=[0.75;0.0;0.0]; %Anfangsposition kartesisch
w_e=[0.0;0.75;0.5]; %Endposition kartesisch
T  = 1;             %Dauer der Sollbahn
dt = 1e-3;          %Laenge des Diskretisierungs-Intervalls
Kx = 1.0;           %Verstaerkung/Driftkompensation IK
%regler-typ einstellen 
regler = 'PD';%Proportional-Derivative
%regler= 'FFLin'; %feedforward linearisierung
%regler= 'FBLin'; %feedback linearisierung
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
ik_fehler=0;
ik_fehler_max=0;
dot_q_alt=zeros(roboter_regler.N_Q,1);
schleife=1;

%Istwerte auf Sollwerte setzen + Regelfehler
roboter_sim.q=roboter_regler.q+ones(3,1)*regelfehler_anfang;


% Variablen, zur Datenspeicherung fuer spaetere Analyse
plot_zeit=zeros(T/dt+1,1);

plot_sollwerte=zeros(T/dt+1,3);
plot_istwerte=zeros(T/dt+1,3);

plot_dot_sollwerte=zeros(T/dt+1,3);
plot_dot_istwerte=zeros(T/dt+1,3);

plot_tau=zeros(T/dt+1,3);

plot_q_soll=zeros(T/dt+1,3);
plot_dot_q_soll=zeros(T/dt+1,3);

plot_q_ist=zeros(T/dt+1,3);
plot_dot_q_ist=zeros(T/dt+1,3);


%Schleife von Anfangs- bis Endzeit.
% dt ist der Reglertakt
for zeit=0:dt:T
    %1. Zeiten synchronisieren
    roboter_regler.zeit=zeit;
    roboter_sim.zeit=zeit;
    plot_zeit(schleife)=zeit;

    %2. Sollwerte berechnen
    [w_d,dot_w_d] = sollwerte_w(roboter_regler.zeit,w_a, w_e, T);
    
    %3. Inverse Kinematik loesen
    %3.1 Direkte Kinematik berechnen
    roboter_regler=berechne_dk_positionen(roboter_regler);
    roboter_regler=berechne_dk_jacobis(roboter_regler);
    
    %3.2 Abweichung zum Zielpunkt
    dw=w_d-roboter_regler.w;
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
    roboter_regler.dot_q=linsolve(roboter_regler.Jw,dot_w_d_effektiv);
    %3.4.2 Verfahren der transponierten Jacobi
    %roboter_regler.dot_q=roboter_regler.Jw'*dot_w_d_effektiv;
    
    %3.5 Zur Analyse tatsaechliche Arbeitsraum-Geschwindigkeit berechnen
    % (der Sollvorgabe, nicht des virtuellen Roboters!)
    roboter_regler=berechne_dk_geschwindigkeiten(roboter_regler);
    
    %4 Soll-Gelenkwinkel und Beschleunigungen durch numerische
    %Differentiation bzw. Integration
    roboter_regler.q=roboter_regler.q + dt*roboter_regler.dot_q;
    roboter_regler.ddot_q=1/dt*(roboter_regler.dot_q-dot_q_alt);
    %alten Zustand merken (fuer Berechnung ddot_q)
    dot_q_alt=roboter_regler.dot_q;
    
    
    %5. Regelung der Gelenkwinkel ueber Gelenkmomente 
    switch regler
        case 'PD'
        %5.1 Variante 1: Entkoppelte PD Regler fuer Gelenkwinkel
        roboter_sim.tau_reg=PD_regelung(roboter_regler,roboter_sim);
        case 'FFLin'
        %5.2 Variante 2: Feedforward Linearisierung (Vorsteuerung Dynamik) 
        roboter_sim.tau_reg=FFLin_regelung(roboter_regler,roboter_sim);
        case 'FBLin'
        %5.3 Variante 3: Feedback Linearisierung  
        roboter_sim.tau_reg=FBLin_regelung(roboter_regler,roboter_sim);
    end
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
    
    plot_dot_sollwerte(schleife,:)=dot_w_d;
    plot_dot_istwerte(schleife,:)=roboter_regler.dot_w;
        
    plot_q_soll(schleife,:)=roboter_regler.q;
    plot_dot_q_soll(schleife,:)=roboter_regler.dot_q;
    
    plot_q_ist(schleife,:)=roboter_sim.q;
    plot_dot_q_ist(schleife,:)=roboter_sim.dot_q;
    
    
    %9. Gelegentlich die aktuelle Zeit ausgeben
    if mod(schleife,100) == 0
        fprintf('t= %e (T= %e)\n',roboter_regler.zeit,T);
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


%rms regelfehler ausgeben
fprintf('RMS fehler fuer %s-regler war: [%e %e %e]\n', regler, rms(plot_q_soll-plot_q_ist,1))

figure
plot(plot_zeit,plot_q_soll,'-');
hold on;
plot(plot_zeit,plot_q_ist,'-.');
title (strcat('Soll- und Istwerte der Gelenkwinkel (regler: ', regler,')'));
xlabel('Zeit [sec]')
ylabel('Gelenkwinkel [rad]');
legend('q_{soll}(1)','q_{soll}(2)','q_{soll}(3)','q_{ist}(1)','q_{ist}(2)','q_{ist}(3)');



figure;
plot(plot_zeit,plot_q_soll-plot_q_ist,'-');
title (strcat('Regelfehler (soll-ist; regler: ',regler,')'));
xlabel('Zeit [sec]')
ylabel('Gelenkwinkel [rad]');
legend('Delta q(1)','Delta q(2)','Delta q(3)');
