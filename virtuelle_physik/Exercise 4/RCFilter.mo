within ;
model RCFilter
  Modelica.Electrical.Analog.Basic.Capacitor capacitor(C=0.01) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=270,
        origin={-10,40})));
  Modelica.Electrical.Analog.Basic.Resistor resistor(R=5)
    annotation (Placement(transformation(extent={{-44,52},{-24,72}})));
  Modelica.Electrical.Analog.Interfaces.Pin pin
    annotation (Placement(transformation(extent={{-92,52},{-72,72}})));
  Modelica.Electrical.Analog.Interfaces.NegativePin pin_n
    annotation (Placement(transformation(extent={{-92,20},{-72,40}})));
  Modelica.Electrical.Analog.Interfaces.Pin pin1
    annotation (Placement(transformation(extent={{38,52},{58,72}})));
  Modelica.Electrical.Analog.Interfaces.NegativePin pin_n1
    annotation (Placement(transformation(extent={{38,20},{58,40}})));
equation
  connect(capacitor.p, resistor.n) annotation (Line(
      points={{-10,50},{-10,62},{-24,62}},
      color={0,0,255},
      smooth=Smooth.None));
  connect(resistor.p, pin) annotation (Line(
      points={{-44,62},{-82,62}},
      color={0,0,255},
      smooth=Smooth.None));
  connect(capacitor.n, pin_n) annotation (Line(
      points={{-10,30},{-82,30}},
      color={0,0,255},
      smooth=Smooth.None));
  connect(pin1, capacitor.p) annotation (Line(
      points={{48,62},{-10,62},{-10,50}},
      color={0,0,255},
      smooth=Smooth.None));
  connect(pin_n1, capacitor.n) annotation (Line(
      points={{48,30},{-10,30}},
      color={0,0,255},
      smooth=Smooth.None));
  annotation (uses(Modelica(version="3.2")), Diagram(coordinateSystem(
          preserveAspectRatio=false, extent={{-100,-100},{100,100}}), graphics));
end RCFilter;
