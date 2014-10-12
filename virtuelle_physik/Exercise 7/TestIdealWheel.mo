within ;
model TestIdealWheel
  PlanarMechanicsV2.Parts.Body
             body(
    I=0.1,
    g={0,-9.81},
    m=1)   annotation (Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=270,
        origin={0,-70})));
  PlanarMechanicsV2.Joints.Revolute
                  revolute(initialize=true, phi_start=-1.3962634015955)
    annotation (Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=270,
        origin={0,0})));
  PlanarMechanicsV2.Parts.FixedTranslation
                         fixedTranslation(r={0,-1}) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=270,
        origin={0,-30})));
  PlanarMechanicsV2.Parts.Body
             body1(
    m=1,
    I=0.1,
    g={0,-9.81})
    annotation (Placement(transformation(extent={{10,20},{30,40}})));
  IdealWheel idealWheel(R=0.2)
                        annotation (Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={0,52})));
  PlanarMechanicsV2.Parts.FixedTranslation
                         fixedTranslation1(r={0,0.3})
                                                    annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=0,
        origin={-40,30})));
  PlanarMechanicsV2.Parts.FixedTranslation
                         fixedTranslation2(r={-0.3,0})
                                                    annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=0,
        origin={-40,40})));
  PlanarMechanicsV2.Parts.FixedTranslation
                         fixedTranslation3(r={0,-0.3})
                                                    annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=0,
        origin={-40,16})));
  PlanarMechanicsV2.Parts.FixedTranslation
                         fixedTranslation4(r={0.3,0})
                                                    annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=0,
        origin={-40,52})));
equation
  connect(fixedTranslation.frame_b,body. frame_a) annotation (Line(
      points={{0,-40},{0,-60},{1.77636e-015,-60}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(fixedTranslation3.frame_b, fixedTranslation1.frame_b) annotation (
      Line(
      points={{-30,16},{-30,30}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(fixedTranslation2.frame_b, fixedTranslation1.frame_b) annotation (
      Line(
      points={{-30,40},{-30,30}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(fixedTranslation4.frame_b, fixedTranslation2.frame_b) annotation (
      Line(
      points={{-30,52},{-30,40}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(revolute.frame_b, fixedTranslation.frame_a) annotation (Line(
      points={{0,-10},{0,-20}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(body1.frame_a, revolute.frame_a) annotation (Line(
      points={{10,30},{6,30},{6,10},{0,10}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(idealWheel.frame_a, revolute.frame_a) annotation (Line(
      points={{0,42.4},{0,10}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(fixedTranslation1.frame_b, revolute.frame_a) annotation (Line(
      points={{-30,30},{-16,30},{-16,10},{0,10}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  annotation (uses(Modelica(version="3.2")), Diagram(coordinateSystem(
          preserveAspectRatio=false, extent={{-100,-100},{100,100}}), graphics));
end TestIdealWheel;
