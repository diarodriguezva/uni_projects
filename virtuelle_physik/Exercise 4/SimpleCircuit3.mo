within ;
model SimpleCircuit3
  Modelica.Blocks.Sources.Pulse pulse(amplitude=10, period=0.5)
    annotation (Placement(transformation(extent={{-76,6},{-56,26}})));
  Modelica.Blocks.Math.Add add(k1=-1) annotation (Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={24,68})));
  Modelica.Electrical.Analog.Sources.SignalVoltage signalVoltage annotation (
      Placement(transformation(
        extent={{10,-10},{-10,10}},
        rotation=90,
        origin={-31,16})));
  Modelica.Electrical.Analog.Sensors.VoltageSensor voltageSensor annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={58,16})));
  Modelica.Electrical.Analog.Basic.Ground ground
    annotation (Placement(transformation(extent={{-24,-32},{-4,-12}})));
  RCFilter rCFilter
    annotation (Placement(transformation(extent={{12,10},{32,30}})));
equation
  connect(voltageSensor.v, add.u2) annotation (Line(
      points={{68,16},{50,16},{50,56},{30,56}},
      color={0,0,127},
      smooth=Smooth.None));
  connect(signalVoltage.v, pulse.y) annotation (Line(
      points={{-38,16},{-55,16}},
      color={0,0,127},
      smooth=Smooth.None));
  connect(signalVoltage.n, ground.p) annotation (Line(
      points={{-31,6},{-13.5,6},{-13.5,-12},{-14,-12}},
      color={0,0,255},
      smooth=Smooth.None));
  connect(signalVoltage.p, rCFilter.pin) annotation (Line(
      points={{-31,26},{-8,26},{-8,26.2},{13.8,26.2}},
      color={0,0,255},
      smooth=Smooth.None));
  connect(rCFilter.pin_n, ground.p) annotation (Line(
      points={{13.8,23},{-14,23},{-14,-12}},
      color={0,0,255},
      smooth=Smooth.None));
  connect(rCFilter.pin1, voltageSensor.n) annotation (Line(
      points={{26.8,26.2},{42.4,26.2},{42.4,26},{58,26}},
      color={0,0,255},
      smooth=Smooth.None));
  connect(rCFilter.pin1, voltageSensor.p) annotation (Line(
      points={{26.8,26.2},{42.4,26.2},{42.4,6},{58,6}},
      color={0,0,255},
      smooth=Smooth.None));
  connect(add.u1, signalVoltage.v) annotation (Line(
      points={{18,56},{-46,56},{-46,16},{-38,16}},
      color={0,0,127},
      smooth=Smooth.None));
  annotation (uses(Modelica(version="3.2")), Diagram(coordinateSystem(
          preserveAspectRatio=false, extent={{-100,-100},{100,100}}), graphics));
end SimpleCircuit3;
