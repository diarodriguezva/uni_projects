within ;
package PlanarMechanicsV3 "A planar mechanical library for didactical purposes"

  import SI = Modelica.SIunits;
  import MB = Modelica.Mechanics.MultiBody;

  package Interfaces
    connector Frame "General Connector for planar mechanical components"
      SI.Position x "x-position";
      SI.Position y "y-position";
      SI.Angle phi "angle (clockwise)";
      flow SI.Force fx "force in x-direction";
      flow SI.Force fy "force in y-direction";
      flow SI.Torque t "torque (clockwise)";
    end Frame;

    connector Frame_a
      extends Frame;
      annotation (Icon(graphics={
            Rectangle(
              extent={{-40,100},{40,-100}},
              lineColor={95,95,95},
              fillColor={203,237,255},
              fillPattern=FillPattern.Solid,
              lineThickness=0.5),
            Line(
              points={{-18,0},{22,0}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{0,20},{0,-20}},
              color={95,95,95},
              smooth=Smooth.None)}));
    end Frame_a;

    connector Frame_b
      extends Frame;
      annotation (Icon(graphics={
            Rectangle(
              extent={{-40,100},{40,-100}},
              lineColor={95,95,95},
              fillColor={85,170,255},
              fillPattern=FillPattern.Solid,
              lineThickness=0.5),
            Line(
              points={{-18,0},{22,0}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{0,20},{0,-20}},
              color={95,95,95},
              smooth=Smooth.None)}));
    end Frame_b;

    model PlanarToMultiBody
      "This model enables to connect planar models to 3D Models"

      Frame_a frame_a annotation (Placement(transformation(extent={{-46,-8},{-26,12}}),
            iconTransformation(extent={{-48,-20},{-8,20}})));
      MB.Interfaces.Frame_b frame_b annotation (Placement(transformation(extent={{6,
                -16},{38,16}}), iconTransformation(extent={{8,-16},{40,16}})));

    protected
      SI.Force fz "Normal Force";
      SI.Force f0[3] "Force vector";

    equation
      //connect the translatory position w.r.t inertial system
      frame_a.x = frame_b.r_0[1];
      frame_a.y = frame_b.r_0[2];
      0 = frame_b.r_0[3];

      //Express 3D-rotation as planar rotation around z-axes
      MB.Frames.planarRotation({0,0,1},-frame_a.phi, -der(frame_a.phi)) = frame_b.R;

      //define force vector
      f0 = {frame_a.fx, frame_a.fy, fz};
      //the MulitBody force vector is resolved within the body system
      f0*frame_b.R.T + frame_b.f = zeros(3);

      //connect the torque
      -frame_a.t + frame_b.t[3] = 0;

      //This element determines the orientation matrix fully, hence it is a "root-element"
      Connections.root(frame_b.R);

      annotation (Icon(graphics={Line(
              points={{-18,0},{16,0}},
              color={95,95,95},
              smooth=Smooth.None,
              thickness=0.5)}), Diagram(graphics));
    end PlanarToMultiBody;
  end Interfaces;

  package Parts
    model Body "Body component with mass and inertia"

      Interfaces.Frame_a frame_a
        annotation (Placement(transformation(extent={{-100,2},{-80,22}}),
            iconTransformation(extent={{-120,-20},{-80,20}})));

      parameter SI.Mass m "mass of the body";
      parameter SI.Inertia I "Inertia of the Body";

      parameter SI.Acceleration g[2] = {0,0} "local gravity acting on the mass";

      SI.Force f[2] "force";
      SI.Position r[2] "transl. position";
      SI.Velocity v[2] "velocity";
      SI.Acceleration a[2] "acceleration";

      SI.AngularVelocity w "angular velocity";
      SI.AngularAcceleration z "angular acceleration";

      parameter Boolean animate = true "enable Animation"
                                                         annotation(Dialog(group="Animation"));

      //Visualization
      MB.Visualizers.Advanced.Shape sphere(
        shapeType="sphere",
        color={63,63,255},
        specularCoefficient=0.5,
        length=0.15,
        width=0.15,
        height=0.15,
        lengthDirection={0,0,1},
        widthDirection={1,0,0},
        r_shape={0,0,-0.075},
        r={frame_a.x,frame_a.y,0},
        R=MB.Frames.nullRotation()) if animate;

    equation
      //The velocity is a time-derivative of the position
      r = {frame_a.x, frame_a.y};
      v = der(r);
      w = der(frame_a.phi);

      //The acceleration is a time-derivative of the velocity
      a = der(v);
      z = der(w);

      //Newton's law
      f = {frame_a.fx, frame_a.fy};
      f + m*g = m*a;
      frame_a.t = I*z;

      annotation (Icon(graphics={
            Rectangle(
              extent={{-100,40},{-20,-40}},
              lineColor={0,0,0},
              fillColor={85,170,255},
              fillPattern=FillPattern.HorizontalCylinder),
            Ellipse(
              extent={{-60,60},{60,-60}},
              lineColor={0,0,0},
              fillPattern=FillPattern.Sphere,
              fillColor={85,170,255}),
            Text(
              extent={{-100,-80},{100,-120}},
              lineColor={0,0,0},
              fillPattern=FillPattern.Sphere,
              fillColor={85,170,255},
              textString="%name")}), Diagram(graphics));
    end Body;

    model Fixed "FixedPosition"

      Interfaces.Frame_a frame_a
        annotation (Placement(transformation(extent={{-100,0},{-80,20}}),
            iconTransformation(extent={{-120,-20},{-80,20}})));

      parameter SI.Position r[2] = {0,0} "fixed x,y-position";
      parameter SI.Angle phi = 0 "fixed angle";

    equation
      {frame_a.x,frame_a.y} = r;
      frame_a.phi = phi;

      annotation (Icon(graphics={
            Text(
              extent={{-100,-80},{100,-120}},
              lineColor={0,0,0},
              fillPattern=FillPattern.Sphere,
              fillColor={85,170,255},
              textString="%name"),
            Line(
              points={{-92,0},{0,0}},
              color={0,0,0},
              smooth=Smooth.None),
            Line(
              points={{0,80},{0,-80}},
              color={0,0,0},
              smooth=Smooth.None),
            Line(
              points={{0,40},{80,0}},
              color={0,0,0},
              smooth=Smooth.None),
            Line(
              points={{0,80},{80,40}},
              color={0,0,0},
              smooth=Smooth.None),
            Line(
              points={{0,0},{80,-40}},
              color={0,0,0},
              smooth=Smooth.None),
            Line(
              points={{0,-40},{80,-80}},
              color={0,0,0},
              smooth=Smooth.None)}), Diagram(graphics));
    end Fixed;

    model FixedTranslation
      "A fixed translation between two components (rigid rod)"

      Interfaces.Frame_a frame_a
        annotation (Placement(transformation(extent={{-100,0},{-80,20}}),
            iconTransformation(extent={{-120,-20},{-80,20}})));
      Interfaces.Frame_b frame_b annotation (Placement(transformation(extent={{80,0},{
                100,20}}),  iconTransformation(extent={{80,-20},{120,20}})));

      parameter SI.Length r[2] = {1,0}
        "length of the rod resolved w.r.t to body frame at phi = 0";
      final parameter SI.Length l = sqrt(r*r);
      SI.Distance r0[2] "length of the rod resolved w.r.t to inertal frame";
      Real R[2,2] "Rotation matrix";

      parameter Boolean animate = true "enable Animation"
                                                         annotation(Dialog(group="Animation"));

      //Visualization
      MB.Visualizers.Advanced.Shape cylinder(
        shapeType="cylinder",
        color={128,128,128},
        specularCoefficient=0.5,
        length=l,
        width=0.1,
        height=0.1,
        lengthDirection={r0[1]/l,r0[2]/l,0},
        widthDirection={0,0,1},
        r_shape={0,0,0},
        r={frame_a.x,frame_a.y,0},
        R=MB.Frames.nullRotation()) if  animate;

    equation
      //resolve the rod w.r.t inertial system
    //  sx0 = cos(frame_a.phi)*sx + sin(frame_a.phi)*sy;
    //  sy0 = -sin(frame_a.phi)*sx + cos(frame_a.phi)*sy;
      R = {{cos(frame_a.phi), sin(frame_a.phi)}, {-sin(frame_a.phi),cos(frame_a.phi)}};
      r0 = R*r;

      //rigidly connect positions
      frame_a.x + r0[1] = frame_b.x;
      frame_a.y + r0[2] = frame_b.y;
      frame_a.phi = frame_b.phi;

      //balance forces including lever principle
      frame_a.fx + frame_b.fx = 0;
      frame_a.fy + frame_b.fy = 0;
    //  frame_a.t + frame_b.t - sx0*frame_b.fy + sy0*frame_b.fx = 0;
      frame_a.t  + frame_b.t + r0*{-frame_b.fy,frame_b.fx} = 0;

      annotation (Icon(graphics={
            Text(
              extent={{-100,-40},{100,-80}},
              lineColor={0,0,0},
              fillPattern=FillPattern.Sphere,
              fillColor={85,170,255},
              textString="%name"), Rectangle(
              extent={{-92,6},{92,-6}},
              lineColor={0,0,0},
              fillPattern=FillPattern.Solid,
              fillColor={175,175,175})}), Diagram(graphics));
    end FixedTranslation;

    model FixedRotation
      "A fixed translation between two components (rigid rod)"

      Interfaces.Frame_a frame_a
        annotation (Placement(transformation(extent={{-100,0},{-80,20}}),
            iconTransformation(extent={{-120,-20},{-80,20}})));
      Interfaces.Frame_b frame_b annotation (Placement(transformation(extent={{80,0},{
                100,20}}),  iconTransformation(extent={{80,-20},{120,20}})));

      parameter SI.Angle alpha "fixed rotation angle";

    equation
      frame_a.x = frame_b.x;
      frame_a.y = frame_b.y;
      frame_a.phi + alpha = frame_b.phi;

      frame_a.fx + frame_b.fx = 0;
      frame_a.fy + frame_b.fy = 0;
      frame_a.t + frame_b.t = 0;

      annotation (Icon(graphics={
            Text(
              extent={{-100,-40},{100,-80}},
              lineColor={0,0,0},
              fillPattern=FillPattern.Sphere,
              fillColor={85,170,255},
              textString="%name"),
            Polygon(
              points={{4,48},{92,8},{92,-12},{0,32},{-92,-10},{-92,8},{-6,48},{4,48}},
              lineColor={0,0,0},
              smooth=Smooth.None,
              fillColor={175,175,175},
              fillPattern=FillPattern.Solid),
            Ellipse(
              extent={{-20,60},{20,20}},
              lineColor={0,0,0},
              fillColor={175,175,175},
              fillPattern=FillPattern.Solid),
            Ellipse(
              extent={{-10,50},{10,30}},
              lineColor={255,255,255},
              fillColor={175,175,175},
              fillPattern=FillPattern.Solid,
              lineThickness=0.5)}),       Diagram(graphics));
    end FixedRotation;
  end Parts;

  package Joints "Planar joint models"
    model Revolute "A revolute joint "

      Interfaces.Frame_a frame_a
        annotation (Placement(transformation(extent={{-100,0},{-80,20}}),
            iconTransformation(extent={{-120,-20},{-80,20}})));
      Interfaces.Frame_b frame_b annotation (Placement(transformation(extent={{80,0},{
                100,20}}),  iconTransformation(extent={{80,-20},{120,20}})));

      parameter Boolean initialize = false "Initialize Position and Velocity";
      parameter SI.Angle phi_start = 0;
      parameter SI.AngularVelocity w_start = 0;

      parameter Boolean animate = true "enable Animation"
                                                         annotation(Dialog(group="Animation"));

      parameter Boolean enforceStates = false
        "enforce the state of the revolute to become the state of the total system"
                                                                                                            annotation(Dialog(group="Advanced"));

      SI.Angle phi(stateSelect = if enforceStates then StateSelect.always else StateSelect.prefer)
        "Angular position";
      SI.AngularVelocity w(stateSelect = if enforceStates then StateSelect.always else StateSelect.prefer)
        "Angular velocity";
      SI.AngularAcceleration z "Angular acceleration";
      SI.Torque t "Torque";

      //Visualization
      MB.Visualizers.Advanced.Shape cylinder(
        shapeType="cylinder",
        color={255,0,0},
        specularCoefficient=0.5,
        length=0.2,
        width=0.1,
        height=0.1,
        lengthDirection={0,0,1},
        widthDirection={1,0,0},
        r_shape={0,0,-0.05},
        r={frame_a.x,frame_a.y,0},
        R=MB.Frames.nullRotation()) if  animate;

    initial equation

      //Initialization of Position and Velocity
      if initialize then
        phi = phi_start;
        w = w_start;
      end if;

    equation

      //Differential Equations
      w = der(phi);
      z = der(w);

      //No torque
      t = 0;

      //rigidly connect positions
      frame_a.x = frame_b.x;
      frame_a.y = frame_b.y;
      frame_a.phi + phi = frame_b.phi;

      //balance forces
      frame_a.fx + frame_b.fx = 0;
      frame_a.fy + frame_b.fy = 0;
      frame_a.t + frame_b.t = 0;
      frame_a.t = t;

      annotation (Icon(graphics={
            Text(
              extent={{-100,-80},{100,-120}},
              lineColor={0,0,0},
              fillPattern=FillPattern.Sphere,
              fillColor={85,170,255},
              textString="%name"), Rectangle(
              extent={{-20,20},{20,-20}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={175,175,175}),
                                   Rectangle(
              extent={{-100,60},{-20,-62}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={175,175,175}),
                                   Rectangle(
              extent={{20,60},{100,-60}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={175,175,175})}), Diagram(graphics));
    end Revolute;

    model Prismatic "A prismatic joint"

      Interfaces.Frame_a frame_a
        annotation (Placement(transformation(extent={{-100,0},{-80,20}}),
            iconTransformation(extent={{-120,-20},{-80,20}})));
      Interfaces.Frame_b frame_b annotation (Placement(transformation(extent={{80,0},{
                100,20}}),  iconTransformation(extent={{80,-20},{120,20}})));

      parameter SI.Distance r[2]
        "direction of the rod wrt. body system at phi=0";
      final parameter SI.Length l = sqrt(r*r) "lengt of r";
      final parameter SI.Distance e[2]= r/l "normalized r";
      SI.Distance s;
      SI.Distance r0[2]
        "direction of the prismatic rod resolved wrt.inertial frame";
      Real R[2,2] "Rotation Matrix";

    //  SI.Length s "elongation of the prismatic joint";
      SI.Velocity v "velocity of elongation";
      SI.Acceleration a "acceleration of elongation";
      SI.Force f "force in direction of elongation";

      parameter Boolean initialize = false "Initialize Position and Velocity";
      parameter SI.Length s_start = 0;
      parameter SI.Velocity v_start = 0;

      parameter Boolean animate = true "enable Animation"
                                                         annotation(Dialog(group="Animation"));

      //Visualization
      MB.Visualizers.Advanced.Shape box(
        shapeType="box",
        color={255,63,63},
        specularCoefficient=0.5,
        length=s,
        width=0.1,
        height=0.1,
        lengthDirection={(R*e)[1],(R*e)[2],0},
        widthDirection={0,0,1},
        r_shape={0,0,0},
        r={frame_a.x,frame_a.y,0},
        R=MB.Frames.nullRotation()) if  animate;

    initial equation

      //Initialization of Position and Velocity
     if initialize then
        s = s_start;
        v = v_start;
      end if;

    equation

      //resolve the rod w.r.t. inertial system
      R = {{cos(frame_a.phi), sin(frame_a.phi)}, {-sin(frame_a.phi),cos(frame_a.phi)}};
      r0 = R*e*s;

      //differential equations
      v = der(s);
      a = der(v);
      f = 0;

      //rigidly connect positions
      frame_a.x + r0[1] = frame_b.x;
      frame_a.y + r0[2] = frame_b.y;
      frame_a.phi = frame_b.phi;

      //balance forces including lever principle
      frame_a.fx + frame_b.fx = 0;
      frame_a.fy + frame_b.fy = 0;
      frame_a.t  + frame_b.t + r0*{-frame_b.fy,frame_b.fx} = 0;
      {frame_a.fx,frame_a.fy}*(R*e) = 0;

      annotation (Icon(graphics={
            Text(
              extent={{-100,-60},{100,-100}},
              lineColor={0,0,0},
              fillPattern=FillPattern.Sphere,
              fillColor={85,170,255},
              textString="%name"), Rectangle(
              extent={{-100,40},{-20,-40}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={175,175,175}),
                                   Rectangle(
              extent={{-20,-20},{100,20}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={175,175,175})}), Diagram(graphics));
    end Prismatic;

    model ActuatedRevolute "A revolute joint "

      Interfaces.Frame_a frame_a
        annotation (Placement(transformation(extent={{-100,0},{-80,20}}),
            iconTransformation(extent={{-120,-20},{-80,20}})));
      Interfaces.Frame_b frame_b annotation (Placement(transformation(extent={{80,0},{
                100,20}}),  iconTransformation(extent={{80,-20},{120,20}})));

      parameter Boolean initialize = false "Initialize Position and Velocity";
      parameter SI.Angle phi_start = 0;
      parameter SI.AngularVelocity w_start = 0;

      SI.Angle phi "Angular position";
      SI.AngularVelocity w "Angular velocity";
      SI.AngularAcceleration z "Angular acceleration";
      SI.Torque t "Torque";

      parameter Boolean animate = true "enable Animation"
                                                         annotation(Dialog(group="Animation"));

      MB.Visualizers.Advanced.Shape cylinder(
        shapeType="cylinder",
        color={255,0,0},
        specularCoefficient=0.5,
        length=0.2,
        width=0.1,
        height=0.1,
        lengthDirection={0,0,1},
        widthDirection={1,0,0},
        r_shape={0,0,-0.05},
        r={frame_a.x,frame_a.y,0},
        R=MB.Frames.nullRotation()) if  animate;

      Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_a annotation (
          Placement(transformation(extent={{-20,80},{0,100}}), iconTransformation(
              extent={{-10,90},{10,110}})));
    initial equation
      if initialize then
        phi = phi_start;
        w = w_start;
      end if;

    equation

      //Differential Equations
      phi = flange_a.phi;
      w = der(phi);
      z = der(w);

      //Acturation Torque
      t = flange_a.tau;

      //rigidly connect positions
      frame_a.x = frame_b.x;
      frame_a.y = frame_b.y;
      frame_a.phi + phi = frame_b.phi;

      //balance forces
      frame_a.fx + frame_b.fx = 0;
      frame_a.fy + frame_b.fy = 0;
      frame_a.t + frame_b.t = 0;
      frame_a.t = t;

      annotation (Icon(graphics={
            Text(
              extent={{-100,-80},{100,-120}},
              lineColor={0,0,0},
              fillPattern=FillPattern.Sphere,
              fillColor={85,170,255},
              textString="%name"), Rectangle(
              extent={{-20,20},{20,-20}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={175,175,175}),
                                   Rectangle(
              extent={{-100,60},{-20,-62}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={175,175,175}),
                                   Rectangle(
              extent={{20,60},{100,-60}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={175,175,175}),
            Line(
              points={{0,80},{0,20}},
              color={0,0,0},
              smooth=Smooth.None)}),      Diagram(graphics));
    end ActuatedRevolute;

    model ActuatedPrismatic "A prismatic joint"

      Interfaces.Frame_a frame_a
        annotation (Placement(transformation(extent={{-100,0},{-80,20}}),
            iconTransformation(extent={{-120,-20},{-80,20}})));
      Interfaces.Frame_b frame_b annotation (Placement(transformation(extent={{80,0},{
                100,20}}),  iconTransformation(extent={{80,-20},{120,20}})));

      parameter SI.Distance r[2]
        "direction of the rod wrt. body system at phi=0";
      final parameter SI.Length l = sqrt(r*r) "lengt of r";
      final parameter SI.Distance e[2]= r/l "normalized r";
      SI.Distance s;
      SI.Distance r0[2]
        "direction of the prismatic rod resolved wrt.inertial frame";
      Real R[2,2] "Rotation Matrix";

      SI.Velocity v "velocity of elongation";
      SI.Acceleration a "acceleration of elongation";
      SI.Force f "force in direction of elongation";

      parameter Boolean initialize = false "Initialize Position and Velocity";
      parameter SI.Length s_start = 0;
      parameter SI.Velocity v_start = 0;

      parameter Boolean animate = true "enable Animation"
                                                         annotation(Dialog(group="Animation"));

      //Visualization
      MB.Visualizers.Advanced.Shape box(
        shapeType="box",
        color={255,63,63},
        specularCoefficient=0.5,
        length=s,
        width=0.1,
        height=0.1,
        lengthDirection={(R*e)[1],(R*e)[2],0},
        widthDirection={0,0,1},
        r_shape={0,0,0},
        r={frame_a.x,frame_a.y,0},
        R=MB.Frames.nullRotation()) if  animate;

      Modelica.Mechanics.Translational.Interfaces.Flange_a flange_a annotation (
          Placement(transformation(extent={{-8,80},{12,100}}), iconTransformation(
              extent={{-10,80},{10,100}})));
    initial equation

      //Initialization of Position and Velocity
     if initialize then
        s = s_start;
        v = v_start;
      end if;

    equation

      //resolve the rod w.r.t. inertial system
      R = {{cos(frame_a.phi), sin(frame_a.phi)}, {-sin(frame_a.phi),cos(frame_a.phi)}};
      r0 = R*e*s;

      //differential equations
      s = flange_a.s;
      v = der(s);
      a = der(v);

      //actuation force
      f = flange_a.f;

      //rigidly connect positions
      frame_a.x + r0[1] = frame_b.x;
      frame_a.y + r0[2] = frame_b.y;
      frame_a.phi = frame_b.phi;

      //balance forces including lever principle
      frame_a.fx + frame_b.fx = 0;
      frame_a.fy + frame_b.fy = 0;
      frame_a.t  + frame_b.t + r0*{-frame_b.fy,frame_b.fx} = 0;
      {frame_a.fx,frame_a.fy}*(R*e) = f;

      annotation (Icon(graphics={
            Text(
              extent={{-100,-60},{100,-100}},
              lineColor={0,0,0},
              fillPattern=FillPattern.Sphere,
              fillColor={85,170,255},
              textString="%name"), Rectangle(
              extent={{-100,40},{-20,-40}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={175,175,175}),
                                   Rectangle(
              extent={{-20,-20},{100,20}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={175,175,175}),
            Line(
              points={{0,80},{0,20}},
              color={0,0,0},
              smooth=Smooth.None)}),      Diagram(graphics));
    end ActuatedPrismatic;

    model IdealRolling "A revolute joint "

      Interfaces.Frame_a frame_a
        annotation (Placement(transformation(extent={{-100,0},{-80,20}}),
            iconTransformation(extent={{-120,-20},{-80,20}})));

      parameter SI.Length R = 1.0 "Radius of the wheel";

      parameter Boolean initialize = false "Initialize Position and Velocity";
      parameter SI.Position x_start = 0;
      parameter SI.Angle phi_start = 0;
      parameter SI.AngularVelocity w_start = 0;

      parameter Boolean animate = true "enable Animation"
                                                         annotation(Dialog(group="Animation"));

      SI.Angle phi "Angular position";
      SI.AngularVelocity w "Angular velocity";
      SI.AngularAcceleration z "Angular acceleration";
      SI.Velocity vx "Velocity in x-direction";

      //Visualization
      MB.Visualizers.Advanced.Shape cylinder(
        shapeType="cylinder",
        color={255,0,0},
        specularCoefficient=0.5,
        length=0.06,
        width=2*R,
        height=2*R,
        lengthDirection={0,0,1},
        widthDirection={1,0,0},
        r_shape={0,0,-0.03},
        r={frame_a.x,frame_a.y,0},
        R=MB.Frames.nullRotation()) if  animate;

      MB.Visualizers.Advanced.Shape rim1(
        shapeType="cylinder",
        color={195,195,195},
        specularCoefficient=0.5,
        length=R*2,
        width=0.1,
        height=0.1,
        lengthDirection={1,0,0},
        widthDirection={0,0,1},
        r_shape={-R,0,0},
        r={frame_a.x,frame_a.y,0},
        R=MB.Frames.planarRotation({0,0,1},-phi,0)) if animate;

      MB.Visualizers.Advanced.Shape rim2(
        shapeType="cylinder",
        color={195,195,195},
        specularCoefficient=0.5,
        length=R*2,
        width=0.1,
        height=0.1,
        lengthDirection={1,0,0},
        widthDirection={0,0,1},
        r_shape={-R,0,0},
        r={frame_a.x,frame_a.y,0},
        R=MB.Frames.planarRotation({0,0,1},-phi+Modelica.Constants.pi/2,0)) if animate;

    initial equation

      //Initialization of Position and Velocity
      if initialize then
        phi = phi_start;
        w = w_start;
        frame_a.x = x_start;
      end if;

    equation
      //Differential Equations
      phi = frame_a.phi;
      w = der(phi);
      z = der(w);
      vx = der(frame_a.x);

      //holonomic constraint
      frame_a.y = R;

      //non-holonomic constraint
      vx = w*R;

      //balance forces
      frame_a.fx*R = -frame_a.t;

      annotation (Icon(graphics={
            Text(
              extent={{-100,-80},{100,-120}},
              lineColor={0,0,0},
              fillPattern=FillPattern.Sphere,
              fillColor={85,170,255},
              textString="%name"),
            Ellipse(
              extent={{-80,80},{80,-80}},
              pattern=LinePattern.None,
              fillColor={95,95,95},
              fillPattern=FillPattern.Solid,
              lineColor={0,0,0}),
            Ellipse(
              extent={{-70,70},{70,-70}},
              pattern=LinePattern.None,
              fillColor={255,255,255},
              fillPattern=FillPattern.Solid,
              lineColor={0,0,0}),
            Ellipse(
              extent={{-20,20},{20,-20}},
              fillColor={255,255,255},
              fillPattern=FillPattern.Solid,
              lineColor={0,0,255}),
            Line(
              points={{-20,0},{-92,0}},
              color={0,0,255},
              smooth=Smooth.None)}),      Diagram(graphics));
    end IdealRolling;

    model SlipBasedRolling "A revolute joint "

      Interfaces.Frame_a frame_a
        annotation (Placement(transformation(extent={{-100,0},{-80,20}}),
            iconTransformation(extent={{-120,-20},{-80,20}})));

      parameter SI.Length R = 1.0 "Radius of the wheel";

      parameter SI.Velocity vAdhesion "adhesion velocity";
      parameter SI.Velocity vSlide "sliding velocity";
      parameter Real mu_A "friction coefficient at adhesion";
      parameter Real mu_S "friction coefficient at sliding";

      parameter Boolean initialize = false "Initialize Position and Velocity";
      parameter SI.Position x_start = 0;
      parameter SI.Velocity vx_start = 0;
      parameter SI.Angle phi_start = 0;
      parameter SI.AngularVelocity w_start = 0;

      parameter Boolean animate = true "enable Animation"
                                                         annotation(Dialog(group="Animation"));

      SI.Angle phi "Angular position";
      SI.AngularVelocity w "Angular velocity";
      SI.AngularAcceleration z "Angular acceleration";
      SI.Velocity vx "Velocity in x-direction";

      SI.Force N "normal force";
      SI.Velocity v_slip "slip velocity";

      //Visualization
      MB.Visualizers.Advanced.Shape cylinder(
        shapeType="cylinder",
        color={255,0,0},
        specularCoefficient=0.5,
        length=0.06,
        width=2*R,
        height=2*R,
        lengthDirection={0,0,1},
        widthDirection={1,0,0},
        r_shape={0,0,-0.03},
        r={frame_a.x,frame_a.y,0},
        R=MB.Frames.nullRotation()) if  animate;

      MB.Visualizers.Advanced.Shape rim1(
        shapeType="cylinder",
        color={195,195,195},
        specularCoefficient=0.5,
        length=R*2,
        width=0.1,
        height=0.1,
        lengthDirection={1,0,0},
        widthDirection={0,0,1},
        r_shape={-R,0,0},
        r={frame_a.x,frame_a.y,0},
        R=MB.Frames.planarRotation({0,0,1},-phi,0)) if animate;

      MB.Visualizers.Advanced.Shape rim2(
        shapeType="cylinder",
        color={195,195,195},
        specularCoefficient=0.5,
        length=R*2,
        width=0.1,
        height=0.1,
        lengthDirection={1,0,0},
        widthDirection={0,0,1},
        r_shape={-R,0,0},
        r={frame_a.x,frame_a.y,0},
        R=MB.Frames.planarRotation({0,0,1},-phi+Modelica.Constants.pi/2,0)) if animate;

    initial equation

      //Initialization of Position and Velocity
      if initialize then
        phi = phi_start;
        w = w_start;
        frame_a.x = x_start;
        vx = vx_start;
      end if;

    equation
      //Differential Equations
      phi = frame_a.phi;
      w = der(phi);
      z = der(w);
      vx = der(frame_a.x);

      //holonomic constraint
      frame_a.y = R;

      //dry-friction law
      v_slip = vx - w*R;
      N = -frame_a.fy;
      frame_a.fx = N*noEvent(Utilities.TripleS_Func(vAdhesion,vSlide,mu_A,mu_S,v_slip));

      //balance forces
      frame_a.fx*R = -frame_a.t;

      annotation (Icon(graphics={
            Text(
              extent={{-100,-80},{100,-120}},
              lineColor={0,0,0},
              fillPattern=FillPattern.Sphere,
              fillColor={85,170,255},
              textString="%name"),
            Ellipse(
              extent={{-80,80},{80,-80}},
              pattern=LinePattern.None,
              fillColor={95,95,95},
              fillPattern=FillPattern.Solid,
              lineColor={0,0,0}),
            Ellipse(
              extent={{-70,70},{70,-70}},
              pattern=LinePattern.None,
              fillColor={255,255,255},
              fillPattern=FillPattern.Solid,
              lineColor={0,0,0}),
            Ellipse(
              extent={{-20,20},{20,-20}},
              fillColor={255,255,255},
              fillPattern=FillPattern.Solid,
              lineColor={0,0,255}),
            Line(
              points={{-20,0},{-92,0}},
              color={0,0,255},
              smooth=Smooth.None)}),      Diagram(graphics));
    end SlipBasedRolling;
  end Joints;

  package Forces "Force models... Spring and Dampers"
    model Damper "A fixed translation between two components (rigid rod)"

      Interfaces.Frame_a frame_a
        annotation (Placement(transformation(extent={{-100,0},{-80,20}}),
            iconTransformation(extent={{-120,-20},{-80,20}})));
      Interfaces.Frame_b frame_b annotation (Placement(transformation(extent={{80,0},{
                100,20}}),  iconTransformation(extent={{80,-20},{120,20}})));

      parameter SI.TranslationalDampingConstant d=1;
      SI.Length[2] r0;
      Real[2] d0;
      SI.Velocity vx;
      SI.Velocity vy;
      SI.Velocity v;
      SI.Force f;
    equation
      frame_a.x + r0[1] = frame_b.x;
      frame_b.y + r0[2] = frame_b.y;
      d0= Modelica.Math.Vectors.normalize(r0);
      der(frame_a.x) + vx = der(frame_b.x);
      der(frame_a.y) + vy = der(frame_b.y);
      v = {vx,vy}*d0;
      f = -d*v;
      frame_a.fx = d0[1] * f;
      frame_a.fy = d0[2] * f;
      frame_a.t = 0;
      frame_a.fx + frame_b.fx = 0;
      frame_a.fy + frame_b.fy = 0;
      frame_a.t + frame_b.t = 0;

    annotation(Dialog(group="Animation"),
                  Icon(graphics={
            Text(
              extent={{-100,-40},{100,-80}},
              lineColor={0,0,0},
              fillPattern=FillPattern.Sphere,
              fillColor={85,170,255},
              textString="%name"),
            Line(points={{-60,30},{60,30}}, color={0,0,0}),
            Line(points={{-60,-30},{60,-30}}, color={0,0,0}),
            Line(points={{30,0},{100,0}}, color={0,0,0}),
            Line(points={{-101,0},{-60,0}}, color={0,0,0}),
            Rectangle(
              extent={{-60,30},{30,-30}},
              lineColor={0,0,0},
              fillColor={192,192,192},
              fillPattern=FillPattern.Solid)}),
                                          Diagram(graphics));
    end Damper;

    model AbsoluteForce

      Interfaces.Frame_b frame_b
        annotation (Placement(transformation(extent={{80,-20},{120,20}})));
      Modelica.Blocks.Interfaces.RealInput u[2]
        annotation (Placement(transformation(extent={{-140,-20},{-100,20}})));
    equation
      {frame_b.fx,frame_b.fy} = u;
      frame_b.t = 0;
      annotation (Icon(graphics={
            Polygon(
              points={{-100,10},{20,10},{20,41},{90,0},{20,-41},{20,-10},{-100,-10},
                  {-100,10}},
              lineColor={0,127,0},
              fillColor={215,215,215},
              fillPattern=FillPattern.Solid),
            Text(
              extent={{-100,-40},{100,-80}},
              textString="%name",
              lineColor={0,0,0})}));
    end AbsoluteForce;
  end Forces;

  package Examples
    model FreeBody "AcceleratingBody"
      Parts.Body body(
        m=1,
        I=0.1,
        g={0,-9.81})
        annotation (Placement(transformation(extent={{0,0},{20,20}})));
    end FreeBody;

    model Pendulum "A free swinging pendulum"

      Parts.Body body(
        m=1,
        I=0.1,
        g={0,-9.81})
        annotation (Placement(transformation(extent={{40,-10},{60,10}})));
      Joints.Revolute revolute(initialize=true)
        annotation (Placement(transformation(extent={{-40,-10},{-20,10}})));
      Parts.FixedTranslation fixedTranslation(r= {1,0})
        annotation (Placement(transformation(extent={{0,-10},{20,10}})));
      Parts.Fixed fixed(phi=0) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-70,0})));
    equation
      connect(fixed.frame_a, revolute.frame_a) annotation (Line(
          points={{-60,-1.22465e-015},{-50,-1.22465e-015},{-50,0},{-40,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute.frame_b, fixedTranslation.frame_a) annotation (Line(
          points={{-20,0},{0,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation.frame_b, body.frame_a) annotation (Line(
          points={{20,0},{30,0},{30,0},{40,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end Pendulum;

    model CraneCrab "A free swinging pendulum"

      Parts.Body body(
        I=0.1,
        g={0,-9.81},
        m=0.5) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-10,-50})));
      Joints.Revolute revolute(initialize=true, phi_start=-2.7925268031909)
        annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-10,20})));
      Parts.FixedTranslation fixedTranslation(r={0,-1}) annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-10,-10})));
      Parts.Fixed fixed annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-70,50})));
      Joints.Prismatic prismatic(r={1,0},
        initialize=true)
        annotation (Placement(transformation(extent={{-40,40},{-20,60}})));
      Parts.Body body1(
        m=1,
        I=0.1,
        g={0,-9.81})
        annotation (Placement(transformation(extent={{0,40},{20,60}})));
      Forces.Damper damper(d=5)
        annotation (Placement(transformation(extent={{-40,60},{-20,80}})));
    equation
      connect(revolute.frame_b, fixedTranslation.frame_a) annotation (Line(
          points={{-10,10},{-10,7.5},{-10,7.5},{-10,5},{-10,0},{-10,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation.frame_b, body.frame_a) annotation (Line(
          points={{-10,-20},{-10,-25},{-10,-25},{-10,-30},{-10,-40},{-10,-40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));

      connect(prismatic.frame_a, fixed.frame_a) annotation (Line(
          points={{-40,50},{-60,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(body1.frame_a, prismatic.frame_b) annotation (Line(
          points={{0,50},{-10,50},{-10,50},{-20,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute.frame_a, prismatic.frame_b) annotation (Line(
          points={{-10,30},{-10,50},{-20,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(damper.frame_b, body1.frame_a) annotation (Line(
          points={{-20,70},{-10,70},{-10,50},{0,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(damper.frame_a, fixed.frame_a) annotation (Line(
          points={{-40,70},{-50,70},{-50,50},{-60,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end CraneCrab;

    model WheelBasedCranCrab

      Joints.IdealRolling idealRolling(R=0.3) annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-10,50})));
      Parts.Body body(
        m=1,
        I=0.1,
        g={0,-9.81})
        annotation (Placement(transformation(extent={{20,20},{40,40}})));
      Joints.Revolute revolute annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-10,10})));
      Parts.FixedTranslation fixedTranslation(r={1,0}) annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-10,-20})));
      Parts.Body body1(
        m=1,
        I=0.1,
        g={0,-9.81}) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-10,-50})));
    equation
      connect(revolute.frame_a, idealRolling.frame_a) annotation (Line(
          points={{-10,20},{-10,30},{-10,30},{-10,40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(body.frame_a, idealRolling.frame_a) annotation (Line(
          points={{20,30},{-10,30},{-10,40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(body1.frame_a, fixedTranslation.frame_b) annotation (Line(
          points={{-10,-40},{-10,-37.5},{-10,-37.5},{-10,-35},{-10,-30},{-10,
              -30}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation.frame_a, revolute.frame_b) annotation (Line(
          points={{-10,-10},{-10,-7.5},{-10,-7.5},{-10,-5},{-10,0},{-10,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end WheelBasedCranCrab;

    model CounterSpin
      Joints.SlipBasedRolling slipBasedRolling(
        R=0.1,
        initialize=true,
        x_start=0,
        phi_start=0,
        vAdhesion=0.001,
        vSlide=0.01,
        mu_A=0.4,
        mu_S=0.15,
        vx_start=2,
        w_start=-15)
        annotation (Placement(transformation(extent={{-10,0},{10,20}})));
      Parts.Body body(
        g={0,-9.81},
        animate=false,
        m=0.01,
        I=0.0005) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-50,10})));
    equation
      connect(body.frame_a, slipBasedRolling.frame_a) annotation (Line(
          points={{-40,10},{-25,10},{-25,10},{-10,10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end CounterSpin;

    model DoublePendulum "A free swinging pendulum"

      Parts.Body body(
        m=1,
        I=0.1,
        g={0,-9.81})
        annotation (Placement(transformation(extent={{20,60},{40,80}})));
      Joints.Revolute revolute(initialize=true)
        annotation (Placement(transformation(extent={{-60,60},{-40,80}})));
      Parts.FixedTranslation fixedTranslation(r={1,0})
        annotation (Placement(transformation(extent={{-20,60},{0,80}})));
      Parts.Fixed fixed annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-90,70})));
      Parts.Body body1(
        g={0,-9.81},
        m=0.2,
        I=0.01)
        annotation (Placement(transformation(extent={{60,20},{80,40}})));
      Joints.Revolute revolute1(
                               initialize=true)
        annotation (Placement(transformation(extent={{-20,20},{0,40}})));
      Parts.FixedTranslation fixedTranslation1(r={0.4,0})
        annotation (Placement(transformation(extent={{20,20},{40,40}})));
      Parts.Body body2(
        m=1,
        I=0.1,
        g={0,-9.81})
        annotation (Placement(transformation(extent={{20,-20},{40,0}})));
      Joints.Revolute revolute2(
                               initialize=true)
        annotation (Placement(transformation(extent={{-60,-20},{-40,0}})));
      Parts.FixedTranslation fixedTranslation2(r={1,0})
        annotation (Placement(transformation(extent={{-20,-20},{0,0}})));
      Parts.Fixed fixed1 annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-90,-10})));
      Parts.Body body3(
        g={0,-9.81},
        m=0.2,
        I=0.01)
        annotation (Placement(transformation(extent={{60,-60},{80,-40}})));
      Joints.Revolute revolute3(
                               initialize=true, phi_start=1.7453292519943e-05)
        annotation (Placement(transformation(extent={{-20,-60},{0,-40}})));
      Parts.FixedTranslation fixedTranslation3(r={0.4,0})
        annotation (Placement(transformation(extent={{20,-60},{40,-40}})));
    equation
      connect(fixed.frame_a, revolute.frame_a) annotation (Line(
          points={{-80,70},{-60,70}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute.frame_b, fixedTranslation.frame_a) annotation (Line(
          points={{-40,70},{-20,70}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation.frame_b, body.frame_a) annotation (Line(
          points={{0,70},{20,70}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute1.frame_b, fixedTranslation1.frame_a)
                                                          annotation (Line(
          points={{0,30},{20,30}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation1.frame_b, body1.frame_a)
                                                      annotation (Line(
          points={{40,30},{60,30}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute1.frame_a, fixedTranslation.frame_b) annotation (Line(
          points={{-20,30},{-32,30},{-32,50},{10,50},{10,70},{0,70}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixed1.frame_a, revolute2.frame_a)
                                               annotation (Line(
          points={{-80,-10},{-70,-10},{-70,-10},{-60,-10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute2.frame_b, fixedTranslation2.frame_a)
                                                          annotation (Line(
          points={{-40,-10},{-20,-10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation2.frame_b, body2.frame_a)
                                                      annotation (Line(
          points={{0,-10},{20,-10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute3.frame_b,fixedTranslation3. frame_a)
                                                          annotation (Line(
          points={{0,-50},{20,-50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation3.frame_b,body3. frame_a)
                                                      annotation (Line(
          points={{40,-50},{60,-50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute3.frame_a, fixedTranslation2.frame_b)
                                                           annotation (Line(
          points={{-20,-50},{-32,-50},{-32,-30},{10,-30},{10,-10},{0,-10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end DoublePendulum;

    model PistonEngine "A Piston Engine"

      Parts.Body bodyDrive(
        m=1,
        I=0.1,
        g={0,-9.81})
        annotation (Placement(transformation(extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-62,20})));
      Joints.Revolute revoluteDrive(
        initialize=true,
        phi_start=0,
        w_start=1)
        annotation (Placement(transformation(extent={{-70,40},{-50,60}})));
      Parts.FixedTranslation fixedTranslationDisc(r={0.3,0})
        annotation (Placement(transformation(extent={{-40,40},{-20,60}})));
      Parts.Fixed fixed annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-90,50})));
      Joints.Prismatic prismatic(r={1,0})
        annotation (Placement(transformation(extent={{20,-60},{40,-40}})));
      Parts.Fixed fixed1   annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={70,-50})));
      Joints.Revolute revoluteDisc(initialize=false)
        annotation (Placement(transformation(extent={{-10,-10},{10,10}},
            rotation=270,
            origin={0,30})));
      Parts.FixedTranslation pistonRod(r={0.8,0})
        annotation (Placement(transformation(extent={{-10,-10},{10,10}},
            rotation=270,
            origin={0,0})));
      Parts.Body bodyPiston(
        I=0.1,
        g={0,-9.81},
        m=3)
        annotation (Placement(transformation(extent={{30,-30},{50,-10}})));
      Joints.Revolute revolutePiston(initialize=false)
        annotation (Placement(transformation(extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,-30})));
    equation
      connect(fixed.frame_a, revoluteDrive.frame_a)
                                               annotation (Line(
          points={{-80,50},{-70,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revoluteDrive.frame_b, fixedTranslationDisc.frame_a)
                                                          annotation (Line(
          points={{-50,50},{-40,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixed1.frame_a, prismatic.frame_b) annotation (Line(
          points={{60,-50},{40,-50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslationDisc.frame_b, revoluteDisc.frame_a) annotation (
          Line(
          points={{-20,50},{0,50},{0,40},{1.83697e-015,40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(bodyDrive.frame_a, revoluteDrive.frame_b) annotation (Line(
          points={{-52,20},{-44,20},{-44,50},{-50,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revoluteDisc.frame_b, pistonRod.frame_a) annotation (Line(
          points={{-1.83697e-015,20},{1.83697e-015,20},{1.83697e-015,10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolutePiston.frame_b, pistonRod.frame_b) annotation (Line(
          points={{6.12323e-016,-20},{6.12323e-016,-12},{-1.83697e-015,-12},{
              -1.83697e-015,-10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(prismatic.frame_a, revolutePiston.frame_a) annotation (Line(
          points={{20,-50},{-6.12323e-016,-50},{-6.12323e-016,-40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(prismatic.frame_a, bodyPiston.frame_a) annotation (Line(
          points={{20,-50},{14,-50},{14,-20},{30,-20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end PistonEngine;

    model KinematicLoop

      Joints.Revolute revolute(phi(stateSelect=StateSelect.always), w(
            stateSelect=StateSelect.always))
                               annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-20,50})));
      Joints.Revolute revolute1 annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={80,50})));
      Joints.Revolute revolute2
        annotation (Placement(transformation(extent={{10,-10},{30,10}})));
      Joints.Revolute revolute3(
        initialize=true,
        w_start=0,
        phi_start=0) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-20,-30})));
      Parts.FixedTranslation fixedTranslation1(r={0, -0.5}) annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-20,20})));
      Parts.FixedTranslation fixedTranslation2(r={0, -0.5}) annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={80,20})));
      Parts.FixedTranslation fixedTranslation3(r={0, -0.6}) annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={10,-50})));
      Parts.Body body(
        m=1,
        I=0.1,
        g={0,-9.81}) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={50,-50})));
      Parts.Fixed fixed annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-50,70})));
      Joints.ActuatedPrismatic actuatedPrismatic(r={1,0},
        initialize=true,
        s_start=0.4,
        v_start=0)
        annotation (Placement(transformation(extent={{20,60},{40,80}})));
      Modelica.Mechanics.Translational.Components.SpringDamper springDamper(
        c=10,
        s_rel0=0.6,
        d=2) annotation (Placement(transformation(extent={{0,80},{20,100}})));
      Modelica.Mechanics.Translational.Components.Fixed fixed1 annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-46,90})));
    equation
      connect(fixedTranslation1.frame_a, revolute.frame_b) annotation (Line(
          points={{-20,30},{-20,32.5},{-20,32.5},{-20,35},{-20,40},{-20,40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation2.frame_a, revolute1.frame_b) annotation (Line(
          points={{80,30},{80,40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute2.frame_a, fixedTranslation1.frame_b) annotation (Line(
          points={{10,0},{-20,0},{-20,10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute2.frame_b, fixedTranslation2.frame_b) annotation (Line(
          points={{30,0},{80,0},{80,10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation3.frame_a, revolute3.frame_b) annotation (Line(
          points={{0,-50},{-20,-50},{-20,-40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(actuatedPrismatic.frame_b, revolute1.frame_a) annotation (Line(
          points={{40,70},{80,70},{80,60}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(actuatedPrismatic.frame_a, fixed.frame_a) annotation (Line(
          points={{20,70},{-40,70}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute.frame_a, fixed.frame_a) annotation (Line(
          points={{-20,60},{-20,70},{-40,70}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(springDamper.flange_b, actuatedPrismatic.flange_a) annotation (
          Line(
          points={{20,90},{30,90},{30,79}},
          color={0,127,0},
          smooth=Smooth.None));
      connect(fixed1.flange, springDamper.flange_a) annotation (Line(
          points={{-46,90},{0,90}},
          color={0,127,0},
          smooth=Smooth.None));
      connect(revolute3.frame_a, fixedTranslation1.frame_b) annotation (Line(
          points={{-20,-20},{-20,-12.5},{-20,-12.5},{-20,-5},{-20,10},{-20,10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));

      connect(body.frame_a, fixedTranslation3.frame_b) annotation (Line(
          points={{40,-50},{30,-50},{30,-50},{20,-50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end KinematicLoop;

    model TestIdealWheel

      VehicleComponents.Wheels.IdealWheelJoint idealWheelJoint(
        radius=0.3,
        r={1,0}) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,40})));
      Joints.Prismatic prismatic(
        r={0,1},
        s(start=1)) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,10})));
      Joints.Revolute revolute annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,-20})));
      Parts.Fixed fixed annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={0,-50})));
      Modelica.Mechanics.Rotational.Sources.ConstantTorque engineTorque(
          tau_constant=2)
        annotation (Placement(transformation(extent={{-32,70},{-12,90}})));
      Parts.Body body(m=10, I=1)
        annotation (Placement(transformation(extent={{20,10},{40,30}})));
      Modelica.Mechanics.Rotational.Components.Inertia inertia(
        phi(fixed=true, start=0),
        w(fixed=true, start=0),
        J=1)                    annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=270,
            origin={0,70})));
    equation
      connect(idealWheelJoint.frame_a, prismatic.frame_b) annotation (Line(
          points={{-2.93915e-016,35.2},{-2.93915e-016,38.6},{6.12323e-016,38.6},
              {6.12323e-016,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(prismatic.frame_a, revolute.frame_b) annotation (Line(
          points={{-6.12323e-016,0},{6.12323e-016,0},{6.12323e-016,-10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute.frame_a, fixed.frame_a) annotation (Line(
          points={{-6.12323e-016,-30},{1.83697e-015,-30},{1.83697e-015,-40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(engineTorque.flange, inertia.flange_a) annotation (Line(
          points={{-12,80},{1.83697e-015,80}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(inertia.flange_b, idealWheelJoint.flange_a) annotation (Line(
          points={{-1.83697e-015,60},{0,52},{6.12323e-016,50}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(body.frame_a, prismatic.frame_b) annotation (Line(
          points={{20,20},{6.12323e-016,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end TestIdealWheel;

    model TestDryFrictionWheel

      Joints.Prismatic prismatic(
        r={0,1},
        s(start=1)) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,10})));
      Joints.Revolute revolute annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,-20})));
      Parts.Fixed fixed annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={0,-50})));
      Modelica.Mechanics.Rotational.Sources.ConstantTorque engineTorque(
          tau_constant=2)
        annotation (Placement(transformation(extent={{-32,70},{-12,90}})));
      Parts.Body body(m=10, I=1)
        annotation (Placement(transformation(extent={{20,10},{40,30}})));
      Modelica.Mechanics.Rotational.Components.Inertia inertia(
        phi(fixed=true, start=0),
        w(fixed=true, start=0),
        J=1)                    annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=270,
            origin={0,70})));
      VehicleComponents.Wheels.DryFrictionWheelJoint dryFrictionWheelJoint(
        radius=0.3,
        r={1,0},
        N=100,
        vAdhesion=0.1,
        vSlide=0.3,
        mu_A=0.8,
        mu_S=0.4) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,42})));
    equation
      connect(prismatic.frame_a, revolute.frame_b) annotation (Line(
          points={{-6.12323e-016,0},{6.12323e-016,0},{6.12323e-016,-10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute.frame_a, fixed.frame_a) annotation (Line(
          points={{-6.12323e-016,-30},{1.83697e-015,-30},{1.83697e-015,-40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(engineTorque.flange, inertia.flange_a) annotation (Line(
          points={{-12,80},{1.83697e-015,80}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(body.frame_a, prismatic.frame_b) annotation (Line(
          points={{20,20},{6.12323e-016,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(dryFrictionWheelJoint.frame_a, prismatic.frame_b) annotation (
          Line(
          points={{-2.93915e-016,37.2},{-2.93915e-016,28.6},{6.12323e-016,28.6},
              {6.12323e-016,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(dryFrictionWheelJoint.flange_a, inertia.flange_b) annotation (
          Line(
          points={{6.12323e-016,52},{-1.83697e-015,52},{-1.83697e-015,60}},
          color={0,0,0},
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end TestDryFrictionWheel;

    model TestSlipBasedWheel

      Joints.Prismatic prismatic(r={0,1},
        s(start=1)) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,10})));
      Joints.Revolute revolute annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,-20})));
      Parts.Fixed fixed annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={0,-50})));
      Modelica.Mechanics.Rotational.Sources.ConstantTorque engineTorque(
          tau_constant=2)
        annotation (Placement(transformation(extent={{-32,70},{-12,90}})));
      Parts.Body body(m=10, I=1)
        annotation (Placement(transformation(extent={{20,10},{40,30}})));
      Modelica.Mechanics.Rotational.Components.Inertia inertia(
        phi(fixed=true, start=0),
        w(fixed=true, start=0),
        J=1)                    annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=270,
            origin={0,70})));
      VehicleComponents.Wheels.SlipBasedWheelJoint slipBasedWheelJoint(
        radius=0.3, r = {1,0},
        mu_A=0.8,
        mu_S=0.4,
        N=100,
        sAdhesion=0.04,
        sSlide=0.12,
        vAdhesion_min=0.05,
        vSlide_min=0.15)
                  annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,42})));
      Modelica.Blocks.Sources.Constant const(k=0)
        annotation (Placement(transformation(extent={{-60,32},{-40,52}})));
    equation
      connect(prismatic.frame_a, revolute.frame_b) annotation (Line(
          points={{-6.12323e-016,0},{6.12323e-016,0},{6.12323e-016,-10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute.frame_a, fixed.frame_a) annotation (Line(
          points={{-6.12323e-016,-30},{1.83697e-015,-30},{1.83697e-015,-40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(engineTorque.flange, inertia.flange_a) annotation (Line(
          points={{-12,80},{1.83697e-015,80}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(body.frame_a, prismatic.frame_b) annotation (Line(
          points={{20,20},{6.12323e-016,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(slipBasedWheelJoint.frame_a, prismatic.frame_b) annotation (Line(
          points={{-2.93915e-016,37.2},{-2.93915e-016,28.6},{6.12323e-016,28.6},
              {6.12323e-016,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(slipBasedWheelJoint.flange_a, inertia.flange_b) annotation (Line(
          points={{6.12323e-016,52},{-1.83697e-015,52},{-1.83697e-015,60}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(const.y, slipBasedWheelJoint.dynamicLoad) annotation (Line(
          points={{-39,42},{-10,42}},
          color={0,0,127},
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end TestSlipBasedWheel;

    model SingleTrackWithEngine "AcceleratingBody"

      Parts.Body bodyFront(
        I=0.1,
        m=2,
        g={0,0})
        annotation (Placement(transformation(extent={{-10,-10},{10,10}},
            rotation=0,
            origin={40,50})));
      VehicleComponents.Wheels.IdealWheelJoint idealWheelFront(
        r={0,1},
        radius=0.3)
              annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={0,50})));
      Parts.FixedTranslation chassis(r={0,1})             annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={20,-40})));
      Parts.Body bodyRear(
        I=0.1,
        g={0,0},
        m=10) annotation (Placement(transformation(extent={{30,-90},{50,-70}})));
      VehicleComponents.Wheels.IdealWheelJoint idealWheelRear(
        r={0,1},
        radius=0.3) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={0,-80})));
      Joints.Revolute revolute(
        initialize=true,
        w_start=0,
        phi_start=-0.69813170079773)
                   annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={20,0})));
      Modelica.Mechanics.Rotational.Sources.ConstantTorque engineTorque(
          tau_constant=2)
        annotation (Placement(transformation(extent={{-40,-90},{-20,-70}})));
      Parts.FixedTranslation trail(r={0,-0.1})            annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={20,30})));
    equation
      connect(idealWheelFront.frame_a, bodyFront.frame_a)
                                                     annotation (Line(
          points={{4.8,50},{30,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(chassis.frame_a, idealWheelRear.frame_a)             annotation (
          Line(
          points={{20,-50},{20,-80},{4.8,-80}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(bodyRear.frame_a, chassis.frame_a)        annotation (Line(
          points={{30,-80},{20,-80},{20,-50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute.frame_a, chassis.frame_b)           annotation (Line(
          points={{20,-10},{20,-30}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(engineTorque.flange, idealWheelRear.flange_a)      annotation (
          Line(
          points={{-20,-80},{-10,-80}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(trail.frame_a, revolute.frame_b) annotation (Line(
          points={{20,20},{20,10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(trail.frame_b, idealWheelFront.frame_a) annotation (Line(
          points={{20,40},{20,50},{4.8,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end SingleTrackWithEngine;

    model SingleTrackFixedSteering "AcceleratingBody"

      Parts.Body body(
        m=1,
        I=0.1,
        g={0,0})
        annotation (Placement(transformation(extent={{-10,-10},{10,10}},
            rotation=0,
            origin={40,50})));
      VehicleComponents.Wheels.IdealWheelJoint idealWheelJoint(
        r={0,1},
        radius=0.2) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={0,50})));
      Parts.FixedTranslation fixedTranslation1(r={0,0.8}) annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={20,-40})));
      Parts.Body body1(
        I=0.1,
        m=10,
        g={0,0})
              annotation (Placement(transformation(extent={{30,-90},{50,-70}})));
      VehicleComponents.Wheels.IdealWheelJoint idealWheelJoint1(
        r={0,1},
        radius=0.2) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={0,-80})));
      Parts.FixedRotation fixedRotation(alpha=-0.13962634015955) annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={20,0})));
      Modelica.Mechanics.Rotational.Sources.ConstantTorque constantTorque(
          tau_constant=0)
        annotation (Placement(transformation(extent={{-50,40},{-30,60}})));
      Modelica.Mechanics.Rotational.Sources.ConstantTorque constantTorque1(
          tau_constant=3)
        annotation (Placement(transformation(extent={{-50,-90},{-30,-70}})));
    equation
      connect(idealWheelJoint.frame_a, body.frame_a) annotation (Line(
          points={{4.8,50},{30,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation1.frame_a, idealWheelJoint1.frame_a) annotation (
          Line(
          points={{20,-50},{20,-80},{4.8,-80}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(body1.frame_a, fixedTranslation1.frame_a) annotation (Line(
          points={{30,-80},{20,-80},{20,-50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedRotation.frame_b, fixedTranslation1.frame_b) annotation (
          Line(
          points={{20,-10},{20,-20},{20,-20},{20,-30}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedRotation.frame_a, idealWheelJoint.frame_a) annotation (Line(
          points={{20,10},{20,50},{4.8,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(constantTorque1.flange, idealWheelJoint1.flange_a) annotation (
          Line(
          points={{-30,-80},{-10,-80}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(constantTorque.flange, idealWheelJoint.flange_a) annotation (Line(
          points={{-30,50},{-10,50}},
          color={0,0,0},
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end SingleTrackFixedSteering;

    model SingleTrackFixedSteeringFriction "AcceleratingBody"

      Parts.Body body(
        m=1,
        I=0.1,
        g={0,0})
        annotation (Placement(transformation(extent={{-10,-10},{10,10}},
            rotation=0,
            origin={40,50})));
      VehicleComponents.Wheels.DryFrictionWheelJoint dryFrictionWheelJoint1(
        r={0,1},
        radius=0.2,
        N=20,
        vAdhesion=0.1,
        vSlide=0.2,
        mu_A=0.8,
        mu_S=0.4)   annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={0,50})));
      Parts.FixedTranslation fixedTranslation1(r={0,0.8}) annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={20,-40})));
      Parts.Body body1(
        I=0.1,
        m=10,
        g={0,0})
              annotation (Placement(transformation(extent={{30,-90},{50,-70}})));
      VehicleComponents.Wheels.DryFrictionWheelJoint dryFrictionWheelJoint2(
        r={0,1},
        radius=0.2,
        N=100,
        vAdhesion=0.1,
        vSlide=0.2,
        mu_A=0.8,
        mu_S=0.4)   annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={0,-80})));
      Parts.FixedRotation fixedRotation(alpha=-0.2090729910964)  annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={20,0})));
      Modelica.Mechanics.Rotational.Sources.ConstantTorque constantTorque(
          tau_constant=0)
        annotation (Placement(transformation(extent={{-50,40},{-30,60}})));
      Modelica.Mechanics.Rotational.Sources.ConstantTorque constantTorque1(
          tau_constant=3)
        annotation (Placement(transformation(extent={{-50,-90},{-30,-70}})));
    equation
      connect(body1.frame_a, fixedTranslation1.frame_a) annotation (Line(
          points={{30,-80},{20,-80},{20,-50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedRotation.frame_b, fixedTranslation1.frame_b) annotation (
          Line(
          points={{20,-10},{20,-20},{20,-20},{20,-30}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(dryFrictionWheelJoint1.frame_a, body.frame_a) annotation (Line(
          points={{4.8,50},{30,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(dryFrictionWheelJoint1.frame_a, fixedRotation.frame_a)
        annotation (Line(
          points={{4.8,50},{20,50},{20,10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(body1.frame_a, dryFrictionWheelJoint2.frame_a) annotation (Line(
          points={{30,-80},{4.8,-80}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(constantTorque1.flange, dryFrictionWheelJoint2.flange_a)
        annotation (Line(
          points={{-30,-80},{-10,-80}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(constantTorque.flange, dryFrictionWheelJoint1.flange_a)
        annotation (Line(
          points={{-30,50},{-10,50}},
          color={0,0,0},
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end SingleTrackFixedSteeringFriction;

    model SimpleCarWithDifferentialGear "AcceleratingBody"

      Parts.Body body(
        g={0,0},
        m=100,
        I=1)
        annotation (Placement(transformation(extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-40,90})));
      VehicleComponents.Wheels.DryFrictionWheelJoint WheelJoint1(
        vAdhesion=0.1,
        r = {0,1},
        vSlide=0.3,
        mu_A=1,
        mu_S=0.7,
        radius=0.25,
        N=1000)
              annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-62,70})));
      Parts.FixedTranslation fixedTranslation1(r={0,2})   annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,-2})));
      Parts.Body body1(
        I=0.1,
        g={0,0},
        m=300)
              annotation (Placement(transformation(extent={{12,-30},{32,-10}})));
      VehicleComponents.Wheels.DryFrictionWheelJoint WheelJoint2(
        r= {0,1},
        vAdhesion=0.1,
        vSlide=0.3,
        mu_A=1,
        mu_S=0.7,
        radius=0.25,
        N=1500)
               annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-60,-40})));
      Modelica.Mechanics.Rotational.Sources.ConstantTorque constantTorque1(
          tau_constant=25)
        annotation (Placement(transformation(extent={{-10,-10},{10,10}},
            rotation=0,
            origin={-50,-80})));
      Modelica.Mechanics.Rotational.Components.Inertia inertia(
        phi(fixed=true, start=0),
        w(fixed=true, start=0),
        J=1)                    annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=0,
            origin={-90,70})));
      Modelica.Mechanics.Rotational.Components.Inertia inertia1(
        phi(fixed=true, start=0),
        w(fixed=true, start=0),
        J=1)                    annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=0,
            origin={-92,-40})));
      Parts.FixedTranslation fixedTranslation2(r={0.75,0})   annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={-20,-40})));
      Parts.FixedTranslation fixedTranslation3(r={-0.75,0})  annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={20,-40})));
      VehicleComponents.Wheels.DryFrictionWheelJoint WheelJoint3(
        r = {0,1},
        vAdhesion=0.1,
        vSlide=0.3,
        mu_A=1,
        mu_S=0.7,
        radius=0.25,
        N=1500)
               annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={62,-40})));
      Modelica.Mechanics.Rotational.Components.Inertia inertia2(
        phi(fixed=false, start=0),
        w(fixed=false, start=0),
        J=1)                    annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={90,-40})));
      Parts.FixedTranslation fixedTranslation4(r={0.75,0})   annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={-20,20})));
      Parts.FixedTranslation fixedTranslation5(r={-0.75,0})  annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={20,20})));
      VehicleComponents.Wheels.DryFrictionWheelJoint WheelJoint4(
        vAdhesion=0.1,
        r={0,1},
        vSlide=0.3,
        mu_A=1,
        mu_S=0.7,
        radius=0.25,
        N=1000)
              annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={60,70})));
      Modelica.Mechanics.Rotational.Components.Inertia inertia3(
        phi(fixed=true, start=0),
        w(fixed=true, start=0),
        J=1)                    annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=180,
            origin={90,70})));
      Parts.Body body2(
        g={0,0},
        m=100,
        I=1)
        annotation (Placement(transformation(extent={{-10,-10},{10,10}},
            rotation=90,
            origin={40,90})));
      Joints.ActuatedRevolute actuatedRevolute(
        initialize=true,
        w_start=0,
        phi_start=0.43633231299858) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-40,40})));
      Joints.ActuatedRevolute actuatedRevolute1 annotation (Placement(
            transformation(
            extent={{-10,10},{10,-10}},
            rotation=270,
            origin={40,40})));
      Modelica.Mechanics.Rotational.Sources.Torque torque
        annotation (Placement(transformation(extent={{-10,70},{-30,90}})));
      Modelica.Blocks.Sources.Pulse pulse(
        amplitude=1,
        period=2,
        offset=0,
        startTime=1,
        width=30)
        annotation (Placement(transformation(extent={{20,70},{0,90}})));
      VehicleComponents.DifferentialGear differentialGear
        annotation (Placement(transformation(extent={{-10,-72},{10,-52}})));
      Parts.FixedTranslation leftTrail(r={0.,-0.05})         annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-40,64})));
      Parts.FixedTranslation rightTrail(r={0.,-0.05})        annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={40,66})));
    equation
      connect(WheelJoint2.flange_a, inertia1.flange_b) annotation (Line(
          points={{-70,-40},{-82,-40}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(inertia.flange_b, WheelJoint1.flange_a) annotation (Line(
          points={{-80,70},{-72,70}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(fixedTranslation2.frame_b, fixedTranslation1.frame_a) annotation (
         Line(
          points={{-10,-40},{0,-40},{0,-12},{-6.12323e-016,-12}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation2.frame_a, WheelJoint2.frame_a) annotation (Line(
          points={{-30,-40},{-55.2,-40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation3.frame_b, fixedTranslation1.frame_a) annotation (
         Line(
          points={{10,-40},{-6.12323e-016,-40},{-6.12323e-016,-12}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(WheelJoint3.frame_a, fixedTranslation3.frame_a) annotation (Line(
          points={{57.2,-40},{30,-40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(inertia2.flange_b, WheelJoint3.flange_a) annotation (Line(
          points={{80,-40},{72,-40}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(body1.frame_a, fixedTranslation1.frame_a) annotation (Line(
          points={{12,-20},{-6.12323e-016,-20},{-6.12323e-016,-12}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation1.frame_b, fixedTranslation4.frame_b) annotation (
         Line(
          points={{6.12323e-016,8},{0,8},{0,20},{-10,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation1.frame_b, fixedTranslation5.frame_b) annotation (
         Line(
          points={{6.12323e-016,8},{0,8},{0,20},{10,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(inertia3.flange_b, WheelJoint4.flange_a) annotation (Line(
          points={{80,70},{70,70}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(actuatedRevolute1.frame_b, fixedTranslation5.frame_a) annotation (
         Line(
          points={{40,30},{40,20},{30,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(actuatedRevolute.frame_b, fixedTranslation4.frame_a) annotation (
          Line(
          points={{-40,30},{-40,20},{-30,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(actuatedRevolute.flange_a, actuatedRevolute1.flange_a)
        annotation (Line(
          points={{-30,40},{30,40}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(torque.flange, actuatedRevolute.flange_a) annotation (Line(
          points={{-30,80},{-30,40}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(pulse.y, torque.tau) annotation (Line(
          points={{-1,80},{-8,80}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(differentialGear.flange_right, WheelJoint3.flange_a) annotation (
          Line(
          points={{10,-62},{78,-62},{78,-40},{72,-40}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(differentialGear.flange_left, WheelJoint2.flange_a) annotation (
          Line(
          points={{-10,-62},{-70,-62},{-70,-40}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(constantTorque1.flange, differentialGear.flange_b) annotation (
          Line(
          points={{-40,-80},{0,-72}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(body.frame_a, leftTrail.frame_b) annotation (Line(
          points={{-40,80},{-40,74}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(leftTrail.frame_b, WheelJoint1.frame_a) annotation (Line(
          points={{-40,74},{-52,74},{-52,70},{-57.2,70}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(leftTrail.frame_a, actuatedRevolute.frame_a) annotation (Line(
          points={{-40,54},{-40,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(body2.frame_a, rightTrail.frame_b) annotation (Line(
          points={{40,80},{40,76}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(rightTrail.frame_a, actuatedRevolute1.frame_a) annotation (Line(
          points={{40,56},{40,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(WheelJoint4.frame_a, rightTrail.frame_b) annotation (Line(
          points={{55.2,70},{44,70},{44,76},{40,76}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end SimpleCarWithDifferentialGear;

    model TwoTrackStaticLoad "AcceleratingBody"

      Modelica.Mechanics.Rotational.Sources.Torque torque annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={-30,-70})));
      Modelica.Blocks.Sources.Pulse pulse(
        period=2,
        offset=0,
        width=30,
        startTime=3,
        amplitude=10)
        annotation (Placement(transformation(extent={{80,60},{60,80}})));
      PlanarMechanicsV3.VehicleComponents.SimpleRearAxis rearAxis
        annotation (Placement(transformation(extent={{-20,-50},{20,-30}})));
      PlanarMechanicsV3.VehicleComponents.SimpleFrontAxis frontAxis(trail=0.02,
          I_susp=2)
        annotation (Placement(transformation(extent={{-20,30},{20,50}})));
      inner MB.World world(n={0,0,-1})
        annotation (Placement(transformation(extent={{-80,60},{-60,80}})));
      Modelica.Blocks.Sources.Ramp ramp(
        duration=2,
        offset=0,
        startTime=0.2,
        height=100)
        annotation (Placement(transformation(extent={{-80,-80},{-60,-60}})));
      Modelica.Mechanics.Rotational.Sources.Torque torque1
        annotation (Placement(transformation(extent={{40,60},{20,80}})));
      VehicleComponents.SimpleChassis simpleChassis
        annotation (Placement(transformation(extent={{-20,-20},{20,20}})));
    equation
      connect(ramp.y, torque.tau) annotation (Line(
          points={{-59,-70},{-42,-70}},
          color={0,0,127},
          pattern=LinePattern.None,
          thickness=0.5,
          smooth=Smooth.None));
      connect(torque.flange, rearAxis.flange_b) annotation (Line(
          points={{-20,-70},{0,-70},{0,-50}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(torque1.flange, frontAxis.flange_b) annotation (Line(
          points={{20,70},{0,70},{0,50}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(pulse.y, torque1.tau) annotation (Line(
          points={{59,70},{42,70}},
          color={0,0,127},
          pattern=LinePattern.None,
          thickness=0.5,
          smooth=Smooth.None));
      connect(simpleChassis.frame_b, frontAxis.frame_a) annotation (Line(
          points={{0,20},{0,37}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(simpleChassis.frame_a, rearAxis.frame_a) annotation (Line(
          points={{0,-20.2},{0,-37}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end TwoTrackStaticLoad;

    model TwoTrackStaticLoad3D "AcceleratingBody"

      Modelica.Mechanics.Rotational.Sources.Torque torque annotation (Placement(
            transformation(
            extent={{10,-10},{-10,10}},
            rotation=0,
            origin={30,-70})));
      Modelica.Blocks.Sources.Pulse pulse(
        period=2,
        offset=0,
        width=30,
        startTime=3,
        amplitude=10)
        annotation (Placement(transformation(extent={{80,60},{60,80}})));
      PlanarMechanicsV3.VehicleComponents.SimpleRearAxis rearAxis
        annotation (Placement(transformation(extent={{-20,-50},{20,-30}})));
      PlanarMechanicsV3.VehicleComponents.SimpleFrontAxis frontAxis(trail=0.02,
          I_susp=2)
        annotation (Placement(transformation(extent={{-20,30},{20,50}})));
      Modelica.Blocks.Sources.Ramp ramp(
        duration=2,
        offset=0,
        startTime=0.2,
        height=100)
        annotation (Placement(transformation(extent={{80,-80},{60,-60}})));
      Modelica.Mechanics.Rotational.Sources.Torque torque1
        annotation (Placement(transformation(extent={{40,60},{20,80}})));
      VehicleComponents.SimpleChassis3D simpleChassis3D(
        c_roll=2000,
        d_roll=200,
        c_pitch=3000,
        d_pitch=300)
        annotation (Placement(transformation(extent={{-20,-20},{20,20}})));
      inner MB.World world(n={0,0,-1})
        annotation (Placement(transformation(extent={{-70,70},{-50,90}})));
    equation
      connect(torque1.flange, frontAxis.flange_b) annotation (Line(
          points={{20,70},{0,70},{0,50}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(simpleChassis3D.frame_a, rearAxis.frame_a) annotation (Line(
          points={{0,-20.2},{0,-37}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(simpleChassis3D.frame_b, frontAxis.frame_a) annotation (Line(
          points={{0,20},{0,37}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(torque.flange, rearAxis.flange_b) annotation (Line(
          points={{20,-70},{0,-70},{0,-50}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(ramp.y, torque.tau) annotation (Line(
          points={{59,-70},{42,-70}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(pulse.y, torque1.tau) annotation (Line(
          points={{59,70},{42,70}},
          color={0,0,127},
          smooth=Smooth.None));
      annotation (Diagram(coordinateSystem(preserveAspectRatio=false, extent={{
                -100,-100},{100,100}}),
                          graphics));
    end TwoTrackStaticLoad3D;

    model TwoTrackWithDynamicLoadSimVis "AcceleratingBody"

      Modelica.Mechanics.Rotational.Sources.Torque torque annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={-36,-90})));
      inner MB.World world(n={0,0,-1}, enableAnimation=false)
        annotation (Placement(transformation(extent={{80,80},{100,100}})));
      Modelica.Mechanics.Rotational.Sources.Torque torque1
        annotation (Placement(transformation(extent={{10,10},{-10,-10}},
            rotation=180,
            origin={-30,90})));
      PlanarMechanicsV3.VehicleComponents.Chassis3D chassis(
        animate=false,
        w=1.5,
        l=2.8,
        wheelBase=2.2,
        m_static=1200,
        m_dynamic=400,
        c_roll=20000,
        d_roll=2000,
        c_pitch=20000,
        d_pitch=2000)
        annotation (Placement(transformation(extent={{-20,-20},{20,20}})));
      VehicleComponents.DynamicRearAxis dynamicRearAxis(
        animate=false,
        sAdhesion=0.02,
        sSlide=0.03,
        axisLength=1.4,
        vAdhesion_min=0.05,
        vSlide_min=0.1,
        N=3700)
        annotation (Placement(transformation(extent={{-20,-60},{20,-40}})));
      VehicleComponents.DynamicFrontAxis dynamicFrontAxis(
        animate=false,
        sAdhesion=0.02,
        sSlide=0.03,
        axisLength=1.4,
        I=3,
        I_susp=15,
        vAdhesion_min=0.05,
        vSlide_min=0.1,
        N=4300)
        annotation (Placement(transformation(extent={{-20,40},{20,60}})));
      Visualization.Cameras.DynamicFollowCamera camera(T=0.2,
        windowMode=Visualization.Cameras.Internal.Types.WindowMode.Window,
        r_0={0,0,25})
        annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={60,0})));
      Interfaces.PlanarToMultiBody planarToMultiBody
        annotation (Placement(transformation(extent={{20,-40},{40,-20}})));
      Interfaces.PlanarToMultiBody planarToMultiBody1
        annotation (Placement(transformation(extent={{12,20},{32,40}})));
      MB.Parts.FixedTranslation fixedTranslation(r={0,-8.5,1.7})
        annotation (Placement(transformation(extent={{40,-40},{60,-20}})));
      VehicleComponents.VehicleControl vehicleControl(
        steeringTorque_max=100,
        drivingTorque_max=360,
        frontBrakeTorque_max=450,
        rearBrakeTorque_max=300,
        handBrakeTorque_max=300)
                               annotation (Placement(transformation(
            extent={{-15,15},{15,-15}},
            rotation=180,
            origin={-73,-1})));
      VehicleComponents.SimpleLimiter simpleLimiter(phi_lim=Modelica.Constants.pi
            /6)
        annotation (Placement(transformation(extent={{14,80},{34,100}})));
      VehicleComponents.SimpleBrake simpleBrake annotation (Placement(
            transformation(
            extent={{-10,10},{10,-10}},
            rotation=180,
            origin={-40,50})));
      VehicleComponents.SimpleBrake simpleBrake1
        annotation (Placement(transformation(extent={{34,40},{54,60}})));
      VehicleComponents.SimpleBrake simpleBrake2 annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-40,-50})));
      VehicleComponents.SimpleBrake simpleBrake3
        annotation (Placement(transformation(extent={{30,-40},{50,-60}})));
      Visualization.Shapes.FileShape shape1(filename=Visualization.Utilities.RootDir
             + "/Extras/3DData/testarea/testarea.3DS", scaleFactor={0.1,
                                                                       0.1,
                                                                          0.1})
                        annotation (Placement(transformation(extent={{80,-100},
                {100,-80}},
                       rotation=0)));
      MB.Parts.Fixed fixed1(                                        animation=false)
        annotation (Placement(transformation(extent={{60,-100},{80,-80}},rotation=0)));
      MB.Parts.FixedTranslation fixedTranslation1(r={0,1,1})
        annotation (Placement(transformation(extent={{30,20},{50,40}})));
      Visualization.Lights.SpotLight light(
        lightDirection={0,-1,0},
        spotAngle=180,
        color={255,235,168})
        annotation (Placement(transformation(extent={{86,-80},{106,-60}})));
      MB.Parts.Fixed fixed2(                                        animation=false, r={0,500,
            100})
        annotation (Placement(transformation(extent={{60,-80},{80,-60}}, rotation=0)));
      Visualization.Lights.DiffuseLight light1(color={0,20,60})
        annotation (Placement(transformation(extent={{80,-60},{100,-40}})));
      Modelica.Mechanics.Rotational.Components.SpringDamper springDamper(c=10, d=10)
        annotation (Placement(transformation(extent={{12,64},{32,84}})));
      Modelica.Mechanics.Rotational.Components.Fixed fixed(phi0=0)
        annotation (Placement(transformation(extent={{48,62},{68,82}})));
      Modelica_DeviceDrivers.Blocks.OperatingSystem.SynchronizeRealtime
        synchronizeRealtime
        annotation (Placement(transformation(extent={{80,-20},{100,0}})));
    equation
      connect(dynamicRearAxis.frame_a, chassis.frame_a) annotation (Line(
          points={{0,-47},{0,-20.2}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(chassis.dynamicLoadRR, dynamicRearAxis.dynamicLoadRight)
        annotation (Line(
          points={{16.1,-19.9},{16.1,-28.95},{16,-28.95},{16,-40}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(chassis.dynamicLoadLR, dynamicRearAxis.dynamicLoadLeft)
        annotation (Line(
          points={{-16,-20},{-16,-40}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(dynamicFrontAxis.frame_a, chassis.frame_b) annotation (Line(
          points={{0,47},{0,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(chassis.dynamicLoadRF, dynamicFrontAxis.dynamicLoadRight)
        annotation (Line(
          points={{16,20},{16,40}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(chassis.dynamicLoadLF, dynamicFrontAxis.dynamicLoadLeft)
        annotation (Line(
          points={{-16,20},{-16,40}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(torque1.flange, dynamicFrontAxis.flange_b) annotation (Line(
          points={{-20,90},{0,90},{0,60}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(planarToMultiBody1.frame_a, chassis.frame_b) annotation (Line(
          points={{19.2,30},{0,30},{0,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(planarToMultiBody.frame_a, dynamicRearAxis.frame_a) annotation (
          Line(
          points={{27.2,-30},{0,-30},{0,-47}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation.frame_a, planarToMultiBody.frame_b) annotation (
          Line(
          points={{40,-30},{32.4,-30}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation.frame_b, camera.frame_a) annotation (Line(
          points={{60,-30},{60,-10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(torque.flange, dynamicRearAxis.flange_b) annotation (Line(
          points={{-26,-90},{0,-90},{0,-60}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(vehicleControl.drivingTorque, torque.tau) annotation (Line(
          points={{-73,-16.2},{-74,-90},{-48,-90}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(vehicleControl.steering, torque1.tau) annotation (Line(
          points={{-73,14},{-74,14},{-74,90},{-42,90}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(simpleLimiter.flange_a, dynamicFrontAxis.flange_b) annotation (
          Line(
          points={{14,90},{0,90},{0,60}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(simpleBrake1.flange_a, dynamicFrontAxis.flange_right) annotation (
         Line(
          points={{34,50},{20,50}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(simpleBrake.flange_a, dynamicFrontAxis.flange_left) annotation (
          Line(
          points={{-30,50},{-20,50}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(vehicleControl.frontBrake, simpleBrake.tau_brake) annotation (
          Line(
          points={{-58.2,7},{-50,7},{-50,68},{-40,68},{-40,61}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(vehicleControl.frontBrake, simpleBrake1.tau_brake) annotation (
          Line(
          points={{-58.2,7},{-58.2,68},{44,68},{44,61}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(simpleBrake2.flange_a, dynamicRearAxis.flange_left) annotation (
          Line(
          points={{-30,-50},{-20,-50}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(simpleBrake3.flange_a, dynamicRearAxis.flange_right) annotation (
          Line(
          points={{30,-50},{20,-50}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(simpleBrake2.tau_brake, vehicleControl.rearBrake) annotation (
          Line(
          points={{-40,-61},{-40,-70},{-52,-70},{-52,-9},{-58,-9}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(simpleBrake3.tau_brake, vehicleControl.rearBrake) annotation (
          Line(
          points={{40,-61},{40,-70},{-52,-70},{-52,-9},{-58,-9}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(fixed1.frame_b,shape1. frame_a) annotation (Line(
          points={{80,-90},{80,-90}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation1.frame_a, planarToMultiBody1.frame_b)
        annotation (Line(
          points={{30,30},{24.4,30}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation1.frame_b, camera.frame_b) annotation (Line(
          points={{50,30},{60,30},{60,10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(light.frame_a, fixed2.frame_b) annotation (Line(
          points={{86,-70},{80,-70}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixed.flange, springDamper.flange_b) annotation (Line(
          points={{58,72},{46,72},{46,74},{32,74}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(springDamper.flange_a, dynamicFrontAxis.flange_b) annotation (
          Line(
          points={{12,74},{0,74},{0,60}},
          color={0,0,0},
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end TwoTrackWithDynamicLoadSimVis;

    model FilterKeyboardInput
      Modelica_DeviceDrivers.Blocks.InputDevices.KeyboardInput keyboardInput(
          sampleTime=0.05)
        annotation (Placement(transformation(extent={{-60,0},{-40,20}})));
      Modelica.Blocks.Continuous.CriticalDamping criticalDamping(
        normalized=false,
        n=2,
        f=1) annotation (Placement(transformation(extent={{40,0},{60,20}})));
      Modelica.Blocks.Math.BooleanToReal booleanToReal
        annotation (Placement(transformation(extent={{-20,0},{0,20}})));
    equation
      connect(booleanToReal.u, keyboardInput.keyUp) annotation (Line(
          points={{-22,10},{-32,10},{-32,16},{-39,16}},
          color={255,0,255},
          smooth=Smooth.None));
      connect(booleanToReal.y, criticalDamping.u) annotation (Line(
          points={{1,10},{20,10},{20,10},{38,10}},
          color={0,0,127},
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end FilterKeyboardInput;

  end Examples;

  package Utilities
    function S_Func "Models an S-Function"

      input Real x_min;
      input Real x_max;
      input Real y_min;
      input Real y_max;

      input Real x;
      output Real y;

    protected
      Real x2;

    algorithm
      x2 := x - x_max/2 - x_min/2;
      x2 := x2*2/(x_max-x_min);

      if x2 > 1 then
        y := 1;
      elseif x2 < -1 then
        y := -1;
      else
        y := -0.5*x2^3 + 1.5*x2;
      end if;

      y := y*(y_max-y_min)/2;
      y := y + y_max/2 + y_min/2;

      annotation(smoothOrder=1);
    end S_Func;

    function TripleS_Func "Models a point-symmetric Triple S-Function"

      input Real x_max;
      input Real x_sat;
      input Real y_max;
      input Real y_sat;

      input Real x;
      output Real y;

    algorithm
      if x > x_max then
        y := S_Func(x_max,x_sat,y_max,y_sat,x);
      elseif x < -x_max then
        y := S_Func(-x_max,-x_sat,-y_max,-y_sat,x);
      else
        y := S_Func(-x_max,x_max,-y_max,y_max,x);
      end if;

      annotation(smoothOrder=1);
    end TripleS_Func;

    block S_FuncBlock
      extends Modelica.Blocks.Interfaces.SISO;

      parameter Real x_min = 0;
      parameter Real x_max = 1;
      parameter Real y_min = 0;
      parameter Real y_max = 1;

    equation
      y = S_Func(x_min,x_max,y_min,y_max,u);

      annotation (Icon(graphics={
        Line(points={{-70,-78},{-70,78}}, color={192,192,192}),
        Polygon(
          points={{-70,100},{-78,78},{-62,78},{-70,100}},
          lineColor={192,192,192},
          fillColor={192,192,192},
          fillPattern=FillPattern.Solid),
        Polygon(
          points={{100,-70},{78,-62},{78,-78},{100,-70}},
          lineColor={192,192,192},
          fillColor={192,192,192},
          fillPattern=FillPattern.Solid),
        Line(points={{-80,-70},{78,-70}}, color={192,192,192}),
        Text(
          extent={{2,6},{74,-42}},
          lineColor={192,192,192},
              textString="S"),
        Line(points={{-70,-70},{-62,-70},{-50,-66},{-40,-58},{-30,-40},{-18,-12},
                  {-2,22},{10,40},{22,52},{32,60},{42,64},{56,68},{70,68}},
                                                          color={0,0,0})}));
    end S_FuncBlock;
  end Utilities;

  package VehicleComponents
    package Wheels
      model IdealWheelJoint

        Interfaces.Frame_a frame_a annotation (Placement(transformation(extent={{-48,0},
                  {-28,20}}), iconTransformation(extent={{-68,-20},{-28,20}})));
        Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_a annotation (
            Placement(transformation(extent={{90,-8},{110,12}}), iconTransformation(
                extent={{90,-10},{110,10}})));

        parameter SI.Length radius "radius of the wheel";

        parameter SI.Length r[2]
          "driving direction of the wheel at angle phi = 0";

        final parameter SI.Length l = sqrt(r*r);
        final parameter Real e[2] =  r/l "normalized direction";

        Real e0[2] "normalized direction w.r.t inertial system";
        Real R[2,2] "Rotation Matrix";

        SI.AngularVelocity w_roll "roll velocity of wheel";
        SI.Velocity v[2] "velocity";

        SI.Velocity v_long
          "driving velocity in (longitudinal) driving direction";
        SI.Acceleration a "acceleration of driving velocity";
        SI.Force f_long "longitudinal force";

        parameter Boolean animate = true "enable Animation"
                                                           annotation(Dialog(group="Animation"));
        parameter Boolean SimVis = false "perform animation with SimVis" annotation(Dialog(group="Animation"));

        MB.Visualizers.Advanced.Shape cylinder(
          shapeType="cylinder",
          color={63,63,63},
          specularCoefficient=0.5,
          length=0.06,
          width=radius*2,
          height=radius*2,
          lengthDirection={-e0[2],e0[1],0},
          widthDirection={0,0,1},
          r_shape=-0.03*{-e0[2],e0[1],0},
          r={frame_a.x,frame_a.y,0},
          R=MB.Frames.nullRotation()) if animate;

        MB.Visualizers.Advanced.Shape rim1(
          shapeType="cylinder",
          color={195,195,195},
          specularCoefficient=0.5,
          length=radius*2,
          width=0.1,
          height=0.1,
          lengthDirection={0,0,1},
          widthDirection={1,0,0},
          r_shape={0,0,-radius},
          r={frame_a.x,frame_a.y,0},
          R=MB.Frames.planarRotation({-e0[2],e0[1],0},flange_a.phi,0)) if animate;

        MB.Visualizers.Advanced.Shape rim2(
          shapeType="cylinder",
          color={195,195,195},
          specularCoefficient=0.5,
          length=radius*2,
          width=0.1,
          height=0.1,
          lengthDirection={0,0,1},
          widthDirection={1,0,0},
          r_shape={0,0,-radius},
          r={frame_a.x,frame_a.y,0},
          R=MB.Frames.planarRotation({-e0[2],e0[1],0},flange_a.phi+Modelica.Constants.pi/2,0)) if animate;

      equation
        R = {{cos(frame_a.phi), sin(frame_a.phi)}, {-sin(frame_a.phi),cos(frame_a.phi)}};
        e0 = R*e;

        v = der({frame_a.x,frame_a.y});
        v = v_long*e0;

        w_roll = der(flange_a.phi);
        v_long = radius*w_roll;
        a = der(v_long);

        -f_long*radius = flange_a.tau;

        frame_a.t = 0;
        {frame_a.fx, frame_a.fy}*e0 = f_long;

        annotation (Icon(graphics={
              Rectangle(
                extent={{-40,100},{40,-100}},
                lineColor={95,95,95},
                fillPattern=FillPattern.HorizontalCylinder,
                fillColor={231,231,231}),
              Line(
                points={{-40,30},{40,30}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,-30},{40,-30}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,60},{40,60}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,80},{40,80}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,90},{40,90}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,100},{40,100}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,-80},{40,-80}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,-90},{40,-90}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,-100},{40,-100}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,-60},{40,-60}},
                color={95,95,95},
                smooth=Smooth.None),
              Rectangle(
                extent={{100,10},{40,-10}},
                lineColor={0,0,0},
                fillPattern=FillPattern.HorizontalCylinder,
                fillColor={231,231,231}),
              Text(
                extent={{-100,-100},{100,-140}},
                lineColor={0,0,0},
                fillPattern=FillPattern.Sphere,
                fillColor={85,170,255},
                textString="%name")}),      Diagram(graphics));
      end IdealWheelJoint;

      model DryFrictionWheelJoint

        Interfaces.Frame_a frame_a annotation (Placement(transformation(extent={{-48,0},
                  {-28,20}}), iconTransformation(extent={{-68,-20},{-28,20}})));
        Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_a annotation (
            Placement(transformation(extent={{90,-8},{110,12}}), iconTransformation(
                extent={{90,-10},{110,10}})));

        parameter SI.Length radius "radius of the wheel";

        parameter SI.Length r[2]
          "driving direction of the wheel at angle phi = 0";

        parameter SI.Force N "normal force";
        parameter SI.Velocity vAdhesion "adhesion velocity";
        parameter SI.Velocity vSlide "sliding velocity";
        parameter Real mu_A "friction coefficient at adhesion";
        parameter Real mu_S "friction coefficient at sliding";

        final parameter SI.Length l = sqrt(r*r);
        final parameter Real e[2] =  r/l "normalized direction";

        Real e0[2] "normalized direction w.r.t inertial system";
        Real R[2,2] "Rotation Matrix";

        SI.AngularVelocity w_roll "roll velocity of wheel";
        SI.Velocity v[2] "velocity";

        SI.Velocity v_lat "driving in lateral direction";
        SI.Velocity v_long "velocity in longitudinal direction";

        SI.Velocity v_slip_long "slip velocity in longitudinal direction";
        SI.Velocity v_slip_lat "slip velocity in lateral direction";
        SI.Velocity v_slip "slip velocity";

        SI.Force f "longitudinal force";
        SI.Force f_lat "longitudinal force";
        SI.Force f_long "longitudinal force";

        parameter Boolean animate = true "enable Animation"
                                                           annotation(Dialog(group="Animation"));
        parameter Boolean SimVis = false "perform animation with SimVis" annotation(Dialog(group="Animation"));

        MB.Visualizers.Advanced.Shape cylinder(
          shapeType="cylinder",
          color={63,63,63},
          specularCoefficient=0.5,
          length=0.06,
          width=radius*2,
          height=radius*2,
          lengthDirection={-e0[2],e0[1],0},
          widthDirection={0,0,1},
          r_shape=-0.03*{-e0[2],e0[1],0},
          r={frame_a.x,frame_a.y,0},
          R=MB.Frames.nullRotation()) if animate;

        MB.Visualizers.Advanced.Shape rim1(
          shapeType="cylinder",
          color={195,195,195},
          specularCoefficient=0.5,
          length=radius*2,
          width=0.1,
          height=0.1,
          lengthDirection={0,0,1},
          widthDirection={1,0,0},
          r_shape={0,0,-radius},
          r={frame_a.x,frame_a.y,0},
          R=MB.Frames.planarRotation({-e0[2],e0[1],0},flange_a.phi,0)) if animate;

        MB.Visualizers.Advanced.Shape rim2(
          shapeType="cylinder",
          color={195,195,195},
          specularCoefficient=0.5,
          length=radius*2,
          width=0.1,
          height=0.1,
          lengthDirection={0,0,1},
          widthDirection={1,0,0},
          r_shape={0,0,-radius},
          r={frame_a.x,frame_a.y,0},
          R=MB.Frames.planarRotation({-e0[2],e0[1],0},flange_a.phi+Modelica.Constants.pi/2,0)) if animate;

      equation
        R = {{cos(frame_a.phi), sin(frame_a.phi)}, {-sin(frame_a.phi),cos(frame_a.phi)}};
        e0 = R*e;
        v = der({frame_a.x,frame_a.y});
        w_roll = der(flange_a.phi);

        v_long = v*e0;
        v_lat = -v[1]*e0[2] + v[2]*e0[1];

        v_slip_lat = v_lat - 0;
        v_slip_long = v_long - radius*w_roll;
        v_slip = sqrt(v_slip_long^2 + v_slip_lat^2)+0.0001;

        -f_long*radius = flange_a.tau;
        frame_a.t = 0;

        f = N*noEvent(Utilities.TripleS_Func(vAdhesion,vSlide,mu_A,mu_S,v_slip));

        f_long =f*v_slip_long/v_slip;
        f_lat  =f*v_slip_lat/v_slip;
        f_long = {frame_a.fx, frame_a.fy}*e0;
        f_lat = {frame_a.fy, -frame_a.fx}*e0;

        annotation (Icon(graphics={
              Rectangle(
                extent={{-40,100},{40,-100}},
                lineColor={95,95,95},
                fillPattern=FillPattern.HorizontalCylinder,
                fillColor={231,231,231}),
              Line(
                points={{-40,30},{40,30}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,-30},{40,-30}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,60},{40,60}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,80},{40,80}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,90},{40,90}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,100},{40,100}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,-80},{40,-80}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,-90},{40,-90}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,-100},{40,-100}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,-60},{40,-60}},
                color={95,95,95},
                smooth=Smooth.None),
              Rectangle(
                extent={{100,10},{40,-10}},
                lineColor={0,0,0},
                fillPattern=FillPattern.HorizontalCylinder,
                fillColor={231,231,231}),
              Text(
                extent={{-100,-100},{100,-140}},
                lineColor={0,0,0},
                fillPattern=FillPattern.Sphere,
                fillColor={85,170,255},
                textString="%name")}),      Diagram(graphics));
      end DryFrictionWheelJoint;

      model SlipBasedWheelJoint

        Interfaces.Frame_a frame_a annotation (Placement(transformation(extent={{-48,0},
                  {-28,20}}), iconTransformation(extent={{-68,-20},{-28,20}})));
        Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_a annotation (
            Placement(transformation(extent={{90,-8},{110,12}}), iconTransformation(
                extent={{90,-10},{110,10}})));

        Modelica.Blocks.Interfaces.RealInput dynamicLoad(unit="N") annotation (Placement(transformation(
              extent={{-20,-20},{20,20}},
              rotation=270,
              origin={0,100}), iconTransformation(
              extent={{-20,-20},{20,20}},
              rotation=270,
              origin={0,100})));

        parameter SI.Length radius "radius of the wheel";

        parameter SI.Length r[2]
          "driving direction of the wheel at angle phi = 0";

        parameter SI.Force N "base normal load";
        parameter SI.Velocity vAdhesion_min "minimum adhesion velocity";
        parameter SI.Velocity vSlide_min "minimum sliding velocity";

        parameter Real sAdhesion "adhesion slippage";
        parameter Real sSlide "sliding slippage";

        parameter Real mu_A "friction coefficient at adhesion";
        parameter Real mu_S "friction coefficient at sliding";

        final parameter SI.Length l = sqrt(r*r);
        final parameter Real e[2] =  r/l "normalized direction";

        Real e0[2] "normalized direction w.r.t inertial system";
        Real R[2,2] "Rotation Matrix";

        SI.AngularVelocity w_roll "roll velocity of wheel";
        SI.Velocity v[2] "velocity";

        SI.Velocity v_lat "driving in lateral direction";
        SI.Velocity v_long "velocity in longitudinal direction";

        SI.Velocity v_slip_long "slip velocity in longitudinal direction";
        SI.Velocity v_slip_lat "slip velocity in lateral direction";
        SI.Velocity v_slip "slip velocity";

        SI.Force f "longitudinal force";
        SI.Force f_lat "longitudinal force";
        SI.Force f_long "longitudinal force";
        SI.Force fN "base normal load";

        SI.Velocity vAdhesion "adhesion velocity";
        SI.Velocity vSlide "sliding velocity";

        parameter Boolean animate = true "enable Animation"
                                                           annotation(Dialog(group="Animation"));

        MB.Visualizers.Advanced.Shape cylinder(
          shapeType="cylinder",
          color={63,63,63},
          specularCoefficient=0.5,
          length=0.06,
          width=radius*2,
          height=radius*2,
          lengthDirection={-e0[2],e0[1],0},
          widthDirection={0,0,1},
          r_shape=-0.03*{-e0[2],e0[1],0},
          r={frame_a.x,frame_a.y,0},
          R=MB.Frames.nullRotation()) if animate;

        MB.Visualizers.Advanced.Shape rim1(
          shapeType="cylinder",
          color={195,195,195},
          specularCoefficient=0.5,
          length=radius*2,
          width=0.1,
          height=0.1,
          lengthDirection={0,0,1},
          widthDirection={1,0,0},
          r_shape={0,0,-radius},
          r={frame_a.x,frame_a.y,0},
          R=MB.Frames.planarRotation({-e0[2],e0[1],0},flange_a.phi,0)) if animate;

        MB.Visualizers.Advanced.Shape rim2(
          shapeType="cylinder",
          color={195,195,195},
          specularCoefficient=0.5,
          length=radius*2,
          width=0.1,
          height=0.1,
          lengthDirection={0,0,1},
          widthDirection={1,0,0},
          r_shape={0,0,-radius},
          r={frame_a.x,frame_a.y,0},
          R=MB.Frames.planarRotation({-e0[2],e0[1],0},flange_a.phi+Modelica.Constants.pi/2,0)) if animate;

      equation
        R = {{cos(frame_a.phi), sin(frame_a.phi)}, {-sin(frame_a.phi),cos(frame_a.phi)}};
        e0 = R*e;
        v = der({frame_a.x,frame_a.y});
        w_roll = der(flange_a.phi);

        v_long = v*e0;
        v_lat = -v[1]*e0[2] + v[2]*e0[1];

        v_slip_lat = v_lat - 0;
        v_slip_long = v_long - radius*w_roll;
        v_slip = sqrt(v_slip_long^2 + v_slip_lat^2)+0.0001;

        -f_long*radius = flange_a.tau;
        frame_a.t = 0;

        vAdhesion = noEvent(max(sAdhesion*abs(radius*w_roll),vAdhesion_min));
        vSlide = noEvent(max(sSlide*abs(radius*w_roll),vSlide_min));
        fN = max(0, N+dynamicLoad);

        f = fN*noEvent(Utilities.TripleS_Func(vAdhesion,vSlide,mu_A,mu_S,v_slip));

        f_long =f*v_slip_long/v_slip;
        f_lat  =f*v_slip_lat/v_slip;
        f_long = {frame_a.fx, frame_a.fy}*e0;
        f_lat = {frame_a.fy, -frame_a.fx}*e0;

        annotation (Icon(graphics={
              Rectangle(
                extent={{-40,100},{40,-100}},
                lineColor={95,95,95},
                fillPattern=FillPattern.HorizontalCylinder,
                fillColor={231,231,231}),
              Line(
                points={{-40,30},{40,30}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,-30},{40,-30}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,60},{40,60}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,80},{40,80}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,90},{40,90}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,100},{40,100}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,-80},{40,-80}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,-90},{40,-90}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,-100},{40,-100}},
                color={95,95,95},
                smooth=Smooth.None),
              Line(
                points={{-40,-60},{40,-60}},
                color={95,95,95},
                smooth=Smooth.None),
              Rectangle(
                extent={{100,10},{40,-10}},
                lineColor={0,0,0},
                fillPattern=FillPattern.HorizontalCylinder,
                fillColor={231,231,231}),
              Text(
                extent={{-100,-100},{100,-140}},
                lineColor={0,0,0},
                fillPattern=FillPattern.Sphere,
                fillColor={85,170,255},
                textString="%name")}),      Diagram(graphics));
      end SlipBasedWheelJoint;
    end Wheels;

    model SimpleRearAxis

      parameter SI.Length axisLength = 1.7
        "length of the axis (width of the car)";
      parameter SI.Inertia I =  2 "Inertia of the wheel";

      parameter SI.Length R =  0.25 "radius of the wheel" annotation(Dialog(group="Wheel and Tire Characteristics"));

      final parameter SI.Length r[2] = {0,1} "driving direction of the wheel" annotation(Dialog(group="Wheel and Tire Characteristics"));

      parameter SI.Force N = 1500 "normal force" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter SI.Velocity vAdhesion = 0.1 "adhesion velocity" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter SI.Velocity vSlide = 0.3 "sliding velocity" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter Real mu_A = 0.8 "friction coefficient at adhesion" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter Real mu_S = 0.4 "friction coefficient at sliding" annotation(Dialog(group="Wheel and Tire Characteristics"));

      Wheels.DryFrictionWheelJoint WheelJointLeft(
        radius=R,
        r=r,
        N=N,
        vAdhesion=vAdhesion,
        vSlide=vSlide,
        mu_A=mu_A,
        mu_S=mu_S)
               annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-60,0})));
      Modelica.Mechanics.Rotational.Components.Inertia inertia1(
        phi(fixed=true, start=0),
        w(fixed=true, start=0),
        J=I)                    annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=0,
            origin={-92,0})));
      Parts.FixedTranslation fixedTranslation2( r={axisLength/2,0})
                                                             annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={-20,0})));
      Wheels.DryFrictionWheelJoint WheelJointRight(
        radius=R,
        r=r,
        N=N,
        vAdhesion=vAdhesion,
        vSlide=vSlide,
        mu_A=mu_A,
        mu_S=mu_S)
               annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=0,
            origin={62,0})));
      Modelica.Mechanics.Rotational.Components.Inertia inertia2(
        phi(fixed=false, start=0),
        w(fixed=false, start=0),
        J=I)                    annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={90,0})));
      Parts.FixedTranslation fixedTranslation1(r={axisLength/2,0})
                                                             annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={20,0})));
      Modelica.Mechanics.Rotational.Interfaces.Flange_b flange_b
        annotation (Placement(transformation(extent={{-10,-110},{10,-90}})));
      Interfaces.Frame_a frame_a annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,20}), iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=90,
            origin={0,30})));
      DifferentialGear differentialGear
        annotation (Placement(transformation(extent={{-10,-70},{10,-50}})));
    equation
      connect(WheelJointLeft.flange_a, inertia1.flange_b)
                                                       annotation (Line(
          points={{-70,1.22465e-015},{-76,1.22465e-015},{-76,0},{-82,0}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(fixedTranslation2.frame_a, WheelJointLeft.frame_a)
                                                              annotation (Line(
          points={{-30,0},{-42,0},{-42,-5.8783e-016},{-55.2,-5.8783e-016}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(inertia2.flange_b, WheelJointRight.flange_a)
                                                       annotation (Line(
          points={{80,1.22465e-015},{76,1.22465e-015},{76,0},{72,0}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(fixedTranslation1.frame_b, WheelJointRight.frame_a)
                                                              annotation (Line(
          points={{30,0},{57.2,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation2.frame_b, frame_a) annotation (Line(
          points={{-10,0},{0,0},{0,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation1.frame_a, frame_a) annotation (Line(
          points={{10,0},{0,0},{0,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(flange_b, differentialGear.flange_b) annotation (Line(
          points={{0,-100},{0,-70}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(differentialGear.flange_right, WheelJointRight.flange_a)
        annotation (Line(
          points={{10,-60},{76,-60},{76,0},{72,0}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(differentialGear.flange_left, WheelJointLeft.flange_a)
        annotation (Line(
          points={{-10,-60},{-74,-60},{-74,1.22465e-015},{-70,1.22465e-015}},
          color={0,0,0},
          smooth=Smooth.None));
      annotation (Diagram(coordinateSystem(preserveAspectRatio=true, extent={{-200,
                -100},{200,100}}),
                          graphics), Icon(coordinateSystem(preserveAspectRatio=
                true, extent={{-200,-100},{200,100}}),
                                          graphics={
            Rectangle(
              extent={{-200,60},{-160,-60}},
              lineColor={95,95,95},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231}),
            Line(
              points={{-200,20},{-160,20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-20},{-160,-20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,40},{-160,40}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,60},{-160,60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,50},{-160,50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,56},{-160,56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-50},{-160,-50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-60},{-160,-60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-56},{-160,-56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-40},{-160,-40}},
              color={95,95,95},
              smooth=Smooth.None),
            Rectangle(
              extent={{160,60},{200,-60}},
              lineColor={95,95,95},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231}),
            Line(
              points={{160,20},{200,20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-20},{200,-20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,40},{200,40}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,60},{200,60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,50},{200,50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,56},{200,56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-50},{200,-50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-60},{200,-60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-56},{200,-56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-40},{200,-40}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{0,-10},{0,-80}},
              color={0,0,0},
              smooth=Smooth.None),
            Rectangle(
              extent={{160,8},{20,-10}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231}),
            Rectangle(
              extent={{20,20},{-20,-20}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231}),
            Rectangle(
              extent={{8,14},{-20,-14}},
              fillPattern=FillPattern.Solid,
              fillColor={255,255,255},
              pattern=LinePattern.None),
            Rectangle(
              extent={{0,10},{-160,-10}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231})}));
    end SimpleRearAxis;

    model SimpleFrontAxis

      parameter SI.Length axisLength = 1.6
        "length of the axis (width of the car)";
      parameter SI.Length trail = 0.05;

      parameter SI.Inertia I =  2 "Inertia of the wheel";
      parameter SI.Inertia I_susp =  5
        "Rotational Inertia of the steering suspension";

      parameter SI.Length R =  0.25 "radius of the wheel" annotation(Dialog(group="Wheel and Tire Characteristics"));

      final parameter SI.Length r[2] = {0,1} "driving direction of the wheel" annotation(Dialog(group="Wheel and Tire Characteristics"));

      parameter SI.Force N = 1500 "normal force" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter SI.Velocity vAdhesion = 0.1 "adhesion velocity" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter SI.Velocity vSlide = 0.3 "sliding velocity" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter Real mu_A = 0.8 "friction coefficient at adhesion" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter Real mu_S = 0.4 "friction coefficient at sliding" annotation(Dialog(group="Wheel and Tire Characteristics"));

      Wheels.DryFrictionWheelJoint WheelJointLeft(
        radius=R,
    r = r,
        N=N,
        vAdhesion=vAdhesion,
        vSlide=vSlide,
        mu_A=mu_A,
        mu_S=mu_S)
               annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-60,60})));
      Modelica.Mechanics.Rotational.Components.Inertia leftInertia(
        phi(fixed=true, start=0),
        w(fixed=true, start=0),
        J=I)                    annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=0,
            origin={-90,60})));
      Parts.FixedTranslation leftAxis(r={axisLength/2,0}) annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={-20,0})));
      Wheels.DryFrictionWheelJoint WheelJointRight(
        radius=R,
        r=r,
        N=N,
        vAdhesion=vAdhesion,
        vSlide=vSlide,
        mu_A=mu_A,
        mu_S=mu_S)
               annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=0,
            origin={62,60})));
      Modelica.Mechanics.Rotational.Components.Inertia rightInertia(
        J=I,
        phi(fixed=true, start=0),
        w(fixed=true, start=0)) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={90,60})));
      Parts.FixedTranslation rightAxis(r={axisLength/2,0})   annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={20,0})));
      Modelica.Mechanics.Rotational.Interfaces.Flange_b flange_b
        annotation (Placement(transformation(extent={{-10,90},{10,110}})));
      Interfaces.Frame_a frame_a annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,-42}), iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=90,
            origin={0,-30})));
      Joints.ActuatedRevolute leftSteeringRevolute(initialize=false)
                                    annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-40,20})));
      Joints.ActuatedRevolute rightSteeringRevolute
                                                annotation (Placement(
            transformation(
            extent={{-10,10},{10,-10}},
            rotation=270,
            origin={40,20})));
      Modelica.Mechanics.Rotational.Components.Inertia SteeringInertia(
        phi(fixed=true, start=0),
        w(fixed=true, start=0),
        J=I_susp)               annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=270,
            origin={0,50})));
      Parts.FixedTranslation leftTrail(r={0, -trail})      annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-40,46})));
      Parts.FixedTranslation rigthtTrail(r={0, -trail})    annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={40,46})));
    equation
      connect(WheelJointLeft.flange_a, leftInertia.flange_b)
                                                       annotation (Line(
          points={{-70,60},{-80,60}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(rightInertia.flange_b, WheelJointRight.flange_a)
                                                       annotation (Line(
          points={{80,60},{72,60}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(leftAxis.frame_b, frame_a)          annotation (Line(
          points={{-10,0},{0,0},{0,-42}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(rightAxis.frame_a, frame_a)         annotation (Line(
          points={{10,0},{0,0},{0,-42}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(leftSteeringRevolute.flange_a, rightSteeringRevolute.flange_a)
                                                                     annotation (
          Line(
          points={{-30,20},{30,20}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(leftAxis.frame_a, leftSteeringRevolute.frame_b)      annotation (Line(
          points={{-30,0},{-40,0},{-40,10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(rightAxis.frame_b, rightSteeringRevolute.frame_b)     annotation (
          Line(
          points={{30,0},{40,0},{40,10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(SteeringInertia.flange_b, leftSteeringRevolute.flange_a)
                                                            annotation (Line(
          points={{-1.83697e-015,40},{0,40},{0,20},{-30,20}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(SteeringInertia.flange_a, flange_b)
                                           annotation (Line(
          points={{1.83697e-015,60},{0,60},{0,100}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(leftTrail.frame_a, leftSteeringRevolute.frame_a)
                                                           annotation (Line(
          points={{-40,36},{-40,30}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(leftTrail.frame_b, WheelJointLeft.frame_a) annotation (Line(
          points={{-40,56},{-40,60},{-55.2,60}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(rigthtTrail.frame_a, rightSteeringRevolute.frame_a)
                                                              annotation (Line(
          points={{40,36},{40,30}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(rigthtTrail.frame_b, WheelJointRight.frame_a) annotation (Line(
          points={{40,56},{40,60},{57.2,60}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(coordinateSystem(preserveAspectRatio=true, extent={{
                -200,-100},{200,100}}),
                          graphics), Icon(coordinateSystem(preserveAspectRatio=
                true, extent={{-200,-100},{200,100}}),
                                          graphics={
            Rectangle(
              extent={{-200,60},{-160,-60}},
              lineColor={95,95,95},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231}),
            Line(
              points={{-200,20},{-160,20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-20},{-160,-20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,40},{-160,40}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,60},{-160,60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,50},{-160,50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,56},{-160,56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-50},{-160,-50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-60},{-160,-60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-56},{-160,-56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-40},{-160,-40}},
              color={95,95,95},
              smooth=Smooth.None),
            Rectangle(
              extent={{140,10},{-140,-10}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231}),
            Rectangle(
              extent={{160,60},{200,-60}},
              lineColor={95,95,95},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231}),
            Line(
              points={{160,20},{200,20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-20},{200,-20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,40},{200,40}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,60},{200,60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,50},{200,50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,56},{200,56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-50},{200,-50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-60},{200,-60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-56},{200,-56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-40},{200,-40}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{0,80},{0,40}},
              color={0,0,0},
              smooth=Smooth.None),
            Ellipse(
              extent={{-160,10},{-140,-10}},
              lineColor={0,0,0},
              fillPattern=FillPattern.Solid,
              fillColor={95,95,95}),
            Ellipse(
              extent={{140,10},{160,-10}},
              lineColor={0,0,0},
              fillColor={95,95,95},
              fillPattern=FillPattern.Solid),
            Line(
              points={{-150,10},{-120,40},{120,40},{150,10}},
              pattern=LinePattern.None,
              thickness=0.5,
              smooth=Smooth.None)}));
    end SimpleFrontAxis;

    model DynamicRearAxis

      parameter SI.Length axisLength = 1.7
        "length of the axis (width of the car)";
      parameter SI.Inertia I =  2 "Inertia of the wheel";

      parameter SI.Length R =  0.25 "radius of the wheel" annotation(Dialog(group="Wheel and Tire Characteristics"));

      final parameter SI.Length r[2] = {0,1} "driving direction of the wheel" annotation(Dialog(group="Wheel and Tire Characteristics"));

      parameter SI.Force N = 1500 "normal force" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter SI.Velocity vAdhesion_min = 0.1 "adhesion velocity" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter SI.Velocity vSlide_min = 0.3 "sliding velocity" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter Real sAdhesion = 0.05 "adhesion velocity" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter Real sSlide = 0.15 "sliding velocity" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter Real mu_A = 0.8 "friction coefficient at adhesion" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter Real mu_S = 0.4 "friction coefficient at sliding" annotation(Dialog(group="Wheel and Tire Characteristics"));

      parameter Boolean animate = true "enable Animation"
                                                         annotation(Dialog(group="Animation"));
      parameter Boolean SimVis = false "perform animation with SimVis" annotation(Dialog(group="Animation"));

      Wheels.SlipBasedWheelJoint WheelJointLeft(
        radius=R,
        r=r,
        N=N,
        vAdhesion_min=vAdhesion_min,
        vSlide_min=vSlide_min,
        mu_A=mu_A,
        mu_S=mu_S,
        sAdhesion=sAdhesion,
        sSlide=sSlide,
        animate=animate)
               annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=180,
            origin={-60,0})));
      Modelica.Mechanics.Rotational.Components.Inertia inertia1(
        phi(fixed=true, start=0),
        w(fixed=true, start=0),
        J=I)                    annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=0,
            origin={-92,0})));
      Parts.FixedTranslation fixedTranslation2(r={axisLength/2,0},
        animate=animate)                                     annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={-20,0})));
      Wheels.SlipBasedWheelJoint WheelJointRight(
        radius=R,
        r=r,
        N=N,
        vAdhesion_min=vAdhesion_min,
        vSlide_min=vSlide_min,
        mu_A=mu_A,
        mu_S=mu_S,
        sAdhesion=sAdhesion,
        sSlide=sSlide,
        animate=animate)
               annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={62,0})));
      Modelica.Mechanics.Rotational.Components.Inertia inertia2(
        phi(fixed=false, start=0),
        w(fixed=false, start=0),
        J=I)                    annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={90,0})));
      Parts.FixedTranslation fixedTranslation1(r={axisLength/2,0},
        animate=animate)                                     annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={20,0})));
      Modelica.Mechanics.Rotational.Interfaces.Flange_b flange_b
        annotation (Placement(transformation(extent={{-10,-110},{10,-90}})));
      Interfaces.Frame_a frame_a annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,20}), iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=90,
            origin={0,30})));
      Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_right
        annotation (Placement(transformation(extent={{190,-10},{210,10}})));
      Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_left
        annotation (Placement(transformation(extent={{-210,-10},{-190,10}})));
      Modelica.Blocks.Interfaces.RealInput dynamicLoadLeft annotation (Placement(
            transformation(
            extent={{-20,-20},{20,20}},
            rotation=270,
            origin={-170,110}), iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=270,
            origin={-160,100})));
      Modelica.Blocks.Interfaces.RealInput dynamicLoadRight annotation (Placement(
            transformation(
            extent={{-20,-20},{20,20}},
            rotation=270,
            origin={160,100})));

      Visualization.Shapes.FileShape leftTire(
        each shininess=0.8,
        transparency=0,
        lengthDirection={0,1,0},
        widthDirection={-1,0,0},
        each smoothNormals=true,
        each reflectsLight=false,
        filename=Visualization.Utilities.RootDir +
            "/Extras/3DData/Car/Tire.3ds")
                             annotation (Placement(transformation(extent={{-10,-10},
                {10,10}},
                       rotation=90,
            origin={-42,92})));
      Interfaces.PlanarToMultiBody planarToMultiBody annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-42,20})));
      Visualization.Shapes.FileShape rightTire(
        each shininess=0.8,
        transparency=0,
        lengthDirection={0,1,0},
        widthDirection={-1,0,0},
        each smoothNormals=true,
        each reflectsLight=false,
        filename=Visualization.Utilities.RootDir +
            "/Extras/3DData/Car/Tire.3ds",
        scaleFactor={-1,1,1})
                             annotation (Placement(transformation(extent={{-10,-10},
                {10,10}},
                       rotation=90,
            origin={46,90})));
      Interfaces.PlanarToMultiBody planarToMultiBody1 annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={46,18})));
      MB.Parts.FixedRotation fixedRotation(
        rotationType=Modelica.Mechanics.MultiBody.Types.RotationTypes.RotationAxis,
        n={0,0,1},
        angle=90,
        r={0,0,0.26}) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-42,40})));

      MB.Parts.FixedRotation fixedRotation2(
        rotationType=Modelica.Mechanics.MultiBody.Types.RotationTypes.RotationAxis,
        n={0,0,1},
        angle=90,
        r={0,0,0.26}) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={46,40})));

      MB.Joints.Revolute revolute(useAxisFlange=true, n={0,1,0}) annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-42,66})));
      MB.Joints.Revolute revolute1(useAxisFlange=true, n={0,1,0}) annotation (
          Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=90,
            origin={46,66})));
      DifferentialGear differentialGear
        annotation (Placement(transformation(extent={{-10,-70},{10,-50}})));
    equation
      connect(WheelJointLeft.flange_a, inertia1.flange_b)
                                                       annotation (Line(
          points={{-70,1.22465e-015},{-76,1.22465e-015},{-76,0},{-82,0}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(fixedTranslation2.frame_a, WheelJointLeft.frame_a)
                                                              annotation (Line(
          points={{-30,0},{-42,0},{-42,-5.8783e-016},{-55.2,-5.8783e-016}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(inertia2.flange_b, WheelJointRight.flange_a)
                                                       annotation (Line(
          points={{80,1.22465e-015},{76,1.22465e-015},{76,0},{72,0}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(fixedTranslation1.frame_b, WheelJointRight.frame_a)
                                                              annotation (Line(
          points={{30,0},{57.2,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation2.frame_b, frame_a) annotation (Line(
          points={{-10,0},{0,0},{0,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslation1.frame_a, frame_a) annotation (Line(
          points={{10,0},{0,0},{0,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(dynamicLoadLeft, WheelJointLeft.dynamicLoad) annotation (Line(
          points={{-170,110},{-170,20},{-60,20},{-60,10}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(dynamicLoadRight, WheelJointRight.dynamicLoad) annotation (Line(
          points={{160,100},{160,20},{62,20},{62,10}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(inertia1.flange_a, flange_left) annotation (Line(
          points={{-102,0},{-200,0}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(inertia2.flange_a, flange_right) annotation (Line(
          points={{100,-1.22465e-015},{150,-1.22465e-015},{150,0},{200,0}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(planarToMultiBody.frame_a, WheelJointLeft.frame_a) annotation (
          Line(
          points={{-42,17.2},{-42,-5.8783e-016},{-55.2,-5.8783e-016}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(planarToMultiBody1.frame_a, WheelJointRight.frame_a) annotation (
          Line(
          points={{46,15.2},{46,0},{57.2,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedRotation2.frame_a, planarToMultiBody1.frame_b) annotation (
          Line(
          points={{46,30},{46,20.4}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute.axis, inertia1.flange_a) annotation (Line(
          points={{-52,66},{-118,66},{-118,0},{-102,0}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(fixedRotation.frame_a, planarToMultiBody.frame_b) annotation (
          Line(
          points={{-42,30},{-42,22.4}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute.frame_a, fixedRotation.frame_b) annotation (Line(
          points={{-42,56},{-42,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute.frame_b, leftTire.frame_a) annotation (Line(
          points={{-42,76},{-42,82}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute1.frame_a, fixedRotation2.frame_b) annotation (Line(
          points={{46,56},{46,50}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute1.frame_b, rightTire.frame_a) annotation (Line(
          points={{46,76},{46,80}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute1.axis, inertia2.flange_a) annotation (Line(
          points={{56,66},{112,66},{112,-1.22465e-015},{100,-1.22465e-015}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(differentialGear.flange_b, flange_b) annotation (Line(
          points={{0,-70},{0,-100}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(differentialGear.flange_right, WheelJointRight.flange_a)
        annotation (Line(
          points={{10,-60},{76,-60},{76,0},{72,0}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(differentialGear.flange_left, WheelJointLeft.flange_a)
        annotation (Line(
          points={{-10,-60},{-74,-60},{-74,1.22465e-015},{-70,1.22465e-015}},
          color={0,0,0},
          smooth=Smooth.None));
      annotation (Diagram(coordinateSystem(preserveAspectRatio=true, extent={{-200,
                -100},{200,100}}),
                          graphics), Icon(coordinateSystem(preserveAspectRatio=true,
                      extent={{-200,-100},{200,100}}),
                                          graphics={
            Rectangle(
              extent={{-200,60},{-160,-60}},
              lineColor={95,95,95},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231}),
            Line(
              points={{-200,20},{-160,20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-20},{-160,-20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,40},{-160,40}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,60},{-160,60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,50},{-160,50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,56},{-160,56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-50},{-160,-50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-60},{-160,-60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-56},{-160,-56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-40},{-160,-40}},
              color={95,95,95},
              smooth=Smooth.None),
            Rectangle(
              extent={{160,60},{200,-60}},
              lineColor={95,95,95},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231}),
            Line(
              points={{160,20},{200,20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-20},{200,-20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,40},{200,40}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,60},{200,60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,50},{200,50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,56},{200,56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-50},{200,-50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-60},{200,-60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-56},{200,-56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-40},{200,-40}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{0,-10},{0,-80}},
              color={0,0,0},
              smooth=Smooth.None),
            Rectangle(
              extent={{160,8},{20,-10}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231}),
            Rectangle(
              extent={{20,20},{-20,-20}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231}),
            Rectangle(
              extent={{8,14},{-20,-14}},
              fillPattern=FillPattern.Solid,
              fillColor={255,255,255},
              pattern=LinePattern.None),
            Rectangle(
              extent={{0,10},{-160,-10}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231})}));
    end DynamicRearAxis;

    model DynamicFrontAxis

      parameter SI.Length axisLength = 1.6
        "length of the axis (width of the car)";
      parameter SI.Length trail = 0.03;

      parameter SI.Inertia I =  2 "Inertia of the wheel";
      parameter SI.Inertia I_susp =  5
        "Rotational Inertia of the steering suspension";

      parameter SI.Length R =  0.25 "radius of the wheel" annotation(Dialog(group="Wheel and Tire Characteristics"));

      final parameter SI.Length r[2] = {0,1} "driving direction of the wheel" annotation(Dialog(group="Wheel and Tire Characteristics"));

      parameter SI.Force N = 1500 "normal force" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter SI.Velocity vAdhesion_min = 0.1 "adhesion velocity" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter SI.Velocity vSlide_min = 0.3 "sliding velocity" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter Real sAdhesion = 0.05 "adhesion velocity" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter Real sSlide = 0.15 "sliding velocity" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter Real mu_A = 0.8 "friction coefficient at adhesion" annotation(Dialog(group="Wheel and Tire Characteristics"));
      parameter Real mu_S = 0.4 "friction coefficient at sliding" annotation(Dialog(group="Wheel and Tire Characteristics"));

      parameter Boolean animate = true "enable Animation"
                                                         annotation(Dialog(group="Animation"));
      parameter Boolean SimVis = false "perform animation with SimVis" annotation(Dialog(group="Animation"));

      Wheels.SlipBasedWheelJoint WheelJointLeft(
        radius=R,
        r=r,
        N=N,
        vAdhesion_min=vAdhesion_min,
        vSlide_min=vSlide_min,
        mu_A=mu_A,
        mu_S=mu_S,
        sAdhesion=sAdhesion,
        sSlide=sSlide,
        animate=animate)
               annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-90,60})));
      Modelica.Mechanics.Rotational.Components.Inertia leftInertia(
        phi(fixed=true, start=0),
        w(fixed=true, start=0),
        J=I)                    annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=0,
            origin={-120,60})));
      Parts.FixedTranslation leftAxis(r={axisLength/2,0},
        animate=animate)                                     annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={-20,0})));
      Wheels.SlipBasedWheelJoint WheelJointRight(
        radius=R,
        r=r,
        N=N,
        vAdhesion_min=vAdhesion_min,
        vSlide_min=vSlide_min,
        mu_A=mu_A,
        mu_S=mu_S,
        sAdhesion=sAdhesion,
        sSlide=sSlide,
        animate=animate)
               annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=0,
            origin={90,60})));
      Modelica.Mechanics.Rotational.Components.Inertia rightInertia(
        J=I,
        phi(fixed=true, start=0),
        w(fixed=true, start=0)) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={120,60})));
      Parts.FixedTranslation rightAxis(r={axisLength/2,0},
        animate=animate)                                     annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={20,0})));
      Modelica.Mechanics.Rotational.Interfaces.Flange_b flange_b
        annotation (Placement(transformation(extent={{-10,90},{10,110}})));
      Interfaces.Frame_a frame_a annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,-42}), iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=90,
            origin={0,-30})));
      Joints.ActuatedRevolute leftSteeringRevolute(initialize=false, animate=
            animate)                annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-40,20})));
      Joints.ActuatedRevolute rightSteeringRevolute(animate=animate)
                                                annotation (Placement(
            transformation(
            extent={{-10,10},{10,-10}},
            rotation=270,
            origin={40,20})));
      Modelica.Mechanics.Rotational.Components.Inertia SteeringInertia(
        phi(fixed=true, start=0),
        w(fixed=true, start=0),
        J=I_susp)               annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=270,
            origin={0,50})));
      Parts.FixedTranslation leftTrail(r={0, -trail})      annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-40,46})));
      Parts.FixedTranslation rigthtTrail(r={0, -trail})    annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={40,46})));
      Modelica.Blocks.Interfaces.RealInput dynamicLoadLeft annotation (Placement(
            transformation(
            extent={{-20,-20},{20,20}},
            rotation=90,
            origin={-160,-100})));
      Modelica.Blocks.Interfaces.RealInput dynamicLoadRight annotation (Placement(
            transformation(
            extent={{-20,-20},{20,20}},
            rotation=90,
            origin={160,-100})));
      Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_left
        annotation (Placement(transformation(extent={{-210,-10},{-190,10}})));
      Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_right
        annotation (Placement(transformation(extent={{190,-10},{210,10}})));
      Visualization.Shapes.FileShape leftTire(
        each shininess=0.8,
        transparency=0,
        lengthDirection={0,1,0},
        widthDirection={-1,0,0},
        each smoothNormals=true,
        each reflectsLight=false,
        filename=Visualization.Utilities.RootDir +
            "/Extras/3DData/Car/Tire.3ds")
                             annotation (Placement(transformation(extent={{-10,-10},
                {10,10}},
                       rotation=270,
            origin={-70,-30})));
      Interfaces.PlanarToMultiBody planarToMultiBody annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-70,50})));
      MB.Parts.FixedRotation fixedRotation(
        rotationType=Modelica.Mechanics.MultiBody.Types.RotationTypes.RotationAxis,
        n={0,0,1},
        angle=90,
        r={0,0,0.26}) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-70,30})));

      Visualization.Shapes.FileShape rightTire(
        each shininess=0.8,
        transparency=0,
        lengthDirection={0,1,0},
        widthDirection={-1,0,0},
        each smoothNormals=true,
        each reflectsLight=false,
        filename=Visualization.Utilities.RootDir +
            "/Extras/3DData/Car/Tire.3ds",
        scaleFactor={-1,1,1})
                             annotation (Placement(transformation(extent={{-10,-10},
                {10,10}},
                       rotation=270,
            origin={70,-30})));
      Interfaces.PlanarToMultiBody planarToMultiBody1 annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={70,50})));
      MB.Parts.FixedRotation fixedRotation1(
        rotationType=Modelica.Mechanics.MultiBody.Types.RotationTypes.RotationAxis,
        n={0,0,1},
        angle=90,
        r={0,0,0.26}) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={70,30})));

      MB.Joints.Revolute revolute(useAxisFlange=true, n={0,1,0}) annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={70,0})));
      MB.Joints.Revolute revolute1(useAxisFlange=true, n={0,1,0}) annotation (
          Placement(transformation(
            extent={{10,-10},{-10,10}},
            rotation=90,
            origin={-70,0})));
    equation
      connect(WheelJointLeft.flange_a, leftInertia.flange_b)
                                                       annotation (Line(
          points={{-100,60},{-110,60}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(rightInertia.flange_b, WheelJointRight.flange_a)
                                                       annotation (Line(
          points={{110,60},{100,60}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(leftAxis.frame_b, frame_a)          annotation (Line(
          points={{-10,0},{0,0},{0,-42}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(rightAxis.frame_a, frame_a)         annotation (Line(
          points={{10,0},{0,0},{0,-42}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(leftSteeringRevolute.flange_a, rightSteeringRevolute.flange_a)
                                                                     annotation (
          Line(
          points={{-30,20},{-15,20},{-15,20},{0,20},{0,20},{30,20}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(leftAxis.frame_a, leftSteeringRevolute.frame_b)      annotation (Line(
          points={{-30,0},{-40,0},{-40,10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(rightAxis.frame_b, rightSteeringRevolute.frame_b)     annotation (
          Line(
          points={{30,0},{40,0},{40,10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(SteeringInertia.flange_b, leftSteeringRevolute.flange_a)
                                                            annotation (Line(
          points={{-1.83697e-015,40},{0,40},{0,20},{-30,20}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(SteeringInertia.flange_a, flange_b)
                                           annotation (Line(
          points={{1.83697e-015,60},{0,60},{0,100}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(leftTrail.frame_a, leftSteeringRevolute.frame_a)
                                                           annotation (Line(
          points={{-40,36},{-40,30}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(leftTrail.frame_b, WheelJointLeft.frame_a) annotation (Line(
          points={{-40,56},{-40,60},{-85.2,60}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(rigthtTrail.frame_a, rightSteeringRevolute.frame_a)
                                                              annotation (Line(
          points={{40,36},{40,30}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(rigthtTrail.frame_b, WheelJointRight.frame_a) annotation (Line(
          points={{40,56},{40,60},{85.2,60}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(leftInertia.flange_a, flange_left) annotation (Line(
          points={{-130,60},{-150,60},{-150,0},{-200,0}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(rightInertia.flange_a, flange_right) annotation (Line(
          points={{130,60},{150,60},{150,0},{200,0}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(WheelJointRight.dynamicLoad, dynamicLoadRight) annotation (Line(
          points={{90,50},{90,-40},{160,-40},{160,-100}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(dynamicLoadLeft, WheelJointLeft.dynamicLoad) annotation (Line(
          points={{-160,-100},{-160,-40},{-90,-40},{-90,50}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(planarToMultiBody.frame_a, WheelJointLeft.frame_a) annotation (
          Line(
          points={{-70,52.8},{-70,60},{-85.2,60}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedRotation.frame_a, planarToMultiBody.frame_b) annotation (
          Line(
          points={{-70,40},{-70,47.6}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedRotation1.frame_a, planarToMultiBody1.frame_b) annotation (
          Line(
          points={{70,40},{70,47.6}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(planarToMultiBody1.frame_a, WheelJointRight.frame_a) annotation (
          Line(
          points={{70,52.8},{70,60},{85.2,60}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute.frame_a, fixedRotation1.frame_b) annotation (Line(
          points={{70,10},{70,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute.frame_b, rightTire.frame_a) annotation (Line(
          points={{70,-10},{70,-20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute.axis, flange_right) annotation (Line(
          points={{80,-1.83697e-015},{100,-1.83697e-015},{100,0},{200,0}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(revolute1.frame_b, leftTire.frame_a) annotation (Line(
          points={{-70,-10},{-70,-20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute1.frame_a, fixedRotation.frame_b) annotation (Line(
          points={{-70,10},{-70,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(revolute1.axis, flange_left) annotation (Line(
          points={{-80,6.12323e-016},{-140,6.12323e-016},{-140,0},{-200,0}},
          color={0,0,0},
          smooth=Smooth.None));
      annotation (Diagram(coordinateSystem(preserveAspectRatio=true, extent={{-200,
                -100},{200,100}}),
                          graphics), Icon(coordinateSystem(preserveAspectRatio=
                true, extent={{-200,-100},{200,100}}),
                                          graphics={
            Rectangle(
              extent={{-200,60},{-160,-60}},
              lineColor={95,95,95},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231}),
            Line(
              points={{-200,20},{-160,20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-20},{-160,-20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,40},{-160,40}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,60},{-160,60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,50},{-160,50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,56},{-160,56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-50},{-160,-50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-60},{-160,-60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-56},{-160,-56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{-200,-40},{-160,-40}},
              color={95,95,95},
              smooth=Smooth.None),
            Rectangle(
              extent={{140,10},{-140,-10}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231}),
            Rectangle(
              extent={{160,60},{200,-60}},
              lineColor={95,95,95},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={231,231,231}),
            Line(
              points={{160,20},{200,20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-20},{200,-20}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,40},{200,40}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,60},{200,60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,50},{200,50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,56},{200,56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-50},{200,-50}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-60},{200,-60}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-56},{200,-56}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{160,-40},{200,-40}},
              color={95,95,95},
              smooth=Smooth.None),
            Line(
              points={{0,80},{0,40}},
              color={0,0,0},
              smooth=Smooth.None),
            Ellipse(
              extent={{-160,10},{-140,-10}},
              lineColor={0,0,0},
              fillPattern=FillPattern.Solid,
              fillColor={95,95,95}),
            Ellipse(
              extent={{140,10},{160,-10}},
              lineColor={0,0,0},
              fillColor={95,95,95},
              fillPattern=FillPattern.Solid),
            Line(
              points={{-150,10},{-120,40},{120,40},{150,10}},
              pattern=LinePattern.None,
              thickness=0.5,
              smooth=Smooth.None)}));
    end DynamicFrontAxis;

    model SimpleBrake

      Modelica.Blocks.Interfaces.RealInput tau_brake(unit="N.m") annotation (Placement(transformation(
            extent={{-20,-20},{20,20}},
            rotation=270,
            origin={0,110}), iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=270,
            origin={0,110})));
      Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_a annotation (
          Placement(transformation(extent={{-110,-10},{-90,10}}),
            iconTransformation(extent={{-110,-10},{-90,10}})));

      SI.AngularVelocity w;

      parameter SI.AngularVelocity w_reg = 0.1 "Regularization Width";

    equation
      w = der(flange_a.phi);
      flange_a.tau = Utilities.S_Func(-w_reg,w_reg,-tau_brake,tau_brake,w);

      annotation (Icon(graphics={
            Polygon(
              points={{-37,-55},{-37,-90},{37,-90},{37,-55},{33,-55},{33,-86},{-33,-86},
                  {-33,-55},{-37,-55}},
              lineColor={192,192,192},
              fillColor={192,192,192},
              fillPattern=FillPattern.Solid),
            Rectangle(
              extent={{-100,10},{-20,-10}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={192,192,192}),
            Rectangle(
              extent={{-20,60},{20,-60}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={192,192,192}),
            Polygon(
              points={{40,-40},{70,-30},{70,-50},{40,-40}},
              lineColor={0,0,127},
              fillColor={0,0,127},
              fillPattern=FillPattern.Solid),
            Rectangle(
              extent={{30,-25},{40,-55}},
              lineColor={0,0,0},
              fillColor={0,0,0},
              fillPattern=FillPattern.Solid),
            Polygon(
              points={{-40,-40},{-70,-30},{-70,-50},{-40,-40}},
              lineColor={0,0,127},
              fillColor={0,0,127},
              fillPattern=FillPattern.Solid),
            Rectangle(
              extent={{-40,-25},{-30,-55}},
              lineColor={0,0,0},
              fillColor={0,0,0},
              fillPattern=FillPattern.Solid),
            Line(points={{0,90},{80,70},{80,-40},{70,-40}}, color={0,0,127}),
            Line(points={{0,90},{-80,70},{-80,-40},{-70,-40}}, color={0,0,127})}),
          Diagram(graphics));
    end SimpleBrake;

    model SimpleLimiter

      Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_a annotation (
          Placement(transformation(extent={{-110,-10},{-90,10}}),
            iconTransformation(extent={{-110,-10},{-90,10}})));

      parameter SI.Angle phi_lim = Modelica.Constants.pi/4 "Limiting Angle";

      parameter SI.RotationalSpringConstant c = 1000 "Spring constant";

      parameter SI.RotationalDampingConstant d = 100 "Damping constant";

      SI.Angle phi;
      SI.Angle phi_excess;
      SI.AngularVelocity w;

    equation
      phi = flange_a.phi;
      phi_excess = noEvent(max(phi-phi_lim,min(phi+phi_lim,0)));
      w = der(flange_a.phi);
    //  flange_a.tau = if noEvent(phi<phi_lim and phi>-phi_lim) then 0 else c*phi_excess + d*noEvent(sign(phi)*max(w*sign(phi),0));
      flange_a.tau = if noEvent(phi<phi_lim and phi>-phi_lim) then 0 else c*phi_excess + d*w;

      annotation (Icon(graphics={
            Polygon(
              points={{-37,-27},{-37,-62},{37,-62},{37,-27},{33,-27},{33,-58},{-33,-58},
                  {-33,-27},{-37,-27}},
              lineColor={192,192,192},
              fillColor={0,0,0},
              fillPattern=FillPattern.Solid),
            Rectangle(
              extent={{-100,10},{-20,-10}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={192,192,192}),
            Rectangle(
              extent={{-20,80},{20,-40}},
              lineColor={0,0,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={192,192,192})}),
          Diagram(graphics));
    end SimpleLimiter;

    model VehicleControl

      parameter SI.Torque drivingTorque_max = 200 "maximum Driving Torque";
      parameter SI.Torque steeringTorque_max = 50 "maximum Steering Torque";
      parameter SI.Torque frontBrakeTorque_max = 200
        "maximum Torque of the Front Brake ";
      parameter SI.Torque rearBrakeTorque_max = 100
        "maximum Torque of the Front Brake ";
      parameter SI.Torque handBrakeTorque_max = 100
        "maximum Torque of the Hand Brake ";

      parameter SI.Torque rollFriction = 1 "maximum Torque of the Hand Brake ";

      Modelica.Blocks.Interfaces.RealOutput drivingTorque annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={0,-150}), iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=270,
            origin={3.55271e-015,-152})));
      Modelica.Blocks.Interfaces.RealOutput frontBrake annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-158,60}), iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=180,
            origin={-148,80})));
      Modelica.Blocks.Interfaces.RealOutput rearBrake annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-150,-60}), iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=180,
            origin={-150,-80})));
      Modelica.Blocks.Interfaces.RealOutput steering annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-10,160}), iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=90,
            origin={0,150})));
      Modelica_DeviceDrivers.Blocks.InputDevices.KeyboardInput keyboardInput(
          sampleTime=0.04)
        annotation (Placement(transformation(extent={{-6,-20},{34,20}})));
      Modelica.Blocks.Math.BooleanToReal booleanToReal(realTrue=-steeringTorque_max)
        annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={34,60})));
      Modelica.Blocks.Math.Add add(k2=+1) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,90})));
      Modelica.Blocks.Continuous.CriticalDamping criticalDamping(
        n=2,
        f=1,
        normalized=false) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,120})));
      Modelica.Blocks.Math.BooleanToReal booleanToReal1(realTrue=steeringTorque_max)
        annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-6,60})));
      Modelica.Blocks.Continuous.CriticalDamping criticalDamping1(
        normalized=false,
        n=1,
        f=0.5) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={0,-120})));
      Modelica.Blocks.Math.BooleanToReal booleanToReal2(realTrue=-0.1*
            drivingTorque_max) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={34,-60})));
      Modelica.Blocks.Math.BooleanToReal booleanToReal3(realTrue=drivingTorque_max)
        annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={-6,-60})));
      Modelica.Blocks.Math.Add add1(k2=+1) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={0,-90})));
      Modelica.Blocks.Math.BooleanToReal booleanToReal4 annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-60,60})));
      Modelica.Blocks.Continuous.CriticalDamping criticalDamping2(
        normalized=false,
        n=2,
        f=1.5) annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=180,
            origin={-90,60})));
      Modelica.Blocks.Math.Add add2(k1=handBrakeTorque_max, k2=rearBrakeTorque_max)
        annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-120,-60})));
      Modelica.Blocks.Math.BooleanToReal booleanToReal5 annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-60,-70})));
      Modelica.Blocks.Continuous.CriticalDamping criticalDamping3(
        normalized=false,
        n=1,
        f=2) annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=180,
            origin={-90,-70})));
      Modelica.Blocks.Math.Gain gain(k=frontBrakeTorque_max) annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-120,60})));
    equation
      connect(criticalDamping.u, add.y) annotation (Line(
          points={{-7.34788e-016,108},{6.73556e-016,108},{6.73556e-016,101}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(criticalDamping.y, steering) annotation (Line(
          points={{6.73556e-016,131},{6.73556e-016,132.5},{-10,132.5},{-10,160}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(booleanToReal1.u, keyboardInput.keyLeft) annotation (Line(
          points={{-6,48},{-6,40},{-26,40},{-26,-28},{2,-28},{2,-22}},
          color={255,0,255},
          smooth=Smooth.None));
      connect(booleanToReal.u, keyboardInput.keyRight) annotation (Line(
          points={{34,48},{34,40},{54,40},{54,-30},{26,-30},{26,-22}},
          color={255,0,255},
          smooth=Smooth.None));
      connect(booleanToReal.y, add.u2) annotation (Line(
          points={{34,71},{34,74},{6,74},{6,78}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(booleanToReal1.y, add.u1) annotation (Line(
          points={{-6,71},{-6,72.75},{-6,72.75},{-6,74.5},{-6,78},{-6,78}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(criticalDamping1.y, drivingTorque) annotation (Line(
          points={{-2.02067e-015,-131},{-2.02067e-015,-150},{0,-150}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(add1.y, criticalDamping1.u) annotation (Line(
          points={{-2.02067e-015,-101},{-2.02067e-015,-102},{0,-102},{0,-104},{
              2.20436e-015,-104},{2.20436e-015,-108}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(keyboardInput.keyUp, booleanToReal3.u) annotation (Line(
          points={{36,12},{68,12},{68,-44},{-6,-44},{-6,-48}},
          color={255,0,255},
          smooth=Smooth.None));
      connect(keyboardInput.keyDown, booleanToReal2.u) annotation (Line(
          points={{14,-22},{14,-40},{34,-40},{34,-48}},
          color={255,0,255},
          smooth=Smooth.None));
      connect(booleanToReal2.y, add1.u1) annotation (Line(
          points={{34,-71},{34,-74},{6,-74},{6,-78}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(booleanToReal3.y, add1.u2) annotation (Line(
          points={{-6,-71},{-6,-72.75},{-6,-72.75},{-6,-74.5},{-6,-78},{-6,-78}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(criticalDamping2.u, booleanToReal4.y) annotation (Line(
          points={{-78,60},{-71,60}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(keyboardInput.keyDown, booleanToReal4.u) annotation (Line(
          points={{14,-22},{14,-32},{-42,-32},{-42,60},{-48,60}},
          color={255,0,255},
          smooth=Smooth.None));
      connect(add2.y, rearBrake) annotation (Line(
          points={{-131,-60},{-150,-60}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(criticalDamping3.y, add2.u1) annotation (Line(
          points={{-101,-70},{-104,-70},{-104,-66},{-108,-66}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(criticalDamping3.u, booleanToReal5.y) annotation (Line(
          points={{-78,-70},{-71,-70}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(keyboardInput.keySpace, booleanToReal5.u) annotation (Line(
          points={{36,-12},{60,-12},{60,-36},{-30,-36},{-30,-70},{-48,-70}},
          color={255,0,255},
          smooth=Smooth.None));
      connect(gain.u, criticalDamping2.y) annotation (Line(
          points={{-108,60},{-101,60}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(gain.y, frontBrake) annotation (Line(
          points={{-131,60},{-158,60}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(criticalDamping2.y, add2.u2) annotation (Line(
          points={{-101,60},{-104,60},{-104,-54},{-108,-54}},
          color={0,0,127},
          smooth=Smooth.None));
      annotation (Diagram(coordinateSystem(preserveAspectRatio=true, extent={{-150,-150},
                {150,150}}), graphics), Icon(coordinateSystem(preserveAspectRatio=true,
              extent={{-150,-150},{150,150}}), graphics={
            Rectangle(
              extent={{-150,150},{150,-150}},
              lineColor={0,0,255},
              fillColor={255,255,255},
              fillPattern=FillPattern.Solid),            Polygon(
              points={{0,-100},{-80,-100},{-88,-98},{-94,-94},{-98,-88},{-100,-80},{
                  -100,80},{-98,88},{-94,94},{-88,98},{-80,100},{80,100},{88,98},{94,
                  94},{98,88},{100,80},{100,-80},{98,-88},{94,-94},{88,-98},{80,-100},
                  {0,-100}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={255,255,255},
              fillPattern=FillPattern.Solid), Line(
              points={{0,-100},{-80,-100},{-88,-98},{-94,-94},{-98,-88},{-100,-80},{
                  -100,80},{-98,88},{-94,94},{-88,98},{-80,100},{80,100},{88,98},{94,
                  94},{98,88},{100,80},{100,-80},{98,-88},{94,-94},{88,-98},{80,-100},
                  {0,-100}},
              color={0,64,127},
              thickness=0.5),
            Rectangle(
              extent={{-28,58},{28,2}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={215,215,215},
              fillPattern=FillPattern.Solid),
            Polygon(
              points={{-28,58},{-20,58},{-20,18},{-28,2},{-28,58}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={175,175,175},
              fillPattern=FillPattern.Solid),
            Polygon(
              points={{28,58},{18,58},{18,18},{28,2},{28,58}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={135,135,135},
              fillPattern=FillPattern.Solid),
            Polygon(
              points={{-28,2},{-20,18},{18,18},{28,2},{-28,2}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={95,95,95},
              fillPattern=FillPattern.Solid),
            Rectangle(
              extent={{-28,2},{28,-54}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={215,215,215},
              fillPattern=FillPattern.Solid),
            Rectangle(
              extent={{28,2},{84,-54}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={215,215,215},
              fillPattern=FillPattern.Solid),
            Rectangle(
              extent={{-84,2},{-28,-54}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={215,215,215},
              fillPattern=FillPattern.Solid),
            Polygon(
              points={{-84,-54},{-76,-38},{-38,-38},{-28,-54},{-84,-54}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={95,95,95},
              fillPattern=FillPattern.Solid),
            Polygon(
              points={{-84,2},{-76,2},{-76,-38},{-84,-54},{-84,2}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={175,175,175},
              fillPattern=FillPattern.Solid),
            Polygon(
              points={{-28,2},{-38,2},{-38,-38},{-28,-54},{-28,2}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={135,135,135},
              fillPattern=FillPattern.Solid),
            Polygon(
              points={{-28,2},{-20,2},{-20,-38},{-28,-54},{-28,2}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={175,175,175},
              fillPattern=FillPattern.Solid),
            Polygon(
              points={{28,2},{18,2},{18,-38},{28,-54},{28,2}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={135,135,135},
              fillPattern=FillPattern.Solid),
            Polygon(
              points={{-28,-54},{-20,-38},{18,-38},{28,-54},{-28,-54}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={95,95,95},
              fillPattern=FillPattern.Solid),
            Polygon(
              points={{28,2},{36,2},{36,-38},{28,-54},{28,2}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={175,175,175},
              fillPattern=FillPattern.Solid),
            Polygon(
              points={{84,2},{74,2},{74,-38},{84,-54},{84,2}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={135,135,135},
              fillPattern=FillPattern.Solid),
            Polygon(
              points={{28,-54},{36,-38},{74,-38},{84,-54},{28,-54}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={95,95,95},
              fillPattern=FillPattern.Solid),
            Line(points={{-2,50},{-2,28}}, color={95,95,95}),
            Polygon(
              points={{-2,50},{-6,42},{2,42},{-2,50}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={95,95,95},
              fillPattern=FillPattern.Solid),
            Line(points={{-2,-10},{-2,-28}},color={95,95,95}),
            Polygon(
              points={{-2,-28},{-6,-20},{2,-20},{-2,-28}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={95,95,95},
              fillPattern=FillPattern.Solid),
            Line(points={{-46,-18},{-68,-18}}, color={95,95,95}),
            Polygon(
              points={{-60,-22},{-68,-18},{-60,-14},{-60,-22}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={95,95,95},
              fillPattern=FillPattern.Solid),
            Line(points={{66,-18},{44,-18}}, color={95,95,95}),
            Polygon(
              points={{58,-22},{66,-18},{58,-14},{58,-22}},
              lineColor={0,0,255},
              pattern=LinePattern.None,
              fillColor={95,95,95},
              fillPattern=FillPattern.Solid)}));
    end VehicleControl;

    model DifferentialGear "\"Simple Model of a differential gear\""

      Modelica.Mechanics.Rotational.Components.IdealPlanetary idealPlanetary(
          ratio=-2)  annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={0,-52})));
      Modelica.Mechanics.Rotational.Interfaces.Flange_b flange_b
        annotation (Placement(transformation(extent={{-10,-110},{10,-90}})));
      Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_left
        annotation (Placement(transformation(extent={{-110,-10},{-90,10}})));
      Modelica.Mechanics.Rotational.Interfaces.Flange_a flange_right
        annotation (Placement(transformation(extent={{90,-10},{110,10}})));
    equation
      connect(flange_b,idealPlanetary. ring) annotation (Line(
          points={{0,-100},{0,-62},{-1.83697e-015,-62}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(idealPlanetary.carrier, flange_right) annotation (Line(
          points={{4,-42},{4,0},{100,0}},
          color={0,0,0},
          pattern=LinePattern.None,
          smooth=Smooth.None));
      connect(idealPlanetary.sun, flange_left) annotation (Line(
          points={{1.83697e-015,-42},{0,-42},{0,0},{-100,0}},
          color={0,0,0},
          smooth=Smooth.None));
      annotation (Diagram(graphics), Icon(graphics={
            Rectangle(
              extent={{-60,50},{40,-50}},
              fillColor={175,175,175},
              fillPattern=FillPattern.Solid,
              pattern=LinePattern.None),
            Rectangle(
              extent={{-48,40},{40,-40}},
              fillColor={255,255,255},
              fillPattern=FillPattern.Solid,
              pattern=LinePattern.None,
              lineColor={0,0,0}),
            Polygon(
              points={{40,-60},{60,-80},{60,80},{40,60},{40,-60}},
              pattern=LinePattern.None,
              smooth=Smooth.None,
              fillColor={175,175,175},
              fillPattern=FillPattern.Solid,
              lineColor={0,0,0}),
            Polygon(
              points={{20,-60},{40,-80},{-40,-80},{-20,-60},{20,-60}},
              pattern=LinePattern.None,
              smooth=Smooth.None,
              fillColor={175,175,175},
              fillPattern=FillPattern.Solid,
              lineColor={0,0,0}),
            Polygon(
              points={{14,10},{34,-10},{-34,-10},{-14,10},{14,10}},
              pattern=LinePattern.None,
              smooth=Smooth.None,
              fillColor={135,135,135},
              fillPattern=FillPattern.Solid,
              origin={-30,0},
              rotation=270),
            Polygon(
              points={{14,10},{34,-10},{-32,-10},{-12,10},{14,10}},
              pattern=LinePattern.None,
              smooth=Smooth.None,
              fillColor={135,135,135},
              fillPattern=FillPattern.Solid,
              origin={-4,-26},
              rotation=360),
            Polygon(
              points={{16,10},{36,-10},{-32,-10},{-12,10},{16,10}},
              pattern=LinePattern.None,
              smooth=Smooth.None,
              fillColor={135,135,135},
              fillPattern=FillPattern.Solid,
              origin={24,-2},
              rotation=90),
            Rectangle(
              extent={{-100,10},{-40,-10}},
              pattern=LinePattern.None,
              fillColor={135,135,135},
              fillPattern=FillPattern.Solid),
            Rectangle(
              extent={{34,10},{102,-10}},
              pattern=LinePattern.None,
              fillColor={135,135,135},
              fillPattern=FillPattern.Solid),
            Rectangle(
              extent={{-10,-100},{10,-80}},
              pattern=LinePattern.None,
              fillColor={175,175,175},
              fillPattern=FillPattern.Solid),
            Rectangle(
              extent={{-16,-36},{10,-40}},
              pattern=LinePattern.None,
              fillColor={175,175,175},
              fillPattern=FillPattern.Solid)}));
    end DifferentialGear;

    model SimpleChassis

      parameter SI.Length wheelBase = 2.6 "Wheel Base of the Vehicle" annotation(Dialog(group="Geometry"));
      parameter SI.Length l = 3.5 "Length of the Vehicle" annotation(Dialog(group="Geometry"));
      parameter SI.Length w = 1.6 "width of the Vehicle" annotation(Dialog(group="Geometry"));
      parameter SI.Length h = 0.5 "height of the dynamic load" annotation(Dialog(group="Geometry"));

      parameter SI.Mass m_static = 1500 "Base load of the vehicle" annotation(Dialog(group="Mass"));
      parameter SI.Mass m_dynamic = 500 "Dynamic load of the vehicle" annotation(Dialog(group="Mass"));

      parameter SI.RotationalSpringConstant c_roll = 10000
        "Roll spring constant"                                                    annotation(Dialog(group="Stiffness"));
      parameter SI.RotationalDampingConstant d_roll = 1000
        "Roll damping constant"                                                   annotation(Dialog(group="Stiffness"));
      parameter SI.RotationalSpringConstant c_pitch = 15000
        "Pitch spring constant"                                                     annotation(Dialog(group="Stiffness"));
      parameter SI.RotationalDampingConstant d_pitch = 1500
        "Pitch damping constant"                                                   annotation(Dialog(group="Stiffness"));

      Parts.FixedTranslation fixedTranslationFront(r={0, wheelBase/2},
        animate=true)                                        annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,30})));
      Parts.Body baseLoad(
        g={0,0},
        m=m_static,
        I=(m_static + m_dynamic)/12*(w^2 + l^2),
        animate=true)
              annotation (Placement(transformation(extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-70,0})));
      Parts.FixedTranslation fixedTranslationRear(r={0, wheelBase/2},
        animate=true)                                        annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,-30})));
      Interfaces.Frame_a frame_a annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,-90}),  iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=90,
            origin={0,-202})));
      Interfaces.Frame_b frame_b annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,90}),  iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=90,
            origin={0,200})));

    equation
      connect(fixedTranslationRear.frame_b, fixedTranslationFront.frame_a)
                                                                    annotation (
         Line(
          points={{6.12323e-016,-20},{6.12323e-016,2},{-6.12323e-016,2},{
              -6.12323e-016,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslationFront.frame_b, frame_b) annotation (Line(
          points={{6.12323e-016,40},{6.12323e-016,80},{0,80},{0,90}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslationRear.frame_a, frame_a) annotation (Line(
          points={{-6.12323e-016,-40},{-6.12323e-016,-80},{0,-80},{0,-90}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslationFront.frame_a, baseLoad.frame_a) annotation (Line(
          points={{-6.12323e-016,20},{-6.12323e-016,-1.22465e-015},{-60,
              -1.22465e-015}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(coordinateSystem(preserveAspectRatio=true, extent={{-200,
                -200},{200,200}}),
                             graphics), Icon(coordinateSystem(preserveAspectRatio=true,
              extent={{-200,-200},{200,200}}), graphics={Polygon(
              points={{-100,200},{-200,40},{-200,-160},{-160,-200},{160,-200},{200,-160},
                  {200,40},{100,200},{-100,200}},
              lineColor={0,0,0},
              smooth=Smooth.None,
              fillColor={135,135,135},
              fillPattern=FillPattern.Solid), Polygon(
              points={{-80,178},{-162,54},{160,54},{76,178},{-80,178}},
              lineColor={0,0,0},
              smooth=Smooth.None,
              fillColor={170,213,255},
              fillPattern=FillPattern.Solid)}));
    end SimpleChassis;

    model SimpleChassis3D

      parameter SI.Length wheelBase = 2.6 "Wheel Base of the Vehicle" annotation(Dialog(group="Geometry"));
      parameter SI.Length l = 3.5 "Length of the Vehicle" annotation(Dialog(group="Geometry"));
      parameter SI.Length w = 1.6 "width of the Vehicle" annotation(Dialog(group="Geometry"));
      parameter SI.Length h = 0.5 "height of the dynamic load" annotation(Dialog(group="Geometry"));

      parameter SI.Mass m_static = 1500 "Base load of the vehicle" annotation(Dialog(group="Mass"));
      parameter SI.Mass m_dynamic = 500 "Dynamic load of the vehicle" annotation(Dialog(group="Mass"));

      parameter SI.RotationalSpringConstant c_roll = 10000
        "Roll spring constant"                                                    annotation(Dialog(group="Stiffness"));
      parameter SI.RotationalDampingConstant d_roll = 1000
        "Roll damping constant"                                                   annotation(Dialog(group="Stiffness"));
      parameter SI.RotationalSpringConstant c_pitch = 15000
        "Pitch spring constant"                                                     annotation(Dialog(group="Stiffness"));
      parameter SI.RotationalDampingConstant d_pitch = 1500
        "Pitch damping constant"                                                   annotation(Dialog(group="Stiffness"));

      Parts.FixedTranslation fixedTranslationFront(r={0, wheelBase/2},
        animate=true)                                        annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-40,30})));
      Parts.Body baseLoad(
        g={0,0},
        m=m_static,
        I=(m_static + m_dynamic)/12*(w^2 + l^2),
        animate=true)
              annotation (Placement(transformation(extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-70,0})));
      Interfaces.PlanarToMultiBody planarToMultiBody
        annotation (Placement(transformation(extent={{-30,-10},{-10,10}})));
      MB.Parts.FixedTranslation toCenterOfGravity(r={0,0,0.5}, animation=true)
        annotation (Placement(transformation(extent={{120,-10},{140,10}})));
      Parts.FixedTranslation fixedTranslationRear(r={0, wheelBase/2},
        animate=true)                                        annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-40,-30})));
      MB.Joints.Revolute roll(
        useAxisFlange=true,
        n={0,1,0} "y axis",
        phi(fixed=true),
        w(fixed=true),
        animation=true)
        annotation (Placement(transformation(extent={{40,-10},{60,10}})));
      MB.Parts.Body dynamicLoad(
        m=m_dynamic,
        I_11=0,
        I_22=0,
        I_33=0,
        animation=true)          annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={170,0})));
      Modelica.Mechanics.Rotational.Components.SpringDamper rollSpringDamper(c=
            c_pitch, d=d_pitch)
        annotation (Placement(transformation(extent={{20,30},{40,50}})));
      MB.Joints.Revolute pitch(
        useAxisFlange=true,
        phi(fixed=true),
        w(fixed=true),
        n={1,0,0} "x axis",
        animation=true)
        annotation (Placement(transformation(extent={{80,10},{100,-10}})));
      Modelica.Mechanics.Rotational.Components.SpringDamper pitchSpringDamper(c=
            c_pitch, d=d_pitch)
        annotation (Placement(transformation(extent={{40,-40},{60,-60}})));
      Interfaces.Frame_a frame_a annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-40,-84}),iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=90,
            origin={0,-202})));
      Interfaces.Frame_b frame_b annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-40,84}),iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=90,
            origin={0,200})));

    equation
      connect(baseLoad.frame_a, fixedTranslationFront.frame_a)
                                                        annotation (Line(
          points={{-60,-1.22465e-015},{-40,-1.22465e-015},{-40,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslationRear.frame_b, fixedTranslationFront.frame_a)
                                                                    annotation (
         Line(
          points={{-40,-20},{-40,20}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslationRear.frame_b, planarToMultiBody.frame_a)
                                                                    annotation (
         Line(
          points={{-40,-20},{-40,0},{-22.8,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(roll.frame_a, planarToMultiBody.frame_b)     annotation (Line(
          points={{40,0},{-17.6,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(toCenterOfGravity.frame_b, dynamicLoad.frame_a)
                                                       annotation (Line(
          points={{140,0},{160,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pitch.frame_a, roll.frame_b)         annotation (Line(
          points={{80,0},{60,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pitch.frame_b, toCenterOfGravity.frame_a)    annotation (Line(
          points={{100,0},{120,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslationFront.frame_b, frame_b) annotation (Line(
          points={{-40,40},{-40,84}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslationRear.frame_a, frame_a) annotation (Line(
          points={{-40,-40},{-40,-84}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pitchSpringDamper.flange_a, pitch.support) annotation (Line(
          points={{40,-50},{30,-50},{30,-20},{84,-20},{84,-10}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(rollSpringDamper.flange_b, roll.axis) annotation (Line(
          points={{40,40},{50,40},{50,10}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(pitchSpringDamper.flange_b, pitch.axis) annotation (Line(
          points={{60,-50},{90,-50},{90,-10}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(rollSpringDamper.flange_a, roll.support) annotation (Line(
          points={{20,40},{10,40},{10,20},{44,20},{44,10}},
          color={0,0,0},
          smooth=Smooth.None));
      annotation (Diagram(coordinateSystem(preserveAspectRatio=false,extent={{-200,
                -200},{200,200}}),
                             graphics), Icon(coordinateSystem(preserveAspectRatio=true,
              extent={{-200,-200},{200,200}}), graphics={Polygon(
              points={{-100,200},{-200,40},{-200,-160},{-160,-200},{160,-200},{200,-160},
                  {200,40},{100,200},{-100,200}},
              lineColor={0,0,0},
              smooth=Smooth.None,
              fillColor={135,135,135},
              fillPattern=FillPattern.Solid), Polygon(
              points={{-80,178},{-162,54},{160,54},{76,178},{-80,178}},
              lineColor={0,0,0},
              smooth=Smooth.None,
              fillColor={170,213,255},
              fillPattern=FillPattern.Solid)}));
    end SimpleChassis3D;

    model Chassis3D

      parameter SI.Length wheelBase = 2.6 "Wheel Base of the Vehicle" annotation(Dialog(group="Geometry"));
      parameter SI.Length l = 3.5 "Length of the Vehicle" annotation(Dialog(group="Geometry"));
      parameter SI.Length w = 1.6 "width of the Vehicle" annotation(Dialog(group="Geometry"));
      parameter SI.Length h = 0.5 "height of the dynamic load" annotation(Dialog(group="Geometry"));

      parameter SI.Mass m_static = 1500 "Base load of the vehicle" annotation(Dialog(group="Mass"));
      parameter SI.Mass m_dynamic = 500 "Dynamic load of the vehicle" annotation(Dialog(group="Mass"));

      parameter SI.RotationalSpringConstant c_roll = 10000
        "Roll spring constant"                                                    annotation(Dialog(group="Stiffness"));
      parameter SI.RotationalDampingConstant d_roll = 1000
        "Roll damping constant"                                                   annotation(Dialog(group="Stiffness"));
      parameter SI.RotationalSpringConstant c_pitch = 15000
        "Pitch spring constant"                                                     annotation(Dialog(group="Stiffness"));
      parameter SI.RotationalDampingConstant d_pitch = 1500
        "Pitch damping constant"                                                   annotation(Dialog(group="Stiffness"));

      parameter Boolean animate = true "enable Animation"
                                                         annotation(Dialog(group="Animation"));
      parameter Boolean SimVis = false "perform animation with SimVis" annotation(Dialog(group="Animation"));

      Parts.FixedTranslation fixedTranslationFront(r={0, wheelBase/2},
        animate=animate)                                     annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-40,50})));
      Parts.Body baseLoad(
        g={0,0},
        m=m_static,
        I=(m_static + m_dynamic)/12*(w^2 + l^2),
        animate=animate)
              annotation (Placement(transformation(extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-70,0})));
      Interfaces.PlanarToMultiBody planarToMultiBody
        annotation (Placement(transformation(extent={{-30,-10},{-10,10}})));
      MB.Parts.FixedTranslation toCenterOfGravity(r={0,0,0.5}, animation=
            animate)
        annotation (Placement(transformation(extent={{120,-10},{140,10}})));
      Parts.FixedTranslation fixedTranslationRear(r={0, wheelBase/2},
        animate=animate)                                     annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-40,-48})));
      MB.Joints.Revolute roll(
        useAxisFlange=true,
        n={0,1,0} "y axis",
        phi(fixed=true),
        w(fixed=true),
        animation=animate)
        annotation (Placement(transformation(extent={{40,-10},{60,10}})));
      MB.Parts.Body dynamicLoad(
        m=m_dynamic,
        I_11=0,
        I_22=0,
        I_33=0,
        animation=animate)       annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=0,
            origin={170,0})));
      Modelica.Mechanics.Rotational.Components.SpringDamper rollSpringDamper(c=
            c_pitch, d=d_pitch)
        annotation (Placement(transformation(extent={{20,30},{40,50}})));
      MB.Joints.Revolute pitch(
        useAxisFlange=true,
        phi(fixed=true),
        w(fixed=true),
        n={1,0,0} "x axis",
        animation=animate)
        annotation (Placement(transformation(extent={{80,10},{100,-10}})));
      Modelica.Mechanics.Rotational.Components.SpringDamper pitchSpringDamper(c=
            c_pitch, d=d_pitch)
        annotation (Placement(transformation(extent={{40,-40},{60,-60}})));
      Interfaces.Frame_a frame_a annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,-190}), iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=90,
            origin={0,-202})));
      Interfaces.Frame_b frame_b annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,190}), iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=90,
            origin={0,200})));
      Modelica.Blocks.Interfaces.RealOutput dynamicLoadRF annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={160,186}), iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=90,
            origin={160,200})));
      Modelica.Blocks.Interfaces.RealOutput dynamicLoadLF annotation (Placement(
            transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-160,186}), iconTransformation(
            extent={{-20,-20},{20,20}},
            rotation=90,
            origin={-160,200})));
      Modelica.Blocks.Interfaces.RealOutput dynamicLoadRR annotation (Placement(
            transformation(
            extent={{10,-10},{-10,10}},
            rotation=90,
            origin={160,-186}), iconTransformation(
            extent={{19,-19},{-19,19}},
            rotation=90,
            origin={161,-199})));
      Modelica.Blocks.Interfaces.RealOutput dynamicLoadLR annotation (Placement(
            transformation(
            extent={{10,-10},{-10,10}},
            rotation=90,
            origin={-160,-186}), iconTransformation(
            extent={{20,-20},{-20,20}},
            rotation=90,
            origin={-160,-200})));

      Visualization.Shapes.FileShape chassis(
        each shininess=0.8,
        filename=Visualization.Utilities.RootDir +
            "/Extras/3DData/Car/AstonMartin.3ds",
        transparency=0,
        lengthDirection={0,1,0},
        widthDirection={-1,0,0},
        each smoothNormals=true,
        each reflectsLight=true)
                             annotation (Placement(transformation(extent={{-10,-10},
                {10,10}},
                       rotation=270,
            origin={150,-60})));
      MB.Parts.FixedRotation fixedRotation(
        rotationType=Modelica.Mechanics.MultiBody.Types.RotationTypes.RotationAxis,
        n={0,0,1},
        angle=90,
        r={0,0.18,-0.45}) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=270,
            origin={150,-30})));

      Modelica.Blocks.Sources.Constant const(k=0)
        annotation (Placement(transformation(extent={{-200,140},{-180,160}})));
    equation
      connect(baseLoad.frame_a, fixedTranslationFront.frame_a)
                                                        annotation (Line(
          points={{-60,-1.22465e-015},{-40,-1.22465e-015},{-40,40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslationRear.frame_b, fixedTranslationFront.frame_a)
                                                                    annotation (
         Line(
          points={{-40,-38},{-40,40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslationRear.frame_b, planarToMultiBody.frame_a)
                                                                    annotation (
         Line(
          points={{-40,-38},{-40,0},{-22.8,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(roll.frame_a, planarToMultiBody.frame_b)     annotation (Line(
          points={{40,0},{-17.6,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(toCenterOfGravity.frame_b, dynamicLoad.frame_a)
                                                       annotation (Line(
          points={{140,0},{160,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(roll.support, rollSpringDamper.flange_a) annotation (Line(
          points={{44,10},{20,10},{20,40}},
          color={0,0,0},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pitch.frame_a, roll.frame_b)         annotation (Line(
          points={{80,0},{60,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pitch.frame_b, toCenterOfGravity.frame_a)    annotation (Line(
          points={{100,0},{120,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslationFront.frame_b, frame_b) annotation (Line(
          points={{-40,60},{-40,80},{0,80},{0,190}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedTranslationRear.frame_a, frame_a) annotation (Line(
          points={{-40,-58},{-40,-80},{0,-80},{0,-190}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pitchSpringDamper.flange_a, pitch.support) annotation (Line(
          points={{40,-50},{30,-50},{30,-20},{84,-20},{84,-10}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(chassis.frame_a, fixedRotation.frame_b) annotation (Line(
          points={{150,-50},{150,-40}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(fixedRotation.frame_a, toCenterOfGravity.frame_b) annotation (
          Line(
          points={{150,-20},{150,0},{140,0}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pitchSpringDamper.flange_b, pitch.axis) annotation (Line(
          points={{60,-50},{90,-50},{90,-10}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(rollSpringDamper.flange_b, roll.axis) annotation (Line(
          points={{40,40},{50,40},{50,10}},
          color={0,0,0},
          smooth=Smooth.None));
      connect(const.y, dynamicLoadLF) annotation (Line(
          points={{-179,150},{-160,150},{-160,186}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(const.y, dynamicLoadRF) annotation (Line(
          points={{-179,150},{160,150},{160,186}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(const.y, dynamicLoadLR) annotation (Line(
          points={{-179,150},{-160,150},{-160,-186}},
          color={0,0,127},
          smooth=Smooth.None));
      connect(const.y, dynamicLoadRR) annotation (Line(
          points={{-179,150},{-160,150},{-160,-160},{160,-160},{160,-186}},
          color={0,0,127},
          smooth=Smooth.None));
      annotation (Diagram(coordinateSystem(preserveAspectRatio=true, extent={{-200,
                -200},{200,200}}),
                             graphics), Icon(coordinateSystem(preserveAspectRatio=true,
              extent={{-200,-200},{200,200}}), graphics={Polygon(
              points={{-100,200},{-200,40},{-200,-160},{-160,-200},{160,-200},{200,-160},
                  {200,40},{100,200},{-100,200}},
              lineColor={0,0,0},
              smooth=Smooth.None,
              fillColor={135,135,135},
              fillPattern=FillPattern.Solid), Polygon(
              points={{-80,178},{-162,54},{160,54},{76,178},{-80,178}},
              lineColor={0,0,0},
              smooth=Smooth.None,
              fillColor={170,213,255},
              fillPattern=FillPattern.Solid)}));
    end Chassis3D;
  end VehicleComponents;

  package Sensors
    model AbsoluteRotation

      Interfaces.Frame_b frame_b annotation (Placement(transformation(extent={{60,40},
                {80,60}}), iconTransformation(extent={{80,-20},{120,20}})));
      Modelica.Blocks.Interfaces.RealOutput y annotation (Placement(transformation(
              extent={{-122,4},{-102,24}}), iconTransformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-110,0})));

    equation
      y = frame_b.phi;

      frame_b.fx = 0;
      frame_b.fy = 0;
      frame_b.t = 0;

      annotation (Icon(graphics={
            Line(points={{-100,0},{-74,0}},
                                          color={0,0,127}),
            Ellipse(
              extent={{-74,70},{66,-70}},
              lineColor={0,0,0},
              fillColor={255,255,255},
              fillPattern=FillPattern.Solid),
            Line(points={{-4,70},{-4,40}},
                                         color={0,0,0}),
            Line(points={{18.9,32.8},{36.2,57.3}}, color={0,0,0}),
            Line(points={{-26.9,32.8},{-44.2,57.3}}, color={0,0,0}),
            Line(points={{33.6,13.7},{61.8,23.9}}, color={0,0,0}),
            Line(points={{-41.6,13.7},{-69.8,23.9}}, color={0,0,0}),
            Line(points={{-4,0},{5.02,28.6}},color={0,0,0}),
            Polygon(
              points={{-4.48,31.6},{14,26},{14,57.2},{-4.48,31.6}},
              lineColor={0,0,0},
              fillColor={0,0,0},
              fillPattern=FillPattern.Solid),
            Ellipse(
              extent={{-9,5},{1,-5}},
              lineColor={0,0,0},
              fillColor={0,0,0},
              fillPattern=FillPattern.Solid),
                                   Text(
              extent={{60,80},{110,40}},
              lineColor={0,0,0},
              textString="phi"),
            Line(points={{86,0},{66,0}},   color={0,0,0}),
            Text(
              extent={{-100,-80},{100,-120}},
              textString="%name",
              lineColor={0,0,0})}));
    end AbsoluteRotation;
  end Sensors;
  annotation (uses(
        Modelica(version="3.2"), Visualization(version="1.2")), version="1");
end PlanarMechanicsV3;
