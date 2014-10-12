within ;
model FrontAxisTwoTrack

  parameter Real WidhtCar = 1.5; //m
  parameter Real mWheel = 10;
  parameter Real IWheel = 1;
  parameter Real JAxis = 3;
  parameter Real N=400;
  parameter Real   vAdhesion=0.05;
  parameter Real   vSlide=0.15;
  parameter Real   mu_A=0.8;
  parameter Real   mu_S=0.4;
  parameter Real   radius=0.3;

  PlanarMechanicsV2.Parts.FixedTranslation Trail(r={-0.05,0})
                                                             annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={80,40})));
  PlanarMechanicsV2.VehicleComponents.Wheels.DryFrictionWheelJoint
    dryFrictionWheelJoint1(
N=N,vAdhesion= vAdhesion,
    vSlide=vSlide,
    mu_A=mu_A,
    mu_S=mu_S,
    radius=radius,
    r={1,0})    annotation (Placement(transformation(
        extent={{10,-10},{-10,10}},
        rotation=0,
        origin={50,50})));
  PlanarMechanicsV2.Parts.Body Front2(m=10, I=1)
    annotation (Placement(transformation(extent={{10,-10},{-10,10}},
        rotation=270,
        origin={68,76})));
  Modelica.Mechanics.Rotational.Components.Inertia inertia2(
                                                           J=3)
    annotation (Placement(transformation(extent={{12,40},{32,60}})));
  PlanarMechanicsV2.VehicleComponents.Wheels.DryFrictionWheelJoint
    dryFrictionWheelJoint3(
N=N,vAdhesion= vAdhesion,
    vSlide=vSlide,
    mu_A=mu_A,
    mu_S=mu_S,
    radius=radius,
    r={1,0})    annotation (Placement(transformation(
        extent={{10,-10},{-10,10}},
        rotation=180,
        origin={-48,50})));
  Modelica.Mechanics.Rotational.Components.Inertia inertia4(
                                                           J=3)
    annotation (Placement(transformation(extent={{-10,40},{-30,60}})));
  PlanarMechanicsV2.Parts.Body Front1(m=10, I=1)
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=90,
        origin={-72,76})));
  PlanarMechanicsV2.Parts.FixedTranslation FrontAxis2(r={0,-0.75})
    annotation (Placement(transformation(extent={{100,-30},{120,-10}})));
  PlanarMechanicsV2.Parts.FixedTranslation FrontAxis1(r={0,0.75}) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=180,
        origin={-114,-20})));
  PlanarMechanicsV2.Interfaces.Frame_a frame_a
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=90,
        origin={-1,-44}), iconTransformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={0,-76})));
  PlanarMechanicsV2.Joints.ActuatedRevolute actuatedRevolute annotation (
      Placement(transformation(
        extent={{-10,10},{10,-10}},
        rotation=90,
        origin={-88,-10})));
  PlanarMechanicsV2.Joints.ActuatedRevolute actuatedRevolute1 annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={80,-10})));
  PlanarMechanicsV2.Parts.FixedTranslation Trail1(r={-0.05,0})
                                                             annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={-88,40})));
  Modelica.Mechanics.Rotational.Components.Inertia SteeringInertia(J=15)
    annotation (Placement(transformation(extent={{10,-10},{-10,10}},
        rotation=270,
        origin={0,20})));
  Modelica.Mechanics.Rotational.Interfaces.Flange_b flange_b annotation (
      Placement(transformation(extent={{-10,66},{10,86}}), iconTransformation(
          extent={{-10,66},{10,86}})));
equation
  connect(dryFrictionWheelJoint3.flange_a,inertia4. flange_b) annotation (Line(
      points={{-38,50},{-30,50}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(inertia2.flange_b,dryFrictionWheelJoint1. flange_a) annotation (Line(
      points={{32,50},{40,50}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(Front2.frame_a,dryFrictionWheelJoint1. frame_a) annotation (Line(
      points={{68,66},{68,50},{54.8,50}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Front1.frame_a,dryFrictionWheelJoint3. frame_a) annotation (Line(
      points={{-72,66},{-72,50},{-52.8,50}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(actuatedRevolute.flange_a, actuatedRevolute1.flange_a) annotation (
      Line(
      points={{-78,-10},{70,-10}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(frame_a, FrontAxis2.frame_b) annotation (Line(
      points={{-1,-44},{120,-44},{120,-20}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Trail.frame_b, dryFrictionWheelJoint1.frame_a) annotation (Line(
      points={{80,50},{54.8,50}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(actuatedRevolute1.frame_b, Trail.frame_a) annotation (Line(
      points={{80,0},{80,30}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Trail1.frame_a, actuatedRevolute.frame_b) annotation (Line(
      points={{-88,30},{-88,0}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(actuatedRevolute1.frame_a, FrontAxis2.frame_a) annotation (Line(
      points={{80,-20},{100,-20}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(FrontAxis1.frame_a, actuatedRevolute.frame_a) annotation (Line(
      points={{-104,-20},{-88,-20}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(FrontAxis1.frame_b, frame_a) annotation (Line(
      points={{-124,-20},{-132,-20},{-132,-44},{-1,-44}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Trail1.frame_b, Front1.frame_a) annotation (Line(
      points={{-88,50},{-72,50},{-72,66}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(SteeringInertia.flange_b, flange_b)
                                       annotation (Line(
      points={{0,30},{0,76}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(flange_b, flange_b) annotation (Line(
      points={{0,76},{0,76}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(SteeringInertia.flange_a, actuatedRevolute.flange_a)
                                                        annotation (Line(
      points={{-1.77636e-015,10},{0,10},{0,-10},{-78,-10}},
      color={0,0,0},
      smooth=Smooth.None));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio=false, extent={{-140,-100},{
            140,100}}),
                    graphics),
    uses(Modelica(version="3.2")),
    Icon(coordinateSystem(extent={{-140,-100},{140,100}}, preserveAspectRatio=false),
                    graphics={Ellipse(extent={{-60,60},{60,-60}}, lineColor={0,
              0,255})}));
end FrontAxisTwoTrack;
