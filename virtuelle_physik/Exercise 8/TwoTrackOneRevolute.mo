within ;
model TwoTrack
  PlanarMechanicsV2.Parts.Body Rear1(m=10, I=1)
    annotation (Placement(transformation(extent={{10,-10},{-10,10}},
        rotation=90,
        origin={-72,-140})));
  PlanarMechanicsV2.VehicleComponents.DifferentialGear differentialGear
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=180,
        origin={0,-112})));
  PlanarMechanicsV2.Parts.Body Rear2(m=10, I=1)
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=270,
        origin={70,-140})));
  Modelica.Mechanics.Rotational.Components.Inertia inertia1(
                                                           J=3)
    annotation (Placement(transformation(extent={{-20,-122},{-40,-102}})));
  Modelica.Mechanics.Rotational.Components.Inertia inertia3(
                                                           J=3)
    annotation (Placement(transformation(extent={{20,-122},{40,-102}})));
  Modelica.Mechanics.Rotational.Sources.ConstantTorque constantTorque(
      tau_constant=80)
    annotation (Placement(transformation(extent={{-20,-88},{0,-68}})));
  PlanarMechanicsV2.VehicleComponents.Wheels.DryFrictionWheelJoint
    dryFrictionWheelJoint4(
    N=400,
    vAdhesion=0.05,
    vSlide=0.15,
    mu_A=0.8,
    mu_S=0.4,
    radius=0.3,
    r={1,0})    annotation (Placement(transformation(
        extent={{10,-10},{-10,10}},
        rotation=0,
        origin={58,-112})));
  PlanarMechanicsV2.VehicleComponents.Wheels.DryFrictionWheelJoint
    dryFrictionWheelJoint2(
    N=400,
    vAdhesion=0.05,
    vSlide=0.15,
    mu_A=0.8,
    mu_S=0.4,
    radius=0.3,
    r={1,0})    annotation (Placement(transformation(
        extent={{10,-10},{-10,10}},
        rotation=180,
        origin={-58,-112})));
  PlanarMechanicsV2.Parts.FixedTranslation RearAxis1(r={0,0.75}) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=180,
        origin={-90,-112})));
  PlanarMechanicsV2.Parts.FixedTranslation RearAxis2(r={0,-0.75})
    annotation (Placement(transformation(extent={{80,-122},{100,-102}})));
  PlanarMechanicsV2.Parts.FixedTranslation Chasis2(r={1.1,0}) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={0,2})));
  PlanarMechanicsV2.Parts.FixedTranslation Chasis(r={-1.1,0}) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=270,
        origin={0,-42})));
  PlanarMechanicsV2.Parts.Body Car(m=1600, I=1270)
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=180,
        origin={-22,-18})));
  PlanarMechanicsV2.Joints.Revolute revolute annotation (Placement(
        transformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={0,32})));
  PlanarMechanicsV2.Parts.FixedTranslation Trail(r={0.05,0}) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={0,66})));
  PlanarMechanicsV2.VehicleComponents.Wheels.DryFrictionWheelJoint
    dryFrictionWheelJoint1(
    N=400,
    vAdhesion=0.05,
    vSlide=0.15,
    mu_A=0.8,
    mu_S=0.4,
    radius=0.3,
    r={1,0})    annotation (Placement(transformation(
        extent={{10,-10},{-10,10}},
        rotation=0,
        origin={58,100})));
  PlanarMechanicsV2.Parts.Body Front2(m=10, I=1)
    annotation (Placement(transformation(extent={{10,-10},{-10,10}},
        rotation=270,
        origin={72,126})));
  Modelica.Mechanics.Rotational.Components.Inertia inertia2(
                                                           J=3)
    annotation (Placement(transformation(extent={{20,90},{40,110}})));
  PlanarMechanicsV2.VehicleComponents.Wheels.DryFrictionWheelJoint
    dryFrictionWheelJoint3(
    N=400,
    vAdhesion=0.05,
    vSlide=0.15,
    mu_A=0.8,
    mu_S=0.4,
    radius=0.3,
    r={1,0})    annotation (Placement(transformation(
        extent={{10,-10},{-10,10}},
        rotation=180,
        origin={-58,100})));
  Modelica.Mechanics.Rotational.Components.Inertia inertia4(
                                                           J=3)
    annotation (Placement(transformation(extent={{-20,90},{-40,110}})));
  PlanarMechanicsV2.Parts.Body Front1(m=10, I=1)
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=90,
        origin={-72,126})));
  PlanarMechanicsV2.Parts.FixedTranslation FrontAxis2(r={0,-0.75})
    annotation (Placement(transformation(extent={{82,90},{102,110}})));
  PlanarMechanicsV2.Parts.FixedTranslation FrontAxis1(r={0,0.75}) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=180,
        origin={-90,100})));
  PlanarMechanicsV2.Parts.Body Steering(m=0, I=15)
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=90,
        origin={0,100})));
