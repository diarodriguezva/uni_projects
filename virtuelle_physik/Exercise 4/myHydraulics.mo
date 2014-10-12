within ;
package myHydraulics
  package Examples

    model Example1

      myHydraulics.Examples.Section   section
        annotation (Placement(transformation(extent={{-32,-10},{-12,10}})));
      myHydraulics.Examples.Section   section1
        annotation (Placement(transformation(extent={{-6,-10},{14,10}})));
      myHydraulics.Examples.Section   section2
        annotation (Placement(transformation(extent={{22,-10},{42,10}})));
      myHydraulics.Examples.Section   section3
        annotation (Placement(transformation(extent={{50,-10},{70,10}})));
      myHydraulics.Examples.Section   section4
        annotation (Placement(transformation(extent={{74,-10},{94,10}})));
      myHydraulics.Components.SignalPressure signalPressure
        annotation (Placement(transformation(extent={{-60,-10},{-40,10}})));
      Modelica.Blocks.Sources.Sine sine(freqHz=60, amplitude=1000)
        annotation (Placement(transformation(extent={{-98,-10},{-78,10}})));
    equation
      connect(section.pin2, section1.pin) annotation (Line(
          points={{-14.6,0},{-3.4,0}},
          color={0,0,255},
          thickness=0.5,
          smooth=Smooth.None));
      connect(section1.pin2, section2.pin) annotation (Line(
          points={{11.4,0},{24.6,0}},
          color={0,0,255},
          thickness=0.5,
          smooth=Smooth.None));
      connect(section2.pin2, section3.pin) annotation (Line(
          points={{39.4,0},{52.6,0}},
          color={0,0,255},
          thickness=0.5,
          smooth=Smooth.None));
      connect(sine.y, signalPressure.u) annotation (Line(
          points={{-77,0},{-58,0}},
          color={0,0,127},
          thickness=0.5,
          smooth=Smooth.None));
      connect(section3.pin2, section4.pin) annotation (Line(
          points={{67.4,0},{76.6,0}},
          color={0,0,255},
          thickness=0.5,
          smooth=Smooth.None));
      connect(signalPressure.first, section.pin) annotation (Line(
          points={{-41,0},{-29.4,0}},
          color={0,0,255},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(coordinateSystem(preserveAspectRatio=false, extent={{-100,
                -100},{100,100}}), graphics));
    end Example1;

    model Section

      Components.CompresiveVolume compresiveVolume(
        Kc=1e-5,
        L=0.2,
        A=0.01) annotation (Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={0,30})));
      Components.HydraulicInductance hydraulicInductance(
        L=0.2,
        D=1.29,
        A=0.01) annotation (Placement(transformation(extent={{-38,-6},{-18,6}})));
      Components.PipeFriction pipeFriction(Kr=5000)
        annotation (Placement(transformation(extent={{20,-10},{40,10}})));
    protected
      Interfaces.Pin pin1
        annotation (Placement(transformation(extent={{-0.6,-0.6},{0.6,0.6}})));
    public
      Interfaces.Pin pin
        annotation (Placement(transformation(extent={{-80,-6},{-68,6}})));
      Interfaces.Pin pin2
        annotation (Placement(transformation(extent={{68,-6},{80,6}})));
    equation
      connect(compresiveVolume.first, pin1) annotation (Line(
          points={{-4.44089e-016,21},{-4.44089e-016,10},{0,10},{0,0}},
          color={0,0,255},
          thickness=0.5,
          smooth=Smooth.None));
      connect(hydraulicInductance.second, pin1) annotation (Line(
          points={{-19,0},{0,0}},
          color={0,0,255},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pipeFriction.first, pin1) annotation (Line(
          points={{21,0},{0,0}},
          color={0,0,255},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pipeFriction.second, pin2) annotation (Line(
          points={{39,0},{74,0}},
          color={0,0,255},
          thickness=0.5,
          smooth=Smooth.None));
      connect(hydraulicInductance.first, pin) annotation (Line(
          points={{-37,0},{-74,0}},
          color={0,0,255},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(coordinateSystem(preserveAspectRatio=false, extent={{-100,
                -100},{100,100}}), graphics), Icon(coordinateSystem(
              preserveAspectRatio=false, extent={{-100,-100},{100,100}}), graphics={
            Rectangle(
              extent={{-60,40},{60,-40}},
              lineColor={255,0,0},
              lineThickness=0.5,
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={255,128,0}),
            Line(
              points={{-80,58},{80,58},{80,58}},
              color={0,0,0},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{-80,-60},{80,-60},{80,-60}},
              color={0,0,0},
              thickness=0.5,
              smooth=Smooth.None)}));
    end Section;
  end Examples;

  package Components
    model HydraulicInductance
      extends Interfaces.OnePortHydraulics;
      parameter Real L;
      parameter Real D;
      parameter Real A;
    equation
      der(v)*D*L/A = P;
      annotation (Icon(coordinateSystem(preserveAspectRatio=false, extent={{-100,-60},
                {100,60}}), graphics={
            Line(
              points={{-80,60},{80,60},{80,60}},
              color={0,0,0},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{-80,-60},{80,-60}},
              color={0,0,0},
              thickness=0.5,
              smooth=Smooth.None),
            Rectangle(
              extent={{-60,40},{60,-40}},
              lineColor={0,0,255},
              lineThickness=0.5,
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={85,255,255})}));
    end HydraulicInductance;

    model CompresiveVolume

      import SI = Modelica.SIunits;

      SI.Pressure P;
      SI.VolumeFlowRate v;

      parameter Real Kc;
      parameter Real L;
      parameter Real A;

      Interfaces.Pin first annotation (Placement(transformation(extent={{-100,-10},{-80,
                10}}), iconTransformation(extent={{-100,-10},{-80,10}})));
    equation
       der(P)*Kc*A*L = v;
       P = first.P;
       v = first.v;
       annotation (Icon(coordinateSystem(preserveAspectRatio=false, extent={{-100,-100},
                {100,100}}), graphics={
            Line(
              points={{-80,40},{-40,40},{-40,80},{100,80},{100,-82},{-40,-82},{-40,-40},
                  {-60,-40},{-80,-40}},
              smooth=Smooth.None,
              color={0,0,0}),
            Rectangle(
              extent={{-20,60},{80,-62}},
              lineColor={128,255,0},
              fillPattern=FillPattern.HorizontalCylinder,
              fillColor={213,255,170}),
            Line(
              points={{-80,0},{-20,0},{-22,2}},
              color={128,255,0},
              smooth=Smooth.None,
              thickness=0.5)}), Diagram(coordinateSystem(preserveAspectRatio=false,
              extent={{-100,-100},{100,100}}), graphics));
    end CompresiveVolume;

    model PipeFriction
      extends Interfaces.OnePortHydraulics;
      parameter Real Kr;
    equation
      P = Kr*v;
      annotation (Icon(coordinateSystem(preserveAspectRatio=false, extent={{-100,-100},
                {100,100}}),            graphics={
            Line(
              points={{-80,60},{-20,60},{0,40},{20,60},{80,60},{78,60}},
              color={135,135,135},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{-80,-60},{-20,-60},{0,-40},{20,-60},{80,-60},{80,-60}},
              color={135,135,135},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{-60,0},{62,0},{60,0}},
              color={0,255,0},
              thickness=0.5,
              smooth=Smooth.None)}), Diagram(coordinateSystem(preserveAspectRatio=false,
              extent={{-100,-60},{100,60}}), graphics));
    end PipeFriction;

    model SignalPressure
      import SI = Modelica.SIunits;

      Modelica.Blocks.Interfaces.RealInput u
        annotation (Placement(transformation(extent={{-100,-20},{-60,20}})));
      Interfaces.Pin first
        annotation (Placement(transformation(extent={{80,-10},{100,10}})));
    equation
      u = first.P;

      annotation (Icon(coordinateSystem(preserveAspectRatio=false, extent={{-100,-100},
                {100,100}}), graphics={
            Polygon(
              points={{60,0},{20,40},{20,-40},{60,0}},
              lineColor={0,128,255},
              lineThickness=0.5,
              fillPattern=FillPattern.HorizontalCylinder,
              smooth=Smooth.None,
              fillColor={85,255,255}),
            Line(
              points={{80,10},{0,94},{0,94}},
              color={135,135,135},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{80,-10},{0,-92}},
              color={135,135,135},
              thickness=0.5,
              smooth=Smooth.None)}));
    end SignalPressure;

    model HydraulicSection

    parameter Real L=1;
    parameter Real A=1;
    parameter Real D=1;
    parameter Real Kc=1;
    parameter Real Kr=1;

    myHydraulics.Components.HydraulicInductance
                        I(D=D,L=L,A=A);
    myHydraulics.Components.CompresiveVolume
                     C(Kc=Kc,L=L,A=A);
    myHydraulics.Components.PipeFriction
                 F(Kr=Kr);

    myHydraulics.Interfaces.Pin
        TubeIn;
    myHydraulics.Interfaces.Pin
        TubeOut;

    equation
      connect(I.second,C.first);
      connect(C.first,F.first);

      connect(TubeIn,I.first);
      connect(TubeOut,F.second);

      annotation ();
    end HydraulicSection;

  end Components;

  package Interfaces
    model OnePortHydraulics

      import SI = Modelica.SIunits;

      SI.Pressure P;
      SI.VolumeFlowRate v;

      Pin first annotation (Placement(transformation(extent={{-100,-10},{-80,10}}),
            iconTransformation(extent={{-100,-10},{-80,10}})));
      Pin second annotation (Placement(transformation(extent={{80,-10},{100,10}}),
            iconTransformation(extent={{80,-10},{100,10}})));
    equation
      P = first.P - second.P;
      first.v + second.v = 0;
      v = first.v;
      annotation (Icon(coordinateSystem(preserveAspectRatio=false, extent={{-100,-60},
                {100,60}}),             graphics={Rectangle(
              extent={{-78,62},{82,-58}},
              pattern=LinePattern.None,
              lineColor={255,255,255})}),          Diagram(coordinateSystem(
              preserveAspectRatio=false, extent={{-100,-60},{100,60}}),   graphics={Text(
              extent={{-48,-64},{36,-78}},
              lineColor={0,0,255},
              textString="name")}));
    end OnePortHydraulics;

    connector Pin
      import SI = Modelica.SIunits;

      SI.Pressure P;
      flow SI.VolumeFlowRate v;
      annotation (Icon(coordinateSystem(preserveAspectRatio=false, extent={{-60,-60},
                {60,60}}),              graphics={Rectangle(
              extent={{-60,60},{60,-60}},
              lineColor={0,0,255},
              fillColor={0,127,0},
              fillPattern=FillPattern.Solid)}), Diagram(coordinateSystem(
              preserveAspectRatio=false, extent={{-60,-60},{60,60}}),
            graphics));
    end Pin;
  end Interfaces;
  annotation (uses(Modelica(version="3.2")));
end myHydraulics;
