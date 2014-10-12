within ;
model TwoTrackFinal
  RearAxisTwoTrack rearAxisTwoTrack annotation (Placement(transformation(
        extent={{-12,-10},{12,10}},
        rotation=180,
        origin={-12,8})));
  FrontAxisTwoTrack frontAxisTwoTrack
    annotation (Placement(transformation(extent={{-24,60},{0,80}})));
  ChasisTwoTrack chasisTwoTrack
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=180,
        origin={-12,38})));
  Modelica.Mechanics.Rotational.Sources.Torque torque
    annotation (Placement(transformation(extent={{-72,-10},{-52,10}})));
  Modelica.Mechanics.Rotational.Sources.Torque torque1
    annotation (Placement(transformation(extent={{40,70},{20,90}})));
  Modelica.Blocks.Sources.Pulse pulse(period=2, amplitude=0.5)
    annotation (Placement(transformation(extent={{96,70},{76,90}})));
  Modelica.Blocks.Sources.Ramp ramp(height=80, duration=2)
    annotation (Placement(transformation(extent={{-118,-10},{-98,10}})));
equation
  connect(torque.flange, rearAxisTwoTrack.flange_a) annotation (Line(
      points={{-52,0},{-12,0}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(frontAxisTwoTrack.frame_a, chasisTwoTrack.frame_a1) annotation (Line(
      points={{-12,62.4},{-12,51.4},{-12.1,51.4},{-12.1,45.6}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(chasisTwoTrack.frame_a, rearAxisTwoTrack.frame_a) annotation (Line(
      points={{-12.1,31},{-12.1,15.6}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(frontAxisTwoTrack.flange_b, torque1.flange) annotation (Line(
      points={{-12,77.6},{-12,80},{20,80}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(pulse.y, torque1.tau) annotation (Line(
      points={{75,80},{42,80}},
      color={0,0,127},
      smooth=Smooth.None));
  connect(ramp.y, torque.tau) annotation (Line(
      points={{-97,0},{-74,0}},
      color={0,0,127},
      smooth=Smooth.None));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio=false, extent={{-140,-160},{
            140,140}}), graphics),
    uses(Modelica(version="3.2")),
    Icon(coordinateSystem(extent={{-140,-160},{140,140}})));
end TwoTrackFinal;
