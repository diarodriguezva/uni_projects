within ;
model Reel

 import SI = Modelica.SIunits;

 Modelica.Mechanics.Translational.Interfaces.Flange_a flangeT;
 Modelica.Mechanics.Rotational.Interfaces.Flange_a flangeR;

 constant Real pi = 3.14159;
 parameter Real r0 = 0.1;
 parameter Real d = 0.0004;

 Real r;

equation
  r = r0 + flangeR.phi*d/(2*pi);
  der(flangeT.s) = der(flangeR.phi)*r;
  flangeR.tau = flangeT.f*r;

  annotation (uses(Modelica(version="3.2")));
end Reel;
