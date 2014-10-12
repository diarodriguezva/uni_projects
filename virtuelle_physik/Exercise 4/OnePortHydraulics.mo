within ;
model OnePortHydraulics

  import SI =   Modelica.SIunits;

  SI.Pressure P;
  SI.VolumeFlowRate v;

  Pin first;
  Pin second;

equation
  P = first.P - second.P;
  first.v + second.v = 0;
  v = first.v;
  annotation (uses(Modelica(version="3.2")));
end OnePortHydraulics;
