within ;
model HydraulicInductance
  extends OnePortHydraulics;
  parameter Real L;
  parameter Real D;
  parameter Real A;
equation
  der(v)*D*L/A = P;
  annotation (uses(Modelica(version="3.2")));
end HydraulicInductance;
