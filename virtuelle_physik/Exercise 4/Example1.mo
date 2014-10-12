within ;
model Example1

  myHydraulics.Examples.Section   section
    annotation (Placement(transformation(extent={{-32,-10},{-12,10}})));
  myHydraulics.Examples.Section   section1
    annotation (Placement(transformation(extent={{-6,-10},{14,10}})));
  myHydraulics.Examples.Section   section2
    annotation (Placement(transformation(extent={{22,-10},{42,10}})));
  myHydraulics.Examples.Section   section3
    annotation (Placement(transformation(extent={{50,-10},{70,10}})));
  myHydraulics.Examples.Section   section4
    annotation (Placement(transformation(extent={{74,-10},{94,10}})));
  myHydraulics.Components.SignalPressure signalPressure
    annotation (Placement(transformation(extent={{-60,-10},{-40,10}})));
  Modelica.Blocks.Sources.Sine sine(amplitude=100, freqHz=60)
    annotation (Placement(transformation(extent={{-98,-10},{-78,10}})));
equation
  connect(section.pin2, section1.pin) annotation (Line(
      points={{-14.6,0},{-3.4,0}},
      color={0,0,255},
      thickness=0.5,
      smooth=Smooth.None));
  connect(section1.pin2, section2.pin) annotation (Line(
      points={{11.4,0},{24.6,0}},
      color={0,0,255},
      thickness=0.5,
      smooth=Smooth.None));
  connect(section2.pin2, section3.pin) annotation (Line(
      points={{39.4,0},{52.6,0}},
      color={0,0,255},
      thickness=0.5,
      smooth=Smooth.None));
  connect(sine.y, signalPressure.u) annotation (Line(
      points={{-77,0},{-58,0}},
      color={0,0,127},
      thickness=0.5,
      smooth=Smooth.None));
  connect(section3.pin2, section4.pin) annotation (Line(
      points={{67.4,0},{76.6,0}},
      color={0,0,255},
      thickness=0.5,
      smooth=Smooth.None));
  connect(signalPressure.first, section.pin) annotation (Line(
      points={{-41,0},{-29.4,0}},
      color={0,0,255},
      thickness=0.5,
      smooth=Smooth.None));
  annotation (Diagram(coordinateSystem(preserveAspectRatio=false, extent={{-100,
            -100},{100,100}}), graphics), uses(Modelica(version="3.2")));
end Example1;
