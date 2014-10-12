within ;
model SignalPressure
//   extends OnePortHydraulics;
//   Modelica.Blocks.Interfaces.RealInput P0;
// equation
//   P = P0;
//   annotation (uses(Modelica(version="3.2")));

  import SI =   Modelica.SIunits;
  Modelica.Blocks.Interfaces.RealInput P;

  // SI.Pressure P;
  SI.VolumeFlowRate v;

  Pin first;

equation
  P = first.P;
  v = first.v;

end SignalPressure;
