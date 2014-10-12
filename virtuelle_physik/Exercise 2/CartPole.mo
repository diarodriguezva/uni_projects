within ;
model CartPole

parameter Real Ms = 250 "Kg";
parameter Real Mp = 70 "Kg";
parameter Real R = 2.5 "m";

parameter Real v0 = 0;
parameter Real Omega0 = 0;
parameter Real s0 = 0;
parameter Real Theta0 = 1.25;

parameter Real G = -9.81;

Real s;
Real v;
Real Theta;
Real Omega;
Real a;
Real Alpha;
Real T;
Real Fn;
Real Fz;
Real Fp;
Real Fs;
Real ap;

Real I = Mp * (R^2);

initial equation

v = v0;
s = s0;
Omega = Omega0;
Theta = Theta0;

equation

  a = der(v);
  v = der(s);
  Fs = Ms*a;

  Alpha = der(Omega);
  Omega = der(Theta);
  T = I*Alpha;

  T = Fn*R;
  Fn = Mp*G*sin(Theta)-Mp*ap*cos(Theta);

  Fz = Mp*R*(Omega^2);
  Fp+Fz*sin(Theta)-Fn*cos(Theta)-Mp*ap = 0;

  ap = a;
  Fp = -Fs;

  annotation (uses(Modelica(version="3.2")));
end CartPole;
