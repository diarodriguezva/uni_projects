within ;
model PipeFriction
  extends OnePortHydraulics;
  parameter Real Kr;
equation
  P = Kr*v;
  annotation (uses(Modelica(version="3.2")));
end PipeFriction;