equation
  connect(dryFrictionWheelJoint4.flange_a, inertia3.flange_b) annotation (Line(
      points={{48,-112},{40,-112}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(dryFrictionWheelJoint2.flange_a, inertia1.flange_b) annotation (Line(
      points={{-48,-112},{-40,-112}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(dryFrictionWheelJoint4.frame_a, RearAxis2.frame_a) annotation (Line(
      points={{62.8,-112},{80,-112}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(RearAxis1.frame_a, dryFrictionWheelJoint2.frame_a) annotation (Line(
      points={{-80,-112},{-62.8,-112}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Car.frame_a, Chasis.frame_a) annotation (Line(
      points={{-12,-18},{0,-18},{0,-32}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Rear1.frame_a, RearAxis1.frame_a) annotation (Line(
      points={{-72,-130},{-72,-112},{-80,-112}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Rear2.frame_a, dryFrictionWheelJoint4.frame_a) annotation (Line(
      points={{70,-130},{70,-112},{62.8,-112}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(RearAxis2.frame_b, Chasis.frame_b) annotation (Line(
      points={{100,-112},{110,-112},{110,-52},{0,-52}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(RearAxis1.frame_b, Chasis.frame_b) annotation (Line(
      points={{-100,-112},{-110,-112},{-110,-52},{0,-52}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Chasis2.frame_a, Car.frame_a) annotation (Line(
      points={{-4.44089e-016,-8},{-4.44089e-016,-18},{-12,-18}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(differentialGear.flange_right, inertia1.flange_a) annotation (Line(
      points={{-10,-112},{-20,-112}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(differentialGear.flange_left, inertia3.flange_a) annotation (Line(
      points={{10,-112},{20,-112}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(constantTorque.flange, differentialGear.flange_b) annotation (Line(
      points={{0,-78},{0,-102},{1.22125e-015,-102}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(revolute.frame_a, Chasis2.frame_b) annotation (Line(
      points={{-6.66134e-016,22},{-6.66134e-016,12},{6.66134e-016,12}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Trail.frame_a, revolute.frame_b) annotation (Line(
      points={{0,56},{4.44089e-016,56},{4.44089e-016,42}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(FrontAxis1.frame_a, dryFrictionWheelJoint3.frame_a) annotation (Line(
      points={{-80,100},{-62.8,100}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(dryFrictionWheelJoint3.flange_a, inertia4.flange_b) annotation (Line(
      points={{-48,100},{-40,100}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(inertia2.flange_b, dryFrictionWheelJoint1.flange_a) annotation (Line(
      points={{40,100},{48,100}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(dryFrictionWheelJoint1.frame_a, FrontAxis2.frame_a) annotation (Line(
      points={{62.8,100},{82,100}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Front2.frame_a, dryFrictionWheelJoint1.frame_a) annotation (Line(
      points={{72,116},{72,100},{62.8,100}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Front1.frame_a, dryFrictionWheelJoint3.frame_a) annotation (Line(
      points={{-72,116},{-72,100},{-62.8,100}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(FrontAxis2.frame_b, Trail.frame_b) annotation (Line(
      points={{102,100},{104,100},{104,76},{0,76}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(FrontAxis1.frame_b, Trail.frame_b) annotation (Line(
      points={{-100,100},{-110,100},{-110,76},{0,76}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Steering.frame_a, Trail.frame_b) annotation (Line(
      points={{0,90},{0,76}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio=false, extent={{-140,-160},{
            140,140}}), graphics),
    uses(Modelica(version="3.2")),
    Icon(coordinateSystem(extent={{-140,-160},{140,140}})));
end TwoTrack;
