within ;
package PlanarMechanicsV2 "A planar mechanical library for didactical purposes"

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

    model FreeWheel "AcceleratingBody"

      Parts.Body body(
        m=1,
        I=0.1,
        g={0,0})
        annotation (Placement(transformation(extent={{-10,-10},{10,10}},
            rotation=0,
            origin={10,10})));
      VehicleComponents.Wheels.IdealWheelJoint idealWheelJoint(
        r={1,0},
        radius=0.2)  annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-30,10})));
      Modelica.Mechanics.Rotational.Components.Inertia inertia(
        J=0.1,
        phi(fixed=true, start=0),
        w(fixed=true, start=5)) annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=0,
            origin={-70,10})));
    equation
      connect(idealWheelJoint.frame_a, body.frame_a) annotation (Line(
          points={{-25.2,10},{0,10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(inertia.flange_b, idealWheelJoint.flange_a) annotation (Line(
          points={{-60,10},{-40,10}},
          color={0,0,0},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end FreeWheel;

    model FreeWheelwithFriction "AcceleratingBody"

      Parts.Body body(
        I=0.1,
        m=2,
        g={0,-9.81})
        annotation (Placement(transformation(extent={{-10,-10},{10,10}},
            rotation=0,
            origin={10,10})));
      VehicleComponents.Wheels.DryFrictionWheelJoint DryFrictionWheelJoint(
        r={1,0},
        vAdhesion=0.1,
        N=100,
        radius=0.3,
        vSlide=0.2,
        mu_A=0.8,
        mu_S=0.4)
               annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=180,
            origin={-30,10})));
      Modelica.Mechanics.Rotational.Components.Inertia inertia(
        phi(fixed=true, start=0),
        J=0.1,
        w(fixed=true, start=5)) annotation (Placement(transformation(
            extent={{-10,10},{10,-10}},
            rotation=0,
            origin={-70,10})));
    equation
      connect(DryFrictionWheelJoint.frame_a, body.frame_a)
                                                     annotation (Line(
          points={{-25.2,10},{0,10}},
          color={95,95,95},
          thickness=0.5,
          smooth=Smooth.None));
      connect(inertia.flange_b, DryFrictionWheelJoint.flange_a)
                                                          annotation (Line(
          points={{-60,10},{-50,10},{-50,10},{-40,10}},
          color={0,0,0},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end FreeWheelwithFriction;

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
  annotation (uses(                         Visualization(version="1.1"),
        Modelica(version="3.2")));
end PlanarMechanicsV2;
