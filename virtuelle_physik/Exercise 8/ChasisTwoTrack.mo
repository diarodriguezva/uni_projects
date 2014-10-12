within ;
model ChasisTwoTrack

  parameter Real WheelBase = 2.2; //m
  parameter Real WeightCar = 1600;
  parameter Real InertiaCar = 1270;

  PlanarMechanicsV2.Parts.FixedTranslation Chasis2(r={WheelBase/2,0}) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=90,
        origin={0,20})));
  PlanarMechanicsV2.Parts.FixedTranslation Chasis(r={-WheelBase/2,0}) annotation (
      Placement(transformation(
        extent={{-10,-10},{10,10}},
        rotation=270,
        origin={0,-24})));
  PlanarMechanicsV2.Parts.Body Car(m=WeightCar, I=InertiaCar)
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=180,
        origin={-22,0})));
  PlanarMechanicsV2.Interfaces.Frame_b frame_a
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=90,
        origin={1,-60}), iconTransformation(extent={{-9,60},{11,80}})));
  PlanarMechanicsV2.Interfaces.Frame_b frame_a1
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=90,
        origin={1,72}), iconTransformation(extent={{-9,-86},{11,-66}})));
equation
  connect(Car.frame_a,Chasis. frame_a) annotation (Line(
      points={{-12,0},{0,0},{0,-14}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Chasis2.frame_a,Car. frame_a) annotation (Line(
      points={{0,10},{0,0},{-12,0}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(Chasis.frame_b, frame_a) annotation (Line(
      points={{0,-34},{0,-60},{1,-60}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  connect(frame_a1, Chasis2.frame_b) annotation (Line(
      points={{1,72},{1,54},{0,54},{0,30}},
      color={95,95,95},
      thickness=0.5,
      smooth=Smooth.None));
  annotation (
    Diagram(coordinateSystem(preserveAspectRatio=false, extent={{-100,-100},{
            100,100}}),
                    graphics),
    uses(Modelica(version="3.2")),
    Icon(coordinateSystem(preserveAspectRatio=false, extent={{-100,-100},{100,100}}),
        graphics={
        Rectangle(extent={{-60,60},{-40,-60}}, lineColor={0,0,255}),
        Rectangle(extent={{40,60},{60,-60}}, lineColor={0,0,255}),
        Line(
          points={{40,40},{-40,40},{-40,40}},
          color={0,0,255},
          smooth=Smooth.None),
        Line(
          points={{-40,-40},{40,-40}},
          color={0,0,255},
          smooth=Smooth.None)}));
end ChasisTwoTrack;
