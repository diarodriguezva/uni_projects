within ;
model Car
  Modelica.Mechanics.Rotational.Components.Damper damper(d=2)
    annotation (Placement(transformation(extent={{-84,-10},{-64,10}})));
  Modelica.Mechanics.Rotational.Components.Inertia inertia(J=0.1)
    annotation (Placement(transformation(extent={{-50,-10},{-30,10}})));
  Modelica.Mechanics.Rotational.Components.Inertia inertia1(J=0.1)
    annotation (Placement(transformation(extent={{20,-10},{40,10}})));
  Modelica.Mechanics.Rotational.Components.Damper damper1(d=1)
    annotation (Placement(transformation(extent={{58,-10},{78,10}})));
  Modelica.Mechanics.Rotational.Sources.ConstantTorque constantTorque(
      tau_constant=1) annotation (Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={0,-52})));
  Diferential diferential
    annotation (Placement(transformation(extent={{-10,-10},{10,10}})));
  Modelica.Mechanics.Rotational.Components.Fixed fixed annotation (Placement(
        transformation(
        extent={{-10,-10},{10,10}},
        rotation=-90,
        origin={-106,0})));
  Modelica.Mechanics.Rotational.Components.Fixed fixed1 annotation (Placement(
        transformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={102,0})));
equation
  connect(damper.flange_a, fixed.flange) annotation (Line(
      points={{-84,0},{-106,0}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(damper1.flange_b, fixed1.flange) annotation (Line(
      points={{78,0},{102,0}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(damper1.flange_a, inertia1.flange_b) annotation (Line(
      points={{58,0},{40,0}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(inertia1.flange_a, diferential.flange_right) annotation (Line(
      points={{20,0},{8,0}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(damper.flange_b, inertia.flange_a) annotation (Line(
      points={{-64,0},{-50,0}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(inertia.flange_b, diferential.flange_left) annotation (Line(
      points={{-30,0},{-8,0}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(diferential.flange_drive, constantTorque.flange) annotation (Line(
      points={{0,-8},{0,-26},{6.66134e-016,-26},{6.66134e-016,-42}},
      color={0,0,0},
      smooth=Smooth.None));
  annotation (
    uses(Modelica(version="3.2")),
    Diagram(coordinateSystem(extent={{-120,-100},{120,100}},
          preserveAspectRatio=false), graphics),
    Icon(coordinateSystem(extent={{-120,-100},{120,100}})));
end Car;
