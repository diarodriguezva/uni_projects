within ;
model Yeast

  parameter Real V = 1 "volume of fermentation vessel";
  parameter Real s0 = 0.2 "inital concentration of sugar";
  parameter Real p0 = 1e-6 "initial population of yeast";

  parameter Real C_f = 50 "Feeding Coefficient [1/day]";
  parameter Real R = 10 "Reproductivity [1/day]";
  parameter Real S = 15 "Sensitivity w.r.t. alcohol [1/day]";
  parameter Real T_ref = 300 "reference temperature";

  Real p "population of yeast";
  Real b "birth rate";
  Real d "deathrate";

  Real s "concentration of sugar";
  Real a "concentration of alcohol";
  Real f "consumption of sugar (feeding)";

  Real T "current temperature";

initial equation

  p = p0;
  s = s0;

equation

  f = s * p * C_f * (T/T_ref);
  a = s0 - s;
  b = R * s;
  d =  S * a;
  T = 310;

  der(p) = p*(b-d);
  V*der(s) = -f;

  annotation (uses(Modelica(version="3.1")));
end Yeast;
