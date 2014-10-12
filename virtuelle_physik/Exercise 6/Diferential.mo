within ;
model Diferential

  parameter Real R_left = 1;
  parameter Real R_right = 1;
  parameter Real R_drive = 1;

  Real w_right;
  Real w_left;
  Real w_drive;

  Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_left
    annotation (Placement(transformation(extent={{-90,-10},{-70,10}})));
  Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_right
    annotation (Placement(transformation(extent={{70,-10},{90,10}})));
  Modelica.Mechanics.Rotational.Interfaces.Flange_b flange_drive
    annotation (Placement(transformation(extent={{-10,-90},{10,-70}})));
  annotation (uses(Modelica(version="3.2")), Diagram(coordinateSystem(
          preserveAspectRatio=false, extent={{-100,-100},{100,100}}), graphics));

equation
  w_drive = der(flange_drive.phi);
  w_left = der(flange_left.phi);
  w_right = der(flange_right.phi);

  2 * der(flange_drive.phi) = der(flange_left.phi) + der(flange_right.phi);
  flange_left.tau = flange_right.tau;

  flange_drive.tau = 2*flange_left.tau;

  // tau_right = der(w_right);
  // tau_left = der(w_left);
  // tau_drive = der(w_drive);

end Diferential;
