function D = dh_trafo(alpha, a, d, theta)
% alpha(i-1), a(i-1), d(i), theta(i): DH-Parameter
% D ist homogene Transformationsmatrix von i -> i-1

%D=
D=[cos(theta), -sin(theta), 0, a;...
    sin(theta)*cos(alpha), cos(theta)*cos(alpha), -sin(alpha), -d*sin(alpha);...
    sin(theta)*sin(alpha), cos(theta)*sin(alpha), cos(alpha), d*cos(alpha);...
    0,0,0,1];
end