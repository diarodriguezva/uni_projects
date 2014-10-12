function rob=schreibe_daten(rob)
%Funktion zur Sicherung der Positionen und Orientierungen des Roboters,
%damit diese im Animationsprogram dargestellt werden koennen
%
% Beim ersten Aufruf werden die Dateien geoeffnet und in das Feld
% rob.animations_datei gespeichert.
%
% Parameter: Roboter rob

for i=1:length(rob.kl)
    
    %% falls die Datei noch nicht offen ist, dann diese OEffnen
    if rob.animations_datei(i) == -1
        filename=sprintf('animations_datei_%02d.dat',i-1); %indizierung im Animationsprogram von 0..N-1
        rob.animations_datei(i)=fopen(filename,'w');
        
        %Dimension des Koerpers in 1. Zeile der Datei schreiben
        %Mittelpunkt des Quaders in der Animation relativ zum Urprung: dx dy dz
        %Dimension des Quaders: lx ly lz
        fprintf(rob.animations_datei(i),'#%e %e %e %e %e %e\n',...
            rob.kl(i).geometrie(1),rob.kl(i).geometrie(2),rob.kl(i).geometrie(3),...
            rob.kl(i).geometrie(4),rob.kl(i).geometrie(5),rob.kl(i).geometrie(6));
        %Beschreibung der Spalten in 2. Zeile Schreiben
        fprintf(rob.animations_datei(i),'#time ');
        for k=1:3
            fprintf(rob.animations_datei(i),'r_i_B0(%d) ', k);
        end
        for k=1:3
            for l=1:3
                fprintf(rob.animations_datei(i), ' T_B0(%d,%d) ',l,k);
            end
        end
        fprintf(rob.animations_datei(i),'\n');
    end
    
    %%Daten fuer Animation Schreiben
    fprintf(rob.animations_datei(i),'%e %e %e %e %e %e %e %e %e %e %e %e %e\n', rob.zeit, rob.kl(i).B0_r_i,rob.kl(i).A_i0(:));    
end

end

