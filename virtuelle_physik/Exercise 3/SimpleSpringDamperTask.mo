within ;
model SimpleSpringDamperTask
  Modelica.Mechanics.Translational.Components.Fixed fixed(s0=0) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=180,
        origin={-10,70})));
  Modelica.Mechanics.Translational.Components.Spring spring(c=10, s_rel0=0) 
    annotation (Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=270,
        origin={10,40})));
  Modelica.Mechanics.Translational.Components.Damper damper(d=2) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=270,
        origin={-30,40})));
  Modelica.Mechanics.Translational.Components.Mass mass(m=1) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=270,
        origin={-10,10})));
  Modelica.Mechanics.Translational.Sources.Force force annotation (Placement(
        transformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={-10,-20})));
  Modelica.Blocks.Sources.Constant const(k=-10) annotation (Placement(
        transformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={-10,-56})));
equation
  connect(fixed.flange, damper.flange_a) annotation (Line(
      points={{-10,70},{-10,60},{-30,60},{-30,50}},
      color={0,127,0},
      smooth=Smooth.None));
  connect(fixed.flange, spring.flange_a) annotation (Line(
      points={{-10,70},{-10,60},{10,60},{10,50}},
      color={0,127,0},
      smooth=Smooth.None));
  connect(damper.flange_b, mass.flange_a) annotation (Line(
      points={{-30,30},{-30,20},{-10,20}},
      color={0,127,0},
      smooth=Smooth.None));
  connect(spring.flange_b, mass.flange_a) annotation (Line(
      points={{10,30},{10,20},{-10,20}},
      color={0,127,0},
      smooth=Smooth.None));
  connect(const.y, force.f) annotation (Line(
      points={{-10,-45},{-10,-32}},
      color={0,0,127},
      smooth=Smooth.None));
  connect(force.flange, mass.flange_b) annotation (Line(
      points={{-10,-10},{-10,0}},
      color={0,127,0},
      smooth=Smooth.None));
  annotation (uses(Modelica(version="3.1")), Diagram(graphics));
end SimpleSpringDamperTask;
