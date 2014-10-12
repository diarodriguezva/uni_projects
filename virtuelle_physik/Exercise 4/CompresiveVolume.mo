within ;
model CompresiveVolume

  import SI =   Modelica.SIunits;

  SI.Pressure P;
  SI.VolumeFlowRate v;

  Pin first;

  parameter Real Kc;
  parameter Real L;
  parameter Real A;

equation
   der(P)*Kc*A*L = v;
   P = first.P;
   v = first.v;
   annotation (uses(Modelica(version="3.2")));
end CompresiveVolume;
