within ;
model SimpleCircuit2
  import E = Modelica.Electrical.Analog;
  E.Basic.Ground G;
  E.Basic.Resistor R1(R=100);
  E.Basic.Resistor R2(R=20);
  E.Basic.Capacitor C(C=1e-6);
  E.Sources.SineVoltage V(V=10,freqHz=60);
  E.Basic.Inductor L(L=0.0015);
equation
  connect(G.p, V.n);
  connect(V.p, R1.n);
  connect(V.p, L.p);
  connect(R1.p, C.p);
  connect(R1.p, R2.n);
  connect(C.n, G.p);
  connect(R2.n, G.p);
  connect(L.n, G.p);
  annotation (uses(Modelica(version="3.2")));
end SimpleCircuit2;
