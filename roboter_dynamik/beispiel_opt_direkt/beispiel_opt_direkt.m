%%% Beispiel Skript zur Trajektorienoptimierung mit direkter
%%% (Voll)diskretisierung (u, q und dot_q werde diskretisiert) 

%Aufraeumen
close all
clear all

%% 1. Parameter Setzen und Modell aufbauen
%Modell fuer Regelung und inverse Kinematik
roboter=erstelle_roboter();
% Parameter der Sollbahn
w_a=[0.75;0.0;0.0]; %Anfangsposition kartesisch
w_e=[0.0;0.75;0.5]; %Endposition kartesisch
T  = 1.0;       %Dauer der Sollbahn
dt = 5e-2;      %Länge des Diskretisierungs-Intervalls
Kx = 1.0;       %Verstärkung/Driftkompensation IK
Nt  = T/dt+1;    %Anzahl der Zeitschritte

%Anzahl der Freiheitsgrade des Optimierungsproblems
% Zeitpunkte Nt x 3 x anzahl winkel 
Nz   = roboter.N_Q*Nt*3;




%% 3.  Inverse Kinematik initialisieren (Loesung fuer Startwert w_a)
% mit Newton-Raphson Verfahren
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
    roboter.zeit=iteration;
    if iteration> maximale_anzahl_der_iterationen_die_zulaessig_sind
        error('Initialisierung Inverse Kinematik: keine Konvergenz!\n');
    end
    iteration=iteration+1;
end
%ok, alles gut gelaufen
%roboter.q hat jetzt den richtigen Wert

%% 4. IK-Loesung einer Gerade als Startloesung fuer die Optimierung
% Variablen initialisieren
ik_fehler=0;
ik_fehler_max=0;
dot_q_alt=zeros(roboter.N_Q,1);
schleife=1;


% Diskretisierte Werte 
ti=linspace(0,T,Nt)'; %Zeit
qi_init=zeros(Nt,3); %Gelenkwinkel
dot_qi_init=zeros(Nt,3); %Gelenkwinkelgeschwindigkeiten
tau_init=zeros(Nt,3); %Gelenkmomente

% Startwert aus IK fuer Gerade
%Schleife von Anfangs- bis Endzeit.
% dt ist der Reglertakt
for schleife=1:Nt
    %1. Zeiten synchronisieren
    zeit=ti(schleife);
    roboter.zeit=zeit;
    ti(schleife)=zeit;

    %2. Sollwerte berechnen
    [w_d,dot_w_d] = sollwerte_w(roboter.zeit,w_a, w_e, T);
    
    %3. Inverse Kinematik lösen
    %3.1 Direkte Kinematik berechnen
    roboter=berechne_dk_positionen(roboter);
    roboter=berechne_dk_jacobis(roboter);
    
    %3.2 Abweichung zum Zielpunkt
    dw=w_d-roboter.w;
     
    %3.3 effektive Sollgeschwindigkeit berechnen
    dot_w_d_effektiv = dot_w_d + Kx/dt * dw;
    
    %3.4  Gelenkwinkelgeschwindigkeit berechnen
    %      Verfahren der Inversen Jacobi
    roboter.dot_q=linsolve(roboter.Jw,dot_w_d_effektiv);
     
    %4 Soll-Gelenkwinkel und Beschleunigungen durch numerische
    %Differentiation bzw. Integration
    roboter.q=roboter.q + dt*roboter.dot_q;
    roboter.ddot_q=1/dt*(roboter.dot_q-dot_q_alt);
    %alten Zustand merken (fuer Berechnung ddot_q)
    dot_q_alt=roboter.dot_q;
    
    %5 Drehmomente aus inverser Dynamik
    roboter=berechne_id(roboter);
  
    %8. Daten als Startwerte merken
    qi_init(schleife,:)=roboter.q;
    dot_qi_init(schleife,:)=roboter.dot_q;
    tau_init(schleife,:)=roboter.tau_id;
    %9. Gelegentlich die aktuelle Zeit ausgeben
    if mod(schleife,100) == 0
        fprintf('t= %e (T= %e)\n',roboter.zeit,T);
    end
    
    %2. werte speichern
    %roboter=schreibe_daten(roboter);
end
%return;
%Wert der Guetefunktion fuer Startloesung
zi_init=[qi_init(:);dot_qi_init(:);tau_init(:)]

guete_init=guete_aufwand_z(zi_init,ti,roboter)


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Hier beginnt die eigentliche Optimierung
%% 5. Nebenbedingungen an die Loesung: Start und Endwert gleich
%Anzahl Nebenbedingungen fuer BGL : 2 Bedingungen pro Gelenk und Zeitpunkt
N_NB_BGL=Nt*roboter.N_Q*2;
% Anzahl der lineraren Randbedingungen: Anfangs- und Endpositionen und Geschwindigkeiten
N_NB_RB_LIN = 2*roboter.N_Q*2;

%N_NB = N_NB_BGL+N_NB_RB;

% Randbedingungen in der Form Aeq*z=beq
Aeq=zeros(N_NB_RB_LIN,Nz);
beq=zeros(N_NB_RB_LIN,1);

