within ;
model Interface2D3D

  PlanarMechanicsV2.Interfaces.Frame_a frame_a annotation (Placement(
        transformation(extent={{-50,-10},{-30,10}}), iconTransformation(extent={
            {-74,-22},{-26,20}})));
  Modelica.Mechanics.MultiBody.Interfaces.Frame_b frame_b annotation (Placement(
        transformation(extent={{24,-16},{56,16}}), iconTransformation(extent={{22,
            -20},{62,20}})));
  annotation (
    uses(Modelica(version="3.2")),
    Diagram(coordinateSystem(preserveAspectRatio=false, extent={{-100,-80},{100,
            80}}), graphics),
    Icon(coordinateSystem(extent={{-100,-80},{100,80}}, preserveAspectRatio=false),
        graphics={Line(
          points={{-40,0},{36,0},{36,0}},
          color={175,175,175},
          smooth=Smooth.None,
          thickness=1)}));

protected
  Real fz;
  Real f0[3];

equation
frame_a.x = frame_b.r_0[1];
frame_a.y = frame_b.r_0[2];
0 = frame_b.r_0[3];

frame_b.R = MB.Frames.planarRotation({0,0,1},-frame_b,phi,-der(frame_b.phi));

f0[1] = frame_a.fx;
f0[2] = frame_a.fy;
f0[3] = fz;

f0*frame_b.R.T + frame_b.f = zeros(3);
-frame_b.t[3] + frame_a.t = 0;

Conecctions.root(frame_b.R);

end Interface2D3D;
