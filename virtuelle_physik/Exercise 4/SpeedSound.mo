within ;
model SpeedSound

  HydraulicSection one(
    L=0.2,
    D=1.29,
    A=0.01,
    Kc=1e-5,
    Kr=5000);
  HydraulicSection two(
    L=0.2,
    D=1.29,
    A=0.01,
    Kc=1e-5,
    Kr=5000);
  HydraulicSection three(
    L=0.2,
    D=1.29,
    A=0.01,
    Kc=1e-5,
    Kr=5000);
  HydraulicSection four(
    L=0.2,
    D=1.29,
    A=0.01,
    Kc=1e-5,
    Kr=5000);
  HydraulicSection five(
    L=0.2,
    D=1.29,
    A=0.01,
    Kc=1e-5,
    Kr=5000);

  SignalPressure source;

  Modelica.Blocks.Sources.Pulse signal(amplitude=100, period=1/60);

equation
  connect(signal.y, source.P);

  connect(source.first, one.TubeIn);
  connect(one.TubeOut, two.TubeIn);
  connect(two.TubeOut, three.TubeIn);
  connect(three.TubeOut, four.TubeIn);
  connect(four.TubeOut, five.TubeIn);

  annotation (uses(Modelica(version="3.2")));
end SpeedSound;
