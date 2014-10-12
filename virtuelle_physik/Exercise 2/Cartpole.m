%% CartPole

Ms = 250;
Mp = 70;
R = 2.5;

v(1) = 0;
Omega(1) = 0;
s(1) = 0;
Theta(1) = 1.25;

G = -9.81;

h = 0.001;
n = 1;
t = 0;

while t<=5
    ds_dt(n) = v(n);
    s(n+1) = s(n)+ds_dt(n)*h;
    
    dv_dt(n) = Mp*sin(Theta(n))*(R*(Omega(n)^2)-G*cos(Theta(n)))/(Ms+Mp*(1-(cos(Theta(n)))^2));
    v(n+1) = v(n)+(dv_dt(n))*h;
    
    dTheta_dt(n) = Omega(n);
    Theta(n+1) = Theta(n)+dTheta_dt(n)*h;
    
    dOmega_dt(n) = ((G.*sin(Theta(n)).*(Ms+Mp))-Mp.*R.*(Omega(n)^2).*(sin(Theta(n))).*(cos(Theta(n))))/(Ms+Mp.*(1-(cos(Theta(n)))^2))/R;
    Omega(n+1) = Omega(n)+(dOmega_dt(n))*h;
    
    t = t+h;
    n = n+1;
end

plot(v)
hold on
grid on
plot(Omega,'r')