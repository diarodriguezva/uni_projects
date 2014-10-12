within ;
model IdealWheel

  import MB = Modelica.Mechanics.MultiBody;

  PlanarMechanicsV2.Interfaces.Frame_a frame_a annotation (Placement(
        transformation(extent={{-106,-10},{-86,10}}), iconTransformation(extent=
           {{-106,-10},{-86,10}})));
  annotation (uses(Modelica(version="3.2")), Icon(coordinateSystem(
          preserveAspectRatio=false, extent={{-100,-100},{100,100}}), graphics={
          Ellipse(extent={{-80,80},{82,-80}}, lineColor={0,0,255})}),
    Diagram(coordinateSystem(preserveAspectRatio=false, extent={{-100,-100},{100,
            100}}), graphics));

  parameter Real R = 1;
  parameter Boolean animate = true;
  Real w;

  MB.Visualizers.Advanced.Shape cylinder(
    shapeType="cylinder",
    color={63,63,63},
    specularCoefficient=0.5,
    length=0.06,
    width=R*2,
    height=R*2,
    lengthDirection={0,0,-1},
    widthDirection={0,0,1},
    r_shape=-0.03*{0,0,-1},
    r={frame_a.x,frame_a.y,0},
    R=MB.Frames.nullRotation()) if animate;

initial equation
  frame_a.phi = 0;

equation
  w = der(frame_a.phi);
  w = der(frame_a.x)/R;

  frame_a.y = R;

  -frame_a.t = frame_a.fx*R;

end IdealWheel;
