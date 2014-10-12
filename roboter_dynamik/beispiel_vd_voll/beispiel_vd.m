%% Beispiel zur Vorwaertsdynamik eines Knickarmroboters

%% 1. workspace aufraeumen (Variablen loeschen)
clear all;
close all;

%% 2. parameter setzen und Modell aufbauen
rob=erstelle_roboter();
%Endzeit fuer Zeitintegration
t_ende=4;
%Integrationsschritt fuer Euler Verfahren
dt=1e-3;
%Startwerte der Gelenkwinkel einstellen
rob.q=[0.0;-pi/4.0;0.0];
%Daten fuer spaetere Plots initialisieren
anzahl_zeitschritte=t_ende/dt+1;
plot_q=zeros(rob.N_Q,anzahl_zeitschritte);
plot_dot_q=zeros(rob.N_Q,anzahl_zeitschritte);
plot_ddot_q=zeros(rob.N_Q,anzahl_zeitschritte);
plot_zeit=[0:dt:t_ende];

%% Vorwaertsdynamik berechnen
%%Variante 1: Zeitintegration mit explizitem Euler-Verfahren
% Hinweis: Im allgemeinen Fall sollten Verfahren hoeherer Ordnung vorgezogen
% werden (z.B. ode45)
% Hier wird zur klareren Darstellung des Ablaufs das Euler-Verfahren
% bevorzugt
schleife=1;
for zeit=0:dt:t_ende
    rob.zeit=zeit;
    
    %Bewegungsgleichungen auswerten (ddot_q berechnen)
    rob=berechne_bgl(rob);
    %Expliziter Euler-Schritt
    rob.q= rob.q + dt*rob.dot_q;
    rob.dot_q= rob.dot_q + dt*rob.ddot_q;
    %Daten fuer Animation speichern
    rob=schreibe_daten(rob);
    %Daten fuer Plots merken
    plot_q(:,schleife)=rob.q;
    plot_dot_q(:,schleife)=rob.dot_q;
    plot_ddot_q(:,schleife)=rob.ddot_q;
    
    %Gelegentlich die Zeit ausgeben
    if mod(schleife,100)==0
        fprintf('zeit= %e\n', rob.zeit);
    end
    schleife=schleife+1;
end

