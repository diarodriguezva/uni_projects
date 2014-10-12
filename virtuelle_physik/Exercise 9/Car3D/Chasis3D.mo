within ;
model Chasis3D

  parameter Real c_roll = 20000;
  parameter Real d_roll = 2000;
  parameter Real c_pitch = 20000;
  parameter Real d_pitch = 2000;

  parameter Real WheelBase = 2.2; //m
  parameter Real WeightCar = 1600;
  parameter Real InertiaCar = 1270;

  PlanarMechanicsV2.Parts.FixedTranslation Chasis2(r={WheelBase/2,0}) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={-80,30})));
  PlanarMechanicsV2.Parts.FixedTranslation Chasis(r={-WheelBase/2,0}) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=270,
        origin={-80,-30})));
  PlanarMechanicsV2.Parts.Body Car(m=WeightCar, I=InertiaCar)
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=180,
        origin={-100,0})));
  PlanarMechanicsV2.Interfaces.Frame_b frame_a
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=90,
        origin={-79,-64}),
                         iconTransformation(extent={{-9,60},{11,80}})));
  PlanarMechanicsV2.Interfaces.Frame_b frame_a1
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=90,
        origin={-80,64}),
                        iconTransformation(extent={{-9,-86},{11,-66}})));
  Interface2D3D interface2D3D
    annotation (Placement(transformation(extent={{-64,-8},{-44,8}})));
  Modelica.Mechanics.MultiBody.Joints.Revolute Roll(useAxisFlange=true, n={1,0,0})
    annotation (Placement(transformation(extent={{-40,-10},{-20,10}})));
  Modelica.Mechanics.MultiBody.Joints.Revolute Pitch(n={0,1,0}, useAxisFlange=true)
    annotation (Placement(transformation(extent={{0,-10},{20,10}})));
  Modelica.Mechanics.Rotational.Components.SpringDamper springDamper_roll(c=
        c_roll, d=d_roll) annotation (Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=0,
        origin={-30,30})));
  Modelica.Mechanics.Rotational.Components.SpringDamper springDamper_pitch(c=
        c_pitch, d=d_pitch) annotation (Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=0,
        origin={10,30})));
  Modelica.Mechanics.MultiBody.Parts.Body body
    annotation (Placement(transformation(extent={{80,-10},{100,10}})));
  Modelica.Mechanics.MultiBody.Parts.FixedTranslation CenterToTop(r={0,0,0.5})
    annotation (Placement(transformation(extent={{40,-10},{60,10}})));
equation
  connect(Car.frame_a,Chasis. frame_a) annotation (Line(
      points={{-90,0},{-80,0},{-80,-20}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Chasis2.frame_a,Car. frame_a) annotation (Line(
      points={{-80,20},{-80,0},{-90,0}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Chasis.frame_b,frame_a)  annotation (Line(
      points={{-80,-40},{-80,-64},{-79,-64}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(frame_a1,Chasis2. frame_b) annotation (Line(
      points={{-80,64},{-80,40}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Chasis2.frame_a, interface2D3D.frame_a) annotation (Line(
      points={{-80,20},{-80,-0.1},{-59,-0.1}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(springDamper_roll.flange_a, Roll.support) annotation (Line(
      points={{-40,30},{-40,10},{-36,10}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(springDamper_roll.flange_b, Roll.axis) annotation (Line(
      points={{-20,30},{-20,10},{-30,10}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(springDamper_pitch.flange_a, Pitch.support) annotation (Line(
      points={{0,30},{0,10},{4,10}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(springDamper_pitch.flange_b, Pitch.axis) annotation (Line(
      points={{20,30},{20,10},{10,10}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(Roll.frame_a, interface2D3D.frame_b) annotation (Line(
      points={{-40,0},{-49.8,0}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Roll.frame_b, Pitch.frame_a) annotation (Line(
      points={{-20,0},{0,0}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(CenterToTop.frame_a, Pitch.frame_b) annotation (Line(
      points={{40,0},{20,0}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(CenterToTop.frame_b, body.frame_a) annotation (Line(
      points={{60,0},{80,0}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio=false, extent={{-120,-100},{120,
            100}}), graphics),
    uses(Modelica(version="3.2")),
    Icon(coordinateSystem(extent={{-120,-100},{120,100}}), graphics={
        Rectangle(extent={{40,60},{60,-60}}, lineColor={0,0,255}),
        Line(
          points={{40,40},{-40,40},{-40,40}},
          color={0,0,255},
          smooth=Smooth.None),
        Rectangle(extent={{-60,60},{-40,-60}}, lineColor={0,0,255}),
        Line(
          points={{-40,-40},{40,-40}},
          color={0,0,255},
          smooth=Smooth.None)}));
end Chasis3D;
