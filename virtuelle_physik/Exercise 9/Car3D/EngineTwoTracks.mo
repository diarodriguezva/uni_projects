within ;
model EngineTwoTracks

parameter Real torque = 80;

  PlanarMechanicsV2.VehicleComponents.DifferentialGear differentialGear
    annotation (Placement(transformation(extent={{-10,-10},{10,10}},
        rotation=180,
        origin={0,0})));
  Modelica.Mechanics.Rotational.Sources.ConstantTorque constantTorque(
      tau_constant=torque)
    annotation (Placement(transformation(extent={{-44,18},{-24,38}})));
  Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_a annotation (
      Placement(transformation(extent={{50,-10},{70,10}}), iconTransformation(
          extent={{-80,-10},{-60,10}})));
  Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_a1
                                                             annotation (
      Placement(transformation(extent={{-70,-10},{-50,10}}),
                                                           iconTransformation(
          extent={{60,-10},{80,10}})));
equation
  connect(constantTorque.flange, differentialGear.flange_b) annotation (Line(
      points={{-24,28},{0,28},{0,10}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(differentialGear.flange_right, flange_a1) annotation (Line(
      points={{-10,0},{-60,0}},
      color={0,0,0},
      smooth=Smooth.None));
  connect(differentialGear.flange_left, flange_a) annotation (Line(
      points={{10,0},{60,0}},
      color={0,0,0},
      smooth=Smooth.None));
  annotation (
    uses(Modelica(version="3.2")),
    Diagram(coordinateSystem(preserveAspectRatio=false, extent={{-100,-100},{100,
            100}}), graphics),
    Icon(coordinateSystem(preserveAspectRatio=false, extent={{-100,-100},{100,100}}),
        graphics={Line(
          points={{-40,-40},{-40,-40},{20,-40},{40,-40},{40,-40},{40,20},{80,20},
              {0,78},{-80,20},{-40,20},{-40,-40},{-40,-40}},
          color={0,0,255},
          smooth=Smooth.None)}));
end EngineTwoTracks;
