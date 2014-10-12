within ;
model WheelWithAxisTwoTrack

  parameter Real rAxis[2] = {0,0.75};

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
        origin={14,0})));
  Modelica.Mechanics.Rotational.Components.Inertia inertia4(
                                                           J=3)
    annotation (Placement(transformation(extent={{52,-10},{32,10}})));
  PlanarMechanicsV2.Parts.Body Front1(m=10, I=1)
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=90,
        origin={0,26})));
  PlanarMechanicsV2.Parts.FixedTranslation FrontAxis1(r=rAxis) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=180,
        origin={-18,0})));
  PlanarMechanicsV2.Interfaces.Frame_b frame_a
    annotation (Placement(transformation(extent={{-73,-10},{-53,10}})));
  Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_a annotation (
      Placement(transformation(extent={{76,-10},{96,10}}), iconTransformation(
          extent={{60,-10},{80,10}})));
equation
  connect(FrontAxis1.frame_a,dryFrictionWheelJoint3. frame_a) annotation (Line(
      points={{-8,0},{9.2,0}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(dryFrictionWheelJoint3.flange_a,inertia4. flange_b) annotation (Line(
      points={{24,0},{32,0}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(Front1.frame_a,dryFrictionWheelJoint3. frame_a) annotation (Line(
      points={{0,16},{0,0},{9.2,0}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(frame_a, FrontAxis1.frame_b) annotation (Line(
      points={{-63,0},{-28,0}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(inertia4.flange_a, flange_a) annotation (Line(
      points={{52,0},{86,0}},
      color={0,0,0},
      smooth=Smooth.None));
  annotation (
    uses(Modelica(version="3.2")),
    Diagram(coordinateSystem(preserveAspectRatio=false, extent={{-100,-100},{100,
            100}}), graphics),
    Icon(coordinateSystem(preserveAspectRatio=false, extent={{-100,-100},{100,100}}),
        graphics={Ellipse(extent={{-58,60},{60,-60}}, lineColor={0,0,255})}));
end WheelWithAxisTwoTrack;
