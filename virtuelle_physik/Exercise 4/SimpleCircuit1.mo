within ;
model SimpleCircuit1
  import E = Modelica.Electrical.Analog;
  E.Basic.Ground G;
  E.Basic.Resistor R(R=100);
  E.Basic.Capacitor C(C=0.001);
  E.Sources.ConstantVoltage V(V=10);
equation
  connect(G.p, V.n);
  connect(V.p, R.n);
  connect(R.p, C.p);
  connect(C.n, G.p);
  annotation (uses(Modelica(version="3.2")));
end SimpleCircuit1;
