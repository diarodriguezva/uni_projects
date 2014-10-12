within ;
model HydraulicSection

parameter Real L=1;
parameter Real A=1;
parameter Real D=1;
parameter Real Kc=1;
parameter Real Kr=1;

HydraulicInductance I(D=D,L=L,A=A);
CompresiveVolume C(Kc=Kc,L=L,A=A);
PipeFriction F(Kr=Kr);

Pin TubeIn;
Pin TubeOut;

equation
  connect(I.second,C.first);
  connect(C.first,F.first);

  connect(TubeIn,I.first);
  connect(TubeOut,F.second);

  annotation (uses(Modelica(version="3.2")));
end HydraulicSection;
