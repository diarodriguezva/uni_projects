function  f=guete_aufwand(zi,ti,roboter)
%%Guetefunktion: Integral ueber Quadrat der Antriebsmomente als funktion
%%von q, dot(q) und u. zi sind die werte von q, dot(q) und u zu den 
%%Zeitpunkten ti

%1. Geschwindigkeit und Beschleunigung aus finiter Differenzen-Approximation.
%Annahme: Gleichverteilte ti!
dt=ti(2)-ti(1);
Nt=length(ti);
%Vektor der Optimierungsparameter in Matrix wandeln, um Zugriff zu
%erleichtern
qi=[zi(1:Nt),zi(Nt+1:2*Nt),zi(2*Nt+1:3*Nt)];
dot_qi=[zi(3*Nt+1:4*Nt),zi(4*Nt+1:5*Nt),zi(5*Nt+1:6*Nt)];
ui=[zi(6*Nt+1:7*Nt),zi(7*Nt+1:8*Nt),zi(8*Nt+1:9*Nt)];



%2. Integrand auswerten

fi=zeros(length(qi),1);
for schleife=1:length(ti)
    zeit=ti(schleife);
 
    fi(schleife)=0.5*ui(schleife,:)*ui(schleife,:)';
end

%3. Numerische Integration mit Trapezregel
f=dt*trapz(fi);

end
