within ;
model ReelTest

Modelica.Mechanics.Rotational.Sources.ConstantSpeed source(w_fixed=10);
Reel film1;

equation
  connect(source.flange,film1.flangeR);

  annotation (uses(Modelica(version="3.2")));
end ReelTest;
