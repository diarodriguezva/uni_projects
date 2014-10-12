%% Beispiel zur direkten Kinematik eines Knickarmroboters

%1. Workspace aufraeumen (variablen loeschen)
clear all;

%2. Parameter setzen und Modell aufbauen
rob=erstelle_roboter();
theta_end=pi/4;
delta_theta=pi/20;

%3. Direkte kinematik fuer unterschiedliche Gelenkwinkel berechnen
schleife=1;
%Variable zur Speicherung der Punkte auf der TCP-Trajektorie 
plot_w=zeros(3*(theta_end/delta_theta+1),3);
for i=1:rob.N_Q %schleife ueber alle Gelenke
    for qi=0:delta_theta:theta_end %i-ten Gelenkwinkel variieren
        rob.q(i)=qi;
        
        %% Zwei Varianten zur Berechnung der direkten Kinematik; 
        %eine davon sollte einkommentiert werden.
        % Variante 1: Direkte Kinematik mit Vektorkette
        rob=berechne_dk_positionen(rob);
        % Variante 2: Direkte Kinematik mit Homogenen
        % Transformationsmatrizen
        %rob=berechne_dk_positionen_dh_trafo(rob);
        
        rob=schreibe_daten(rob);
        plot_w(schleife,:)=rob.w;
        rob.zeit=rob.zeit+0.1;
        schleife=schleife+1;
    end
end

%4. Kurve des TCP als 3D-Plot darstellen
plot3(plot_w(:,1),plot_w(:,2),plot_w(:,3));
xlabel('x')
ylabel('y')
zlabel('z')
grid on
axis square


