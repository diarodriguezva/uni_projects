
function [c,ceq] = opt_bgl_nlcon(zi,ti,roboter)
%Berechnet die Einhaltung der BGL fuer eine diskretisierte Trajektorie zi
%zu den zeitpunkten ti
c = [];     % keine ungleichungsnebenbedingungen
%ceq =     % das sind die gleichungs-nebenbedingungen

% fuer alle k: x(k+1)=x(k)+a(x(k),u(x(k)),t(k))*(t(k+1)-t(k))
% ==> ceq(k) = -x(k+1)+x(k)+a(x(k),u(x(k)),t(k))*(t(k+1)-t(k))

%Anzahl der Stuetzstellen
Nt=length(ti);

Nq=roboter.N_Q;
%nebenbedingungen fuer xi(2)...xi(Nt)
ceq=zeros(roboter.N_Q*2*(Nt-1),1); 

% z zurueck in qi/dot_qi/ui wandeln
qi=[zi(1:Nt),zi(Nt+1:2*Nt),zi(2*Nt+1:3*Nt)];
dot_qi=[zi(3*Nt+1:4*Nt),zi(4*Nt+1:5*Nt),zi(5*Nt+1:6*Nt)];
ui=[zi(6*Nt+1:7*Nt),zi(7*Nt+1:8*Nt),zi(8*Nt+1:9*Nt)];

for k=1:Nt-1
    roboter.q = qi(k,:)';
    roboter.dot_q=dot_qi(k,:)';
    roboter.tau_reg=ui(k,:)';
    roboter=berechne_bgl(roboter);
    %rechte seite der BGL 1. Ordnung bei t(k)
    ak = [roboter.dot_q;roboter.ddot_q];
    xk = [qi(k,:)';dot_qi(k,:)'];
    xk_plus_eins=[qi(k+1,:)';dot_qi(k+1,:)'];
    ceq((k-1)*2*Nq+1:k*2*Nq)=-xk_plus_eins+xk+ak*(ti(k+1)-ti(k));
end
 