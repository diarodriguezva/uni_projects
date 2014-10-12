within ;
model RearAxisTwoTrack

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

  PlanarMechanicsV2.Interfaces.Frame_b frame_a
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=90,
        origin={-1,-72}),iconTransformation(extent={{-9,-86},{11,-66}})));
  Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_a annotation (
      Placement(transformation(extent={{-10,44},{10,64}}), iconTransformation(
          extent={{-10,70},{10,90}})));
  PlanarMechanicsV2.Parts.Body Rear1(m=mWheel, I=IWheel)
    annotation (Placement(transformation(extent={{10,-10},{-10,10}},
        rotation=90,
        origin={-70,-28})));
  PlanarMechanicsV2.Parts.Body Rear2(m=mWheel, I=IWheel)
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=270,
        origin={72,-28})));
  Modelica.Mechanics.Rotational.Components.Inertia inertia1(
                                                           J=JAxis)
    annotation (Placement(transformation(extent={{-10,-10},{-30,10}})));
  Modelica.Mechanics.Rotational.Components.Inertia inertia3(
                                                           J=JAxis)
    annotation (Placement(transformation(extent={{10,-10},{30,10}})));
  PlanarMechanicsV2.VehicleComponents.Wheels.DryFrictionWheelJoint
    dryFrictionWheelJoint4(
    N=N,
    vAdhesion= vAdhesion,
    vSlide=vSlide,
    mu_A=mu_A,
    mu_S=mu_S,
    radius=radius,
    r={1,0})    annotation (Placement(transformation(
        extent={{10,-10},{-10,10}},
        rotation=0,
        origin={60,0})));
  PlanarMechanicsV2.VehicleComponents.Wheels.DryFrictionWheelJoint
dryFrictionWheelJoint2(
    N=N,
    vAdhesion= vAdhesion,
    vSlide=vSlide,
    mu_A=mu_A,
    mu_S=mu_S,
    radius=radius,
    r={1,0})    annotation (Placement(transformation(
        extent={{10,-10},{-10,10}},
        rotation=180,
        origin={-56,0})));
  PlanarMechanicsV2.Parts.FixedTranslation RearAxis1(r={0,WidhtCar/2}) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=180,
        origin={-88,0})));
  PlanarMechanicsV2.Parts.FixedTranslation RearAxis2(r={0,-WidhtCar/2})
    annotation (Placement(transformation(extent={{82,-10},{102,10}})));
  PlanarMechanicsV2.VehicleComponents.DifferentialGear differentialGear
    annotation (Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=180,
        origin={0,20})));
equation
  connect(dryFrictionWheelJoint4.flange_a,inertia3. flange_b) annotation (Line(
      points={{50,0},{30,0}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(dryFrictionWheelJoint2.flange_a,inertia1. flange_b) annotation (Line(
      points={{-46,0},{-30,0}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(dryFrictionWheelJoint4.frame_a,RearAxis2. frame_a) annotation (Line(
      points={{64.8,0},{82,0}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(RearAxis1.frame_a,dryFrictionWheelJoint2. frame_a) annotation (Line(
      points={{-78,0},{-60.8,0}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Rear1.frame_a,RearAxis1. frame_a) annotation (Line(
      points={{-70,-18},{-70,0},{-78,0}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Rear2.frame_a,dryFrictionWheelJoint4. frame_a) annotation (Line(
      points={{72,-18},{72,0},{64.8,0}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(frame_a, RearAxis1.frame_b) annotation (Line(
      points={{-1,-72},{-106,-72},{-106,1.33227e-015},{-98,1.33227e-015}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(frame_a, RearAxis2.frame_b) annotation (Line(
      points={{-1,-72},{102,-72},{102,0}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(differentialGear.flange_b, flange_a) annotation (Line(
      points={{1.33227e-015,30},{0,30},{0,54}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(differentialGear.flange_right, dryFrictionWheelJoint2.flange_a)
    annotation (Line(
      points={{-10,20},{-40,20},{-40,-1.33227e-015},{-46,-1.33227e-015}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(differentialGear.flange_left, dryFrictionWheelJoint4.flange_a)
    annotation (Line(
      points={{10,20},{40,20},{40,0},{50,0}},
      color={0,0,0},
      smooth=Smooth.None));
  annotation (
    uses(Modelica(version="3.2")),
    Diagram(coordinateSystem(preserveAspectRatio=false, extent={{-120,-100},{
            120,100}}),
                    graphics),
    Icon(coordinateSystem(preserveAspectRatio=false, extent={{-120,-100},{120,
            100}}),
        graphics={Ellipse(extent={{-58,60},{60,-60}}, lineColor={0,0,255})}));
end RearAxisTwoTrack;
