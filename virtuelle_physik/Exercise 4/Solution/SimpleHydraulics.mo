within ;
package SimpleHydraulics "Simple Hydraulics Library from Exercise 4"

  import SI = Modelica.SIunits;

  package Interface
    connector HydPlug "General Connector"

      SI.Pressure p "relative Pressure";
      flow SI.VolumeFlowRate v "volume flow";

      annotation (Diagram(graphics), Icon(graphics={Rectangle(
              extent={{-80,80},{80,-80}},
              lineColor={0,63,0},
              fillColor={0,127,0},
              fillPattern=FillPattern.Solid,
              lineThickness=0.5)}));
    end HydPlug;

    partial model OnePort "General Base Class fro components with two plugs"

      HydPlug hydPlug_a annotation (Placement(transformation(extent={{-110,-10},{-90,10}}),
            iconTransformation(extent={{-110,-10},{-90,10}})));
      HydPlug hydPlug_b
        annotation (Placement(transformation(extent={{90,-10},{110,10}})));

      SI.Pressure dp;
      SI.VolumeFlowRate v;

    equation
      hydPlug_a.v + hydPlug_b.v = 0;
      v = hydPlug_a.v;
      hydPlug_a.p - dp = hydPlug_b.p;

      annotation (Icon(graphics));
    end OnePort;
  end Interface;

  package Components
    model PipeFriction "Pressure Drop"
      extends Interface.OnePort;

      parameter Real k = 0.1;

    equation
      dp = k*v;

      annotation (Icon(graphics={
            Line(
              points={{-80,60},{-40,60}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{-80,-60},{-40,-60}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{-80,0},{80,0}},
              color={0,255,128},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{40,60},{80,60}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{0,40},{40,60}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{-40,60},{0,40}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{0,-40},{40,-60}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{-40,-60},{0,-40}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{40,-60},{80,-60}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None)}));
    end PipeFriction;

    model PipeMass "Inertia of volume flow"
      extends Interface.OnePort;

      parameter SI.Density rho = 1.29;
      parameter SI.Area A = 1;
      parameter SI.Length l = 1;

    equation
      der(v) *  rho / A * l = dp;

      annotation (Icon(graphics={
            Line(
              points={{-80,60},{80,60}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{-80,-60},{80,-60}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None),
            Rectangle(
              extent={{-80,40},{80,-40}},
              lineThickness=0.5,
              fillColor={0,255,128},
              fillPattern=FillPattern.HorizontalCylinder,
              pattern=LinePattern.None,
              lineColor={255,255,255})}), Diagram(graphics));
    end PipeMass;

    model CompressibleVolume "Pressur Container"

      parameter SI.Volume V = 1.0;
      parameter SI.Compressibility kappa = 1e-5;

      Interface.HydPlug hydPlug
        annotation (Placement(transformation(extent={{-110,-10},{-90,10}})));
    equation
      der(hydPlug.p) * V * kappa = hydPlug.v;

      annotation (Diagram(graphics), Icon(graphics={
            Rectangle(
              extent={{-60,60},{60,-60}},
              lineColor={95,95,95},
              lineThickness=0.5,
              fillColor={255,255,255},
              fillPattern=FillPattern.Solid),
            Rectangle(
              extent={{-80,20},{-54,-20}},
              lineThickness=0.5,
              fillColor={255,255,255},
              fillPattern=FillPattern.Solid,
              pattern=LinePattern.None),
            Line(
              points={{-80,20},{-60,20}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{-80,-20},{-60,-20}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None),
            Rectangle(
              extent={{-40,40},{40,-40}},
              lineThickness=0.5,
              fillColor={0,255,128},
              fillPattern=FillPattern.Sphere,
              lineColor={255,255,255}),
            Line(
              points={{-80,0},{-40,0}},
              thickness=0.5,
              smooth=Smooth.None,
              color={170,255,213})}));
    end CompressibleVolume;

    model SignalPressure "Variable Pressure Source"

      Interface.HydPlug hydPlug
        annotation (Placement(transformation(extent={{90,-10},{110,10}})));
      Modelica.Blocks.Interfaces.RealInput u
        annotation (Placement(transformation(extent={{-130,-20},{-90,20}})));
    equation
      hydPlug.p = u;

      annotation (Diagram(graphics), Icon(graphics={
            Line(
              points={{0,80},{80,20}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{0,-80},{80,-20}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None),
            Polygon(
              points={{60,0},{20,40},{20,-40},{60,0}},
              lineColor={0,255,128},
              lineThickness=0.5,
              fillPattern=FillPattern.VerticalCylinder,
              smooth=Smooth.None,
              fillColor={0,255,128})}));
    end SignalPressure;

  end Components;

  package Examples
    model PressureWave
      Components.SignalPressure signalPressure
        annotation (Placement(transformation(extent={{-70,60},{-50,80}})));
      PipeSection pipeSection
        annotation (Placement(transformation(extent={{-40,60},{-20,80}})));
      PipeSection pipeSection1
        annotation (Placement(transformation(extent={{0,60},{20,80}})));
      PipeSection pipeSection2
        annotation (Placement(transformation(extent={{40,60},{60,80}})));
      PipeSection pipeSection3
        annotation (Placement(transformation(extent={{40,20},{60,40}})));
      PipeSection pipeSection4
        annotation (Placement(transformation(extent={{0,20},{20,40}})));
      Modelica.Blocks.Sources.Sine sine(amplitude=1e4, freqHz=60)
        annotation (Placement(transformation(extent={{-106,60},{-86,80}})));
    equation
      connect(pipeSection.hydPlug_a, signalPressure.hydPlug) annotation (Line(
          points={{-39.8,70},{-50,70}},
          color={0,63,0},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pipeSection.hydPlug_b, pipeSection1.hydPlug_a) annotation (Line(
          points={{-20.2,70},{0.2,70}},
          color={0,63,0},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pipeSection1.hydPlug_b, pipeSection2.hydPlug_a) annotation (Line(
          points={{19.8,70},{40.2,70}},
          color={0,63,0},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pipeSection2.hydPlug_b, pipeSection3.hydPlug_b) annotation (Line(
          points={{59.8,70},{70,70},{70,30},{59.8,30}},
          color={0,63,0},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pipeSection3.hydPlug_a, pipeSection4.hydPlug_b) annotation (Line(
          points={{40.2,30},{19.8,30}},
          color={0,63,0},
          thickness=0.5,
          smooth=Smooth.None));
      connect(sine.y, signalPressure.u) annotation (Line(
          points={{-85,70},{-71,70}},
          color={0,0,127},
          smooth=Smooth.None));
      annotation (Diagram(graphics));
    end PressureWave;

    model PipeSection
      Components.PipeMass pipeMass(A=0.01, l=0.2)
        annotation (Placement(transformation(extent={{-40,-10},{-20,10}})));
      Components.CompressibleVolume compressibleVolume(V=0.002) annotation (
          Placement(transformation(
            extent={{-10,-10},{10,10}},
            rotation=90,
            origin={-10,20})));
      Components.PipeFriction pipeFriction(k=5000)
        annotation (Placement(transformation(extent={{2,-10},{22,10}})));
      Interface.HydPlug hydPlug_a
        annotation (Placement(transformation(extent={{-108,-10},{-88,10}})));
      Interface.HydPlug hydPlug_b
        annotation (Placement(transformation(extent={{88,-10},{108,10}})));
    equation
      connect(pipeMass.hydPlug_b, compressibleVolume.hydPlug) annotation (Line(
          points={{-20,0},{-10,0},{-10,10}},
          color={0,63,0},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pipeFriction.hydPlug_a, pipeMass.hydPlug_b) annotation (Line(
          points={{2,0},{-20,0}},
          color={0,63,0},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pipeMass.hydPlug_a, hydPlug_a) annotation (Line(
          points={{-40,0},{-98,0}},
          color={0,63,0},
          thickness=0.5,
          smooth=Smooth.None));
      connect(pipeFriction.hydPlug_b, hydPlug_b) annotation (Line(
          points={{22,0},{98,0}},
          color={0,63,0},
          thickness=0.5,
          smooth=Smooth.None));
      annotation (Diagram(graphics), Icon(graphics={
            Line(
              points={{-78,60},{82,60}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None),
            Line(
              points={{-80,-60},{80,-60}},
              color={95,95,95},
              thickness=0.5,
              smooth=Smooth.None),
            Rectangle(
              extent={{-80,40},{80,-40}},
              lineThickness=0.5,
              fillColor={255,170,85},
              fillPattern=FillPattern.HorizontalCylinder,
              pattern=LinePattern.None,
              lineColor={255,255,255})}));
    end PipeSection;
  end Examples;
  annotation (uses(Modelica(version="3.2")));
end SimpleHydraulics;