%Startwerte
Aeq(1,1)=1;%erste Gelenkwinkel, erster Zeitschritt bei z(1)
beq(1)=qi_init(1,1);
Aeq(2,Nt+1)=1;%zweiter Gelenkwinkel, erster Zeitschritt bei z(Nt+1)
beq(2)=qi_init(1,2);
Aeq(3,2*Nt+1)=1;%dritter Gelenkwinkel, erster Zeitschritt bei z(2*Nt+1)
beq(3)=qi_init(1,3);

Aeq(4,3*Nt+1)=1;%erst Gelenkwinkel-Geschwindigkeit, erster Zeitschritt bei z(3*Nt+1)
beq(4)=0; %Sollgeschwindigkeit Null
Aeq(5,4*Nt+1)=1;%zweite Gelenkwinkel-Geschwindigkeit, erster Zeitschritt bei z(4*Nt+1)
beq(5)=0;%Sollgeschwindigkeit Null
Aeq(6,5*Nt+1)=1;%dritte Gelenkwinkel-Geschwindigkeit, erster Zeitschritt bei z(5*Nt+1)
beq(6)=0;%Sollgeschwindigkeit Null


%Endwerte
Aeq(7,Nt)=1;%erste Gelenkwinkel, letzter Zeitschritt bei z(Nt)
beq(7)=qi_init(length(ti),1);
Aeq(8,2*Nt)=1;%zweiter Gelenkwinkel, letzter Zeitschritt bei z(2*Nt)
beq(8)=qi_init(length(ti),2);
Aeq(9,3*Nt)=1;%dritter Gelenkwinkel, letzter Zeitschritt bei z(3*Nt)
beq(9)=qi_init(length(ti),3);

Aeq(10,4*Nt)=1;%erst Gelenkwinkel-Geschwindigkeit, letzter Zeitschritt bei z(4*Nt)
beq(10)=0; %Sollgeschwindigkeit Null
Aeq(11,5*Nt)=1;%zweite Gelenkwinkel-Geschwindigkeit, letzter Zeitschritt bei z(5*Nt)
beq(11)=0;%Sollgeschwindigkeit Null
Aeq(12,6*Nt)=1;%dritte Gelenkwinkel-Geschwindigkeit, letzter Zeitschritt bei z(6*Nt)
beq(12)=0;%Sollgeschwindigkeit Null



%Guetefunktion ohne extra Parameter fuer fmincon [fmincon benoetigt eine
%Funktion, die nur vom zu bestimmenden Vektor z abhaengt]
guete_aufwand_fmincon=@(z) guete_aufwand_z(z,ti,roboter);

%Nebenbedingungen ohne extra Parameter fuer fmincon
% opt_bgl_nlcon sind die nichtlinearen Geleichungs-Nebenbedingungen fuer
% das Optimierungsproblem. Hier sind das die Bewegungsgleichungen in
% diskretisierter Form
opt_bgl_nlcon_fmincon =@(z) opt_bgl_nlcon(z,ti,roboter);


% optionen fuer die Optimierung
options.Display='iter';
options.MaxFunEvals=1e9;

%options.OutputFcn=@(x, optimValues, state) fprintf('output: x(4)= %e\n',x(4));
[zopt,fval]=fmincon(guete_aufwand_fmincon, zi_init(:), [],[], Aeq, beq,[],[],opt_bgl_nlcon_fmincon,options);


fval

% z zurueck in qi/dot_qi/ui wandeln
qi_opt=[zopt(1:Nt),zopt(Nt+1:2*Nt),zopt(2*Nt+1:3*Nt)];
dot_qi_opt=[zopt(3*Nt+1:4*Nt),zopt(4*Nt+1:5*Nt),zopt(5*Nt+1:6*Nt)];
ui_opt=[zopt(6*Nt+1:7*Nt),zopt(7*Nt+1:8*Nt),zopt(8*Nt+1:9*Nt)];

%% Ergebnis 

% Animationsdaten fuer optimierter Trajektorie produzieren
for schleife=1:length(ti)
    zeit=ti(schleife);
    %1. Werte in Roboterobjekt setzen
    roboter.zeit=zeit;
    roboter.q=qi_opt(schleife,:)';
    roboter.dot_q=dot_qi_opt(schleife,:)';
    roboter=berechne_dk_positionen(roboter);
    %roboter.ddot_q=ddot_qi_opt(schleife,:)'; 
    
    %2. werte speichern
    roboter=schreibe_daten(roboter);
end

%Plot Anfangsloesung
figure
plot(ti,qi_opt,'-');
title ('Gelenkwinkel (optimiert)');
xlabel('Zeit [sec]')
ylabel('Gelenkwinkel [rad]');
hold on;
plot(ti,qi_init,'--');
legend('q_{opt}(1)','q_{opt}(2)','q_{opt}(3)','q_{start}(1)','q_{start}(2)','q_{start}(3)');


figure;
plot(ti,ui_opt,'-');
title ('Gelenkmomente (optimiert)');
xlabel('Zeit [sec]')
ylabel('Gelenkmomente [Nm]');
hold on;
plot(ti,tau_init,'--');
legend('Q_{opt}(1)','Q_{opt}(2)','Q_{opt}(3)','Q_{start}(1)','Q_{start}(2)','Q_{start}(3)');


